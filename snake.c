#include <Snake.h>
#include "FastLED.h"

#define NUM_LEDS 144
#define LEDS_PER_ROW 12
#define DATA_PIN 6

Snake snakeGame(12,12,10);      //размер на полето        
CRGB leds[NUM_LEDS];

void setup() {
    snakeGame.setBodyColor(255,0,255);
    snakeGame.setFoodColor(0,60,125);
    snakeGame.setHeadColor(225,20,60);

    delay(2000);
    FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);
    Serial.begin(9600);
}

byte setPixel(byte x, byte y, byte r, byte g, byte b)
{
    byte ledID = NUM_LEDS - (y * LEDS_PER_ROW  ) - x - 1;
 
    leds[ledID].setRGB(r,g,b);
    return ledID;
}
void changeRGBtoGBR()
{
    for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed++)
    {
      leds[whiteLed].setRGB(leds[whiteLed].g , leds[whiteLed].b, leds[whiteLed].r);
    }
}

void clearScreen()
{
    for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed++)
    {
      leds[whiteLed].setRGB( 3, 3, 3);
    }
}

void loop()
{     
    Snake::pixel* snakeLimbs=snakeGame.getSnakeLimbs();
    Snake::pixel* snakeFood = snakeGame.getFoodPositions();
    clearScreen();
    setPixel(snakeFood[0].posX,11-snakeFood[0].posY,snakeFood[0].pixelColor.r,snakeFood[0].pixelColor.g,snakeFood[0].pixelColor.b); // показване на храна
    for(int i=0; i<snakeGame.getSnakeLenght(); i++)
    {
   
        setPixel(snakeLimbs[i].posX,11-snakeLimbs[i].posY,snakeLimbs[i].pixelColor.r,snakeLimbs[i].pixelColor.g,snakeLimbs[i].pixelColor.b);  // дисплей с размер на лентата
    }
    FastLED.show();
    snakeGame.tick();
    if(snakeGame.wasGameReset())
    {
        for(int i=0; i<30; i++)
        {
            changeRGBtoGBR();
            FastLED.show();
            delay(40);
        }
    }
    else
        delay(30);
}

byte incomingByte=0;
void serialEvent() {
    while (Serial.available())
    {
        incomingByte = Serial.read();
        Serial.write(incomingByte);
    }
    switch(incomingByte)
    {
    case 37:
        snakeGame.goLeft();
        break;
    case 39:
        snakeGame.goRight();
        break;
    case 40:
        snakeGame.goDown();
        break;
    case 38:
        snakeGame.goUp(); 
        break;
    }
}
