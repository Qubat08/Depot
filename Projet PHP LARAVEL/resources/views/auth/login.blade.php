@section('title') Connexion @endsection
@extends('template')

@section('content')
<header id="head" class="secondary"></header>
<div class="container">
				<header class="page-header">
					<h1 class="page-title">Se connecter</h1>
				</header>
				
				<div class="col-md-6 col-md-offset-3 col-sm-8 col-sm-offset-2">
					<div class="panel panel-default">
						<div class="panel-body">
							<h3 class="thin text-center">Se connecter à votre compte</h3>
							<p class="text-center text-muted">Vous n'avez pas de compte ? Cliquez sur  <a href="{{ url('register')}}">Créer un compte</a> </p>
							<hr>
							
							<form action = "{{route('login')}}" method="post">
                                @csrf
								<div class="top-margin">
									<label for="email">Email <span class="text-danger">*</span></label>
									<input id = "email" name="email" class="form-control @error('email') is-invalid @enderror" type="email" value= "{{old('email')}}" required autocomplete="email" autofocus>
									@error('email')
									<div id="validationServerUsernameFeedback" class="invalid-feedback">
										{{ $message }}
									</div>
									@enderror
								</div>
								<div class="top-margin">
									<label for= "password">Mot de passe <span class="text-danger">*</span></label>
									<input id= "password" name = "password" type="password" class="form-control" required autocomplete="current-password">
									@error('password')
									<div id="validationServerUsernameFeedback" class="invalid-feedback">
									  {{ $message }}
									</div>
									@enderror
								</div>
								
								<hr>

								<div class="row">
									<div class="col-lg-7">
										<b><a href="">Mot de passe oublié ?</a></b>
									</div>
									<div class="col-lg-4 text-center">
										<button class="btn btn-primary" type="submit">Se connecter</button>
									</div>
								</div>
							</form>
						</div>
					</div>
</div>

</div>