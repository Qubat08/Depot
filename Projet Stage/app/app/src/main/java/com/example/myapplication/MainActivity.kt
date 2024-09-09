package com.example.myapplication

import android.Manifest
import android.content.pm.PackageManager
import android.graphics.*
import android.location.Location
import android.net.Uri
import android.os.Bundle
import android.util.Log
import android.util.Size
import android.view.Menu
import android.view.MenuItem
import android.view.SurfaceView
import android.view.View
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import androidx.appcompat.app.AlertDialog
import androidx.appcompat.app.AppCompatActivity
import androidx.camera.core.*
import androidx.camera.lifecycle.ProcessCameraProvider
import androidx.camera.view.PreviewView
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.google.android.gms.location.FusedLocationProviderClient
import com.google.android.gms.location.LocationServices
import org.tensorflow.lite.support.image.TensorImage
import toBitmap
import java.io.File
import java.io.IOException
import java.text.SimpleDateFormat
import java.util.*
import java.util.concurrent.ExecutorService
import java.util.concurrent.Executors

class MainActivity : AppCompatActivity() {
    private lateinit var viewFinder: PreviewView
    private lateinit var surfaceView: SurfaceView
    private var imageCapture: ImageCapture? = null
    private lateinit var outputDirectory: File
    private lateinit var cameraExecutor: ExecutorService
    private lateinit var recyclerView: RecyclerView
    private lateinit var photoAdapter: PhotoAdapter
    private lateinit var classNameInput: EditText
    private lateinit var fusedLocationClient: FusedLocationProviderClient
    private var currentLocation: Location? = null
    private lateinit var objectDetectionHelper: ObjectDetectionHelper

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        viewFinder = findViewById(R.id.previewView)
        surfaceView = findViewById(R.id.surfaceView)
        classNameInput = findViewById(R.id.class_name_input)
        fusedLocationClient = LocationServices.getFusedLocationProviderClient(this)
        objectDetectionHelper = ObjectDetectionHelper(this)

        recyclerView = findViewById(R.id.recyclerView)
        recyclerView.layoutManager = LinearLayoutManager(this, LinearLayoutManager.HORIZONTAL, false)
        photoAdapter = PhotoAdapter(getAllPhotos(), { photo ->
            val metadata = getMetadata(photo)
            showMetadataDialog(metadata)
        }, { photo ->
            deletePhoto(photo)
        })
        recyclerView.adapter = photoAdapter

        if (allPermissionsGranted()) {
            startCamera()
        } else {
            ActivityCompat.requestPermissions(
                this, REQUIRED_PERMISSIONS, REQUEST_CODE_PERMISSIONS)
        }

        findViewById<Button>(R.id.capture_button).setOnClickListener {
            getLocationAndTakePhoto()
        }

