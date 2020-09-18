struct Map {
    bool L;
    bool R;
    bool F;
  };

struct Map curPos, prePos, action,impDec,deadEnd;

//For moving straight ahead, limits for crash protection  #TODO
#define F_RIGHT_MAX
#define F_LEFT_MAX

//Limits for left, right, front detection  #TODO
#define LIM_R 5
#define LIM_L 5
#define LIM_F 8

//Wait time between detecting a change in curPos and prePos and executing.  #TODO
#define NOT_YET 100

//Motor pins
#define vel_motor_lef 10 // controls the speed of the left engine;
#define vel_motor_rig 11 // controls the speed of the right engine;
#define e1 8 // controls left motor rotation direction;
#define e2 9 // controls left motor rotation direction;
#define d1 12 // controls the direction of rotation of the right motor;
#define d2 7 // controls the direction of rotation of the right motor;

void resync();
void clearSerial();
void front_driveRWALL();
 void front();
 void left();
 void right();

 int trigger_front = 6; // controls the pulse sent from the front sensor
 int echo_front = 5; // controls the pulse received from the front sensor

 int trigger_lef = 4; // controls the pulse sent from the left sensor
 int echo_lef = 3; // controls the pulse received from the left sensor

 int trigger_rig = 13; // controls the pulse sent from the front sensor
 int echo_rig = 2; // controls the pulse received from the front sensor

 // configuration of theINPUT types of the declared variables;
void setup()
{
  Serial.begin(9600);
  pinMode(trigger_front,OUTPUT); // trigger_front arduino signalOUTPUT
  pinMode(echo_front,INPUT); // arduino signalINPUT from echo_front

  pinMode(trigger_lef,OUTPUT); // arduino signalOUTPUT from trigger_front
  pinMode(echo_lef,INPUT); // signalINPUT from echo_front arduino

  pinMode(trigger_rig,OUTPUT); // arduino signalOUTPUT from trigger_front
  pinMode(echo_rig,INPUT); // echo_front arduino signalINPUT

  pinMode(vel_motor_lef,OUTPUT); // left motor speed arduino signalOUTPUT
  pinMode(vel_motor_rig,OUTPUT); // arduino signalOUTPUT of the right motor speed

  pinMode(e1,OUTPUT); // arduino signalOUTPUT from left motor rotation direction control
  pinMode(e2,OUTPUT); // arduino signalOUTPUT from left motor rotation direction control
  pinMode(d1,OUTPUT); // arduino signalOUTPUT of the right motor direction of rotation control
  pinMode(d2,OUTPUT); // arduino signalOUTPUT of the right motor direction of rotation control
  

  //Initialize the curPos and prePos to |0   0|
  //                                    |  1  |
  curPos.L = false;
  curPos.R = false;
  curPos.F = true;

  prePos.L = false;
  prePos.R = false;
  prePos.F = true;

  Serial.println("curPos and prePos successfully initialized!");
  
  delay(5000);
}

// code in infinite repetition of the project

void loop()
{
  // declaration of variables used to control the project;
  long dur_front, dur_left, dur_right, right, left, front;


  digitalWrite (trigger_front,LOW); // the respective signalINPUTs andOUTPUTs of the
  delayMicroseconds (2); // ultrasonic sensor and stored by the sensor variable
  digitalWrite (trigger_front,HIGH); // which converts the speed of sound that is 340 m / s or
  delayMicroseconds (5); // 29 microseconds per centimeter, as the signal comes and goes
  digitalWrite (trigger_front,LOW); // this time is half being sensor = time / 29/2;
  dur_front = pulseIn (echo_front,HIGH); // so it goes on with the other two sensors as well.
  front = dur_front*0.034/2;
  //Serial.print("front: ");
  //Serial.println(front);

  digitalWrite(trigger_lef,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_lef,HIGH);
  delayMicroseconds(5);
  digitalWrite(trigger_lef,LOW);
  dur_left = pulseIn(echo_lef,HIGH);
  left = dur_left*0.034/2;
  //Serial.print("left: ");
  //Serial.println(left);

  digitalWrite(trigger_rig,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_rig,HIGH);
  delayMicroseconds(5);
  digitalWrite(trigger_rig,LOW);
  dur_right = pulseIn(echo_rig,HIGH);
  right = dur_right*0.034/2;
  //Serial.print("right: ");
  //Serial.println(right);

  digitalWrite(vel_motor_lef, 0); // block to initialize theINPUTs with pulse 0 or off;
  digitalWrite(vel_motor_rig, 0); //
  digitalWrite(e1, 0); //
  digitalWrite(e2, 0); //
  digitalWrite(d1, 0); //
  digitalWrite(d2, 0); //

  //Regen curPos based on sensor data

    curPos.L = left<=LIM_L;
    curPos.R = right<=LIM_R;
    curPos.F = front<LIM_F;
    
    Serial.print("| ");Serial.print(curPos.F);Serial.println(" ");
    Serial.print(curPos.L);Serial.print("   ");Serial.println(curPos.R);
    Serial.println();

    bool bfront,bleft,bright;
    bfront=curPos.F==prePos.F;
    bleft=curPos.L==prePos.L;
    bright=curPos.R==prePos.R;

    if(curPos.F != 1 && curPos.R==1 && curPos.L ==1)
       frontf();
    if(bfront==0 && bleft==1 && bright==0)
    {
       if(curPos.F==1 && curPos.R==0)
          rightf();
       else if(curPos.F==0
    }
    else if(!bfront && bleft && bright)
       backf();
    else if(front && !bleft && bright)
       rightf();
    else if(front && bleft && !bright)
       leftf();

    prePos.L=curPos.L;
    prePos.R=curPos.R;
    prePos.F=curPos.F;

   
}
void frontf()
{
  Serial.print("frontf");
  digitalWrite(vel_motor_lef, HIGH);
  digitalWrite(vel_motor_rig, HIGH);
  digitalWrite(e1, LOW);
  digitalWrite(e2, HIGH);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  delay(500);
  
}
void leftf() // function to make the robot turn 90º to the left if there is no front and right exit;
{
  Serial.print("leftf");
  digitalWrite(vel_motor_lef, HIGH);
  digitalWrite(vel_motor_rig, HIGH);

  digitalWrite(e1, HIGH);
  digitalWrite(e2, LOW);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  delay (500);

}

void rightf () // function to make the robot turn 90º to the right if there is no exit ahead or left;
{

   Serial.print("rightf");
  digitalWrite(vel_motor_lef, HIGH);
  digitalWrite(vel_motor_rig, HIGH);

  digitalWrite(e1, LOW);
  digitalWrite(e2, HIGH);
  digitalWrite(d1, LOW);
  digitalWrite(d2, HIGH);
  delay(500);
}

void backf () // function to make the robot turn 180º if there is no front, right and left exit;
{
  Serial.print("backf");
  digitalWrite(vel_motor_lef, HIGH);
  digitalWrite(vel_motor_rig, HIGH);
  digitalWrite(e1, LOW);
  digitalWrite(e2, HIGH);
  digitalWrite(d1, HIGH);
  digitalWrite(d2, LOW);
  delay(1200);
}
  
