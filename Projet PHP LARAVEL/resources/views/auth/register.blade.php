@extends('template')

@section('title') Enregistrement @endsection

@section('content')

<header id="head" class="secondary"></header>
<div class="container">
				<header class="page-header">
					<h1 class="page-title">Se connecter</h1>
  </header>


<div class="col-md-6 col-md-offset-3 col-sm-8 col-sm-offset-2">
					<div class="panel panel-default">
						<div class="panel-body">
            <h3 class="thin text-center">Creer votre compte</h3>
            <p class="text-center text-muted">Vous avez déjà un compte ? <a href="{{ url('login')}}">Se connecter</a> </p>
            <hr>
      <form action="{{ route('register') }}" method="post">
        @csrf
        <div class="top-margin">

      <label for="name">Nom :</label>
      <input id="name" name="name" type="text" class="form-control @error('name') is-invalid @enderror" value="{{ old('name') }}" required autocomplete="name" autofocus />
      @error('name')
      <div id="validationServerUsernameFeedback" class="invalid-feedback">
        {{ $message }}
      </div>
      @enderror
    </div>

    <div class="top-margin">
      <label for="email">Login :</label>
      <input id="email" name="email" type="email" class="form-control @error('email') is-invalid @enderror" value="{{ old('email') }}" required autocomplete="email" autofocus />
      @error('email')
      <div id="validationServerUsernameFeedback" class="invalid-feedback">
        {{ $message }}
      </div>
      @enderror
    </div>


    <div class="row top-margin">
    <div class="col-sm-6">
      <label for="password">Mot de passe :</label>
      <input id="password" name="password" type="password" class="form-control @error('password') is-invalid @enderror" required autocomplete="current-password" />
      @error('password')
      <div id="validationServerUsernameFeedback" class="invalid-feedback">
        {{ $message }}
      </div>
      @enderror
    </div>

    <div class="col-sm-6">
      <label for="password-confirm">Confirmation :</label>
      <input id="password-confirm" name="password_confirmation" type="password" class="form-control" required autocomplete="new-password" />
      @error('password')
      <div id="validationServerUsernameFeedback" class="invalid-feedback">
        {{ $message }}
      </div>
      @enderror
    </div>
    </div>
    <hr>

        <div class="row">
                                <div class="col-lg-7">
                                <div class="col-lg-9 text-center">
                                    <button class="btn btn-action" type="submit">Créer</button>
                                </div>
                                </div>
                                <div class="col-lg-4 text-center">
                                  <a href="{{ url('/') }}" class="btn btn-danger">Retour</a>
                                </div>
                            </div>
                        </form>
                    </div>
                </div>

            </div>
            
        </article>

    </div>
</div>
    
  </form>
</div>
@endsection