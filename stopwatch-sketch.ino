#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 256

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 6
#define CLOCK_PIN 13
#define SENSOR_PIN 3
#define BTN1_PIN 4
#define BTN2_PIN 8

#define CONNECTION_ANGLE 1
#define STRIP_DIRECTION 3
#define MATRIX_TYPE 0
#define COLOR_ORDER GRB
#define WIDTH 32
#define HEIGHT 8
#define SEGMENTS 1

// Define the array of leds
CRGB leds[NUM_LEDS];

// служебные функции

// функция отрисовки точки по координатам X Y
void drawPixelXY(int x, int y, uint32_t color) {
  //if (x < 0 || x > WIDTH - 1 || y < 0 || y > HEIGHT - 1) return;
  leds[getPixelNumber(x, y)] = color;
}

// **************** НАСТРОЙКА МАТРИЦЫ ****************
/*
#if (CONNECTION_ANGLE == 0 && STRIP_DIRECTION == 0)
#define _WIDTH WIDTH
#define THIS_X x
#define THIS_Y y

#elif (CONNECTION_ANGLE == 0 && STRIP_DIRECTION == 1)
#define _WIDTH HEIGHT
#define THIS_X y
#define THIS_Y x

#elif (CONNECTION_ANGLE == 1 && STRIP_DIRECTION == 0)
#define _WIDTH WIDTH
#define THIS_X x
#define THIS_Y (HEIGHT - y - 1)
*/

//#elif (CONNECTION_ANGLE == 1 && STRIP_DIRECTION == 3)
#if (CONNECTION_ANGLE == 1 && STRIP_DIRECTION == 3)
#define _WIDTH HEIGHT
#define THIS_X (HEIGHT - y - 1)
#define THIS_Y x
/*
#elif (CONNECTION_ANGLE == 2 && STRIP_DIRECTION == 2)
#define _WIDTH WIDTH
#define THIS_X (WIDTH - x - 1)
#define THIS_Y (HEIGHT - y - 1)

#elif (CONNECTION_ANGLE == 2 && STRIP_DIRECTION == 3)
#define _WIDTH HEIGHT
#define THIS_X (HEIGHT - y - 1)
#define THIS_Y (WIDTH - x - 1)

#elif (CONNECTION_ANGLE == 3 && STRIP_DIRECTION == 2)
#define _WIDTH WIDTH
#define THIS_X (WIDTH - x - 1)
#define THIS_Y y

#elif (CONNECTION_ANGLE == 3 && STRIP_DIRECTION == 1)
#define _WIDTH HEIGHT
#define THIS_X y
#define THIS_Y (WIDTH - x - 1)
*/
#else
#define _WIDTH WIDTH
#define THIS_X x
#define THIS_Y y
#pragma message "Wrong matrix parameters! Set to default"

#endif

// получить номер пикселя в ленте по координатам
uint16_t getPixelNumber(int x, int y) {
  if ((THIS_Y % 2 == 0) || MATRIX_TYPE) {               // если чётная строка
    return (THIS_Y * _WIDTH + THIS_X);
  } else {                                              // если нечётная строка
    return (THIS_Y * _WIDTH + _WIDTH - THIS_X - 1);
  }
}







int digits [10] [8] [4] = {
{
  {0,1,1,0},
  {1,0,0,1},
  {1,0,0,1},
  {1,0,0,1},
  {1,0,0,1},
  {1,0,0,1},
  {1,0,0,1},
  {0,1,1,0},
},
{
  {0,0,1,0},
  {0,1,1,0},
  {0,0,1,0},
  {0,0,1,0},
  {0,0,1,0},
  {0,0,1,0},
  {0,0,1,0},
  {0,1,1,1},
},
{
  {0,1,1,0},
  {1,0,0,1},
  {0,0,0,1},
  {0,0,0,1},
  {0,0,1,0},
  {0,1,0,0},
  {1,0,0,0},
  {1,1,1,1},
},
{
  {0,1,1,0},
  {1,0,0,1},
  {0,0,0,1},
  {0,0,1,0},
  {0,0,0,1},
  {0,0,0,1},
  {1,0,0,1},
  {0,1,1,0},
},
{
  {1,0,0,1},
  {1,0,0,1},
  {1,0,0,1},
  {0,1,1,1},
  {0,0,0,1},
  {0,0,0,1},
  {0,0,0,1},
  {0,0,0,1},
},
{
  {1,1,1,1},
  {1,0,0,0},
  {1,0,0,0},
  {1,1,1,0},
  {0,0,0,1},
  {0,0,0,1},
  {1,0,0,1},
  {0,1,1,0},
},
{
  {0,1,1,0},
  {1,0,0,1},
  {1,0,0,0},
  {1,1,1,0},
  {1,0,0,1},
  {1,0,0,1},
  {1,0,0,1},
  {0,1,1,0},
},
{
  {1,1,1,1},
  {0,0,0,1},
  {0,0,0,1},
  {0,0,1,0},
  {0,1,0,0},
  {0,1,0,0},
  {0,1,0,0},
  {0,1,0,0},
},
{
  {0,1,1,0},
  {1,0,0,1},
  {1,0,0,1},
  {0,1,1,0},
  {1,0,0,1},
  {1,0,0,1},
  {1,0,0,1},
  {0,1,1,0},
},
{
  {0,1,1,0},
  {1,0,0,1},
  {1,0,0,1},
  {0,1,1,0},
  {0,0,0,1},
  {0,0,0,1},
  {1,0,0,1},
  {0,1,1,0},
}};


int startStopState;
int startStopLastState;
int timerState = 0;
long startTime;
long elapsedTime;
long currentTime;
long lastChange;
int minutes = 0;
int tSeconds = 0;
int seconds = 0;
int mSeconds = 0;
int miSeconds = 0;
int milSeconds = 0;

