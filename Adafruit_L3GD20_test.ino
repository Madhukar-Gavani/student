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
Adafruit_L3GD20 gyro;
#else
// To use SPI, you have to define the pins
#define GYRO_CS 4 // labeled CS
#define GYRO_DO 5 // labeled SA0
#define GYRO_DI 6  // labeled SDA
#define GYRO_CLK 7 // labeled SCL
Adafruit_L3GD20 gyro(GYRO_CS, GYRO_DO, GYRO_DI, GYRO_CLK);
#endif

float sumX = 0, dgXAxis;
float sumY = 0, dgYAxis;
float sumZ = 0, dgZAxis;
float sigmaX = 0, thXAxis;
float sigmaY = 0, thYAxis;
float sigmaZ = 0, thZAxis, yaw;

long unsigned int timer, tp;
float timestep;
int samples = 1000;
void setup()
{
  Serial.begin(9600);

  // Try to initialise and warn if we couldn't detect the chip
  //   if (!gyro.begin(gyro.L3DS20_RANGE_250DPS))
  //if (!gyro.begin(gyro.L3DS20_RANGE_500DPS))
  if (!gyro.begin(gyro.L3DS20_RANGE_2000DPS))
  {
    Serial.println("Oops ... unable to initialize the L3GD20. Check your wiring!");
    while (1);
  }

  for (int i = 0; i < samples; ++i)
  {
    gyro.read();

    sumX += gyro.data.x;
    sumY += gyro.data.y;
    sumZ += gyro.data.z;

    sigmaX += gyro.data.x * gyro.data.x;
    sigmaY += gyro.data.y * gyro.data.y;
    sigmaZ += gyro.data.z * gyro.data.z;

    delay(5);
  }

  // Calculate delta vectors
  dgXAxis = sumX / samples;
  dgYAxis = sumY / samples;
  dgZAxis = sumZ / samples;

  // Calculate threshold vectors
   thXAxis = sqrt((sigmaX / 50) - (dgXAxis * dgXAxis));
    thYAxis = sqrt((sigmaY / 50) - (dgYAxis * dgYAxis));
    thZAxis = sqrt((sigmaZ / 50) - (dgZAxis * dgZAxis));
  
  delay(1000);
}

void loop()
{
  timer = millis();
  timestep = (timer - tp) / 1000.0;
  gyro.read();
  yaw  = yaw + (gyro.data.z - dgZAxis) * timestep;
  //  Serial.print("X: "); Serial.print((int)gyro.data.x);   Serial.print(" ");
  //  Serial.print("Y: "); Serial.print((int)gyro.data.y);   Serial.print(" ");
  Serial.print("Z: "); Serial.println(yaw); Serial.print(" ");
  //  delay(100);
  tp = timer;
}
