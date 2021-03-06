

// definitions and declarations of variables in the code of the labyrinth-solving robot;

 #define vel_motor_lef 10 // controls the speed of the left engine;
 #define vel_motor_rig 11 // controls the speed of the right engine;
 #define e1 8 // controls left motor rotation direction;
 #define e2 9 // controls left motor rotation direction;
 #define d1 12 // controls the direction of rotation of the right motor;
 #define d2 7 // controls the direction of rotation of the right motor;

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
  Serial.print("front: ");
  Serial.println(front);

  digitalWrite(trigger_lef,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_lef,HIGH);
  delayMicroseconds(5);
  digitalWrite(trigger_lef,LOW);
  dur_left = pulseIn(echo_lef,HIGH);
  left = dur_left*0.034/2;
  Serial.print("left: ");
  Serial.println(left);

  digitalWrite(trigger_rig,LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_rig,HIGH);
  delayMicroseconds(5);
  digitalWrite(trigger_rig,LOW);
  dur_right = pulseIn(echo_rig,HIGH);
  right = dur_right*0.034/2;
  Serial.print("right: ");
  Serial.println(right);

  digitalWrite(vel_motor_lef, 0); // block to initialize theINPUTs with pulse 0 or off;
  digitalWrite(vel_motor_rig, 0); //
  digitalWrite(e1, 0); //
  digitalWrite(e2, 0); //
  digitalWrite(d1, 0); //
  digitalWrite(d2, 0); //

if(front>5) // if there is a free way forward it follows this logic below
  {
// the use of the four if´s below within this if are for controlling the driveability of the robot,
// in order to keep it following the right wall in a straight line;

 if (right >= 1 && right < 30
 
 
 
 ) // if the distance to the right wall is between 9 and 12 cm, the robot will
// keeps it straight;
{
       Serial.print("Front");
      digitalWrite(vel_motor_lef, HIGH);
       digitalWrite(vel_motor_rig, HIGH);

       digitalWrite(e1, HIGH);
       digitalWrite(e2, LOW);
       digitalWrite(d1, LOW);
       digitalWrite(d2,HIGH );

    }
  
  /*  if (right >= 13) // if the distance to the right wall is greater than or equal to 13 cm, the robot increases
// your left engine speed to approach the right wall;
   {
    delay(10);
      Serial.print("left");
      digitalWrite(vel_motor_lef, HIGH);
      digitalWrite(vel_motor_rig, HIGH);

      digitalWrite(e1, LOW);
      digitalWrite(e2, HIGH);
      digitalWrite(d1, LOW);
      digitalWrite(d2, HIGH);

   } */
   if (right <= 7) // if the distance to the right wall is less than or equal to 8 cm, the robot increases
       // your right engine speed to distance yourself from the right wall;
   {
    delay(10);
     Serial.print("right");
     digitalWrite(vel_motor_lef, HIGH);
     digitalWrite(vel_motor_rig, HIGH);

     digitalWrite(e1, HIGH);
     digitalWrite(e2, LOW);
     digitalWrite(d1, LOW);
     digitalWrite(d2, HIGH);

    }
    
  
  }


  if (left <= 20 && right > 20 && front <= 8) 
    {  
      delay(200);
      dirf ();     // if the distance in front is less than or equal to 8 cm,
                         // the distance to the right is greater than 20 cm and the distance
    }                    // the left is less than or equal to 20 cm it calls the dir () function;

  if (left > 20 && right > 20 && front <= 8) 
  {
    delay(200);
       dirf (); // if the distance in front is less than or equal to 8 cm,
      // the distance to the right is greater than 20 cm and the distance
  }     // the left is greater than 20 cm it calls the dir () function;

  if (right <= 20 && left > 20 && front <= 8) 
  {
    delay(200);
      leftf(); // if the distance in front is less than or equal to 8 cm,
                  // the distance to the right is less than or equal to 20 cm and the distance
  }                // the left is greater than 20 cm it calls the left () function;

  if (right <= 20 && left <= 20 && front <= 8)
  {
    delay(200);
       backf (); // if the distance in front is less than or equal to 8 cm,
                 // the distance to the right is less than or equal to 20 cm and the distance
  }              // the left is less than or equal to 20 cm it calls the function back ();   

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
  delay (700);

}

void dirf () // function to make the robot turn 90º to the right if there is no exit ahead or left;
{

   Serial.print("rightf");
  digitalWrite(vel_motor_lef, HIGH);
  digitalWrite(vel_motor_rig, HIGH);

  digitalWrite(e1, LOW);
  digitalWrite(e2, HIGH);
  digitalWrite(d1, LOW);
  digitalWrite(d2, HIGH);
  delay(800);
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



                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
