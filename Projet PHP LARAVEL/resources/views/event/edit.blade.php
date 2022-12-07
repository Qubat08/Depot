@extends('template')
@section('title') Modifier un event @endsection
@section('content')
<header id="head" class="secondary"></header>
@if($errors->any())
    <div class="alert alert-danger">
        <ul>
            @foreach ($errors->all() as $error)
                <li>{{ $error }}</li>
            @endforeach
        </ul>
    </div>
@endif
<hr>
<section class="content">
    <div class="container">
<form action="{{url('event', $event->id)}}" method="post">
  @csrf
  @method('PUT')
  <div class="mb-3 row">
    <label for="title" class="col-sm-2 col-form-label">Titre</label>
    <div class="col-sm-10">
      <input type="text" class="form-control @error('title') is-invalid @enderror" name="title" id="title" placeholder="Saisir le Nom" value="{{$event->title}}"/>
    </div>
  </div>
  <hr>
  <div class="mb-3 row">
    <label for="message" class="col-sm-2 col-form-label">Message</label>
    <div class="col-sm-10">
      <textarea class="form-control" id="message" name="message" rows="3" placeholder="Saisir informations">{{$event->message}}</textarea>
    </div>
  </div>
  <hr>
  <div class="mb-3 row">
    <label for="date" class="col-sm-2 col-form-label">Date</label>
    <div class="col-sm-10">
      <input type="datetime-local" class="form-control" name="date" id="date" placeholder="Saisir la date " value="{{date('Y-m-d\TH:i', strtotime($event->date))}}"/>
    </div>
  </div>
  <hr>
  <div class="mb-3 row">
    <label for="lieu" class="col-sm-2 col-form-label">Lieu</label>
    <div class="col-sm-10">
      <input type="text" class="form-control @error('lieu') is-invalid @enderror" name="lieu" id="lieu" placeholder="Saisir le lieu" value="{{$event->lieu}}"/>
    </div>
  </div>
  <hr>
  <div class="mb-3 row">
    <label for="nbparticipant" class="col-sm-2 col-form-label">Nombre de participants</label>
    <div class="col-sm-10">
      <input type="text" class="form-control @error('nbparticipant') is-invalid @enderror" name="nbparticipant" id="nbparticipant" placeholder="Saisir le nombre de place" value="{{$event->nbparticipant}}"/>
    </div>
  </div>
<hr>
  <div class="mb-3 row">
    <label for="prix" class="col-sm-2 col-form-label">Prix</label>
    <div class="col-sm-10">
      <input type="text" class="form-control @error('prix') is-invalid @enderror" name="prix" id="prix" placeholder="Saisir le prix" value="{{$event->prix}}"/>
    </div>
  </div>
<hr>
  <div class="mb-3">
    <div class="offset-sm-2 col-sm-10">
      <button class="btn btn-primary mb-1 mr-1" type="submit">Modifier</button>
      <a href="{{route('event.show',$event->id)}}" class="btn btn-danger mb-1">Annuler</a>
    </div>
  </div>
</form>
</div>
@endsection