#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int a = 41;
int b = 43;
int c = 45;
int d = 35;
int e = 33;
int f = 39;
int g = 37;
int x2, x1, x3, x4, x5, x6;
int ldr1 = 0, ldr2 = 0, ldr3 = 0, kat = 0, Durum1, Durum2, Durum3, acil_count = 0, servis_count = 0, Kabin1, Kabin2, Kabin3, sayac = 0;
int output[15] = {a, b, c, d, e, f, g, 11, 4, 5, 6, 7, 8, 13};
int input[12] = {53, 51, 49, 10, 9, 12, A0, A2, A3, 2, 3};

unsigned long lcdzaman = 0, lcdzaman1 = 0, zaman1 = 0, zaman2, zaman3, zaman4, zaman;

Servo myservo1;
Servo myservo2;
Servo myservo3;

void setup() {
  // put your setup code here, to run once:

  for (int i = 0; i <= 14; i++)pinMode(output[i], OUTPUT);
  for (int j = 0; j <= 12; j++)pinMode(input[j], INPUT);

  myservo1.attach(13);
  myservo2.attach(8);
  myservo3.attach(11);

  attachInterrupt(digitalPinToInterrupt(2), acil, RISING);
  attachInterrupt(digitalPinToInterrupt(3), servis, RISING);
  lcd.init();
  lcd.backlight();
}

