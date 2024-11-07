//Servo Control Using ESP8266 and Whatsapp

#include <ESP8266WiFi.h> //Library untuk esp8266 || Library for esp8266
#include <ThingESP.h> // Library ThingEsp yang bisa kalian unduh dari arduino IDE || Library ThingsEsp You can download it on Arduino IDE
#include <Servo.h> //Library untuk Servo || Library for Servo

ThingsESP8266 things("ThingESP account usernamep", "Project name", "Project Devices Code");

Servo myservo;
#define Servo 4 //defines what pin are use

unsigned long previousMillis = 0;
/*This variable is used to store the last time an event occurred, measured in milliseconds.*/

const long INTERVAL = 6000;  
/*This variable is used to set the interval in milliseconds (in this case, 6000 milliseconds or 6 seconds).*/

Void Setup(){
  Serial.begin(115200);
  myservo.attach(Servo);  // Add servo pin
  myservo.write(0);  // Servo start position
  
  thing.SetWiFi("WiFi Username", "WiFi Password");

  thing.initDevice();
}

//use this program line if you want to control the servo to a specified position
String HandleResponse(String query){
  if (query == "open servo") {
    myservo.write(180); 
/*In this program line the servo is immediately set to move in the direction of 180 degrees.*/
    return "Servo is open";
  } 
  else if (query == "close servo") {
    myservo.write(0); 
/*In this program line the servo is immediately set to move in the direction of 0 degrees.*/
    return "servo is close";
  }
  else if (query == "servo conditon") {
    return myservo.read() == 180 ? "Servo is open " : "Servo is close";
  }
  else return "Invalid Text";
}

//Use this program line if you want to control the servo as you wish
String HandleResponse(String query){
  if (query.startsWith("Open servo ")) {
   int angle = query.substring(11).toInt(); //Get numbers from query
    if (angle >= 0 && angle <= 180) {
    myservo.write(angle);
      return "The servo is already open as much as " + String(angle) + " degree";
      } else {
        return "Invalid angle. Please enter between 0 and 180.";
        }
  }
  else return "Invalid Text";
}

void loop() {
  thing.Handle();
}
