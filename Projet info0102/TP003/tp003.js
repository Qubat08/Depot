var latitude=0
var longitude=0
activeLocation();


function activeLocation() {
    navigator.geolocation.getCurrentPosition(showLocation);
}

function showLocation(location) {
   latitude = location.coords.latitude;
   longitude = location.coords.longitude;
    console.log("ma latitude: "+latitude);
    console.log("ma longitude: "+longitude);
    localStorage.clear();
    localStorage.setItem("latitude",latitude);
    localStorage.setItem("longitude",longitude);
    ajaxOpenSM();
}

function ajaxOpenSM(){
  maRequete = new XMLHttpRequest();
  maRequete.open('GET','https://nominatim.openstreetmap.org/reverse?format=json&lat='+latitude+'&lon='+longitude, true);
  maRequete.onreadystatechange = callB;
  maRequete.responseType = 'json'; // récupère la réponse en JSON
  maRequete.send();

}
function callB(){
if (maRequete.readyState === XMLHttpRequest.DONE) { 
  if (maRequete.status === 200) { 
    var codeP = getCP(maRequete.response);
    console.log(maRequete.response)
    colorDPT(codeP);
  }
    else { 
      alert(maRequete.status); 
    } 
  }
  return codeP;
}
function getCP(response){
var x; var y ;
x = (response["address"]["postcode"]) // accès au code postal (via json avec les)
y = x.substr(0,2); // récupère les deux premiers chiffres du code postal
console.log(y)
return y;
}

function colorDPT(codeP){
  var x = document.querySelectorAll("*[data-num]"); // récupère tous les codes postals
  var i;
  for (i = 0; i!= x.length; i++){ 
    if (x[i].getAttribute("data-num")==codeP){ // test quand le codePostal est égal
      x[i].classList.add("maClasse") // ajoute une classe à l'élément pour identifier le path
    }
  }
}
