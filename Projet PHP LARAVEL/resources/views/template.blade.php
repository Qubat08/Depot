<!doctype html>
<html lang="fr">
  <head>
  <title>@yield('title')</title>
    <!-- Required meta tags -->
    <meta charset="utf-8">
    <meta name="viewport"    content="width=device-width, initial-scale=1.0">
	<meta name="description" content="SQLan, Trouvez toutes les LAN et faites des parties epic avec vos amies ou des inconnues!">
	<meta name="author"      content="Quentin BATISTE, Simon DELOCHE">
    <title>SQLan - Only for Gamers</title>
    <!-- Bootstrap CSS -->
    <link rel="shortcut icon" href="/images/LogoSQLan.png">
	
	<link rel="stylesheet" media="screen" href="http://fonts.googleapis.com/css?family=Open+Sans:300,400,700">
	<link rel="stylesheet" href="{{url('css/bootstrap.min.css')}}">
	<link rel="stylesheet" href="{{url('css/font-awesome.min.css')}}">
  <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/bootstrap-icons@1.6.1/font/bootstrap-icons.css">
	<link rel="stylesheet" href="{{url('css/bootstrap-theme.css')}}" media="screen" >
	<link rel="stylesheet" href="{{url('css/main.css')}}">
  </head>

  <body class="home">
<form id="formLogout" action="{{url('/logout')}}" method="POST"> @csrf
  </form>

	<div class="navbar navbar-inverse navbar-fixed-top headroom" >
		<div class="container">
			<div class="navbar-header">

				<button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse"><span class="icon-bar"></span> <span class="icon-bar"></span> <span class="icon-bar"></span> </button>
				<a class="navbar-brand" href="{{ url('/')}}"><img class='logo' src="/images/LogoSQLan.png" ?></a>
			</div>
			<div class="navbar-collapse collapse">
				<ul class="nav navbar-nav pull-right">
					<li><a href="{{ url('about')}}">A propos</a></li>
                    <li><a href="{{ url('event')}}">Liste des Lans</a></li>
					<li><a href="{{ url('contact')}}">Nous contacter</a></li>
					@auth
                        <li><a href="{{ url('/dashboard')}}">Dashboard</a></li>
                    @endauth
                    <li>
              <span>
                @auth
                <li><button class="btn" type="submit" form="formLogout"> Déconnexion </button></li>
                @else
                <li><a class="btn" href="{{url('/login')}}">Se connecter</a></li>
                @endauth
                </span>
          </li>
				</ul>
			</div>
		</div>
	</div> 

  @yield('content')


  <footer id="footer" class="top-space">

<div class="footer1">
  <div class="container">
    <div class="row">
      
      <div class="col-md-3 widget">
        <h3 class="widget-title">Contact</h3>
        <div class="widget-body">
          <p>
            <a href="mailto:#">simon.deloche@etudiant.univ-reims.fr</a><br>
            <a href="mailto:#">quentin.batiste@etudiant.univ-reims.fr</a><br>
            <br>
            2 Av. Robert Schuman, 51100 Reims<br>
            03 26 91 30 00
          </p>	
        </div>
      </div>

      <div class="col-md-3 widget">
        <h3 class="widget-title">Nous suivre</h3>
        <div class="widget-body">
          <p class="follow-me-icons">
            <a href=""><i class="bi bi-twitter"></i></a>
            <a href=""><i class="bi bi-instagram"></i></i></a>
            <a href=""><i class="bi bi-github"></i></a>
            <a href=""><i class="bi bi-facebook"></i></i></a>
          </p>	
        </div>
      </div>

      <div class="col-md-6 widget">
        <h3 class="widget-title">Aide</h3>
        <div class="widget-body">
          <p>Besoin d'aide ? Veuillez nous envoyer un message via la page de contact et nous signaler le probleme. Qu'il soit dû au site ou un problème de connexion nous essayerons de vous répondre au plus vite</p>
          <p>Une remarque ? Un conseil ? Vous pouvez nous le faire parvenir via le formulaire de contact dans la zone de texte dédié.</p>
        </div>
      </div>

    </div>
  </div>
</div>

<div class="footer2">
  <div class="container">
    <div class="row">
      
      <div class="col-md-6 widget">
        <div class="widget-body">
          <p class="simplenav">
            <a href="{{ url('/')}}">Accueil</a> | 
            <a href="{{ url('about')}}">A propos</a> | 
            <a href="{{ url('contact')}}">Nous contacter</a> |
            <b><a href="{{ url('/login')}}">Se connecter</a></b>
          </p>
        </div>
      </div>

      <div class="col-md-6 widget">
        <div class="widget-body">
          <p class="text-right">
            Copyright &copy; 2021-2022, SQLAN 
          </p>
        </div>
      </div>

    </div> 
  </div>
</div>

</footer>			

	<script src="http://ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js"></script>
	<script src="http://netdna.bootstrapcdn.com/bootstrap/3.0.0/js/bootstrap.min.js"></script>
	<script src="storage/js/headroom.min.js"></script>
	<script src="storage/js/jQuery.headroom.min.js"></script>
	<script src="storage/js/template.js"></script>

</body>

</html>
  