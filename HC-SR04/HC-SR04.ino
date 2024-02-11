//DHT11 ve HC-SR04 SENSÖRLERİN BİR ARADA KULLANIMI//
//EREN BOZ//

#include "DHT.h"             //Kütüphane tanıtıldı.
#define DHTPIN 2             //DHT11'in pinini atadık. 
#define DHTTYPE DHT11        //DHT sensör modelimizi tanımladık.
DHT dht11(DHTPIN, DHTTYPE);  //Sensörümüze isim verdik.

const int trig_a =  8;       //HC-SR04 sensörün trig ve echo pinlerini atadık.
const int echo_a =  0;

int sure_a;                  //Süre ve mesafe değişkenleri tanımlandı.
int mesafe_a;

void setup() {
  pinMode(trig_a , OUTPUT);  //Trig ve echo pinlerini giriş, çıkış olarak tanımladık.
  pinMode(echo_a , INPUT);
  
  Serial.begin(9600);        //Serial ekranı çalıştırdık.
  dht11.begin();             //DHT11'i çalıştırdık.
  
  Serial.println("EREN BOZ DHT11 ve HC-SR04 SENSÖRLERİN BİR ARADA KULLANIMI");
}

void loop() {

  float t = dht11.readTemperature();  //Sıcaklık için "t" isimli değişken tanımladık.

  //Ses hızını sıcaklığa bağlı olarak güncelliyoruz.Formül "331√ 1+t/273" 
  float seshizi = 1 / (((sqrt((t / 273) + 1)) * 331) / 10000);
  
  digitalWrite(trig_a , HIGH);         //Trig pinine güç yolladık.
  delayMicroseconds(1000);             //1 milisaniye çalışmasını sağladık.
  digitalWrite(trig_a , LOW);          //Gücü kestik.
  sure_a = pulseIn(echo_a , HIGH);     //Trig pininden engele yollanan sesin geri gelme süresini "sure_a" isimli değişkene kaydettik. 
  mesafe_a = (sure_a/2) / seshizi;     //Mesafeyi hesaplamak için "sure_a" değişkenini 2'ye bölüyoruz çünkü "sure_a" değişkeni engele çarpıp geri yansıma süresiydi. Bize sadece birtanesi lazım o yüzden
                                       //ikiye bölüyoruz. Sonra sonucu ses hızına bölüyoruz ve mesafeyi buluyoruz.

  Serial.print(" Uzaklik = ");          //Mesafeyi serial ekrana yazdırıyoruz.
  Serial.print(mesafe_a);
  Serial.println(" cm ");
  Serial.println("--------------");

  Serial.print(" Sicaklik = ");         //Sıcaklığı serial ekrana yazdırıyoruz.
  Serial.print(t);
  Serial.println(" *C ");
  Serial.println("--------------");
  delay(500);

}
