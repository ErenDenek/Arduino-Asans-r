#include <Servo.h>
#define a 20
#define b 21
#define c 22
#define d 23
#define e 24
#define f 25
#define g 26
bool buton1 = 0, buton2 = 0, buton3 = 0, x = 0, buton = 0;
int ldr1 = 0, ldr2 = 0, ldr3 = 0;
int Durum1, Durum2, Durum3, kat = 0;

int Durum[3];

int output[10] = {a, b, c, d, e, f, g, 6, 5, 4};
int input[6] = {2, 8, 9, A0, A2, A3};

Servo myservo1;
Servo myservo2;
Servo myservo3;

unsigned long zaman1 = 0, zaman2, zaman3, zaman4, zaman;

void setup() {
  Serial.begin(250000);

  myservo1.attach(12);
  myservo2.attach(10);
  myservo3.attach(11);

  for (int i = 0; i <= 9; i++)pinMode(output[i], OUTPUT);
  for (int j = 0; j <= 5; j++)pinMode(input[j], INPUT);

}

void loop() {

  Durum1 = but(2, 1);
  Durum2 = but(8, 2);
  Durum3 = but(9, 3);
  sens();
  katSegment();

  zaman = millis();

  while (Durum2 == 1) {

flag2:
    zaman = millis();
    sens();

    if (kat == 1 )up();
    if (kat == 3 )down();
    if (kat != 2)goto flag2;

    while (kat == 2) {

      Serial.println("SERVO ON");
      myservo1.write(180);

      if (millis() - zaman > 3000) {

        zaman = millis();
        Serial.println("SERVO OFF");
        myservo1.write(0);
        Durum2 = 0;
        break;

      }
    }
  }

  while (Durum1 == 1)  {

flag1:
    
    zaman = millis();
    sens();
    
    if (!(kat == 1))down();
    if (kat != 1)goto flag1;
    
    while (kat == 1)  {
      Serial.println("SERVO ON");
      myservo2.write(180);
      if (millis() - zaman > 3000)  {
        
        zaman = millis();
        Serial.println("SERVO OFF");
        myservo2.write(0);
        Durum1 = 0;
        break;
      
      }
    }
  }
  
  while (Durum3 == 1){

flag3:
    zaman = millis();
    sens();

    if (!(kat == 3))up();
    if (kat != 3)goto flag3;
    
    while (kat == 3){
      
      Serial.println("SERVO ON");
      myservo3.write(180);
      
      if (millis() - zaman > 3000)  {
        zaman = millis();
        Serial.println("SERVO OFF");
        myservo3.write(0);
        Durum3 = 0;
        break;
      
      }
    }
  }  
  
  Serial.print(kat); Serial.println(".KATTA Durdu");

}

void up()
{
  digitalWrite(6, LOW);
  digitalWrite(4, HIGH);
  
  if (millis() - zaman1 > 1){
    
    digitalWrite(5, HIGH);
    zaman1 = millis();
  }
  
  if (millis() - zaman2 > 1){
    
    digitalWrite(5, LOW);
    zaman2 = millis();
  }

  Serial.println("UP");

}

void down()
{
  digitalWrite(6, LOW);
  digitalWrite(4, LOW);

  if (millis() - zaman3 > 1){
    
    digitalWrite(5, HIGH);
    zaman3 = millis();
  }
  if (millis() - zaman4 > 1){
    
    digitalWrite(5, LOW);
    zaman4 = millis();
  }
  
  Serial.println("down");  
}

void sens()
{

  ldr1 = analogRead(A1);
  ldr2 = analogRead(A2);
  ldr3 = analogRead(A0);
  
  if (ldr1 <= 700)kat = 3;
  if (ldr2 <= 800)kat = 2;
  if (ldr3 <= 700)kat = 1;


}
void button(int pin)
{
  
  if (digitalRead(pin) == 1 && x == 0) {
    x = 1;
    if (Durum[pin] == 0) Durum[pin] = 1;
    else if (Durum[pin] == 1) Durum[pin] = 0;
  }
  else if (digitalRead(pin) == 0 && x == 1) {
    x = 0;
  }
  Serial.print(Durum[pin]);
  Serial.println();
}
void katSegment()
{
  
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  
  switch (kat)
  {
    case 1:
      digitalWrite(a, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH); break;
    case 2:
      digitalWrite(c, HIGH);
      digitalWrite(f, HIGH);  break;
    case 3:
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);   break;
  }
}

void but(int but_pin, int but_kat)
{
  if (digitalRead(but_pin) == 1 && x == 0) {
    x = 1;
    if (Durum[but_kat] == 0) Durum[but_kat] = 1;
    else if (Durum[but_kat] == 1) Durum[but_kat] = 0;
  }
  else if (digitalRead(but_pin) == 0 && x == 1) {
    x = 0;
  }

  return Durum[but_kat];

}
