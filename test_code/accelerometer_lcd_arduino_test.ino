#include <Wire.h>  // Wire library - used for I2C communication
#include <LiquidCrystal.h>


// #### May Need to Change #s ####
int ADXL345 = 0x53; // The ADXL345 sensor I2C address

float X_out, Y_out, Z_out;  // Outputs

// #### May Need to Change #s ####
LiquidCrystal lcd(7,8,9,10,11,12); // initialize library with the numbers of the interface pins

void setup() {
  Serial.begin(9600); // Initiate serial communication for printing the results on the Serial monitor
  Wire.begin(); // Initiate the Wire library
  // Set ADXL345 in measuring mode
  Wire.beginTransmission(ADXL345); // Start communicating with the device
  Wire.write(0x2D); // Access/ talk to POWER_CTL Register - 0x2D

// #### May Need to Change #s ####
  // Setup LCD's columns and rows
  lcd.begin(16,1);
  lcd.clear();

  // Enable measurement
  Wire.write(8); // (8dec -> 0000 1000 binary) Bit D3 High for measuring enable 
  Wire.endTransmission();
  delay(10);
}

void loop() {
  // === Read acceleromter data === //
  Wire.beginTransmission(ADXL345);
  Wire.write(0x32); // Start with register 0x32 (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(ADXL345, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  X_out = ( Wire.read()| Wire.read() << 8); // X-axis value
  X_out = X_out/256; //For a range of +-2g, we need to divide the raw values by 256, according to the datasheet
  Y_out = ( Wire.read()| Wire.read() << 8); // Y-axis value
  Y_out = Y_out/256;
  Z_out = ( Wire.read()| Wire.read() << 8); // Z-axis value
  Z_out = Z_out/256;

  // LCD Prints
  // #### May Need to Change #s before/after testing ####
  lcd.setCursor(0,0);
  lcd.print(X_out);
  lcd.setCursor(6,0);
  lcd.print(Y_out);
  lcd.setCursor(12,0)
  lcd.print(Z_out);

  // Serial Monitor Check Prints
  Serial.print("Xa= ");
  Serial.print(X_out);
  Serial.print("   Ya= ");
  Serial.print(Y_out);
  Serial.print("   Za= ");
  Serial.println(Z_out);

  // #### May Need to Change #s before/after testing ####
  // Prevent LCD from updating too fast and become unreadable
  delay(50)
}
