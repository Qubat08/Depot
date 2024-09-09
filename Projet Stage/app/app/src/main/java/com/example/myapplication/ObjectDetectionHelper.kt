package com.example.myapplication

import android.content.Context
import android.graphics.Bitmap
import org.tensorflow.lite.task.vision.detector.ObjectDetector
import org.tensorflow.lite.support.image.TensorImage
import java.io.File
import java.io.FileOutputStream

class ObjectDetectionHelper(context: Context) {

    private val objectDetector: ObjectDetector

    init {
        val modelName = "model.tflite"
        val modelFile = loadModelFile(context, modelName)
        objectDetector = ObjectDetector.createFromFileAndOptions(
            modelFile,
            ObjectDetector.ObjectDetectorOptions.builder().build()
        )
    }

    fun detectObjects(bitmap: Bitmap): List<DetectionResult> {
        val image = TensorImage.fromBitmap(bitmap)
        val results = objectDetector.detect(image)
        return results.map {
            DetectionResult(
                it.boundingBox.left,
                it.boundingBox.top,
                it.boundingBox.right,
                it.boundingBox.bottom,
                it.categories[0].label
            )
        }
    }

    private fun loadModelFile(context: Context, modelName: String): File {
        val assetManager = context.assets
        val file = File(context.filesDir, modelName)
        assetManager.open(modelName).use { input ->
            FileOutputStream(file).use { output ->
                input.copyTo(output)
            }
        }
        return file
    }

    data class DetectionResult(
        val xmin: Float,
        val ymin: Float,
        val xmax: Float,
        val ymax: Float,
        val label: String
    )
}
