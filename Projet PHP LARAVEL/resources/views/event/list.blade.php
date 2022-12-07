@extends('template')
@section('title') Liste des events @endsection
@section('content')
<body>
<header id="head" class="secondary"></header>
  <form id="formLogout" action="{{url('/logout')}}" method="POST">
    @csrf
  </form> 
  <section class="content">
  <div>
    @can('user_access')
      <div class="d-flex justify-content-center">
        <a href="{{route('event.create')}}" class="btn btn-sm btn-primary mb-3 mr-3">Création d'un Event</a>
      </div>
    @endcan



  <ul class="list-group">
  @foreach($eventList as $events)
  <div class="row">
      <li class="list-group-item d-flex justify-content-between align-items-center">
        <div class="col-lg-12">
          <span class="badge rounded-pill bg-primary">
            {{strftime('%d/%m/%Y', strtotime($events->date))}}
          </span>
          <strong>{{$events->title}}</strong>
          <br/>
          <br/>
          Lieu : {{$events->lieu}} <br/>
          Nombre de place:  {{$events->nbparticipant}}<br/>
          Prix : {{$events->prix}}<br/>
        </div>      


        <div class="col">
          <a href="{{route('event.show', $events->id)}}" class="btn btn-sm-primary"><i class="bi bi-search"></i></a>
          @can('user_access')
          <a href="{{route('event.edit',$events->id)}}" class="btn btn-sm-primary"><i class="bi bi-pen"></i></a>
          <form action="{{route('event.destroy', $events->id)}}" method="POST" onsubmit="return confirm('Vous êtes sûr?');">
            @method('DELETE')
            @csrf
            <button type="submit" class="btn btn-sm btn-danger"><i class="bi bi-trash"></i></button>
          </form>
          @endcan
        </div>
      </li>
  </div>
  @endforeach
    </ul>
  @endsection