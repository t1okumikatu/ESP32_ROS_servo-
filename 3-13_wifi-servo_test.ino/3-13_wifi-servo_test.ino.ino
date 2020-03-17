
#include "esp_system.h"  
#include <ros.h>
#include <std_msgs/UInt16.h>

ros::NodeHandle nh;

//Servo servo;

void servo_cb(const std_msgs::UInt16& cmd_msg){

    //servo.write(cmd_msg.data);
    ledcWrite(0,cmd_msg.data);
    //delay(150);
    Serial.print(cmd_msg.data);
    digitalWrite(17, HIGH-digitalRead(17));

}

ros::Subscriber<std_msgs::UInt16> sub("servo", servo_cb);
    String a;
void setup(){
  
  Serial.begin(115200);//
    //ledcSetup(0,50,10);//0ch50hz10bit
    //ledcAttachPin(15,0);//15pin0ch//
  

    pinMode(17, OUTPUT);
    digitalWrite(17, LOW);
    nh.initNode();
    nh.subscribe(sub);
    ledcSetup(0,50,10);//0ch50hz10bit
    ledcAttachPin(15,0);//15pin0ch//

   // servo.attach(9);

}
int mini=10;//左端//
int maxi=167;//右端//
int n=mini;//

void loop(){
 //ledcWrite(0,10);//
 //n+=15;//
 //if (n>maxi) n=mini;//
  //delay(1500);//
  //ledcWrite(0,n);
  //delay(1500);
 //ledcWrite(0,150);
  //Serial.println(n);//
  //delay(1500);


   

    nh.spinOnce();
    delay(1);
}