int btn1state = LOW;
int btn2state = LOW;
int btn1laststate = LOW;
int btn2laststate = LOW;

int brightness = 20;

void incrBrightness() {
  brightness = min(100, brightness + 5);
  FastLED.setBrightness(brightness);
}
void decrBrightness() {
  brightness = max(5, brightness - 5);
  FastLED.setBrightness(brightness);
}


void setup() { 
    // Uncomment/edit one of the following lines for your leds arrangement.
    // ## Clockless types ##
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
    FastLED.setBrightness(brightness);
    // FastLED.addLeds<SM16703, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<TM1829, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<TM1812, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<UCS1904, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<UCS2903, DATA_PIN, RGB>(leds, NUM_LEDS);
//     FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    // FastLED.addLeds<WS2852, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    // FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    // FastLED.addLeds<GS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<SK6812, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    // FastLED.addLeds<SK6822, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<APA106, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<PL9823, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<SK6822, DATA_PIN, RGB>(leds, NUM_LEDS);
//     FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<WS2813, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<APA104, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<WS2811_400, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<GE8822, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<LPD1886, DATA_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<LPD1886_8BIT, DATA_PIN, RGB>(leds, NUM_LEDS);
    // ## Clocked (SPI) types ##
    // FastLED.addLeds<LPD6803, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<WS2803, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
    // FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // BGR ordering is typical
    // FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // BGR ordering is typical
    // FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // BGR ordering is typical
    // FastLED.addLeds<SK9822, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // BGR ordering is typical

    pinMode(SENSOR_PIN, INPUT);
    pinMode(BTN1_PIN, INPUT);
    pinMode(BTN2_PIN, INPUT);
}


void setDigits(long currentTime){
  minutes = (int)(currentTime / 60000) % 10;
  tSeconds = (int)(currentTime % 60000 / 10000);
  seconds = (int)(currentTime % 60000 % 10000 / 1000);
  mSeconds = (int)(currentTime % 60000 % 1000 / 100);
  miSeconds = (int)(currentTime % 60000 % 100 / 10);
  milSeconds = (int)(currentTime % 60000 % 10);
}

void drawDigit(int dX, int digit, uint32_t color ){
  for (int y = 0; y < 8; y++){
    for (int x = 0; x < 4; x++){
      if (digits[digit][y][x] == 1){
        drawPixelXY(x+dX, abs(y-7), color);
      } else {
        drawPixelXY(x+dX, abs(y-7), CRGB::Black);
      }
    }
  }
}
void drawEmpty(int dX, int digit, uint32_t color ){
  for (int y = 0; y < 8; y++){
    for (int x = 0; x < 4; x++){
      if (digits[digit][y][x] == 1){
        drawPixelXY(x+dX, abs(y-7), color);
      } else {
        drawPixelXY(x+dX, abs(y-7), CRGB::Black);
      }
    }
  }
}
void drawDot(int dX, uint32_t color ){
  for (int y = 0; y < 8; y++){
    for (int x = 0; x < 2; x++){
      if ( x == 1 && y == 0){
        drawPixelXY(x+dX, y, color);
      } else {
        drawPixelXY(x+dX, y, CRGB::Black);
      }
    }
  }
}


void setMatrix(){
  int dX = 0;
  // minutes
  drawDigit(dX, minutes, CRGB::White);
  // dots
  dX = 4;
  for (int y = 1; y < 8; y++){
    for (int x = 0; x < 3; x++){
      if (x == 1 && (y == 3 || y == 5)){
        if (millis() - lastChange > 3000) {
          drawPixelXY(x+dX, y, CRGB::Green);          
        } else {
          drawPixelXY(x+dX, y, CRGB::Red);
        }
      } else {
          drawPixelXY(x+dX, y, CRGB::Black);
      }
    }
  }
  // tSeconds
  dX = 7;
  drawDigit(dX, tSeconds, CRGB::White);
  // seconds
  dX = 12;
  drawDigit(dX, seconds, CRGB::White);
  // dot
  dX = 16;
  drawDot(dX, CRGB::Green);
  dX = 18;
  drawDigit(dX, mSeconds, CRGB::White);
  dX = 23;
  drawDigit(dX, miSeconds, CRGB::White);
  dX = 28;
  drawDigit(dX, milSeconds, CRGB::White);
}


void loop() { 
  btn1state = digitalRead(BTN1_PIN);
  btn2state = digitalRead(BTN2_PIN);
  if (btn1state == HIGH && btn1laststate == LOW){
    incrBrightness();
  }
  if (btn2state == HIGH && btn2laststate == LOW){
    decrBrightness();
  }
  btn1laststate = btn1state;
  btn2laststate = btn2state;
  
  startStopState = digitalRead(SENSOR_PIN);

  if (startStopState == LOW){
    drawPixelXY(5, 0, CRGB::Black);    
  } else {
    drawPixelXY(5, 0, CRGB::Red);    
  }
  
  if (timerState == 0){
    if (startStopState == HIGH && startStopLastState == LOW && millis() - lastChange > 3000){
      startTime = millis();
      timerState = 1;
      currentTime = millis() - startTime;
      lastChange = millis();
    }
    startStopLastState = startStopState;
  } else {
    currentTime = millis() - startTime;
    if (startStopState == HIGH && startStopLastState == LOW && millis()-lastChange  > 3000){
        timerState = 0;
        elapsedTime =   currentTime;
        lastChange = millis();
    }
    startStopLastState = startStopState;
    setDigits(currentTime);
  }

  // Turn the LED on, then pause
  
//  leds[seconds] = CRGB::Red;
  setMatrix();
  FastLED.show();
  delay(1);
}
