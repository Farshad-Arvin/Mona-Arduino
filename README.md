# Mona-Arduino

This Sketch file prepared for MRAS Lab at EEE University of Manchester

It's a single file including all the required functions

Board: Arduino Pro or Pro Mini, ATMega 328P (3.3 V, 8MHz) 
Serial port: 9600 bps


List of functions:

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
