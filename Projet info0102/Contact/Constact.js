function recupformulaire(){
    var nom = document.getElementById("nom").value;
    var email = document.getElementById("email").value;
    var msg = document.getElementById("msg").value;
    console.log(msg)
    if (nom!="" & email!=""){
        if (msg != ""){
            alert("Monsieur "+nom +",\nVotre message a bien été envoyé.\nUne réponse vous sera envoyer sur l'adresse email suivante: "+email)
        }
    }
}