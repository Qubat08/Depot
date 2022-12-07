@extends('template')
@section('title') A propos @endsection
@section('content')
<body>
	<header id="head" class="secondary"></header>


	<div class="container">

		<ol class="breadcrumb">
			<li><a href="{{ url('/')}}">Menu</a></li>
			<li class="active">A propos</li>
		</ol>

		<div class="row">
			

			<article class="col-sm-8 maincontent">
				<header class="page-header">
					<h1 class="page-title">A propos de nous</h1>
				</header>
				<h3>Qui sommes-nous ?</h3>
				<p>SQLAN est une société crée en 2010, nous organisons des rencontres entre joueurs sur de nombreux jeux vidéo tel que League of Leagends, Valorant, Fortnite, CS:GO, Rocket League et plein d'autre encore</p>
				<h3>Notre équipe:</h3>
				<p>Notre société comporte une dizaine de membres à l'heure actuel. Mais avec l'explosion des jeux vidéo notre equipe s'agrandit petit à petit. Alors que les rassemblements sont difficiles, nous préparons le futur après la pandémie du Covid-19. Nous avons accueilli un nouveau membre dans notre équipe. Bernard Pivot nous a rejoint en Septembre 2021 pour nous aider.<br><br>Etant spécialisé dans la communication, il aura pour but de vous partager les news sur les futur LAN. Grâce à la création de nos réseaux socieau nous vous partagerons les meilleurs moments de nos événements</p>
				<h3>Où organisons-nous des évènements  ?</h3>
				<p>Nous agissons dans toute la France: Paris, Lyon, Marseille, Reims, Bordeaux, Lille, Nante etc... Envie qu'une LAN se déroule près de chez vous ? Faites-nous des propositions dans l'espace contact.</p>
			</article>

			<aside class="col-sm-4 sidebar sidebar-right">

				<div class="widget">
					<h4>Questions fréquentes:	</h4>
					<ul class="list-unstyled list-spaces">
						<span class="small text-muted">Qui somme-nous ?</span><br>
						<span class="small text-muted">Notre équipe</span><br>
						<span class="small text-muted">Où sera le prochain évenement</span><br>
					</ul>
				</div>

			</aside>


		</div>
	</div>
</body>
