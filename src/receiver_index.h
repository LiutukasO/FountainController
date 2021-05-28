#ifndef __RECEIVER_INDEX_H__
#define __RECEIVER_INDEX_H__

#include "ESPAsyncWebServer.h"

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>FONTANO VALDYMAS</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    p {  font-size: 1.2rem;}
    body {  margin: 0;}
    .topnav { overflow: hidden; background-color: #2f4468; color: white; font-size: 1.7rem; }
    .content { padding: 20px; }
    .card { background-color: white; box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5); }
    .cards { max-width: 700px; margin: 0 auto; display: grid; grid-gap: 2rem; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); }
    .reading { font-size: 2.8rem; }
    .packet { color: #bebebe; }
    .card.valve { color: #fd7e14; }
    .card.led { color: #1b78e2; }
  </style>
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
</head>
<body>
  <div class="topnav">
    <h3>FONTANO VALDYMAS</h3>
  </div>
  <div class="content">
    <div class="cards">
      <div class="card valve">
        <h4><i class="fas fa-thermometer-half"></i> SROVĖ</h4>
        <p><span class="reading">Centras: <span id="valve-center"></span></span></p>
        <p><span class="reading">Vidus: <span id="valve-middle"></span></span></p>
        <p><span class="reading">Išorė: <span id="valve-external"></span></span></p>
      </div>
      <div class="card led">
        <h4><i class="fas fa-tint"></i> LED #1</h4>
        <p><span class="reading"><span id="led-1-red"></span></span></p>
        <p><span class="reading"><span id="led-1-green"></span></span></p>
        <p><span class="reading"><span id="led-1-blue"></span></span></p>
      </div>
      <div class="card led">
        <h4><i class="fas fa-tint"></i> LED #2</h4>
        <p><span class="reading"><span id="led-2-red"></span></span></p>
        <p><span class="reading"><span id="led-2-green"></span></span></p>
        <p><span class="reading"><span id="led-2-blue"></span></span></p>
      </div>
      <div class="card led">
        <h4><i class="fas fa-tint"></i> LED #3</h4>
        <p><span class="reading"><span id="led-3-red"></span></span></p>
        <p><span class="reading"><span id="led-3-green"></span></span></p>
        <p><span class="reading"><span id="led-3-blue"></span></span></p>
      </div>
      <div class="card led">
        <h4><i class="fas fa-tint"></i> LED #4</h4>
        <p><span class="reading"><span id="led-4-red"></span></span></p>
        <p><span class="reading"><span id="led-4-green"></span></span></p>
        <p><span class="reading"><span id="led-4-blue"></span></span></p>
      </div>
    </div>
  </div>
<script>
 $.getJSON('/fountain/status', function(fountainState) {
    console.log("new_readings", fountainState);
    //var fountainState = JSON.parse(data);
    document.getElementById("valve-center").innerHTML   = fountainState.valveState.center;
    document.getElementById("valve-middle").innerHTML   = fountainState.valveState.middle;
    document.getElementById("valve-external").innerHTML = fountainState.valveState.external;

    document.getElementById("led-1-red").innerHTML   = fountainState.led1State.red;
    document.getElementById("led-1-green").innerHTML = fountainState.led1State.green;
    document.getElementById("led-1-blue").innerHTML  = fountainState.led1State.blue;

    document.getElementById("led-2-red").innerHTML   = fountainState.led2State.red;
    document.getElementById("led-2-green").innerHTML = fountainState.led2State.green;
    document.getElementById("led-2-blue").innerHTML  = fountainState.led2State.blue;

    document.getElementById("led-3-red").innerHTML   = fountainState.led3State.red;
    document.getElementById("led-3-green").innerHTML = fountainState.led3State.green;
    document.getElementById("led-3-blue").innerHTML  = fountainState.led3State.blue;

    document.getElementById("led-4-red").innerHTML   = fountainState.led4State.red;
    document.getElementById("led-4-green").innerHTML = fountainState.led4State.green;
    document.getElementById("led-4-blue").innerHTML  = fountainState.led4State.blue;
 });
</script>
</body>
</html>)rawliteral";

#endif