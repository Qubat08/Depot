<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;
use Illuminate\Database\Eloquent\SoftDeletes;

class Event extends Model
{
    use HasFactory;
    use SoftDeletes;

    protected $dates = [
            'created_at',
            'deleted_at',
            'started_at',
            'update_at'
        ];

    protected $fillable = [
            'title',
            'message',
            'date',
            'lieu',
            'nbparticipant',
            'prix'
        ];
        
    // public function user() {
    //     return $this->belongsTo(User::class);
    // }
}