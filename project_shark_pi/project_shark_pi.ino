/* Program to control the Shark Robot, 
it controls the motors, reads the encoder and establishes a communication with ROS
Project developed during the fall of 2018
*/

#define USE_USBCON //Useful to synchronize ROS and Arduino DUE

#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32MultiArray.h>
#include <Encoder.h>


/* ------------------------- Pins declaration -----------------------*/
//Motor one
const int enA = 8;
const int in1 = 4;
const int in2 = 3;
//Motor two
const int enB = 9;
const int in3 = 6;
const int in4 = 5;
//Joystick pins
const int SW_pin = 2;
const int X_pin = A0;
const int Y_pin = A1;
//Encoders pins
const int enc_left_A = 22;
const int enc_left_B = 23;
const int enc_right_A = 24;
const int enc_right_B = 25;

/* --------------------------- Constants ---------------------------*/

//Physical parameters of the robot
const double R = 0.06;//Radius of the wheels [m]
const double L = 0.55;//Length from wheel to wheel [m]

//Counts Per Revolution of the encoders
const int CPR = 4480;

const int MAX_PWM = 255;

/* --------------------- Custom data types -------------------------*/

// Represents a wheel
struct Wheel {
  double w;     //Angular speed set by ROS [rad/s]
  double real_w;//Actual speed [rad/s]
  long new_count, old_count;//Encoder data
  int pwm; // PWM needed to achieve the desired speed
};

/* ----------------------- Globals ---------------------------------*/
Wheel wheel_left;
Wheel wheel_right;

//Movement variables read from the Joystick
int horizontal, vertical;

// Variables to monitor the time
unsigned long init_time, end_time;
double t;

//ROS object to manage the node
ros::NodeHandle nh;

// Declaration of Publishers to ROS topics
std_msgs::Float32MultiArray array_msg;
ros::Publisher speed_publisher("wheels_speed", &array_msg);

std_msgs::String str_msg1;
ros::Publisher chatter2("info", &str_msg1);

//Attach the pins of the encoder to the Encoder object
Encoder enc_left(enc_left_A, enc_left_B);
Encoder enc_right(enc_right_A, enc_right_B);

/*---------------- Motors logic -----------------------*/

// Callback invoked when the program receives information from the teleoperation station
void motors_cb( const geometry_msgs::Twist& cmd_msg){
  double v; //Linear speed
  double w; //Angular speed
  //Get the data from the Twist message and compute the angular speed of the wheels
  v = cmd_msg.linear.x;
  w = cmd_msg.angular.z;


  wheel_right.w = (2.0*v + w*L) / (2.0*R);
  wheel_left.w  = (2.0*v - w*L) / (2.0*R);

}


void backward(int wr, int wl){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, wr);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, wl); 

}

void forward(int wr, int wl){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, wr);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, wl);
}

void turn_left(int wr, int wl){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH); 
  analogWrite(enA, wr);  
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW);
  analogWrite(enB, wl);
}

void turn_right(int wr, int wl){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, wr);  
  digitalWrite(in3, LOW); 
  digitalWrite(in4, HIGH);
  analogWrite(enB, wl);
}

void stopped(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW); 
  analogWrite(enA, 0);  
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW);
  analogWrite(enB, 0);
}

/* ------------------   Extra functions -----------------------------*/
void publish_speed(double wr, double wl) {
  array_msg.data[0] = wl;
  array_msg.data[1] = wr;
  speed_publisher.publish(&array_msg);
}

double compute_speed(Wheel wheel, double delta_time) {
  long counts;
  double w;
  
  counts = wheel.new_count - wheel.old_count;
  w = counts/((double) CPR * delta_time);
  w *= 2.0*PI;
  return w;
}
/*  Controller */
double u_ant = 0, e_ant = 0;

