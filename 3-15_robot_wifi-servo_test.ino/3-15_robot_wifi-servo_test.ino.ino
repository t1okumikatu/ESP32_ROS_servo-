
#include "esp_system.h"  
#include <ros.h>
#include <std_msgs/UInt16.h>
#include <WiFi.h>

//const char SSID[] = "aterm-ecce1b-g";
const char SSID[] = "KICK-event";
//const char PASSWORD[] = "753bf0b3391c9";
const char PASSWORD[] = "g6f5R9sP";

IPAddress server(192,168,1,12);
const uint16_t serverPort = 11411;

WiFiClient client;
class WiFiHardware {

  public:
  WiFiHardware() {};

  void init() {
    // do your initialization here. this probably includes TCP server/client setup
    client.connect(server, serverPort);
  }

  // read a byte from the serial port. -1 = failure
  int read() {
    // implement this method so that it reads a byte from the TCP connection and returns it
    //  you may return -1 is there is an error; for example if the TCP connection is not open
    return client.read();         //will return -1 when it will works
  }

  // write data to the connection to ROS
  void write(uint8_t* data, int length) {
    // implement this so that it takes the arguments and writes or prints them to the TCP connection
    for(int i=0; i<length; i++)
      client.write(data[i]);
  }

 // returns milliseconds since start of program
  unsigned long time() {
     return millis(); // easy; did this one for you
  }
};


ros::NodeHandle_<WiFiHardware> nh;

//Servo servo;

void servo_cb(const std_msgs::UInt16& cmd_msg){

    //servo.write(cmd_msg.data);
    ledcWrite(0,cmd_msg.data);
    ledcWrite(1,cmd_msg.data);
    //delay(150);
    Serial.print(cmd_msg.data);
    digitalWrite(17, HIGH-digitalRead(17));

}

ros::Subscriber<std_msgs::UInt16> sub("servo", servo_cb);
   
void setup(){
   pinMode(27, OUTPUT);
  Serial.begin(57600);//
     WiFi.begin(SSID,PASSWORD);
    Serial.print("WiFi connecting");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
   Serial.println(" connected");
   //digitalWrite(27, HIGH);
   nh.initNode();
    nh.subscribe(sub);
  delay(10);
    //pinMode(27, OUTPUT);
    digitalWrite(27, LOW);


    pinMode(17, OUTPUT);
    digitalWrite(17, LOW);
   
    ledcSetup(0,50,10);//0ch50hz10bit//L-wheel
    ledcAttachPin(15,0);//15pin0ch//

    ledcSetup(1,50,10);//1ch50hz10bit//R-wheel
    ledcAttachPin(16,1);//16pin1ch//

}


int mini=10;//左端//
int maxi=167;//右端//
int n=mini;//

void loop(){
 //ledcWrite(0,60);//
 //n+=15;//
 //if (n>maxi) n=mini;//
  //delay(1500);//
 //ledcWrite(1,100);
  //delay(1500);
 //ledcWrite(0,150);
  //Serial.println(n);//
  //delay(1500);
     digitalWrite(27, HIGH);


   

    nh.spinOnce();
    delay(1);
}
