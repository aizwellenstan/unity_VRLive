#include <M5StickC.h>
#include <WiFi.h>
#include <WiFiUDP.h>
#include <OSCMessage.h>

/**
 * WiFiアクセス用
 */
const char ssid[] = "[お使いのルーターのSSID]";
const char pass[] = "[パスワード]";
static WiFiUDP wifiUdp; 
static const char *kRemoteIpadr = "[受け取りたいPCのプライベートIP]";
static const int kRmoteUdpPort = 8001; //送信先のポート
static const int kLocalPort = 7000;  //自身のポート
boolean connected = false;

/**
 * HCSR-04用
 */
  int Trig = 26;
  int Echo = 36;
  int Duration;
  float Distance;

/**
 * IMU用
 */
float pitch = 0.0F;
float roll  = 0.0F;
float yaw   = 0.0F;

float temp = 0;

/**
 * Setup
 */
static void WiFi_setup()
{
  WiFi.begin(ssid, pass);
  while( WiFi.status() != WL_CONNECTED) {
    delay(500);  
  }  
}

static void Serial_setup()
{
  Serial.begin(115200);
  Serial.println(""); // to separate line  
}

static void Hcsr04_setup()
{
    pinMode(Trig,OUTPUT);
    pinMode(Echo,INPUT);
}

void setup() {
  Hcsr04_setup();
  Serial_setup();
  WiFi_setup();
  M5.begin();
  M5.IMU.Init();
}

void loop() {
  /**
   * 距離計測
   */
  digitalWrite(Trig,LOW);
  delayMicroseconds(1);
  digitalWrite(Trig,HIGH);
  delayMicroseconds(11);
  digitalWrite(Trig,LOW);
  Duration = pulseIn(Echo,HIGH);
  if (Duration>0) {
    Distance = Duration/2;
    Distance = Distance*340*100/1000000; // ultrasonic speed is 340m/s = 34000cm/s = 0.034cm/us 

    OSCMessage msgDistance("/leftHand/distance");
    msgDistance.add(Distance);
    wifiUdp.beginPacket(kRemoteIpadr, kRmoteUdpPort);
    msgDistance.send(wifiUdp);
    wifiUdp.endPacket();  
  }

 /**
  * IMU計測
  */
  M5.IMU.getAhrsData(&pitch,&roll,&yaw);
  M5.IMU.getTempData(&temp);

  /**
   * OSCSend
   */
  OSCMessage msgPitch("/guitar/pitch");
  msgPitch.add(pitch);
  OSCMessage msgRoll("/guitar/roll");
  msgRoll.add(roll);
  OSCMessage msgYaw("/guitar/yaw");
  msgYaw.add(yaw);


  wifiUdp.beginPacket(kRemoteIpadr, kRmoteUdpPort);
  msgPitch.send(wifiUdp);
  wifiUdp.endPacket();  

  wifiUdp.beginPacket(kRemoteIpadr, kRmoteUdpPort);
  msgRoll.send(wifiUdp);
  wifiUdp.endPacket();  

  wifiUdp.beginPacket(kRemoteIpadr, kRmoteUdpPort);
  msgYaw.send(wifiUdp);
  wifiUdp.endPacket();  

  delay(33);
}
