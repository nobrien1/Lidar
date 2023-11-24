#include <SoftwareSerial.h>
#include <math.h>

void setup() {
  Serial.begin(115200); // Init serial from microcontroller to computer
  Serial1.begin(115200); // Init serial from lidar sensor to microcontroller
}

void loop() {
  if(!Serial1.available()) return;

  unsigned int start = Serial1.read(); // first byte of packet, should be 0xFA

  if(start != 0xFA) return;

  unsigned int data[22]; // data array
  data[0] = start;
  int i = 1;

  while (i < 22) { // loop through reading all pieces of data
    if(!Serial1.available()) continue;
    data[i] = Serial1.read();
    i++;
  }


  Serial.write(data[0]); // start 0xfa
  Serial.write(data[1]); // 0 <= index < 90 (-0xa0)
  Serial.write(data[4]); // low distance at angle (index * 4) deg 
  Serial.write(data[5]); // high distance at angle (index * 4) deg
  Serial.write(data[8]); // low distance at angle (index * 4 + 1) deg
  Serial.write(data[9]); // high distance at angle (index * 4 + 1) deg
  Serial.write(data[12]);// low distance at angle (index * 4 + 2) deg
  Serial.write(data[13]);// high distance at angle (index * 4 + 2) deg
  Serial.write(data[16]);// low distance at angle (index * 4 + 3) deg
  Serial.write(data[17]);// high distance at angle (index * 4 + 3) deg
}
