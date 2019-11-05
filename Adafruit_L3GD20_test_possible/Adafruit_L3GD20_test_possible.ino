/*************************************************** 
  This is an example for the Adafruit Triple-Axis Gyro sensor

  Designed specifically to work with the Adafruit L3GD20 Breakout 
  ----> https://www.adafruit.com/products/1032

  These sensors use I2C or SPI to communicate, 2 pins (I2C) 
  or 4 pins (SPI) are required to interface.

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Kevin "KTOWN" Townsend for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h> 
#include <Adafruit_L3GD20.h>

// Comment this next line to use SPI
#define USE_I2C

#ifdef USE_I2C
  // The default constructor uses I2C
  Adafruit_L3GD20 yaw1;
#else
  // To use SPI, you have to define the pins
  #define GYRO_CS 4 // labeled CS
  #define GYRO_DO 5 // labeled SA0
  #define GYRO_DI 6  // labeled SDA
  #define GYRO_CLK 7 // labeled SCL
  Adafruit_L3GD20 gyro(GYRO_CS, GYRO_DO, GYRO_DI, GYRO_CLK);
#endif
long unsigned int timer,tp;
float yaw=0.0,timestep;

void setup() 
{
  Serial.begin(115200);
  
  // Try to initialise and warn if we couldn't detect the chip
//   if (!yaw1.begin(yaw1.L3DS20_RANGE_250DPS))
  //if (!gyro.begin(gyro.L3DS20_RANGE_500DPS))
  if (!yaw1.begin(yaw1.L3DS20_RANGE_2000DPS))
  {
    Serial.println("Oops ... unable to initialize the L3GD20. Check your wiring!");
    while (1);
  }
  yaw1.calibrateGyro();
  delay(100);
  yaw1.setThreshold(7);
  delay(100);
}

void loop() 
{
  timer = millis();
  timestep = (timer - tp)/1000.0;
  yaw1.readGyro();
  yaw = yaw + yaw1.gyro.z*timestep;
//  Serial.print("X: "); Serial.print(yaw1.gyro.x);   Serial.print(" ");
  Serial.print(" raw z: "); Serial.print(yaw1.gyro.z);   Serial.print(" ");
  Serial.print("Z: "); Serial.println(yaw); Serial.print(" ");
//  delay(100);
tp = timer;
}
