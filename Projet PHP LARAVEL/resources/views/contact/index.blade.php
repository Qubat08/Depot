@extends('contact.layout')
@section('content')
<x-app-layout>
    <x-slot name="header">
        <h2 class="font-semibold text-xl text-gray-800 leading-tight">
            Liste messagerie contact
        </h2>
    </x-slot>

 

@if ($message = Session::get('success'))
        <div class="alert alert-success">
            <p>{{ $message }}</p>
        </div>
    @endif

    

<div class="container">
    
    <table class="table table-striped" id="myTable">
        <thead>
            <tr class="table-flex justify-content-center">
                <th scope="cpm" >ID</th>
                <th scope="col">Nom</th>
                <th scope="col">Email</th>
                <th scope="col">Message</th>


            </tr>
        </thead>
        @foreach ($contacts as $contact)
        

            <tr>
                <td>{{$contact->id}}</td>
                <td>{{$contact->nom}}</td>
                <td>{{$contact->email}}</td>
                <td>
                    @if(strlen($contact->message) > 50)
                    {{substr($contact->message, 0, 50)}}...
                    @else
                    {{$contact->message}}
                    @endif
                </td>
                <td>
                   <a class="btn btn-primary" href="{{route('adminContact.show', $contact->id)}}"><i class="fa fa-eye" aria-hidden="true"></i></a>
                   <!-- <a class="btn btn-danger" href="{{route('adminContact.destroy', $contact->id)}}"><i class="bi bi-trash2" aria-hidden="true"></i></a> -->
                   <form class="inline-block" action="{{ route('adminContact.destroy', $contact->id) }}" method="POST" onsubmit="return confirm('Vous êtes sûr?');">
                        @csrf
                        <input type="hidden" name="_method" value="DELETE">
                        <button type="submit" class="btn btn-danger"><i class="bi bi-trash"></i></input>
                    </form>

                </td>
            </tr>
        
        @endforeach
    </table>
      </span>
</div>
</x-app-layout>