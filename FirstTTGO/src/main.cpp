#include <TFT_eSPI.h>
#include "oil.h" 
TFT_eSPI tft = TFT_eSPI(); 
TFT_eSprite img = TFT_eSprite(&tft);

const int pwmFreq = 5000;
const int pwmResolution = 8;
const int pwmLedChannelTFT = 0;

#define green 0x33F0
#define gray 0xBDD7
double rad=0.01745;

int sx=67;
int sy=76;
int angle=0;
float x[360];
float y[360];
int r=38;

int sx2=34;
int sy2=170;
int angle2=150;
float x2[360];
float y2[360];
int r2=22;

int sx3=106;
int sy3=204;
int angle3=100;
float x3[360];
float y3[360];
int r3=20;

void setup() {
  
tft.init();
tft.fillScreen(TFT_WHITE);
img.createSprite(135, 240);
img.setTextDatum(4);
img.setSwapBytes(true);

img.setFreeFont(&FreeSansBold9pt7b);

     int i=0;
     int a=136;

     while(a!=44)
  {
   x[i]=r*cos(rad*a)+sx;
   y[i]=r*sin(rad*a)+sy;
   x2[i]=r2*cos(rad*a)+sx2;
   y2[i]=r2*sin(rad*a)+sy2;
   x3[i]=r3*cos(rad*a)+sx3;
   y3[i]=r3*sin(rad*a)+sy3;
   
   i++;
   a++;
   if(a==360)
   a=0;
  }

 ledcSetup(pwmLedChannelTFT, pwmFreq, pwmResolution);
  ledcAttachPin(TFT_BL, pwmLedChannelTFT);
  ledcWrite(pwmLedChannelTFT,100);

}


void loop() {
  angle++;
  if(angle==266)
  angle=0;

  angle2=angle2+2;;
  if(angle2==266)
  angle2=0;

  angle3++;
  if(angle3==266)
  angle3=0;
  
  img.fillSprite(TFT_WHITE);
  img.fillCircle(sx+52,sy-32,4,0x9062);
  img.fillCircle(sx+52,sy-18,4,0x9062);
  
  img.drawCircle(sx,sy,r,gray);
  img.drawCircle(sx,sy,r-1,gray);
  img.drawCircle(sx2,sy2,r2,gray);
  img.fillRect(sx-r,sy+r-12,100,20,TFT_WHITE);
  

 
   img.fillRect(0,0,140,22,green);
   img.fillRect(0,122,68,16,green);
   img.fillRect(68,160,68,16,green);
  img.setTextColor(TFT_WHITE,green);
  img.drawString("GAUGES", 30,10,2);
  img.drawString("FUEL", 36,130,2);
  
  img.drawString("TEMP", 36+68,168,2);

  img.setTextColor(TFT_PURPLE,TFT_WHITE);
  img.drawString("mph", sx,sy+30,2);
  img.drawString("000023", 104,136,2);
  img.drawString("34 mpg", 104,150,2);

 
   img.drawString("check engine", 44,230,2);
  img.setTextColor(TFT_BLACK,TFT_WHITE);
  
 
 
  
  img.drawCircle(sx3,sy3,r3,gray);
  
  
  
  for(int i=0;i<angle;i++)
  img.fillCircle(x[i],y[i],3,green);

   for(int i=0;i<angle2;i++)
  img.fillCircle(x2[i],y2[i],2,green);

   for(int i=0;i<angle3;i++)
  img.fillCircle(x3[i],y3[i],2,green);

 
  
  img.drawString(String(angle),sx,sy,4);
  img.setTextColor(TFT_PURPLE,TFT_WHITE);
  img.drawString(String((int)angle2/10),sx2,sy2);
  img.drawString(String((int)angle3/10),sx3,sy3);
  img.pushImage(12,198,44,17,oil);
 
  img.pushSprite(0,0);

}