//PI controler
int get_speed_controlled(int ref, int w_real, double delta_time) {
  // Variables for the controller
  double u, y, e;
  double ki, kp, A, B, C, T;
  ref = abs(ref);
  y   = abs(w_real);

  ref = ref *  MAX_PWM/15.7;
  y   = y   *  MAX_PWM/15.7; 
  
  e   = ref - y;
  
  ki = 0.5;
  kp = 5;
  T = delta_time;
  
  A = 10000;
  B = (kp  + (ki*T)/2.0) * 10000.0;
  C = (-kp + (ki*T)/2.0) * 10000.0;
  
  u = A*u_ant + B*e + C*e_ant;
  u = (double)(u / 10000.0); //Divide by the factor of 10,000

  if(u > 255)    u = 255;
  else if(u < 0) u =   0;

  //Update values
  e_ant = e;
  u_ant = u;
  
  return (int)u;
}


/*------------------------Main program ------------------------------*/
//ROS topics  to be subscribed
ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", motors_cb);

void setup()
{
  // Set the pin mode for all inputs and outputs
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  //analogWriteResolution(12);

  // Start the node
  nh.initNode();

  // Define the MultiArray params, it will contain 2 float numbers in 1D
  // Set the dimension of the array
  array_msg.layout.dim = (std_msgs::MultiArrayDimension*) malloc(sizeof(std_msgs::MultiArrayDimension) * 2);
  array_msg.layout.dim[0].label = "wheels_speed";
  array_msg.layout.dim[0].size = 2;
  array_msg.layout.dim[0].stride = 1;// To achieve array_msg(i) = data[i]
  array_msg.layout.data_offset = 0;
  array_msg.data = (float*) malloc(sizeof(float)*8);
  array_msg.data_length = 2;

  // Start the communication to and from topics
  nh.advertise(speed_publisher);
  nh.advertise(chatter2);
  nh.subscribe(sub);
}

void loop(){
  //Start timer
  init_time = millis();

  //Read data from the Joystick in case of manual operation
  horizontal = analogRead(Y_pin);
  vertical   = analogRead(X_pin);
  int button = digitalRead(SW_pin); 

  //Manual mode operation
  if(!button) { 
    if      (vertical < 620){
          backward(MAX_PWM, MAX_PWM);
    }
    else if (vertical > 900){
          forward(MAX_PWM, MAX_PWM);          
    }
    else if(horizontal < 620){
          turn_left(MAX_PWM, MAX_PWM); 
    }
    else if(horizontal > 900){
          turn_right(MAX_PWM, MAX_PWM);
    }
    else {
      stopped();
    }
  } 
  else {// Teleoperation

      //Implement proportional control algorithm [rad/s]
      wheel_right.pwm = get_speed_controlled(wheel_right.w, wheel_right.real_w, t);
      wheel_left.pwm =  get_speed_controlled(wheel_left.w,  wheel_left.real_w,  t);
      
      
      if(wheel_right.w > 0.0 && wheel_left.w > 0.0) {
         forward(wheel_right.pwm, wheel_left.pwm);
      }
      else if(wheel_right.w < 0.0 && wheel_left.w < 0.0) {
        backward(wheel_right.pwm, wheel_left.pwm);
      }
      else if(wheel_right.w > 0.0 && wheel_left.w < 0.0) {
        turn_right(wheel_right.pwm, wheel_left.pwm); 
      }
      else if(wheel_right.w < 0.0 && wheel_left.w > 0.0) {
        turn_left(wheel_right.pwm, wheel_left.pwm);
      }
      else {
        stopped();
      }
  }

  // Measure the actual wheels speed and publish the value

  //Stop timer and compute total time
  delay(10);
  end_time = millis();
  t = end_time - init_time;
  //Convert to seconds
  t = t / 1000.0;

  //Read new data from encoders
  wheel_left.new_count  = enc_left.read();
  wheel_right.new_count = enc_right.read();
  
  //Get the actual speed 
  wheel_left.real_w  = compute_speed(wheel_left, t);
  wheel_right.real_w = compute_speed(wheel_right, t);
  
  publish_speed(wheel_left.real_w, wheel_right.real_w);

  // Update the number of counts of the encoder
  if (wheel_left.new_count != wheel_left.old_count) {
    wheel_left.old_count = wheel_left.new_count;
  }
  if (wheel_right.new_count != wheel_right.old_count) {
    wheel_right.old_count = wheel_right.new_count;
  }


  
  nh.spinOnce();
  delay(1);
}