void loop() {

  myservo1.write(0);
  myservo2.write(0);
  myservo3.write(0);

  oku();
  sens();
  katSegment();

  zaman = millis();


  while (Durum2 == 1) {
flag2:
    if (acil_count > 0)goto em;
    zaman = millis();
    sens();
    oku();
    katSegment();
    if (kat == 1 ) up();
    if (kat == 3 ) down();
    if (kat != 2) goto flag2;
    while (kat == 2) {
      if (acil_count > 0)goto em;
      lcd.print("KAPI ACILIYOR");
      delay(60);
      lcd.clear();
      myservo1.write(90);
      oku();
      tone(7, 1000);


      if (millis() - zaman > 3000) {
        oku();
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
aa:
while(!(ldr1<890))
{
  sens();
  katSegment();
  down();
  acil_count=0;
}


    if (acil_count > 0)goto em;
    zaman = millis();
    sens();
    oku();
    katSegment();
    if (!(kat == 1))down();
    if (kat != 1)goto flag1;
    while (kat == 1) {
      if (acil_count > 0)goto em;
      lcd.print("KAPI ACILIYOR");
      delay(60);
      lcd.clear();
      myservo2.write(90);
      oku();
      tone(7, 1000);


      if (millis() - zaman > 3000)  {
        oku();
        zaman = millis();
        myservo2.write(0);
        Durum3 = 0;
        sayac++;
        break;
      }
    }
  }
  while (Durum1 == 1) {
flag3:
    if (acil_count > 0)goto em;
    zaman = millis();
    sens();
    oku();
    katSegment();
    if (!(kat == 3))up();
    if (kat != 3)goto flag3;
    while (kat == 3) {
      if (acil_count > 0)goto em;
      lcd.print("KAPI ACILIYOR");
      delay(60);
      lcd.clear();
      myservo3.write(90);
      oku();
      tone(7, 1000);


      if (millis() - zaman > 3000)  {
        oku();
        zaman = millis();
        myservo3.write(0);
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
    oku();
    zaman = millis();
    sens();
    katSegment();
    if (kat == 3)down();
    if (kat == 2)down();
    if (kat != 1)goto flag4;
    while (kat == 1) {
      if (acil_count > 0)goto em;
      lcd.print("KAPI ACILIYOR");
      delay(60);
      lcd.clear();
      myservo2.write(90);
      tone(7, 1000);
      oku();


      if (millis() - zaman > 3000)  {
        oku();
        zaman = millis();
        myservo2.write(0);
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
    oku();
    katSegment();
    if (kat == 1 ) up();
    if (kat == 3 ) down();
    if (kat != 2) goto flag5;
    while (kat == 2) {
      if (acil_count > 0)goto em;
      lcd.print("KAPI ACILIYOR");
      delay(60);
      lcd.clear();
      myservo1.write(90);
      tone(7, 1000);
      oku();

      if (millis() - zaman > 3000) {
        oku();
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
    oku();
    if (!(kat == 3))up();
    if (kat != 3)goto flag6;
    while (kat == 3)
    {
      if (acil_count > 0)goto em;
      lcd.print("KAPI ACILIYOR");
      delay(60);
      lcd.clear();
      myservo3.write(90);
      tone(7, 1000);
      oku();


      if (millis() - zaman > 3000)  {
        oku();
        zaman = millis();
        myservo3.write(0);
        Kabin3 = 0;
        sayac++;
        break;
      }
    }
  }
em:
if(acil_count>0)
{
  Durum1=0;
  Durum2=0;
  Durum3=0;
  Kabin1=0;
  Kabin2=0;
  Kabin3=0;
  goto aa;
}
  while (sayac >= 10)
  {
    lcd.print("BAKIM ZAMANI");
    delay(1000);
    lcd.clear();
    lcd.print("YETKILIYI CAGIRINIZ");
    delay(1000);
    lcd.clear();

    if (servis_count > 1)
    {
      servis_count = 0;
      sayac = 0;
      break;
    }
  }
  lcd.print(kat); lcd.print(".katta");
  delay(90);
  lcd.clear();
  noTone(7);
  myservo3.write(0);
}

void sens()
{
  ldr1 = analogRead(A1);
  ldr2 = analogRead(A2);
  ldr3 = analogRead(A3);
  if (ldr1 <= 800)kat = 1;
  if (ldr2 <= 800)kat = 3;
  if (ldr3 <= 800)kat = 2;
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
void katSegment()
{
  switch (kat)
  {
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
  if (digitalRead(10) == 1 && x1 == 0) {
    x1 = 1;
    if (Durum1 == 0) Durum1 = 1;
    else if (Durum1 == 1) Durum1 = 0;
  }
  else if (digitalRead(10) == 0 && x1 == 1)x1 = 0;

  if (digitalRead(12) == 1 && x2 == 0) {
    x2 = 1;
    if (Durum2 == 0) Durum2 = 1;
    else if (Durum2 == 1) Durum2 = 0;
  }
  else if (digitalRead(12) == 0 && x2 == 1)x2 = 0;

  if (digitalRead(9) == 1 && x3 == 0) {
    x3 = 1;
    if (Durum3 == 0) Durum3 = 1;
    else if (Durum3 == 1) Durum3 = 0;
  }
  else if (digitalRead(9) == 0 && x3 == 1)x3 = 0;

  if (digitalRead(53) == 1 && x4 == 0) {
    x4 = 1;
    if (Kabin1 == 0) Kabin1 = 1;
    else if (Kabin1 == 1) Kabin1 = 0;
  }
  else if (digitalRead(53) == 0 && x4 == 1)x4 = 0;

  if (digitalRead(51) == 1 && x5 == 0) {
    x5 = 1;
    if (Kabin2 == 0) Kabin2 = 1;
    else if (Kabin2 == 1) Kabin2 = 0;
  }
  else if (digitalRead(51) == 0 && x5 == 1)x5 = 0;

  if (digitalRead(49) == 1 && x6 == 0) {
    x6 = 1;
    if (Kabin3 == 0) Kabin3 = 1;
    else if (Kabin3 == 1) Kabin3 = 0;
  }
  else if (digitalRead(49) == 0 && x6 == 1)x6 = 0;
}

void servis()
{
  servis_count++;
}
/*void emerg()
{
  noTone(7);
  oku();
  katSegment();
  while (acil_count > 0)
  {
    oku();
    sens();
    goto aa; 
    acil_count = 0;
    }
  }
*/
void acil()
{
  acil_count++;
}
