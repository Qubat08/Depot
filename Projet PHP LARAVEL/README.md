# Projet version PHP LARAVEL

## Prérequis: 
- avoir un serveur PHP (8.0)
- git clone le répertoire

## Installation:

- composer install
- cp .env.example .env (vérifier que vous avez une base de données du même nom, login et mot de passe)
- php artisan key:generate
- php artisan migrate:fresh --seed
- créer un virtual host
