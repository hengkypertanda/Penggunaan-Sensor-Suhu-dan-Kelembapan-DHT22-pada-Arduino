#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Definisikan pin untuk sensor DHT
#define DHTPIN 2     // Pin yang terhubung ke sensor DHT
#define DHTTYPE DHT22   // DHT 22

// Inisialisasi objek DHT
DHT dht(DHTPIN, DHTTYPE);

// Inisialisasi objek LCD I2C (alamat default 0x27, ubah jika berbeda)
LiquidCrystal_I2C lcd(0x27, 16, 2); // Alamat I2C, ukuran LCD 16x2

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  // Inisialisasi LCD
  lcd.init(); // Inisialisasi LCD
  lcd.backlight(); // Mengaktifkan lampu latar
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Tunggu beberapa detik antara pembacaan
  delay(2000);

  // Membaca kelembapan
  float h = dht.readHumidity();
  // Membaca suhu dalam Celcius
  float t = dht.readTemperature();

  // Cek apakah pembacaan gagal dan keluar jika demikian
  if (isnan(h) || isnan(t)) {
    Serial.println("Gagal membaca dari sensor DHT!");
    lcd.clear();
    lcd.print("Sensor Error!");
    return;
  }

  // Menampilkan hasil pembacaan di Serial Monitor
  Serial.print("Kelembapan: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Suhu: ");
  Serial.print(t);
  Serial.println(" *C");

  // Menampilkan hasil pembacaan di LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Kelembapan: ");
  lcd.print(h);
  lcd.print(" %");
  lcd.setCursor(0, 1);
  lcd.print("Suhu: ");
  lcd.print(t);
  lcd.print(" *C");
}
