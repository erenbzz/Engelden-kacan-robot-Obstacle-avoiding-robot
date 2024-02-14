//EREN BOZ ENGEL ALGILAYAN ROBOT//

#include "DHT.h"             //Kütüphane tanıtıldı.
#define DHTPIN 13            //DHT11'in pinini atadık. 
#define DHTTYPE DHT11        //DHT sensör modelimizi tanımladık.Burada DHT22'niz varsa DHT22 yazınız.
DHT dht11(DHTPIN, DHTTYPE);  //Sensörümüze isim verdik.

const int trig_a =  8;       //HC-SR04 sensörün trig ve echo pinlerini atadık.
const int echo_a =  0;

const int trig_b =  4;
const int echo_b =  7;

const int trig_c =  2;
const int echo_c =  3;

const int sol_i  = 11;       //Motor sürücü pinlerini atadık.
const int sol_g  =  9;
const int sag_i  = 12;
const int sag_g  = 10;

const int e1     =  5;
const int e2     =  6;

#define hiz  255            //Hız ve bekleme değişkenleri tanımlandı.
#define bek  200

int sure_a;                 //Süre ve mesafe değişkenleri tanımlandı.
int mesafe_a;

int sure_b;
int mesafe_b;

int sure_c;
int mesafe_c;

void setup() {
  pinMode(trig_a , OUTPUT);
  pinMode(trig_b , OUTPUT);
  pinMode(trig_c , OUTPUT);
  pinMode(echo_a , INPUT);
  pinMode(echo_b , INPUT);
  pinMode(echo_c , INPUT);

  pinMode(sol_i, OUTPUT); 
  pinMode(sol_g, OUTPUT);
  pinMode(sag_i, OUTPUT); 
  pinMode(sag_g, OUTPUT);

  pinMode(e1, OUTPUT);
  pinMode(e2, OUTPUT);

  Serial.begin(9600);        //Serial ekranı çalıştırdık.
  dht11.begin();             //DHT11'i çalıştırdık.
}

void loop() 
{

  float t = 33;  //Sıcaklık için "t" isimli değişken tanımladık.

  //Ses hızını sıcaklığa bağlı olarak güncelliyoruz.Formül "331√ 1+t/273" 
  float seshizi = 1 / (((sqrt((t / 273) + 1)) * 331) / 10000);
  
  digitalWrite(trig_a , HIGH);         //Trig pinine güç yolladık.
  delayMicroseconds(1000);             //1 milisaniye çalışmasını sağladık.
  digitalWrite(trig_a , LOW);          //Gücü kestik.
  sure_a = pulseIn(echo_a , HIGH);     //Trig pininden engele yollanan sesin geri gelme süresini "sure_a" isimli değişkene kaydettik. 
  mesafe_a = (sure_a/2) / seshizi;     //Mesafeyi hesaplamak için "sure_a" değişkenini 2'ye bölüyoruz çünkü "sure_a" değişkeni engele çarpıp geri yansıma süresiydi. Bize sadece birtanesi lazım o yüzden
                                       //ikiye bölüyoruz. Sonra sonucu ses hızına bölüyoruz ve mesafeyi buluyoruz.

  digitalWrite(trig_b , HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig_b , LOW);
  sure_b = pulseIn(echo_b , HIGH);
  mesafe_b = (sure_b/2) / seshizi;

  digitalWrite(trig_c , HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig_c , LOW);
  sure_c = pulseIn(echo_c , HIGH);
  mesafe_c = (sure_c/2) / seshizi;

  Serial.print("Sicaklik = ");         //Sıcaklığı serial ekrana yazdırıyoruz.
  Serial.print(t);
  Serial.println(" *C ");
  Serial.println("--------------");
  
  Serial.print("Uzaklik 1 = ");         //Mesafeyi serial ekrana yazdırıyoruz.
  Serial.print(mesafe_a);
  Serial.println(" cm");
  Serial.println("--------------");
  
  Serial.print("Uzaklik 2 = ");
  Serial.print(mesafe_b);
  Serial.println(" cm");
  Serial.println("--------------");

  Serial.print("Uzaklik 3 = ");
  Serial.print(mesafe_c);
  Serial.println(" cm");
  Serial.println("--------------");

  if (mesafe_a < 20)                   //Engel algılandığında yapılması gereken dönme hareketlerini yazdık.
  {
    analogWrite(e1 , hiz);
    analogWrite(e2 , hiz);
    digitalWrite(sol_i ,   LOW);
    digitalWrite(sol_g ,  HIGH);
    digitalWrite(sag_i ,   LOW);
    digitalWrite(sag_g ,  HIGH);
    delay(bek);
    digitalWrite(sol_i , HIGH);
    digitalWrite(sol_g ,  LOW);
    digitalWrite(sag_i ,  LOW);
    digitalWrite(sag_g , HIGH);
  }
  else if (mesafe_b < 25)
  {
    analogWrite(e1 , hiz);
    analogWrite(e2 , hiz);
    digitalWrite(sol_i ,  LOW);
    digitalWrite(sol_g , HIGH);
    digitalWrite(sag_i ,  LOW);
    digitalWrite(sag_g , HIGH);
    delay(bek);
    digitalWrite(sol_i , HIGH);
    digitalWrite(sol_g ,  LOW);
    digitalWrite(sag_i ,  LOW);
    digitalWrite(sag_g , HIGH);
  }
  else if (mesafe_c < 20)
  {
    analogWrite(e1 , hiz);
    analogWrite(e2 , hiz);
    digitalWrite(sol_i ,  LOW);
    digitalWrite(sol_g , HIGH);
    digitalWrite(sag_i ,  LOW);
    digitalWrite(sag_g , HIGH);
    delay(bek);
    digitalWrite(sol_i ,  LOW);
    digitalWrite(sol_g , HIGH);
    digitalWrite(sag_i , HIGH);
    digitalWrite(sag_g ,  LOW);
  }
  else                                 //Eğer bir engel yoksa düz gitmesini istedik.
  {
    analogWrite(e1 , hiz);
    analogWrite(e2 , hiz);
    digitalWrite(sol_i , HIGH);
    digitalWrite(sol_g ,  LOW);
    digitalWrite(sag_i , HIGH);
    digitalWrite(sag_g ,  LOW);
   
  }
  

}
