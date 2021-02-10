
 
#define BLYNK_PRINT Serial

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "-oRYRz3W3Wi8y6lyAejL2802MvrIJnGw";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "tugasloh";
char pass[] = "12345678";

// Hardware Serial on Mega, Leonardo, Micro...
//#define EspSerial Serial1

// or Software Serial on Uno, Nano...
#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2,6); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);

BlynkTimer timer;

int OutputDO=12; //nama alias pin 12 yaitu Output DO
int OutputAO=A0; //nama alias pin AO yaitu Output AO
 
int val;//val sebagai buffer data
float sensor; //sebagai data buffer sensor
 #include <Servo.h>
Servo myservo;
int pos=0;
int a=0;
int on=1;
WidgetLCD lcd(V5);

void setup()
{
  myservo.attach(5);  //servo disambu di pin 5

pinMode (OutputDO, INPUT) ; //Defisini OutputDO sebagai input
pinMode (OutputAO, INPUT) ; //Defisini OutputAO sebagai input
//inisialisasi komunikasi serial
Serial.begin(9600);
// Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

//  Blynk.begin(auth, wifi, ssid, pass);
  // You can also specify server:
  Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 8080); //khusus indihomo
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8080);

  timer.setInterval(1000L, myTimerEvent);
}
BLYNK_WRITE(V0){
  int pinValue = param.asInt();
  if(pinValue == 1){
    on = 1;
  }
  if(pinValue == 0){
    digitalWrite(10,LOW);
    on = 0;
    Blynk.virtualWrite(V0, 0);
  }
}
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.

sensor = analogRead(OutputAO);//Pembacaan nilai sensor
  

  Blynk.virtualWrite(V1, sensor);
}
 
void loop()
{
 Blynk.run();
 timer.run();
sensor = analogRead(OutputAO);//Pembacaan nilai sensor
Serial.println(sensor); //hasil akan ditampilkan di serial monitor
 
//pembacaan nilai sensor (logika 1 dan 0)
val = digitalRead (OutputDO);
//Pengondisian
if(sensor < 450|| on==0){   //pongodisian untuk temperatur kurang dari 25
  if(a==0){
//  for (pos = 0; pos <= 90; pos += 1) {
    //  diga ao servo para ir para a posição na
    // variável 'pos'
    myservo.write(90);
    Blynk.virtualWrite(V0, 0);
    // aguarde 15 ms para que o servo atinja a posição
    a=90;
    delay(5); // Wait for 15 millisecond(s)
  }
  
  lcd.print(0, 0, "Portal Tertutup");
  }
//  }
  else{
    if(a==90){
  //delay(3000);
      // Mova o servo de 0 a 180 passo de 1 grau
//  for (pos = 90; pos >= 0; pos -= 1) {
    //  diga ao servo para ir para a posição na
    // variável 'pos'
    myservo.write(0);
    Blynk.virtualWrite(V0, 1);
    
    // aguarde 15 ms para que o servo atinja a posição
    delay(5); // Wait for 15 millisecond(s)
    a=0;
//  }
  
  lcd.print(0, 0, "Portal Terbuka ");
  }
  }
}
