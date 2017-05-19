#include <Servo.h>
int a = 41;
int b = 43;
int c = 45;
int d = 35;
int e = 33;
int f = 39;
int g = 37;
int x;
int ldr1 = 0, ldr2 = 0, ldr3 = 0, kat = 0, Durum1, Durum2, Durum3, acil_count = 0, servis_count = 0, Kabin1, Kabin2, Kabin3, sayac = 0;
int output[20] = {a, b, c, d, e, f, g, 6, 5, 4, 22, 23, 24, 25, 29, 27, 28, 11};
int input[11] = {53, 51, 49, 10, 9, 12, A0, A2, A3, 2, 3};
int State[3] = {Durum1, Durum2, Durum3};
unsigned long zaman1 = 0, zaman2, zaman3, zaman4, zaman;

Servo myservo1;
Servo myservo2;
Servo myservo3;

void setup() {
  // put your setup code here, to run once:

  for (int i = 0; i <= 20; i++)pinMode(output[i], OUTPUT);
  for (int j = 0; j <= 11; j++)pinMode(input[j], INPUT);

  myservo1.attach(18);
  myservo2.attach(13);
  myservo3.attach(11);

  attachInterrupt(digitalPinToInterrupt(2), acil, RISING);
  attachInterrupt(digitalPinToInterrupt(3), servis, RISING);

  Serial.begin(250000);

}

void loop() {
  oku();

  Serial.print(Kabin1); Serial.print("  ");
  Serial.print(Kabin2); Serial.print("  ");
  Serial.print(Kabin3); Serial.print("   ");
  Serial.print(ldr1); Serial.print("  ");
  Serial.print(ldr2); Serial.print("  ");
  Serial.print(ldr3); Serial.print("  ");
  Serial.print(acil_count); Serial.print("  ");
  sens();
  katSegment();
  zaman = millis();
  while (Durum2 == 1) {
flag2:
    if (acil_count > 0)goto em;
    zaman = millis();
    sens();
    katSegment();
    if (kat == 1 ) up();
    if (kat == 3 ) down();
    if (kat != 2) goto flag2;
    while (kat == 2) {
      if (acil_count > 0)goto em;
      myservo1.write(180);

      Serial.println("2. Kat Servo On");
      if (millis() - zaman > 3000) {
        zaman = millis();
        myservo1.write(0);
        sayac++;
        Durum2 = 0;
        break;
      }
    }
  }
  while (Durum3 == 1)  {
flag1:
    if (acil_count > 0)goto em;
    zaman = millis();
    sens();
    katSegment();
    if (!(kat == 1))down();
    if (kat != 1)goto flag1;
    while (kat == 1)  {
      if (acil_count > 0)goto em;
      myservo2.write(180);
      Serial.println("1.Kat Servo On");
      if (millis() - zaman > 3000)  {
        zaman = millis();
        myservo2.write(0);
        sayac++;
        Durum3 = 0;
        break;
      }
    }
  }
  while (Durum1 == 1) {
flag3:
    if (acil_count > 0)goto em;
    zaman = millis();
    sens();
    katSegment();
    if (!(kat == 3))up();
    if (kat != 3)goto flag3;
    while (kat == 3) {
      if (acil_count > 0)goto em;
      myservo3.write(180);
      Serial.println("3.Kat Servo On");
      if (millis() - zaman > 3000)  {
        zaman = millis();
        myservo3.write(0);
        Durum1 = 0;
        sayac++;
        break;
      }
    }
  }
  while (Kabin1 == 1) {
flag4:
    if (acil_count > 0)goto em;
    zaman = millis();
    sens();
    katSegment();
    if (kat == 3)down();
    if (kat == 2)down();
    if (kat != 1)goto flag4;
    while (kat == 1) {
      if (acil_count > 0)goto em;
      myservo3.write(180);
      Serial.println("3.Kat Servo On");
      if (millis() - zaman > 3000)  {
        zaman = millis();
        myservo3.write(0);
        Kabin1 = 0;
        sayac++;
        break;
      }
    }
  }
  while (Kabin2 == 1) {
flag5:
    if (acil_count > 0)goto em;
    zaman = millis();
    sens();
    katSegment();
    if (kat == 1 ) up();
    if (kat == 3 ) down();
    if (kat != 2) goto flag5;
    while (kat == 2) {
      if (acil_count > 0)goto em;
      myservo1.write(180);
      Serial.println("2. Kat Servo On");
      if (millis() - zaman > 3000) {
        zaman = millis();
        myservo1.write(0);
        Kabin2 = 0;
        sayac++;
        break;
      }
    }
  }
  while (Kabin3 == 1)  {
flag6:
    if (acil_count > 0)goto em;
    zaman = millis();
    sens();
    katSegment();
    if (!(kat == 3))up();
    if (kat != 3)goto flag6;
    while (kat == 3)
    {
      if (acil_count > 0)goto em;
      myservo2.write(180);
      Serial.println("1.Kat Servo On");
      if (millis() - zaman > 3000)  {
        zaman = millis();
        myservo2.write(0);
        Kabin3 = 0;
        sayac++;
        break;
      }
    }
  }
em:
  emerg();
  while (sayac >= 3)
  {
    Serial.println("bakim");
    if (servis_count > 1)
    {
      servis_count = 0;
      sayac = 0;
      break;
    }
  }
}

