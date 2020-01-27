#include "Stream.h"
#define packet_address 128
void Write_command(byte data_command, byte value);
void autobaud(Stream*  , bool wait = true);
void motor(byte motor , float power);

void setup() {
  Serial2.begin(19200);
  autobaud(&Serial2);
  Serial.begin(115200);
  
}
Stream *stream = &Serial2;
int i=80;
unsigned long timer;
void loop() {
  timer = micros();
//  for( i = 0; i<100 ;++i){
  motor(2, i);
//  delay(100);
//  }
//  delay(2000);
//  for( i = 0 ; i<100 ;++i){
//  motor(2, -i);
//  delay(100);
//  }
//  delay(2000);
Serial.print("timer=");
Serial.println(micros() - timer);
}
void autobaud(Stream *stream, bool wait)
{
  if (wait)
    delay(1500);

  stream->write(0xAA);

  stream->flush();

  if (wait)
    delay(500);
}

void Write_command(byte data_command , byte value)
{
  stream->write(packet_address);
  stream->write(data_command );
  stream->write(value);
  stream->write((packet_address + data_command + value) & B01111111);
}
void motor(byte motor , float power)
{
  if (motor < 1 || motor > 2)
    return;
  power = constrain(power , -100 , 100);
  Write_command((motor == 2 ? 4 : 0) + (power < 0 ? 1 : 0) , (byte)abs(power));

}
