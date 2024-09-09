package com.example.myapplication

import android.content.Context
import android.graphics.Canvas
import android.graphics.Color
import android.graphics.Paint
import android.util.AttributeSet
import android.view.View
import org.tensorflow.lite.task.vision.detector.Detection

class OverlayView(context: Context, attrs: AttributeSet) : View(context, attrs) {

    private val paint: Paint = Paint()
    private var results: List<Detection> = listOf()

    init {
        paint.style = Paint.Style.STROKE
        paint.strokeWidth = 8.0f
        paint.color = Color.RED
    }

    fun setResults(results: List<Detection>) {
        this.results = results
    }

    override fun onDraw(canvas: Canvas) {
        super.onDraw(canvas)
        for (result in results) {
            val boundingBox = result.boundingBox
            canvas.drawRect(boundingBox.left, boundingBox.top, boundingBox.right, boundingBox.bottom, paint)
        }
    }
}
