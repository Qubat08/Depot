<?php

use Illuminate\Support\Facades\Route;
use App\Http\Controllers\EventController;
use App\Http\Controllers\UserController;
use App\Http\Controllers\ContactController;
use \App\Http\Controllers\AdminContactController;
/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/


Route::get('/', function () {
    return view('index');
});


Route::resource('user', UserController::class);
Route::resource('contact', ContactController::class);
Route::resource('adminContact', AdminContactController::class);
Route::middleware(['auth:sanctum', 'verified'])->get('/dashboard', function () {
    return view('dashboard');
})->name('dashboard');


Route::resource('event', EventController::class);

Route::get('contact',function(){
    return view('contact');
});
Route::get('about',function(){
    return view('about');
});
