@extends('template')
@section('Contact') Contact @endsection

@section('content')

<header id="head" class="secondary"></header>
<div class="container">

<ol class="breadcrumb">
    <li><a href="{{ url('/')}}">Menu</a></li>
    <li class="active">Nous contacter</li>
</ol>

@if($errors->any())
    <div class="alert alert-danger">
        <ul>
            @foreach ($errors->all() as $error)
                <li>{{ $error }}</li>
            @endforeach
        </ul>
    </div>
@endif
<div class="row">
    <article class="col-sm-9 maincontent">
        <header class="page-header">
            <h1 class="page-title">Nous contacter</h1>
        </header>
        
        <p>
            Vous souhaitez nous contacter ? Remplissez le formulaire ci-dessous avec quelques informations et votre sujet. Nous vous répondrons dès que possible.
        </p>
        <br>


<form action="{{route('contact.store')}}" method="POST">
@csrf
<div class="row">
<div class="col-sm-4">
    <!-- <label for="title" class="col-sm-2 col-form-label">Nom</label> -->
      <input type="text" class="form-control @error('nom') is-invalid @enderror" name="nom" id="nom" placeholder="Saisir votre nom" value="{{old('nom')}}"/>
  </div>
  <div class="col-sm-4">
    <!-- <label for="email" class="col-sm-2 col-form-label">Email</label> -->
    
      <input type="text" class="form-control @error('email') is-invalid @enderror" name="email" id="email" placeholder="Saisir votre email" value="{{old('email')}}"/>
</div>
  </div>
  <br>
<div class="row">
  <div class="col-sm-12">
      <!-- <label for="message" class="col-sm-2 col-form-label">Message</label> -->
        <textarea class="form-control @error('message') is-invalid @enderror" id="message" name="message" rows="9" placeholder="Saisir votre message" maxlength="255">{{old('message')}}</textarea>
      </div>
    </div>
<br>
<div class = "row">
  <div class="col-sm-6">
      <button type="submbit" class="btn btn-primary mb-1">Envoyer</button>
      <a href="{{url('/')}}" class="btn btn-danger mb-1">Retour</a>
  </div>
  </div>
</form>
</article> 
<aside class="col-sm-3 sidebar sidebar-right">

<div class="widget">
    <h4>Adresse</h4>
    <address>
        2 Av. Robert Schuman, 51100 Reims
    </address>
    <h4>Nous contacter:</h4>
    <address>
        simon.deloche@etudiant.univ-reims.fr<br>
        quentin.batiste@etudiant.univ-reims.fr
    </address>
</div>
</aside>


</div>
</div>

<!-- <section class="container-full top-space">
<div id="map"></div>
</section> -->

<script src="https://maps.googleapis.com/maps/api/js?key=&amp;sensor=false&amp;extension=.js"></script> 
<script src="storage/js/google-map.js"></script>