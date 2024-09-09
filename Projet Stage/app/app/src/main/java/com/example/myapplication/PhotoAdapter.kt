package com.example.myapplication

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.ImageView
import androidx.recyclerview.widget.RecyclerView
import com.bumptech.glide.Glide
import com.example.myapplication.R
import java.io.File

class PhotoAdapter(private var photos: List<File>, private val onPhotoClick: (File) -> Unit, private val onDeleteClick: (File) -> Unit) :
    RecyclerView.Adapter<PhotoAdapter.PhotoViewHolder>() {

    class PhotoViewHolder(view: View) : RecyclerView.ViewHolder(view) {
        val imageView: ImageView = view.findViewById(R.id.imageView)
        val deleteButton: Button = view.findViewById(R.id.delete_button)
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): PhotoViewHolder {
        val view = LayoutInflater.from(parent.context)
            .inflate(R.layout.item_photo, parent, false)
        return PhotoViewHolder(view)
    }

    override fun onBindViewHolder(holder: PhotoViewHolder, position: Int) {
        val photo = photos[position]
        Glide.with(holder.imageView.context)
            .load(photo)
            .into(holder.imageView)
        holder.imageView.setOnClickListener {
            onPhotoClick(photo)
        }
        holder.deleteButton.setOnClickListener {
            onDeleteClick(photo)
        }
    }

    override fun getItemCount() = photos.size

    fun updatePhotos(newPhotos: List<File>) {
        photos = newPhotos
        notifyDataSetChanged()
    }
}
