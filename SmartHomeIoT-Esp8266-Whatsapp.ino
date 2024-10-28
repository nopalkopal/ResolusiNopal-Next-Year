//SmartHome IoT NopalKopal

#include <ESP8266WiFi.h> //library untuk esp8266
#include <ThingESP.h> // library ThingEsp yang bisa kalian unduh dari arduino IDE

ThingESP8266 thing("NopalKopal", "SmartHomeWA", "123456789");
/*ThingsESP8266 things("username akun thingsEsp", "Nama Project", "Kode Project Devices");*/

#define Relay1 0 //mendefinisikan pin apa yang dipakai
#define Relay2 2
#define Relay3 3


unsigned long previousMillis = 0;
/*Variabel ini digunakan untuk menyimpan waktu terakhir suatu peristiwa terjadi, diukur dalam milidetik*/

const long INTERVAL = 6000;  
/*Variable ini digunakan untuk mengatura interval dalam milidetik (dalam hal ini, 6000 milidetik atau 6 detik).*/

void setup()
{
  Serial.begin(115200);
  pinMode(Relay1, OUTPUT); //mengatur relay sebagai output
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);

  digitalWrite(Relay1, HIGH); //mengatur kondisi awal relay agar mati.
  digitalWrite(Relay2, HIGH);
  digitalWrite(Relay3, HIGH);
  things.SetWifi("Username wifi", "Password wifi");

  thing.initDevice();
}


String HandleResponse(String query)
{
  if (query == "lampu 1 hidupin dong") {
    digitalWrite(Relay1, LOW);
    /*Dalam beberapa kasus terutama pada Modul Relay 4 Channel yang saya gunakan untuk program ini, relay sering kali terhubung dengan cara yang membuatnya
    menyala saat pin GPIO diatur ke LOW. Ini adalah logika invers, di mana LOW berarti menghidupkan LED dan HIGH berarti mematikannya.*/
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
  else if (query == "kabar lampu gimana?"){
    return digitalRead(Relay1) ? "Lampu 1 mati" : "Lampu 1 hidup";
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
  else return "Your query was invalid..";

}


void loop()
{
  thing.Handle();

}
