@extends('template')
@section('title') Acceuil @endsection
@section('content')
<header id="head">
		<div class="container">
			<div class="row">
				<h1 class="lead">SQLAN - Only for Gamers</h1>
				<p class="tagline">Trouver toutes les LAN et participe à des confrontations épic ! </p>
				<p><a href="{{ url('event/')}}" class="btn btn-default btn-lg" role="button">Liste des events</a></p>
			</div>
		</div>
	</header>

	<div class="container text-center">
		<br> <br>
		<h2 class="thin">Le meilleur endroit pour prouver que tu sois le meilleur</h2>
		<p class="text-muted">
			Affronte des joueurs de ta région et même du monde entier pour montrer de quoi tu es capable 
		</p>
	</div>

	<div class="jumbotron top-space">
		<div class="container">
			
			<h3 class="text-center thin">Pourquoi participer à nos LAN?</h3>
			
			<div class="row">
				<div class="col-md-3 col-sm-6 highlight">
					<div class="h-caption"><h4><i class="bi bi-people-fill"></i>Une grande communauté</h4></div>
					<div class="h-body text-center">
						<p>Avec plus de 1000 joueurs à l'année, nos LAN permettent une grande rivalité entre les joueurs venant de tous les horizons. Tiens toi prêt à les défier</p>
					</div>
				</div>
				<div class="col-md-3 col-sm-6 highlight">
					<div class="h-caption"><h4><i class="bi bi-controller"></i>Une multitude de jeux</h4></div>
					<div class="h-body text-center">
						<p>Nous proposons des LAN sur un panel de jeux immense. Trouve celui qui te corresponds et entre dans la bataille pour te mesurer aux meilleurs joueurs</p>
					</div>
				</div>
				<div class="col-md-3 col-sm-6 highlight">
					<div class="h-caption"><h4><i class="bi bi-cash-coin"></i>Des cash prize</h4></div>
					<div class="h-body text-center">
						<p>Deviens le meilleur des joueurs et tante de gagner du cash prize. Avec plus de mille euros de cash prize par LAN construit ta fortune dans le jeu vidéo </p>
					</div>
				</div>
				<div class="col-md-3 col-sm-6 highlight">
					<div class="h-caption"><h4><i class="bi bi-wifi"></i>Du haut débit</h4></div>
					<div class="h-body text-center">
						<p>Profite dans nos LAN en ultra haut débit pour un meilleur confort de jeux et affronter tes adversaire comme tu l'as jamais fait avant</p>
					</div>
				</div>
			</div>
		
		</div>
	</div>

	<div class="container">

		<h2 class="text-center top-space">SQLAN Event</h2>
		<br>

		<div class="row">
			<div class="col-sm-6">
				<h3>Le plus gros évenement de l'année</h3>
				<p>Comme chaque année depuis 2016 SQLan vous propose le "SQLAN Event". Une date incontournable pour tout bon joueur  qui se respecte et qui rassemble plus de 100 joueurs chaque année.</p>
			</div>
			<div class="col-sm-6">
				<h3>SQLAN Event 2019</h3>
				<p>
					<img class='ilan' src="<?php echo asset('/images/lan1.jpg'); ?>">
				</p>
			</div>
		</div>

		<div class="row">
			<div class="col-sm-6">
				<h3></h3>
				<p>
				<img class='ilan' src="<?php echo asset('/images/lan2.jpg'); ?>">
				</p>
			</div>
			<div class="col-sm-6">
				<h3>A quand les inscriptions?</h3>
				<p>Intéréssé par la prochaine édition du SQLAN Event ? Elle sera bientôt disponible dans l'onglet 'liste des lans'. Les inscriptions seront disponibles courant mars. Un plan sanitaire sera mis en place dans le respect des gestes barrières. <p>
			</div>
		</div>



</div>	
	<section id="social">
		<div class="container">
			<div class="wrapper clearfix">
				
				<div class="addthis_toolbox addthis_default_style">
				<a class="addthis_button_facebook_like" fb:like:layout="button_count"></a>
				<a class="addthis_button_tweet"></a>
				<a class="addthis_button_linkedin_counter"></a>
				<a class="addthis_button_google_plusone" g:plusone:size="medium"></a>
				</div>
				
			</div>
		</div>
	</section>