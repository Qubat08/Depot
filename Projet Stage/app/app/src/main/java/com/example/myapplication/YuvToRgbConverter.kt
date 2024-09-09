package com.example.myapplication

import android.content.Context
import android.graphics.Bitmap
import android.graphics.ImageFormat
import android.graphics.YuvImage
import android.media.Image
import java.io.ByteArrayOutputStream
import java.nio.ByteBuffer


class YuvToRgbConverter {
    fun yuvToRgb(context: Context, image: Image): Bitmap {
        val nv21 = yuv420888ToNv21(image)
        val yuvImage = YuvImage(nv21, ImageFormat.NV21, image.width, image.height, null)
        val out = ByteArrayOutputStream()
        yuvImage.compressToJpeg(android.graphics.Rect(0, 0, image.width, image.height), 100, out)
        val imageBytes = out.toByteArray()
        return android.graphics.BitmapFactory.decodeByteArray(imageBytes, 0, imageBytes.size)
    }

    private fun yuv420888ToNv21(image: Image): ByteArray {
        val width = image.width
        val height = image.height
        val ySize = width * height
        val uvSize = width * height / 4

        val nv21 = ByteArray(ySize + uvSize * 2)

        val yBuffer = image.planes[0].buffer // Y
        val uBuffer = image.planes[1].buffer // U
        val vBuffer = image.planes[2].buffer // V

        var yPos = 0
        var uvPos = ySize

        for (row in 0 until height) {
            yBuffer.get(nv21, yPos, width)
            yPos += width
        }

        val uvWidth = width / 2
        val uvHeight = height / 2

        for (row in 0 until uvHeight) {
            for (col in 0 until uvWidth) {
                nv21[uvPos++] = vBuffer.get()
                nv21[uvPos++] = uBuffer.get()
            }
        }

        return nv21
    }
}
