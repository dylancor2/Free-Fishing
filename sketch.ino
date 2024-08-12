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


bool beg = true;
int stage = 0;

bool inMenu = false;

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
  beginning();
}

void loop() {

    if(digitalRead(start) == HIGH){
      if(beg && stage == 1){
        men(1);
      }
      else{
        openMenu();
      }
    }
    if(digitalRead(sel) == HIGH){
      if(beg){
        men(stage);
      }
      
    delay(100);
  }

}

void beginning(){
  display.setCursor(40, 0);
  display.setTextSize(2);
  display.println("Free");
  display.setCursor(23, 20);
  display.println("Fishing!");
  display.setCursor(35, 40);
  display.setTextSize(1);
  display.println("Press Start");
  display.display();
  stage = 1;
}

void men(int s){
  switch(s){
    case 1:{
      display.clearDisplay();
      display.setCursor(40, 0);
      display.setTextSize(2);
      display.println("Use");
      display.setCursor(23, 20);
      display.println("Select");
      display.setCursor(35, 40);
      display.setTextSize(1);
      display.println("to continue>");
      display.display();
      stage = 2;
      break;
    }
    case 2:{
      display.clearDisplay();
      display.setCursor(40, 0);
      display.setTextSize(2);
      display.println("Use");
      display.setCursor(30, 20);
      display.println("Slide");
      display.setCursor(10, 40);
      display.setTextSize(1);
      display.println("to scroll and reel>");
      display.display();
      stage = 3;
      break;
    }
    case 3:{
      display.clearDisplay();
      display.setCursor(40, 0);
      display.setTextSize(2);
      display.println("Tilt");
      display.setCursor(5, 20);
      display.println("Controller");
      display.setCursor(35, 40);
      display.setTextSize(1);
      display.println("to cast rod>");
      display.display();
      stage = 4;
      break;
    }
    case 4:{
      display.clearDisplay();
      display.setCursor(17, 0);
      display.setTextSize(2);
      display.println("Rotate");
      display.setCursor(17, 20);
      display.println("Encoder");
      display.setCursor(5, 40);
      display.setTextSize(1);
      display.println("to rotate player>");
      display.display();
      stage = 5;
      break;
    }
    case 5:{
      display.clearDisplay();
      display.setCursor(40, 0);
      display.setTextSize(2);
      display.println("Go");
      display.setCursor(23, 20);
      display.println("Fish");
      display.setCursor(35, 40);
      display.setTextSize(1);
      display.println("to get moneyy>");
      display.display();
      stage = 6;
      break;
    }
    case 6:{
      display.clearDisplay();
      display.setCursor(40, 0);
      display.setTextSize(2);
      display.println("Use");
      display.setCursor(23, 20);
      display.println("Start");
      display.setCursor(35, 40);
      display.setTextSize(1);
      display.println("to open menu>");
      display.display();
      beg = false;
      break;
    }
  }
}

void openMenu(){
  inMenu = true;
  display.clearDisplay();
  display.setCursor(40, 0);
  display.setTextSize(1.3);
  display.println("Menu");
  display.setCursor(35, 20);
  display.setTextSize(1);
  display.println("Go Fish!");
  display.setCursor(35, 40);
  display.setTextSize(1);
  display.println("Shop");
  display.setCursor(25, 60);
  display.setTextSize(1);
  display.println("Gamble >:)");
  display.display();
  stage = 1;
}
