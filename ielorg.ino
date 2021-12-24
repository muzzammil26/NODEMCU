#include <ESP8266WiFi.h>

#include <HCSR04.h>

#include <ESP8266WebServer.h>

const char* ssid = "Infinix HOT 9 Play";  // your SSID

const char* password = "987654321";  //your wifi password

const char index_html[] PROGMEM={"<!DOCTYPE html>\n"

"<html>\n"

"<head>\n"

"<title>IOT Based Water Level Controller Using Ultrasonic</title>\n"

"<script type=\"text/javascript\" src=\"http://static.fusioncharts.com/code/latest/fusioncharts.js\"></script>\n"

"<script type=\"text/javascript\" src=\"http://static.fusioncharts.com/code/latest/themes/fusioncharts.theme.fint.js?cacheBust=56\"></script>\n"

"<script src=\"https://cdnjs.cloudflare.com/ajax/libs/zepto/1.2.0/zepto.min.js\"></script>\n"

"<script src=\"https://simeydotme.github.io/jQuery-ui-Slider-Pips/dist/js/jquery-plus-ui.min.js\"></script>\n"

"<script src=\"https://simeydotme.github.io/jQuery-ui-Slider-Pips/dist/js/jquery-ui-slider-pips.js\"></script>\n"

"<link rel=\"stylesheet\" href=\"https://simeydotme.github.io/jQuery-ui-Slider-Pips/dist/css/jqueryui.min.css\">\n"

"<link rel=\"stylesheet\" href=\"https://simeydotme.github.io/jQuery-ui-Slider-Pips/dist/css/jquery-ui-slider-pips.min.css\">\n"

"<link rel=\"stylesheet\" href=\"https://simeydotme.github.io/jQuery-ui-Slider-Pips/dist/css/app.min.css\">\n"

"<style>\n"

".raphael-group-7-background rect {\n"

"fill: rgb(255, 255, 255) !important;\n"

"}\n"

"[id*=flat-slider].ui-slider.ui-slider-vertical {\n"

"\theight: 320px;\n"

"\tmargin-top: 90px;\n"

"    margin-right: 15%;\n"

"    margin-bottom: 90px;\n"

"    margin-left: 15%;\n"

"}\n"

"$bg: #609fd2;\n"

"[id*=flat-slider].ui-slider,\n"

"[id*=flat-slider].ui-slider .ui-slider-pip .ui-slider-line {\n"

"    background: darken($bg, 15%);\n"

"}\n"

"[id*=flat-slider].ui-slider .ui-slider-handle .ui-slider-tip:after {\n"

"    border-left-color: #609fd2;\n"

"}\n"

"[id*=flat-slider].ui-slider .ui-slider-handle.ui-state-hover, \n"

"[id*=flat-slider].ui-slider .ui-slider-handle.ui-state-focus, \n"

"[id*=flat-slider].ui-slider .ui-slider-handle.ui-state-active {\n"

"      border-color: white; }\n"

"body {\n"

"   \n"

"    font-family: \"Roboto\";\n"

"}\n"

".stuff {    \n"

"    padding: 10px 5px 5px;\n"

"    max-width: 150px;    \n"

"\tmax-height: 550px;    \n"

"}\n"

"div.inline { float:left; }\n"

".clearBoth { clear:both; }\n"

"\n"

"</style>\n"

"<script>\n"

"$(document).ready(function() {\n"

"            setInterval(\"get_motor_status()\", 2000);\n"

"        });\n"

"\t\t\t\t\n"

"        function get_motor_status() {\n"

"            var someUrl = \"/motor_status\";\n"

"            $.ajax({url: someUrl,dataType: \"text\",success: function(response) {\n"

"                    if (response == \"on\")\n"

"                        $(\"#status\").html(\"Water Pump ON\")\n"

"                    else\n"

"                        $(\"#status\").html(\"Water Pump OFF\")\n"

"                   }})}\t\t\n"

"\t\t\t\t\n"

"    </script>\n"

"\t\n"

"<script type=\"text/javascript\">\n"

"    FusionCharts.ready(function(){\n"

"    var fusioncharts = new FusionCharts({\n"

"    \"type\": \"cylinder\",\n"

"    \"dataFormat\": \"json\",\n"

"    \"id\": \"fuelMeter\",\n"

"    \"renderAt\": \"chart-container\",\n"

"    \"width\": \"300\",\n"

"    \"height\": \"450\",\n"

"    \"dataSource\": {\n"

"        \"chart\": {\n"

"            \"theme\": \"fint\",\n"

"            \"caption\": \"Tank Water Level Controller\",\n"

"            \"subcaption\": \"using ultra sonic\",\n"

"            \"lowerLimit\": \"0\",\n"

"            \"upperLimit\": \"100\",\n"

"            \"lowerLimitDisplay\": \"Empty\",\n"

"            \"upperLimitDisplay\": \"Full\",\n"

"            \"numberSuffix\": \" % of Liter\",\n"

"            \"showValue\": \"1\",\n"

"            \"chartBottomMargin\": \"10\"\n"

"        },\n"

"        \"value\": \"10\"\n"

"    },\n"

"    \"events\": {\n"

"    \"rendered\": function(evtObj, argObj) {\n"

"\tsetInterval(function() {\n"

"\tvar someUrl = \"/level\";\n"

"\t\t\t\t\t$.ajax({\n"

"\t\t\t\t\t\turl: someUrl,\n"

"\t\t\t\t\t\tdataType: \"text\",\n"

"\t\t\t\t\t\tsuccess: function(response) {\n"

"\t\t\t\t\t\t\t evtObj.sender.feedData(\"&value=\" + response);\n"

"\t\t\t\t\t\t},\n"

"\t\t\t\t\t\ttimeout: 1000\n"

"\t\t\t\t\t})\t\n"

"\t\t\n"

"        }, 1000); \n"

"   }\n"

"}\n"

"});\n"

"    fusioncharts.render();\n"

"    });\n"

"</script>\n"

"</head>\n"

"<body>\n"

"<div style=\"width:600px;margin:auto;\">\n"

"\n"

"<div class=\"stuff\">\n"

" \n"

"    <main>        \n"

"        <div class=\"inline\" id=\"flat-slider-vertical-1\"></div>        \n"

"    </main>\n"

"    \n"

"</div>\n"

"    <div style=\"margin-left: 10px;\" class=\"outline\" id=\"chart-container\">FusionCharts XT will load here!</div>\n"

"\t<div class=\"inline\" id=\"status\" style=\"background-color: white;\n"

"    width: 200px;\n"

"    margin: 1px;\">Water Pump OFF</div>\n"

" </div>\n"

"\n"

"<script>\n"

"$.extend( $.ui.slider.prototype.options, { \n"

"    animate: 300\n"

"});\n"

"\n"

"\n"

"$(\"#flat-slider-vertical-1\")\n"

"    .slider({\n"

"        max: 100,\n"

"        min: 0,\n"

"        range: true,\n"

"         values: [20, 75],\n"

"        orientation: \"vertical\",\n"

"\t\t\n"

"\t\tslide: function( event, ui ) {\n"

"\t\tconsole.log(ui.values);\n"

"\t\tvar someUrl = \"/configRange?lower=\" + ui.values[0]+\"&upper=\"+ui.values[1];\n"

"            $.ajax(\n"

"\t\t\t{\n"
                 
"\t\t\t\turl: someUrl,dataType: \"text\",success: function(response) {}\n"

"\t\t\t})               \n"

"        }\n"

"    })\n"

"    .slider(\"pips\", {\n"

"        first: \"pip\",\n"

"        last: \"pip\"\n"

"    })\n"

"    .slider(\"float\");\n"

"</script>\n"

"\n"

"\t</body>\n"

"</html>"

  };




