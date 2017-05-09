#include <Servo.h>
int a = 24, b = 25, c = 27, d = 28, e = 29, f = 23, g = 22,x;
int ldr1 = 0, ldr2 = 0, ldr3 = 0, kat = 0, Durum1, Durum2, Durum3;
int output[20] = {a, b, c, d, e, f, g, 6, 5, 4, 22, 23, 24, 25, 29, 27, 28, 11, 12};
int input[6] = {8, 9, 10, A0, A2, A3};
int State[3] = {Durum1, Durum2, Durum3};
unsigned long zaman1 = 0, zaman2, zaman3, zaman4, zaman;

Servo myservo1;
Servo myservo2;
Servo myservo3;

void setup() {
  myservo1.attach(12);
  myservo2.attach(13);
  myservo3.attach(11);
  for (int i = 0; i <= 20; i++)pinMode(output[i], OUTPUT);
  for (int j = 0; j <= 5; j++)pinMode(input[j], INPUT);
}
void loop() {
  State[0] = button(8, 1);
  State[1] = button(9, 2);
  State[2] = button(10, 3);
  sens();
  katSegment();
  zaman = millis();
  while (State[2] == 1) {
flag2:
    zaman = millis();
    sens();
    if (kat == 1 ) up();
    if (kat == 3 ) down();
    if (kat != 2) goto flag2;
    while (kat == 2) {
      myservo1.write(180);
      if (millis() - zaman > 3000) {
        zaman = millis();
        myservo1.write(0);
        State[2] = 0;
        break;
      }
    }
  }
  while (State[1] == 1)  {
flag1:
    zaman = millis();
    sens();
    katSegment();
    if (!(kat == 1))down();
    if (kat != 1)goto flag1;
    while (kat == 1)  {
      myservo2.write(180);
      if (millis() - zaman > 3000)  {
        zaman = millis();
        myservo2.write(0);
        State[1] = 0;
        break;
      }
    }
  }
  while (State[3] == 1) {
flag3:
    zaman = millis();
    sens();
    if (!(kat == 3))up();
    if (kat != 3)goto flag3;
    while (kat == 3) {
      myservo3.write(180);
      if (millis() - zaman > 3000)  {
        zaman = millis();
        myservo3.write(0);
        State[3] = 0;
        break;
      }
    }
  }
}
void up()
{
  digitalWrite(6, LOW);
  digitalWrite(4, HIGH);
  if (millis() - zaman1 > 1) {
    digitalWrite(5, HIGH);
    zaman1 = millis();
  }
  if (millis() - zaman2 > 1) {
    digitalWrite(5, LOW);
    zaman2 = millis();
  }
  katSegment();
}
void down()
{
  digitalWrite(6, LOW);
  digitalWrite(4, LOW);
  if (millis() - zaman3 > 1) {

    digitalWrite(5, HIGH);
    zaman3 = millis();
  }
  if (millis() - zaman4 > 1) {
    digitalWrite(5, LOW);
    zaman4 = millis();
  }
  katSegment();
}
void sens()
{
  ldr1 = analogRead(A1);
  ldr2 = analogRead(A2);
  ldr3 = analogRead(A3);
  if (ldr1 <= 890)kat = 3;
  if (ldr2 <= 900)kat = 2;
  if (ldr3 <= 900)kat = 1;
}
int button(int pin, int durum)
{
  int Durum[3];
  if (digitalRead(pin) == 1 && x == 0) {
    x = 1;
    if (Durum[durum] == 0) Durum[durum] = 1;
    else if (Durum[durum] == 1) Durum[durum] = 0;
  }
  else if (digitalRead(pin) == 0 && x == 1)x = 0;
  return Durum[durum];
}
void katSegment()
{
  for (int k = 0; k <= 6; k++)digitalWrite(k, LOW);
  switch (kat)
  {
    case 1:
      digitalWrite(a, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);  break;
    case 2:
      digitalWrite(c, HIGH);
      digitalWrite(f, HIGH);  break;
    case 3:
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);  break;
  }
}
