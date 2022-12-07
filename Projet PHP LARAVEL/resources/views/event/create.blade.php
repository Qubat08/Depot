@extends('template')
@section('title') Création d'un event @endsection
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
<form action="{{url('event')}}" method="post">
  @csrf
  <div class="mb-3 row">
    <label for="title" class="col-sm-2 col-form-label">Titre</label>
    <div class="col-sm-10">
      <input type="text" class="form-control @error('title') is-invalid @enderror" name="title" id="title" placeholder="Saisir nom de l'event" value="{{old('title')}}"/>
    </div>
  </div>
  <hr>
  <div class="mb-3 row">
    <label for="message" class="col-sm-2 col-form-label">Message</label>
    <div class="col-sm-10">
      <textarea class="form-control @error('message') is-invalid @enderror" id="message" name="message" rows="3" placeholder="Saisir informations">{{old('message')}}</textarea>
    </div>
  </div>
  <hr>
  <div class="mb-3 row">
    <label for="date" class="col-sm-2 col-form-label">Date</label>
    <div class="col-sm-10">
      <input type="datetime-local" class="form-control @error('date') is-invalid @enderror" name="date" id="date" placeholder="Saisir la date" value="{{old('date')}}"/>
    </div>
  </div>
  <hr>
  <div class="mb-3 row">
    <label for="lieu" class="col-sm-2 col-form-label">Lieu</label>
    <div class="col-sm-10">
      <input type="text" class="form-control @error('date') is-invalid @enderror" name="lieu" id="lieu" placeholder="Saisir le lieu" value="{{old('lieu')}}"/>
    </div>
  </div>
  <hr>
  <div class="mb-3 row">
    <label for="nbparticipant" class="col-sm-2 col-form-label">Nombre de participants</label>
    <div class="col-sm-10">
      <input type="text" class="form-control @error('date') is-invalid @enderror" name="nbparticipant" id="nbparticipant" placeholder="Saisir le nombre de place" value="{{old('nbparticipant')}}"/>
    </div>
  </div>
  <hr>
  <div class="mb-3 row">
    <label for="prix" class="col-sm-2 col-form-label">Prix</label>
    <div class="col-sm-10">
      <input type="text" class="form-control @error('date') is-invalid @enderror" name="prix" id="prix" placeholder="Saisir le prix" value="{{old('prix')}}"/>
    </div>
  </div>

<hr>
  <div class="mb-3">
    <div class="offset-sm-2 col-sm-10">
    <button class="btn btn-primary mb-1 mr-1" type="submit">Ajouter</button>
    <a href="{{url('event')}}" class="btn btn-danger mb-1">Annuler</a>
  </div>

</form>
</div>
</div>
@endsection
