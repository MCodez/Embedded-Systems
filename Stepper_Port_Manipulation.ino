

/* Biderectional Stepper Motor Interfacing with Arduino NANO - Using PORT Manipulation
 *  Code Developed By: LALIT ARORA 
 *  Electronics and Communication Engineer, NSIT
 * 
 * Circuit Connections:
 * L293D : pins 1,9 enable -> +5V 
 *         pins 3,6,11,14 : Motor Coils . (Check the ends of coil <3,4> and <11,14> using Multimeter in Resistance Mode. {IF resistance if Low : Same coil ends. ELSE Different coils ends.}
 *         pins 4,5,12,13 : GND
 *         pin 8 : Motor Supply ( See Datasheet of Motor: 5V/9V/12V accordingly)
 *         pin 16: L293D Supply : ->5V
 *         pins 2,7,10,15 : Connected to D2,D3,D4,D5 of ARDUINO NANO ( Can use ARDUINO UNO or any other version).
 * NANO :  Supply Vin=9V or any voltage between 6-20V (unregulated or regulated).
 * MINI USB : To program NANO or other usb type for other variants.
 */

// Setup Function Declaration
void setup() {
Serial.begin(9600); // to begin serial
DDRD=B11111111; // make all pins of PORT D as output
}

// Loop Function Declaration
void loop() {
// Call Appropriate Function from the ones declared below.
}


// motor running clockwise - HALF DRIVE (4 pulses)
void motor_clc_4steps()
{
  PORTD=B00011000; // 0x06H
  delay(100);
  PORTD=B00010100; // 0x05H
  delay(100);
  PORTD=B00100100; // 0x09H
  delay(100);
  PORTD=B00101000;  //0x0AH
  delay(100);
}
// motor running anti-clockwise - HALF DRIVE (4 pulses)
void motor_aclc_4steps()
{
  PORTD=B00101000; // 0x0AH
  delay(100);
  PORTD=B00100100; // 0x09H
  delay(100);
  PORTD=B00010100; // 0x05H
  delay(100);
  PORTD=B00011000;  //0x06H
  delay(100);
}
// motor running anti-clockwise - FULL DRIVE (8 pulses)
void motor_aclc_8steps()
{
PORTD=B00010000; //0x04H
delay(100);
PORTD=B00011000; //0x06H
delay(100);
PORTD=B00001000; // 0x02H
delay(100);
PORTD=B00101000; // 0x0AH
delay(100);
PORTD=B00100000; // 0x08H
delay(100);
PORTD=B00100100; // 0x09H
delay(100);
PORTD=B00000100; //0x01H
delay(100);
PORTD=B00010100; //0x05H
delay(100);
}
// motor running clockwise - FULL DRIVE (8 pulses)
void motor_clc_8steps()
{
PORTD=B00010100; //0x05H
delay(100);
PORTD=B00000100; //0x01H
delay(100);
PORTD=B00100100; //0x09H
delay(100);
PORTD=B00100000; //0x08H
delay(100);
PORTD=B00101000;//0x0AH
delay(100);
PORTD=B00001000;//0x02H
delay(100);
PORTD=B00011000; //0x06H
delay(100);
PORTD=B00010000;  //0x04H
delay(100);
}
/* 
 *  Hex codes commented alongside the PORTD commands are written assuming that <D2=D0,D3=D1,D4=D2,D5=D3>. 
 *  This will help in coding/programming various Microcontrollers and even Microprocessors if you connect your stepper motor with pins <D0,D1,D2,D3>.
*/
