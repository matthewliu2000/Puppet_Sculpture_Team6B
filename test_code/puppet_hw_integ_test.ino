// Basic demo for accelerometer readings from Adafruit MSA301

#include <Wire.h>
#include <Adafruit_MSA301.h>
#include <Adafruit_Sensor.h>

// audio libraries
#include <SD.h>
#include <SPI.h>
#include <Audio.h>

//Declare Variables and Objects
Adafruit_MSA301 msa;
float X_out, Y_out, Z_out;                //Outputs
Servo servoRH, servoLH, servoRL, servoLL; //servos 

// Pin Assignments
const int servoRH_pin = 5;
const int servoLH_pin = 6;
const int servoRL_pin = 9;
const int servoLL_pin = 10;
const int speaker_pin = 3;

void setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MSA301 test!");
  
  // Try to initialize!
  if (! msa.begin()) {
    Serial.println("Failed to find MSA301 chip");
    while (1) { delay(10); }
  }
  Serial.println("MSA301 Found!");

  //msa.setDataRate(MSA301_DATARATE_31_25_HZ);
  Serial.print("Data rate set to: ");
  switch (msa.getDataRate()) {
    case MSA301_DATARATE_1_HZ: Serial.println("1 Hz"); break;
    case MSA301_DATARATE_1_95_HZ: Serial.println("1.95 Hz"); break;
    case MSA301_DATARATE_3_9_HZ: Serial.println("3.9 Hz"); break;
    case MSA301_DATARATE_7_81_HZ: Serial.println("7.81 Hz"); break;
    case MSA301_DATARATE_15_63_HZ: Serial.println("15.63 Hz"); break;
    case MSA301_DATARATE_31_25_HZ: Serial.println("31.25 Hz"); break;
    case MSA301_DATARATE_62_5_HZ: Serial.println("62.5 Hz"); break;
    case MSA301_DATARATE_125_HZ: Serial.println("125 Hz"); break;
    case MSA301_DATARATE_250_HZ: Serial.println("250 Hz"); break;
    case MSA301_DATARATE_500_HZ: Serial.println("500 Hz"); break;
    case MSA301_DATARATE_1000_HZ: Serial.println("1000 Hz"); break;
  }

  //msa.setPowerMode(MSA301_SUSPENDMODE);
  Serial.print("Power mode set to: ");
  switch (msa.getPowerMode()) {
    case MSA301_NORMALMODE: Serial.println("Normal"); break;
    case MSA301_LOWPOWERMODE: Serial.println("Low Power"); break;
    case MSA301_SUSPENDMODE: Serial.println("Suspend"); break;
  }

  //msa.setBandwidth(MSA301_BANDWIDTH_31_25_HZ);
  Serial.print("Bandwidth set to: ");
  switch (msa.getBandwidth()) {
    case MSA301_BANDWIDTH_1_95_HZ: Serial.println("1.95 Hz"); break;
    case MSA301_BANDWIDTH_3_9_HZ: Serial.println("3.9 Hz"); break;
    case MSA301_BANDWIDTH_7_81_HZ: Serial.println("7.81 Hz"); break;
    case MSA301_BANDWIDTH_15_63_HZ: Serial.println("15.63 Hz"); break;
    case MSA301_BANDWIDTH_31_25_HZ: Serial.println("31.25 Hz"); break;
    case MSA301_BANDWIDTH_62_5_HZ: Serial.println("62.5 Hz"); break;
    case MSA301_BANDWIDTH_125_HZ: Serial.println("125 Hz"); break;
    case MSA301_BANDWIDTH_250_HZ: Serial.println("250 Hz"); break;
    case MSA301_BANDWIDTH_500_HZ: Serial.println("500 Hz"); break;
  }

  //msa.setRange(MSA301_RANGE_2_G);
  Serial.print("Range set to: ");
  switch (msa.getRange()) {
    case MSA301_RANGE_2_G: Serial.println("+-2G"); break;
    case MSA301_RANGE_4_G: Serial.println("+-4G"); break;
    case MSA301_RANGE_8_G: Serial.println("+-8G"); break;
    case MSA301_RANGE_16_G: Serial.println("+-16G"); break;
  }

  //msa.setResolution(MSA301_RESOLUTION_14 );
  Serial.print("Resolution set to: ");
  switch (msa.getResolution()) {
    case MSA301_RESOLUTION_14: Serial.println("14 bits"); break;
    case MSA301_RESOLUTION_12: Serial.println("12 bits"); break;
    case MSA301_RESOLUTION_10: Serial.println("10 bits"); break;
    case MSA301_RESOLUTION_8: Serial.println("8 bits"); break;
  }
  // Pin Assignments
  pinMode(speakerPin,OUTPUT);
  pinMode(servoRH_pin,OUTPUT);
  pinMode(servoLH_pin,OUTPUT);
  pinMode(servoRL_pin,OUTPUT);
  pinMode(servoLL_pin,OUTPUT);
  // Map Servos
  // RH - right hand, LH - left hand
  // RL - right leg,  LL - left leg
  servoRH.attach(servoRH_pin);
  servoLH.attach(servoLH_pin);
  servoRL.attach(servoRL_pin);
  servoLL.attach(servoLL_pin);
}

void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g; // a for acceleration, g for gyroscope

  // Print and Set Gyroscope values for accelerometer
  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  X_out = g.gyro.x;
  
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Y_out = g.gyro.y;

  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Z_out = g.gyro.z;

  Serial.println(" rad/s");
  ///////////////////////////////////////////////
  // Play Some Notes and make Some motor movements
  // based on some gyroscope measurments
  if ((-9 <X_out< -7) && (-9 <Y_out< -7) && (-9 <Z_out< -7)){
      servoRH.write(90);
      servoLH.write(90);
      servoRL.write(90);
      servoLL.write(90);
      tone(speaker_pin, 130); // C

  }
  if ((-1<X_out<1) && (-1<Y_out<1) && (-1<Z_out<1)){
      servoRH.write(180);
      servoLH.write(180);
      servoRL.write(180);
      servoLL.write(180);
      tone(speaker_pin, 146); // D

  }
  if ((7<X_out< 9) && (7<Y_out<9) && (7<Z_out<9)){
      servoRH.write(135);
      servoLH.write(135);
      servoRL.write(135);
      servoLL.write(135);
      tone(speaker_pin, 174); // E
  }
  ///////////////////////////////////////////////
  Serial.println("");
 
  delay(100); 
}
