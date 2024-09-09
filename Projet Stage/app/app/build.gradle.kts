import org.jetbrains.kotlin.storage.CacheResetOnProcessCanceled.enabled

plugins {
    alias(libs.plugins.android.application)
    alias(libs.plugins.jetbrains.kotlin.android)
    id("kotlin-kapt")
}

android {
    namespace = "com.example.myapplication"
    compileSdk = 34

    defaultConfig {
        applicationId = "com.example.myapplication"
        minSdk = 24
        targetSdk = 34
        versionCode = 1
        versionName = "1.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(getDefaultProguardFile("proguard-android-optimize.txt"), "proguard-rules.pro")
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_1_8
        targetCompatibility = JavaVersion.VERSION_1_8
    }
    kotlinOptions {
        jvmTarget = "1.8"
    }

    // add assets in project
    sourceSets {
        getByName("main") {
            assets {
                srcDirs("src/main/assets")
            }
        }
    }


}

dependencies {
    implementation(libs.androidx.core.ktx)
    implementation(libs.androidx.appcompat)
    implementation(libs.material)

    // TensorFlow Lite
    implementation("org.tensorflow:tensorflow-lite:2.8.0")
    implementation("org.tensorflow:tensorflow-lite-support:0.3.1")

    // CameraX
    implementation("androidx.camera:camera-core:1.0.0")
    implementation("androidx.camera:camera-camera2:1.0.0")
    implementation("androidx.camera:camera-lifecycle:1.0.0")
    implementation("androidx.camera:camera-view:1.0.0-alpha22")

    // ExifInterface
    implementation("androidx.exifinterface:exifinterface:1.3.2")

    // Guava
    implementation("com.google.guava:guava:31.0.1-android")

    // Glide
    implementation("com.github.bumptech.glide:glide:4.12.0")
    kapt("com.github.bumptech.glide:compiler:4.12.0")

    // RecyclerView
    implementation("androidx.recyclerview:recyclerview:1.2.1")
    implementation ("com.google.android.gms:play-services-location:21.0.1")

    implementation ("org.tensorflow:tensorflow-lite:2.8.0")
    implementation ("org.tensorflow:tensorflow-lite-support:0.3.1")
    implementation ("org.tensorflow:tensorflow-lite-metadata:0.1.0")
    implementation ("org.tensorflow:tensorflow-lite-task-vision:0.2.0")

    testImplementation(libs.junit)
    androidTestImplementation(libs.androidx.junit)
    androidTestImplementation(libs.androidx.espresso.core)

}