        outputDirectory = getOutputDirectory()
        cameraExecutor = Executors.newSingleThreadExecutor()
    }

    private fun getLocationAndTakePhoto() {
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) == PackageManager.PERMISSION_GRANTED) {
            fusedLocationClient.lastLocation
                .addOnSuccessListener { location: Location? ->
                    location?.let {
                        currentLocation = it
                        takePhoto()
                    } ?: run {
                        Toast.makeText(this, "Unable to get current location", Toast.LENGTH_SHORT).show()
                        takePhoto()
                    }
                }
        } else {
            ActivityCompat.requestPermissions(this, arrayOf(Manifest.permission.ACCESS_FINE_LOCATION), REQUEST_CODE_PERMISSIONS)
        }
    }

    private fun takePhoto() {
        val imageCapture = imageCapture ?: return

        val photoFile = File(
            outputDirectory,
            SimpleDateFormat(FILENAME_FORMAT, Locale.US
            ).format(System.currentTimeMillis()) + ".jpg")

        val outputOptions = ImageCapture.OutputFileOptions.Builder(photoFile).build()

        imageCapture.takePicture(
            outputOptions, ContextCompat.getMainExecutor(this), object : ImageCapture.OnImageSavedCallback {
                override fun onError(exc: ImageCaptureException) {
                    Log.e(TAG, "Photo capture failed: ${exc.message}", exc)
                }

                override fun onImageSaved(output: ImageCapture.OutputFileResults) {
                    val savedUri = Uri.fromFile(photoFile)
                    Log.d(TAG, "Photo capture succeeded: $savedUri")

                    val className = classNameInput.text.toString()
                    addMetadata(photoFile, className, currentLocation)
                    photoAdapter.updatePhotos(getAllPhotos())
                }
            })
    }

    private fun startCamera() {
        val cameraProviderFuture = ProcessCameraProvider.getInstance(this)

        cameraProviderFuture.addListener(Runnable {
            val cameraProvider: ProcessCameraProvider = cameraProviderFuture.get()

            val preview = Preview.Builder()
                .build()
                .also {
                    it.setSurfaceProvider(viewFinder.surfaceProvider)
                }

            imageCapture = ImageCapture.Builder().build()

            val cameraSelector = CameraSelector.DEFAULT_BACK_CAMERA

            try {
                cameraProvider.unbindAll()
                cameraProvider.bindToLifecycle(
                    this, cameraSelector, preview, imageCapture)
                bindAnalysisUseCase(cameraProvider, cameraSelector)
            } catch(exc: Exception) {
                Log.e(TAG, "Use case binding failed", exc)
            }

        }, ContextCompat.getMainExecutor(this))
    }

    private fun bindAnalysisUseCase(cameraProvider: ProcessCameraProvider, cameraSelector: CameraSelector) {
        val analysisUseCase = ImageAnalysis.Builder()
            .setTargetResolution(Size(1280, 720))
            .setBackpressureStrategy(ImageAnalysis.STRATEGY_KEEP_ONLY_LATEST)
            .build()

        analysisUseCase.setAnalyzer(cameraExecutor, { imageProxy ->
            val rotationDegrees = imageProxy.imageInfo.rotationDegrees
            val bitmap = imageProxy.toBitmap()
            bitmap?.let {
                val image = TensorImage.fromBitmap(bitmap)
                val results = objectDetectionHelper.detectObjects(image.bitmap)

                runOnUiThread {
                    drawDetections(results)
                }
            }

            imageProxy.close()
        })

        cameraProvider.bindToLifecycle(this, cameraSelector, analysisUseCase)
    }

    private fun drawDetections(detections: List<ObjectDetectionHelper.DetectionResult>) {
        val canvas: Canvas = surfaceView.holder.lockCanvas() ?: return
        canvas.drawColor(Color.TRANSPARENT, PorterDuff.Mode.CLEAR)

        val paint = Paint()
        paint.style = Paint.Style.STROKE
        paint.color = Color.RED
        paint.strokeWidth = 8f

        for (detection in detections) {
            val left = detection.xmin * surfaceView.width
            val top = detection.ymin * surfaceView.height
            val right = detection.xmax * surfaceView.width
            val bottom = detection.ymax * surfaceView.height
            canvas.drawRect(left, top, right, bottom, paint)
        }

        surfaceView.holder.unlockCanvasAndPost(canvas)
    }

    private fun allPermissionsGranted() = REQUIRED_PERMISSIONS.all {
        ContextCompat.checkSelfPermission(
            baseContext, it) == PackageManager.PERMISSION_GRANTED
    }

    override fun onRequestPermissionsResult(
        requestCode: Int, permissions: Array<String>, grantResults: IntArray) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        if (requestCode == REQUEST_CODE_PERMISSIONS) {
            if (allPermissionsGranted()) {
                startCamera()
            } else {
                Toast.makeText(this,
                    "Permissions not granted by the user.",
                    Toast.LENGTH_SHORT).show()
                finish()
            }
        }
    }

    override fun onDestroy() {
        super.onDestroy()
        cameraExecutor.shutdown()
    }

    private fun getOutputDirectory(): File {
        val mediaDir = externalMediaDirs.firstOrNull()?.let {
            File(it, resources.getString(R.string.app_name)).apply { mkdirs() }
        }
        return if (mediaDir != null && mediaDir.exists())
            mediaDir else filesDir
    }

    private fun getAllPhotos(): List<File> {
        val dir = getOutputDirectory()
        return dir.listFiles { file -> file.extension == "jpg" }?.toList() ?: emptyList()
    }

    private fun deletePhoto(photo: File) {
        if (photo.exists()) {
            photo.delete()
            Toast.makeText(this, "Photo deleted", Toast.LENGTH_SHORT).show()
            photoAdapter.updatePhotos(getAllPhotos())
        } else {
            Toast.makeText(this, "File does not exist", Toast.LENGTH_SHORT).show()
        }
    }

    private fun getMetadata(file: File): String {
        return try {
            val exif = androidx.exifinterface.media.ExifInterface(file)
            val userComment = exif.getAttribute(androidx.exifinterface.media.ExifInterface.TAG_USER_COMMENT) ?: "No user comment"
            val dateTime = exif.getAttribute(androidx.exifinterface.media.ExifInterface.TAG_DATETIME) ?: "No date/time"

            val latLong = FloatArray(2)
            val hasLatLong = exif.getLatLong(latLong)
            val latitude = if (hasLatLong) latLong[0].toString() else "No latitude"
            val longitude = if (hasLatLong) latLong[1].toString() else "No longitude"

            "User Comment: $userComment\nDate/Time: $dateTime\nLatitude: $latitude\nLongitude: $longitude"
        } catch (e: IOException) {
            e.printStackTrace()
            "Error reading metadata"
        }
    }

    private fun addMetadata(photoFile: File, className: String, location: Location?) {
        try {
            val exif = androidx.exifinterface.media.ExifInterface(photoFile)
            exif.setAttribute(androidx.exifinterface.media.ExifInterface.TAG_USER_COMMENT, className)
            location?.let {
                exif.setGpsInfo(it)
            }
            exif.saveAttributes()
        } catch (e: IOException) {
            e.printStackTrace()
        }
    }

    private fun showMetadataDialog(metadata: String) {
        val builder = AlertDialog.Builder(this)
        builder.setTitle("Photo Metadata")
        builder.setMessage(metadata)
        builder.setPositiveButton("OK") { dialog, _ -> dialog.dismiss() }
        val dialog = builder.create()
        dialog.show()
    }

    override fun onCreateOptionsMenu(menu: Menu?): Boolean {
        menuInflater.inflate(R.menu.menu_main, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        return when (item.itemId) {
            R.id.action_view_photos -> {
                toggleRecyclerView()
                true
            }
            else -> super.onOptionsItemSelected(item)
        }
    }

    private fun toggleRecyclerView() {
        if (recyclerView.visibility == View.VISIBLE) {
            recyclerView.visibility = View.GONE
        } else {
            recyclerView.visibility = View.VISIBLE
            photoAdapter.updatePhotos(getAllPhotos())
        }
    }

    companion object {
        private const val TAG = "CameraXApp"
        private const val FILENAME_FORMAT = "yyyy-MM-dd-HH-mm-ss-SSS"
        private const val REQUEST_CODE_PERMISSIONS = 10
        private val REQUIRED_PERMISSIONS = arrayOf(Manifest.permission.CAMERA, Manifest.permission.ACCESS_FINE_LOCATION)
    }
}
