@extends('template')
@section('title') Affichage d'un event @endsection
@section('content')
<header id="head" class="secondary"></header>
<hr>
<section class="content">
    <div class="container">
        <br><br><br>
            <i>{{strftime('%d/%m/%Y', strtotime($event->date))}}</i>
            <strong>{{$event->title}}</strong><br/><br/>
            {{$event->message}}<br/><br/>
            Lieu: {{$event->lieu}} <br/><br/>
            Nombre de place: {{$event->nbparticipant}}<br/><br/>
            Prix: {{$event->prix}}<br/><br/>
            <hr>

@auth
    <a href="" class="btn btn-primary mb-1">S'inscrire</a>
@endauth

<a href="{{url('event/')}}">Retour à la liste</a>
</div>
</section>
@endsection
