@extends('contact.layout')
@section('content')

<x-app-layout>
@if ($errors->any())
<div class="alert alert-danger">
    <strong>Whoops!</strong> There were some problems with your input.<br><br>
    <ul>
        @foreach ($errors->all() as $error)
        <li>{{ $error }}</li>
        @endforeach
    </ul>
</div>
@endif
<x-slot name="header">
        <h2 class="font-semibold text-xl text-gray-800 leading-tight">
            Messagerie Contact
        </h2>
    </x-slot>


<div class="container mt-5">
            Nom: {{$contacts->nom}}<br/><br/>
            Email: {{$contacts->email}}<br/><br/>
            Message: <br>
           <?php
                $message = $contacts->message;
                $newtext = wordwrap($message, 50, "<br>", true);
                echo $newtext;
            ?>
            <br><br>

        <div>
            <a href="{{url('adminContact/')}}">Retour à la liste</a>
        </div>
    </div>>
</x-app-layout>