#define MAX_HEIGHT 27 // tank height 27 cm manually enter here for automatic empty tank //scan refer post https://www.dofbot.com/post/water-level-monitoring 

#define MOTOR_CONTROL_PIN D4 

UltraSonicDistanceSensor distanceSensor(D1,D2);  //D1 trig, D2=echo

int waterLevelLowerThreshold=15;

int waterLevelUpperThreshold=90;

float volume = 0;

float liters = 0;

WiFiClient client;

String inputString = "";         // a string to hold incoming data

String dataToSend="";

int waterLevelDownCount=0,waterLevelUpCount=0;

ESP8266WebServer server(80);

void handleRoot() {

  server.send_P(200, "text/html;charset=UTF-8", index_html);

}

void handleLevelRequest(){

  server.send(200,"text",String(liters));

}

void handleNotFound(){

  String message = "File Not Found\n\n";

  server.send(404, "text/plain", message);

}

void handleStatus()

{

  if(digitalRead(MOTOR_CONTROL_PIN)==0)//MOTOR ON

 server.send(200, "text/plain","on"); 

 else server.send(200, "text/plain","off");

}

void handleRangeSetting(){

   waterLevelLowerThreshold=(server.arg(0)).toInt();  

   waterLevelUpperThreshold=(server.arg(1)).toInt(); 

   Serial.print(waterLevelLowerThreshold);

   Serial.print(":");   

   Serial.println(waterLevelUpperThreshold);

     

   server.send(200, "text/plain", "");

}

void measure_Volume()

{

    float heightInch=1*distanceSensor.measureDistanceCm();    

    Serial.println(heightInch); 

   

    volume=(MAX_HEIGHT-heightInch)/28;//MAX_HEIGHT-distance will give actual height, 1 cm for   // offset adjustment

    liters=volume*100  ; // for percentage

    Serial.println(liters); 

    if(liters<=waterLevelLowerThreshold)

        waterLevelDownCount++;

      else waterLevelDownCount=0;

      if(liters>=waterLevelUpperThreshold)

        waterLevelUpCount++;

      else waterLevelUpCount=0;


      if(waterLevelDownCount==3)

      {//TURN ON RELAY

        Serial.println("motor turned on");   

        digitalWrite(MOTOR_CONTROL_PIN,LOW);//Relay is active LOW

      }

      if(waterLevelUpCount==2)

      {//TURN OFF RELAY

        Serial.println("motor turned off");   

        digitalWrite(MOTOR_CONTROL_PIN,HIGH);//Relay is active LOW

      }      

}

void runPeriodicFunc()

{

    static const unsigned long REFRESH_INTERVAL1 = 1000; // 2.1sec

    static unsigned long lastRefreshTime1 = 0;

    

    if(millis() - lastRefreshTime1 >= REFRESH_INTERVAL1)

    {   

      measure_Volume();

      lastRefreshTime1 = millis();

   }

}


void setup(void){

  Serial.begin(115200);

  delay(100);

  pinMode(MOTOR_CONTROL_PIN, OUTPUT);

  WiFi.begin(ssid, password);

  Serial.println("");

  

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");

  }

  Serial.print("IP address:");  

  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);  

  server.on("/level",handleLevelRequest);

  server.on("/configRange",handleRangeSetting);

  server.on("/motor_status",handleStatus);

    

  server.onNotFound(handleNotFound);

  server.begin();

  Serial.println("HTTP server started");

}

void loop(void){

  runPeriodicFunc();

  

  server.handleClient();

}
