// The current Sketch prepared for use in MRAS Lab at EEE UoM (March 2018)
// The code has four sections: 
//  1) Variables/constant/parameters 
//  2) Control library for motion, sensory system, and other IOs
//  3) Setup() (Line 173) function for initialisation of modules   
//  4) Loop() (line 200) function which users will write their code in


// List of all functions:

void motors(int left, int left_dir, int right, int right_dir);
void turn(int turning_direction, int turning_speed, int turning_delay);
void IR_proximity_read(int IR_enable_inp);
int check_obstacle(int IR_enable_inp);
void motors_stop();
int obstacle_avoidance(int IR_enable_inp);
void readLight();
void LED_top(int LED_enable_inp);
void LED_bottom(int LED_enable_inp);
void LED_module(int LED_enable_inp);
void printIR(int IR_enable_inp);
void printLight();

//============================================
//    Variables/ Constants
//============================================

//motors IOs  ---------------------------
int Motor_left_PWM = 10;      // D10 for PWM (0 min -255 max)
int Motor_left_direction = 5; // D5 for Direction 0 Forward - 1 Reverse
int Motor_right_PWM = 9;        // D9 for PWM  
int Motor_right_direction = 6;  // D6 for Direction
int left_speed=40;             // Initial speed for left motor 
int right_speed=40;             // Initial speed for right motor 
#define Forward 0              // Direction code
#define Reverse 1              // Direction code
#define Left    2              // Direction code
#define Right   3              // Direction code

//LEDs  ---------------------------------
int LED1 = 13;        //D13 RED LED on top
int LED2 = 12;        //D12 bottom front LED
int Module_LED = 11;  //D11 for Light Module LED

//Infra-Red -----------------------------
int IR_enable=4;       // D4 for IR Emitters
#define IR_right_sensor       A7   // Analog port 
#define IR_right_front_sensor A0
#define IR_front_sensor       A1
#define IR_left_front_sensor  A2
#define IR_left_sensor        A3
#define ON   1
#define OFF  0
int IR_threshold= 950; // 0 white close obstacle -- 1023 no obstacle
//global values of IR reading from proximity sensors
int IR_right,IR_right_front,IR_front,IR_left_front,IR_left;

//Light Sensor --------------------------
#define Light_left_sensor    A5   // Analog port
#define Light_right_sensor   A4
int Light_left, Light_right; //global variables for light
#define ON   1
#define OFF  0
//============================================
//    Control Libraries
//============================================

// motion-----------------------------
void motors(int left, int left_dir, int right, int right_dir){
// left: PWM max 255, right: PWM max 255
  analogWrite(Motor_right_PWM,right);            // right motor speed
  digitalWrite(Motor_right_direction,right_dir); //right motor direction
  analogWrite(Motor_left_PWM,left);              // left motor speed
  digitalWrite(Motor_left_direction,left_dir);   //left motor direction
}

void turn(int turning_direction, int turning_speed, int turning_delay){
  if (turning_direction==Left)
    motors( turning_speed , Reverse , turning_speed , Forward);  // CW turn
  else
    motors( turning_speed , Forward , turning_speed , Reverse);  //CCW turn
  delay(turning_delay);   // gives time to turn robot
  //after turn backs to forward speed 
  motors( left_speed , Forward , right_speed , Forward); 
}

void motors_stop(){ // set speeds to 0
  analogWrite(Motor_right_PWM,0); // right motor =0
  analogWrite(Motor_left_PWM, 0); // left motor =0
}

// Sensory reading --------------------------------------
void IR_proximity_read(int IR_enable_inp){    // read front IR 
  digitalWrite(IR_enable, IR_enable_inp);  //IR ON or OFF
  IR_right=analogRead(IR_right_sensor);
  IR_right_front=analogRead(IR_right_front_sensor);
  IR_front=analogRead(IR_front_sensor);
  IR_left_front=analogRead(IR_left_front_sensor);
  IR_left=analogRead(IR_left_sensor);
}

int check_obstacle(int IR_enable_inp){
    IR_proximity_read(IR_enable_inp);  // IR emitter on or off
    if (IR_front<IR_threshold || IR_right<IR_threshold || IR_right_front<IR_threshold || IR_left<IR_threshold || IR_left_front<IR_threshold)
      return 1;
    else 
      return 0;
}

int obstacle_avoidance(int IR_enable_inp){
    if (check_obstacle(IR_enable_inp)==0) 
        return 0;
    LED_bottom(ON);
    if (IR_front<IR_threshold){ 
      motors( left_speed , Reverse , right_speed , Reverse);
      delay(200);
      if (IR_right_front<IR_left_front)
           turn(Right,60,300);
      else           
         turn(Left,60,300);
      LED_bottom(OFF);
      return 1;      
    }
      
    if( IR_right<IR_threshold || IR_right_front<IR_threshold)
         turn(Right,60,300);
    else           
         turn(Left,60,300);
    LED_bottom(OFF);
    return 1;      
}

// Read Light ---------------------------------------
void readLight(){
  Light_left=analogRead(Light_left_sensor);
  Light_right=analogRead(Light_right_sensor);
}

// LEDs
void LED_top(int LED_enable_inp){
  digitalWrite(LED1, LED_enable_inp);  
}
void LED_bottom(int LED_enable_inp){
  digitalWrite(LED2, LED_enable_inp);  
}
void LED_module(int LED_enable_inp){
  digitalWrite(Module_LED, LED_enable_inp);  
}

// Print output -------------------------------------
void printIR(int IR_enable_inp){
   IR_proximity_read(IR_enable_inp);  
   Serial.print("IR: ");
   Serial.print(IR_left); 
   Serial.print(",");
   Serial.print(IR_left_front); 
   Serial.print(",");
   Serial.print(IR_front); 
   Serial.print(",");
   Serial.print(IR_right_front); 
   Serial.print(",");
   Serial.println(IR_right); 
}

void printLight(){
  readLight();  // 0 dark, 1023 max light
  Serial.print("Light Left = ");
  Serial.print(Light_left);
  Serial.print(" , Right =");
  Serial.println(Light_right);
}

//============================================
//    Initialisation
//============================================

void setup() {
  Serial.begin(9600);     //Serial port 
  Serial.println("HI MRAS>>");
  pinMode(Module_LED, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(IR_enable, OUTPUT);
  pinMode(Motor_left_PWM, OUTPUT);
  pinMode(Motor_right_PWM, OUTPUT);  
  motors_stop();
  //---test code --blink
  for (int i=0;i<5;i++){
    LED_top (ON);
    LED_bottom(ON);
    LED_module(ON);
    delay(50);
    LED_top (OFF);
    LED_bottom(OFF);
    LED_module(OFF);
    delay(200);
  }
}

//============================================
//    Main Loop for code
//============================================

void BEECLUST(){
   
  
}

void loop() {
  // put your main code here, to run repeatedly:
  // move robot forward
   motors( left_speed , Forward , right_speed , Forward);
   obstacle_avoidance(1);
}
