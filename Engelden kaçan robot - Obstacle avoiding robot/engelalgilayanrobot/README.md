# Arduino Engelden Kaçan Robot - Obstacle Avoiding Robot

# Çalışma prensibi: <br>
İlk başta HC-SR04 mesafe sensörlerinden gelen bilgiyi Arduino mikroişlemci ile okuyoruz ve daha sonra her sensörlerden gelen bilgiye göre motorlara hareket bilgisini yazdırıyoruz.<br> Mesala soldaki sensör bir engel algıladıysa sağa dönme, sağdaki sensör bir engel algıladıysa sola dönme hareketini motorlara yazdırıyoruz. Eğer herhangi bir sensör engel algılamadıysa araç ileri hareketini sağlıyor.<br> Burada motorların kontrollerini sağlamak için L293B motor sürücü entegresini kullanıyoruz.<br> DHT11 sensörünü ise HC-SR04 mesafe sensörünün doğru çalışması için kullanıyoruz. Sıcaklık bilgisine göre mesafe sensörünü kalibre ediyoruz.
# Projede Kullanılan Ana Malzemeler: </br>
- 1 adet Arduino Nano mikroişlemci.
- 3 adet HC-SR04 ultrasonik mesafe sensörü.
- 1 adet DHT11 Sıcaklık sensörü.
- 1 adet L293B motor sürücü entegre.
- 2 adet DC motor ve tekerlek.
- 1 adet Sarhoş tekerlek
# Library: </br>
- DHT.h library: https://drive.google.com/file/d/1_R2OKeb6bdt_ttyqFQsIlH8JnSHp2ZXK/view?usp=sharing
