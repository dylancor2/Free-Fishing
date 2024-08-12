#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int start = 34;
int sel = 35;

int slid = 14;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello, ESP32!");
  pinMode(start, INPUT);
  pinMode(sel, INPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  menu();
}

void loop() {
  // Button press
  if(digitalRead(start) == HIGH){
    Serial.println("Started"); 
    }
  if(digitalRead(sel) == HIGH){
    Serial.println("selected");  
  }
  delay(100);

}

void menu(){
  display.setCursor(5, 5);
  display.setTextSize(3);
  display.println("Free Fishing!");
  display.display();
}