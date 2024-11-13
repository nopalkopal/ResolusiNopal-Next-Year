//SmartHome IoT NopalKopal

#include <ESP8266WiFi.h> //Library untuk esp8266 || Library for esp8266
#include <ThingESP.h> // Library ThingEsp yang bisa kalian unduh dari arduino IDE || Library ThingsEsp You can download it on Arduino IDE
#include <Servo.h> //Library untuk Servo || Library for Servo

ThingESP8266 thing("NopalKopal", "SmartHomeWA", "123456789");
/*ThingESP8266 things("account username thingsEsp", "Project name", "Project Devices Code");*/

#define Relay1 0 //mendefinisikan pin apa yang dipakai || defines what pins are used
#define Relay2 2
#define Relay3 3

Servo myservo;
#define Servo 4

unsigned long previousMillis = 0;
/*Variabel ini digunakan untuk menyimpan waktu terakhir suatu peristiwa terjadi, diukur dalam milidetik.
This variable is used to store the last time an event occurred, measured in milliseconds.*/

const long INTERVAL = 6000;  
/*Variable ini digunakan untuk mengatur interval dalam milidetik (dalam hal ini, 6000 milidetik atau 6 detik).
This variable is used to set the interval in milliseconds (in this case, 6000 milliseconds or 6 seconds).*/

void setup()
{
  Serial.begin(115200);
  pinMode(Relay1, OUTPUT); //Mengatur relay sebagai output || set relay as output
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);

  digitalWrite(Relay1, HIGH); //Mengatur kondisi awal relay agar mati || Set the initial condition of the relay to off.
  digitalWrite(Relay2, HIGH);
  digitalWrite(Relay3, HIGH);
  myservo.attach(Servo);  // Menambahkan pin servo || Add servo pin
  myservo.write(0);  // Posisi awal servo || Servo start potition
  
  thing.SetWiFi("WiFi Username", "WiFi Password");

  thing.initDevice();
}


String HandleResponse(String query)
{
  if (query == "lampu 1 hidupin dong") {
    digitalWrite(Relay1, LOW);
    /*Dalam beberapa kasus terutama pada Modul Relay 4 Channel yang saya gunakan untuk program ini, relay sering kali terhubung dengan cara yang membuatnya
    menyala saat pin GPIO diatur ke LOW. Ini adalah logika invers, di mana LOW berarti menghidupkan LED dan HIGH berarti mematikannya.*/
    /*In some cases especially on the 4 Channel Relay Module that I am using for this program, the relay is often connected in a way that 
    makes it turn on when the GPIO pin is set to LOW. This is inverse logic, where LOW means turning the LED on and HIGH means turning it off.*/
    return "Lampu 1 dah hidup";
  }

  else if (query == "lampu 1 dimatikan dong") {
    digitalWrite(Relay1, HIGH);
    return "Lampu 1 dah mati";
  }
  else if (query == "lampu 2 hidupin dong") {
    digitalWrite(Relay2, LOW);
    return "Lampu 2 dah hidup bos";
  }
  else if (query == "lampu 2 dimatikan dong") {
    digitalWrite(Relay2, HIGH);
    return "Lampu 2 dah mati bos";
  }
  else if (query == "lampu 3 hidupin dong") {
    digitalWrite(Relay3, LOW);
    return "Lampu 3 sudah beraktivitas tuan";
  }
  else if (query == "lampu 3 dimatikan dong") {
    digitalWrite(Relay3, HIGH);
    return "Lampu 3 sudah wafat tuan";
  }
  else if (query == "matikan semua lampu") {
    digitalWrite(Relay1, HIGH);
    digitalWrite(Relay2, HIGH);
    digitalWrite(Relay3, HIGH);
    return "Semua lampu dah mati";
  }
  else if (query == "hidupin semua lampu") {
    digitalWrite(Relay1, LOW);
    digitalWrite(Relay2, LOW);
    digitalWrite(Relay3, LOW);
    return "Semua lampu dah hidup";
  }
  else if (query == "kabar semua lampu") {
    String status = "Status lampu:\n";
    status += "Lampu 1: " + String(digitalRead(Relay1) ? "mati" : "hidup") + "\n";
    status += "Lampu 2: " + String(digitalRead(Relay2) ? "mati" : "hidup") + "\n";
    status += "Lampu 3: " + String(digitalRead(Relay3) ? "mati" : "hidup");
    return status;
  }
  else if (query == "kabar lampu 1 gimana?"){
    return digitalRead(Relay1) ? "Lampu 1 mati" : "Lampu 1 hidup";
  }
  else if (query == "kabar lampu 2 gimana?"){
    return digitalRead(Relay2) ? "Lampu 2 mati" : "Lampu 2 hidup";
  }
  else if (query == "kabar lampu 3 gimana?"){
    return digitalRead(Relay3) ? "Lampu 3 mati" : "Lampu 3 hidup";
  }
  else if (query == "buka pagar") {
    myservo.write(180); // Servo bergerak ke 180 derajat
    return "Pagar sudah terbuka icikbos";
  } 
  else if (query == "tutup pagar") {
    myservo.write(0); // Servo bergerak kembali ke 0 derajat
    return "Pagar sudah tertutup icikbos";
  }
  else if (query == "kondisi pagar") {
    return myservo.read() == 180 ? "Pagar terbuka" : "Pagar tertutup";
  }
  else if (query == "halo masbro"){
   return "ada apa icikbos?";
  }

  else if (query == "biasalah masbro"){
   return "siap sedia icikbos";
  }

  else if (query == "sip, makasih masbro"){
    return "sama sama icikbos yang ganteng, soleh, istrinya cantik, kaya raya, dan baik hati serta tidak sombong";
  }
  else return "Icikbos ngomong apa?";
}


void loop() {
  thing.Handle();
}
