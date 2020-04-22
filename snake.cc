#include <Snake.h>
#include <FastLED.h>
#include<gtest/gtest.h>

#define NUM_LEDS 49
#define LEDS_PER_ROW 7
#define DATA_PIN 6

Snake snakeGame(7,7,10);      //размер на полето 7*7 delay=10        
CRGB leds[NUM_LEDS];

void setup() {
    snakeGame.setBodyColor(255,0,255);
    snakeGame.setFoodColor(0,60,125);
    snakeGame.setHeadColor(225,20,60);

    delay(2000);
    FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);
    Serial.begin(9600); //Задава скорост на предаване на данни
}

byte setPixel(byte x, byte y, byte r, byte g, byte b)// намираме конкретния светодиод който ни трябва
{
    byte ledID = NUM_LEDS - (y * LEDS_PER_ROW  ) - x - 1;
 
    leds[ledID].setRGB(r,g,b);
    return ledID;
}
TEST_F(SetPixelTest, setPixel){
 setPixel(4, 4, 1, 2, 3);
 EXPECT_EQ(leds.setRGB(1, 2, 3),leds[16]);
}

void changeRGBtoGBR()
{
    for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed++)
    {
      leds[whiteLed].setRGB(leds[whiteLed].g , leds[whiteLed].b, leds[whiteLed].r);
    }
}
TEST_F(ChangeRGBtoGBRTest, changeRGBtoGBR){
 changeRGBtoGBR();
 EXPECT_EQ(leds.setRGB(1, 2, 3),leds.setRGB(2, 3, 1));
}

void clearScreen()
{
    for(int whiteLed = 0; whiteLed < NUM_LEDS; whiteLed++)
    {
      leds[whiteLed].setRGB( 3, 3, 3);
    }
}
TEST_F(ClearScreanTest, clearScrean){
 clearScrean();
 EXPECT_EQ(leds[whiteLed].setRGB( 3, 3, 3), leds);
}

void loop()
{     
    Snake::pixel* snakeLimbs=snakeGame.getSnakeLimbs();
    Snake::pixel* snakeFood = snakeGame.getFoodPositions();
    clearScreen();
    setPixel(snakeFood[0].posX,6-snakeFood[0].posY,snakeFood[0].pixelColor.r,snakeFood[0].pixelColor.g,snakeFood[0].pixelColor.b); // показване на храна
    for(int i=0; i<snakeGame.getSnakeLenght(); i++)
    {
   
        setPixel(snakeLimbs[i].posX,6-snakeLimbs[i].posY,snakeLimbs[i].pixelColor.r,snakeLimbs[i].pixelColor.g,snakeLimbs[i].pixelColor.b);  // дисплей с размер на лентата
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
TEST_F(ChangingLeftDirectionTest, serialEvent){
 incomingByte = 37;
 if(leds[12].setRGB(225,20,60)){
 EXPECT_EQ(leds[11], leds.setRGB(225,20,60));
 }
}

TEST_F(ChangingRightDirectionTest, serialEvent){
 incomingByte = 39;
 if(leds[12].setRGB(225,20,60)){
 EXPECT_EQ(leds[13], leds.setRGB(225,20,60));
 }
}

TEST_F(ChangingUpDirectionTest, serialEvent){
 incomingByte = 38;
 if(leds[12].setRGB(225,20,60)){
 EXPECT_EQ(leds[5], leds.setRGB(225,20,60));
 }
}

TEST_F(ChangingDownDirectionTest, serialEvent){
 incomingByte = 40;
 if(leds[12].setRGB(225,20,60)){
 EXPECT_EQ(leds[19], leds.setRGB(225,20,60));
 }
}

int main(int argc, char* argv[]){

 testing::InitGoogleTest(&argc, argv);
 return RUN_ALL_TESTS();
}
