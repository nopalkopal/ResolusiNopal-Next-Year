#include <ESP8266WiFi.h>
#include <ThingESP.h>

ThingESP8266 thing("NopalKopal", "SmartHomeWA", "123456789");
/*ThingsESP8266 things("account username thingsEsp", "Project name", "Project Devices Code");*/

#define Relay1 0
#define Relay2 2
#define Relay3 3
#define Rocker1 10
#define Rocker2 9
#define Rocker3 5
bool manualControl = true;

unsigned long previousMillis = 0;
/*This variable is used to store the last time an event occurred, measured in milliseconds.*/
const long INTERVAL = 6000;  
/*This variable is used to set the interval in milliseconds (in this case, 6000 milliseconds or 6 seconds).*/

void setup() {
  Serial.begin(115200);
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Rocker1, INPUT_PULLUP);
  pinMode(Rocker2, INPUT_PULLUP);
  pinMode(Rocker3, INPUT_PULLUP);

  digitalWrite(Relay1, HIGH);
  digitalWrite(Relay2, HIGH);
  digitalWrite(Relay3, HIGH);

  thing.SetWiFi("WiFi Username", "WiFi Password");
  thing.initDevice();
}

String HandleResponse(String query) {
  if (query == "mode manual") {
    manualControl = true;
    return "Mode manual aktif";
  }
  else if (query == "mode whatsapp") {
    manualControl = false;
    return "Mode WhatsApp aktif";
  }
  else if (!manualControl) {
    if (query == "hidupkan semua lampu") {
      digitalWrite(Relay1, LOW);
      digitalWrite(Relay2, LOW);
      digitalWrite(Relay3, LOW);
      return "Semua lampu hidup";
    }
    else if (query == "matikan semua lampu") {
      digitalWrite(Relay1, HIGH);
      digitalWrite(Relay2, HIGH);
      digitalWrite(Relay3, HIGH);
      return "Semua lampu mati";
    }
  }
  return "Perintah tidak dikenali";
}

void loop() {
  thing.Handle();

  if (manualControl) {
    if (digitalRead(Rocker1) == LOW) {
      digitalWrite(Relay1, LOW);
    } else {
      digitalWrite(Relay1, HIGH);
    }

    if (digitalRead(Rocker2) == LOW) {
      digitalWrite(Relay2, LOW);
    } else {
      digitalWrite(Relay2, HIGH);
    }

    if (digitalRead(Rocker3) == LOW) {
      digitalWrite(Relay3, LOW);
    } else {
      digitalWrite(Relay3, HIGH);
    }
  }
}
