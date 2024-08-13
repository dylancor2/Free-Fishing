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
int oldPos = 0;

bool inShop = false;
int money = 0;

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
      else if(!inMenu){
        openMenu();
      }
    }
    if(digitalRead(sel) == HIGH){
      if(beg){
        men(stage);
      }
      if(inMenu){
        enter(oldPos);
      }
      if(inShop){
        buy(oldPos);
      }
      
    }

      if(inMenu || inShop){
        drawCursor(analogRead(slid), 3);
      }
    
    delay(100);

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
      display.setCursor(15, 50);
      display.println("(or start to skip)");
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
  beg = false;
  inMenu = true;
  display.clearDisplay();
  display.setCursor(40, 0);
  display.setTextSize(1.5);
  display.println("|Menu|");
  display.setCursor(35, 15);
  display.setTextSize(1);
  display.println("Go Fish!");
  display.setCursor(40, 30);
  display.setTextSize(1);
  display.println("Shop");
  display.setCursor(25, 45);
  display.setTextSize(1);
  display.println("Gamble >:)");
  display.display();
}

void drawCursor(int position, int num){
  int newPos = map(position, 0, 4095, 1, num);
  if(oldPos != newPos){
    if(oldPos != 0)
      display.fillRect(100, oldPos*15, 30, 30, BLACK);
    Serial.print("Slide position: ");
    Serial.println(newPos);
    display.setCursor(100, newPos*15);
    display.setTextSize(1);
    display.print("<");
    display.display();
    Serial.print("Covered: ");
    Serial.println(oldPos);
    oldPos = newPos;
  }
}

void enter(int selection){
  switch(selection){
    case 1:{
      startFishing();
    }
    case 2:{
      shop();
    }
    case 3:{
      gamble();
    }
  }
  inMenu = false;
}

void startFishing(){

}

void shop(){
  inShop = true;
  display.clearDisplay();
  display.setCursor(40, 0);
  display.setTextSize(1.5);
  display.println("|Shop|");
  display.setCursor(30, 15);
  display.setTextSize(1);
  display.println("Option 1");
  display.setCursor(30, 30);
  display.setTextSize(1);
  display.println("Option 2");
  display.setCursor(30, 45);
  display.setTextSize(1);
  display.println("Option 3");
  display.display();
}

void gamble(){}

void buy(int selection){}
