#include <AFMotor.h>

int Vl,Vr,kl,kr;

#include <ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
ros::NodeHandle  nh;

//モーターボードの3,4を使用しているため
AF_DCMotor motor3(3, MOTOR12_64KHZ); // create motor #3, 64KHz pwm
AF_DCMotor motor4(4, MOTOR12_64KHZ); // create motor #4, 64KHz pwm


void MotorCmdCallback(const geometry_msgs::Twist& msg){
//  Vl = msg.linear.x+0.13/2*msg.angular.z;
//  Vr = msg.linear.x-0.13/2*msg.angular.z;
//  Vl = kl*Vl;
//  Vr = kr*Vr;

  if (msg.linear.x>0){
    motor3.run(FORWARD);      // forward
    motor4.run(FORWARD);
    }
  else if (msg.linear.x<0){
    motor3.run(BACKWARD);     // backward
    motor4.run(BACKWARD);
  }
  else if (msg.angular.z>0){
    motor3.run(FORWARD);      // turn right
    motor4.run(BACKWARD);
    }
  else if (msg.angular.z<0){
    motor3.run(BACKWARD);     // turn left
    motor4.run(FORWARD);
    }
  else{
    motor3.run(RELEASE);      // stopped
    motor4.run(RELEASE);      
    }
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", MotorCmdCallback);


void setup() {
  //Serial.begin(9600);           // set up Serial library at 9600 bps
  //Serial.println("Motor test!");//↑rosserialはserial.beginをコメントアウトしないと使用できない（XCTUの設定で回避可能？）
  
  motor3.setSpeed(200);     // set the speed to 200/255
  motor4.setSpeed(200);     // set the speed to 200/255

  nh.initNode();
  nh.subscribe(sub);
  
}

void loop() {
  nh.spinOnce();
  delay(1);
}
