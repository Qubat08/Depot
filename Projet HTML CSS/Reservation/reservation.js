function reservation() {
    localStorage.clear();
    var day = document.getElementById("days").options[document.getElementById("days").selectedIndex].text;
    var numero = document.getElementById("numero").value;
    var mois = document.getElementById("month").options[document.getElementById("month").selectedIndex].value;
    var heure = document.getElementById("time").options[document.getElementById("time").selectedIndex].value;
    var nom = document.getElementById("name").value;
    var num = document.getElementById("num").value;
    var number =document.getElementById("couvert").value;

    if (nom!=""&num!=""){
        sauvegarde(day,numero,mois,heure,nom,num,number);
    }


   
}
function sauvegarde(day,numero,mois,heure,nom,num,number){
    localStorage.setItem("day",day);
    localStorage.setItem("numero",numero)
    localStorage.setItem("mois",mois);
    localStorage.setItem("time",heure)
    localStorage.setItem("nom",nom)
    localStorage.setItem("num",num);
    localStorage.setItem("nombre",number);
    alert("M. "+nom+"\nVotre réservation pour le "+day+" "+numero+" "+ mois+" a été envoyé.")
}