void sens()
{
  ldr1 = analogRead(A1);
  ldr2 = analogRead(A2);
  ldr3 = analogRead(A3);
  if (ldr1 <= 890)kat = 1;
  if (ldr2 <= 900)kat = 3;
  if (ldr3 <= 780)kat = 2;
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
  Serial.println("down");
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
  Serial.println("UP");
}
void katSegment()
{

  switch (kat)
  {
    case 0 :
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, LOW);
      digitalWrite(g, HIGH);
      break;
    case 1:
      digitalWrite(a, HIGH);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
    case 2:
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, HIGH);
      digitalWrite(d, LOW);
      digitalWrite(e, LOW);
      digitalWrite(f, HIGH);
      digitalWrite(g, LOW);
      break;
    case 3:
      digitalWrite(a, LOW);
      digitalWrite(b, LOW);
      digitalWrite(c, LOW);
      digitalWrite(d, LOW);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, LOW);
      break;
  }
}
void oku()
{
  if (digitalRead(10) == 1 && x == 0) {
    x = 1;
    if (Durum1 == 0) Durum1 = 1;
    else if (Durum1 == 1) Durum1 = 0;
  }
  else if (digitalRead(10) == 0 && x == 1)x = 0;

  if (digitalRead(12) == 1 && x == 0) {
    x = 1;
    if (Durum2 == 0) Durum2 = 1;
    else if (Durum2 == 1) Durum2 = 0;
  }
  else if (digitalRead(12) == 0 && x == 1)x = 0;

  if (digitalRead(9) == 1 && x == 0) {
    x = 1;
    if (Durum3 == 0) Durum3 = 1;
    else if (Durum3 == 1) Durum3 = 0;
  }
  else if (digitalRead(9) == 0 && x == 1)x = 0;

  if (digitalRead(53) == 1 && x == 0) {
    x = 1;
    if (Kabin1 == 0) Kabin1 = 1;
    else if (Kabin1 == 1) Kabin1 = 0;
  }
  else if (digitalRead(53) == 0 && x == 1)x = 0;

  if (digitalRead(51) == 1 && x == 0) {
    x = 1;
    if (Kabin2 == 0) Kabin2 = 1;
    else if (Kabin2 == 1) Kabin2 = 0;
  }
  else if (digitalRead(51) == 0 && x == 1)x = 0;

  if (digitalRead(49) == 1 && x == 0) {
    x = 1;
    if (Kabin3 == 0) Kabin3 = 1;
    else if (Kabin3 == 1) Kabin3 = 0;
  }
  else if (digitalRead(49) == 0 && x == 1)x = 0;
}

void servis()
{
  servis_count++;
}
void emerg()
{
  Serial.println("EREN");
  while (acil_count > 0)
  {
    Durum1 = 0;
    Durum2 = 0;
    Durum3 = 0;
    Kabin1 = 0;
    Kabin2 = 0;
    Kabin3 = 0;
    sens();
    down();
    katSegment();
    if (ldr1 < 890)
    {
      acil_count = 0;
      Kabin1 = 0;
      Serial.println("ACİL");
      break;
    }
  }
}
void acil()
{
  acil_count++;
}

