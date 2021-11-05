#define uppin 7
#define downpin 6
#define buzz 5
#define resetpin 4
int welcomescroll = 0;
int menustate = 0;
int setupstate = 0;
int setuppage = 0;
int up = 0;
int down = 0;
unsigned long sekunda = 0;

//variables declaration

//injector flow l/sec
volatile static long double injector_value = 0.002875166;
//pulses per km
volatile static double pulse_distance = 0.000397545;

volatile unsigned long counter, avg_speed_divider, distance_pulse_count, all_speed_values, all_fuel_consumption_values, temp_distance_pulse_count, injector_pulse_time, temp_injector_pulse_time, injTime1, injTime2, save_number, distance_puls;
volatile unsigned int speed, avg_speed, max_speed=0, fccounter, save_counter, i;
volatile double traveled_distance, display_speed, display_instant_fuel_consumption, display_traveled_distance, injector_open_time, used_fuel, tank_capacity = 40, average_fuel_consumption, instant_fuel_consumption;
volatile boolean to_be_saved;

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



void setup() {

noInterrupts();

//TIMER ON
TCCR1A = 0; 
TCCR1B |= ((1 << CS10) | (1 << CS11));
TIMSK1 |= (1 << TOIE1); 
TCNT1 = 3036; 

pinMode(3, INPUT); //Injector
pinMode(2, INPUT);//VSS
pinMode(4, INPUT_PULLUP); //resetpin

digitalWrite(4, HIGH);
digitalWrite(2, HIGH);
digitalWrite(3, HIGH);

attachInterrupt(digitalPinToInterrupt(3), injector_count, CHANGE);
attachInterrupt(digitalPinToInterrupt(2), distance_count, FALLING);
//EEPROM.setMemPool(0, 1024);
//loadData();
  
interrupts(); 
  

  Serial.begin(9600);
  pinMode (7, INPUT_PULLUP); //UP
  pinMode (6, INPUT_PULLUP); //DOWN
  pinMode (5, OUTPUT); // BEEPER
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
  }
  display.clearDisplay(); 
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.drawLine(0, 0, 128, 0, SSD1306_WHITE); //Linia nad ekranem powitalnym
  display.setCursor(10, 3);
  display.println("SimpleBrickComputer");
  display.setTextSize(2.5); // Draw 2X-scale text
  display.setCursor(25, 18);
  display.println("Welcome"); 
  display.display(); 
  delay(3000);
  scrolllopp();
  menustate = EEPROM.read(1); // import ostatnie wyświetlane menu po odłączeniu zasilania
 // loadData();
}

void  scrolllopp() {
    if (welcomescroll == 0) {
    display.startscrollleft(0x00, 0x0F);
  delay(3000);
  welcomescroll = 1;
    }
    if (welcomescroll == 1) {
  display.startscrollright(0x00, 0x0F);
  delay(3000);
  welcomescroll = 0;
  }
    display.stopscroll();
    delay(2000);
}

void loop() {
  //reset data
  if (digitalRead(4) == LOW && (millis()%2000 == 0)) {
    traveled_distance = 0;
    used_fuel=0;
    all_fuel_consumption_values = 0;
    avg_speed=0;
    avg_speed_divider=0;
    all_speed_values=0;
    
      
  }
   if(millis()%500 == 0){
  menucounter();
  setupcounter();
  setuppagecounter();
  beeper();
  setupscreen1();
  setupscreen2();
  screen1();
  screen2();
  screen3();
  screen4();
  screen5();
  screen6();
 // Serial.print ("epprom");
  Serial.print (save_counter); //debug 
  EEPROM.update(1, menustate);
  //delay(500);
}
}

void menucounter() {
  up = digitalRead(uppin); //dodawanie do menu
  down = digitalRead(downpin); //odejmowanie do menu
  if (up == LOW) {
    menustate ++ ;
  }

  if (down == LOW) {
    menustate --;
  }

  if (menustate <= 0) {
   menustate = 1;    // zakres min.
  }
  if (menustate == 7) {
     menustate = 6; // zakres max. 
  }

}

void setupcounter() {
  if (down == LOW && up == LOW) {
    setupstate ++;  
  }
  if (down == LOW && up == LOW && setupstate ==2) {
    setupstate = 0;
    menustate = 1;
  }
}

void setuppagecounter() {
  if (setupstate == 1 && up == LOW) {
    setuppage ++;
  }
   if (setupstate == 1 && down == LOW) {
    setuppage --;
  }
  
  if (setuppage <= 0) {
   setuppage = 0;    // zakres min.
  }
  if (setuppage == 2) {
     setuppage = 1; // zakres max. 
  }

}

void setupscreen1() {
  if (setupstate == 1 && setuppage == 0) {
    menustate = 9;
        display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println("SETUP 1");
  display.display();
  }
}

void setupscreen2() {
  if (setupstate == 1 && setuppage == 1) {
    menustate = 9;
        display.clearDisplay();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 0);
  display.println("SETUP 2");
  display.display();
  }
}
