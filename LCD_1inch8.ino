#include <SPI.h>
#include "LCD_Driver.h"
#include "GUI_Paint.h"
#include "image.h"

int loadWidth = 100;
int offset = 8;
// Initialize the TFT display
const int sectionHeight = 40; // Each section's height (pixels)
const int maxLoad = 210;      // Maximum load value
bool toggle = HIGH;

int loads[3] = {};
class MyDisplay
{
public:
  MyDisplay()
  {
    // Constructor if needed
  }

  void fillRect(int x, int y, int w, int h, uint16_t color)
  {
    Paint_DrawRectangle(x, y, x + w, y + h, color, DOT_PIXEL_2X2, DRAW_FILL_FULL);
  }
  void fillScreen(uint16_t color)
  {
    Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, color);
  }
};
MyDisplay tft;
void setup()
{
  Config_Init();
  LCD_Init();
  LCD_Clear(WHITE);
  LCD_SetBacklight(150);
  Paint_NewImage(LCD_WIDTH, LCD_HEIGHT, 0, WHITE);
  Paint_Clear(WHITE);
  Paint_SetRotate(180);

  loads[0] = 0;
  loads[1] = 0;
  loads[2] = 0;
}

void drawLoadBar(int section, int loadValue)
{

  // Determine the color based on the load value
  uint16_t loadColor;
  if (loadValue < 100)
  {
    loadColor = GREEN;
  }
  else if (loadValue < 200)
  {
    loadColor = YELLOW;
  }
  switch (section)
  {
  case 0:
    if (loadValue <= 100)
    {
      loadWidth = map(loadValue, 0, 100, 0, LCD_WIDTH);
      tft.fillRect(0, 0, LCD_WIDTH, sectionHeight, BLACK);
      tft.fillRect(0, 0, loadWidth, sectionHeight, loadColor);
    }
    if (loadValue > 100)
    {
      loadValue = (200 * loadValue) / 210; // the overload value reminder in percentage 210 max
      loadValue = loadValue - 100;         // reminder value for the red
      loadValue = 100 - loadValue;         // value for the yellow
      loadWidth = map(loadValue, 0, 100, 0, LCD_WIDTH);
      tft.fillRect(0, 0, LCD_WIDTH, sectionHeight, BLACK);
      tft.fillRect(0, 0, loadWidth, sectionHeight, loadColor);
      tft.fillRect(loadWidth - offset, 0, 160, sectionHeight, RED);
    }
    break;
  case 1:
    if (loadValue <= 100)
    {
      loadWidth = map(loadValue, 0, 100, 0, LCD_WIDTH);
      tft.fillRect(0, 42, LCD_WIDTH, sectionHeight, BLACK);
      tft.fillRect(0, 42, loadWidth, sectionHeight, loadColor);
    }
    if (loadValue > 100)
    {
      loadValue = (200 * loadValue) / 210; // the overload value reminder in percentage 210 max
      loadValue = loadValue - 100;         // reminder value for the red
      loadValue = 100 - loadValue;         // value for the yellow
      loadWidth = map(loadValue, 0, 100, 0, LCD_WIDTH);
      tft.fillRect(0, 42, LCD_WIDTH, sectionHeight, BLACK);
      tft.fillRect(0, 42, loadWidth, sectionHeight, loadColor);
      tft.fillRect(loadWidth - offset, 42, 160, sectionHeight, RED);
    }
  case 2:
    if (loadValue <= 100)
    {
      loadWidth = map(loadValue, 0, 100, 0, LCD_WIDTH);
      tft.fillRect(0, 84, LCD_WIDTH, sectionHeight, BLACK);
      tft.fillRect(0, 84, loadWidth, sectionHeight, loadColor);
    }
    if (loadValue > 100)
    {
      loadValue = (200 * loadValue) / 210; // the overload value reminder in percentage 210 max
      loadValue = loadValue - 100;         // reminder value for the red
      loadValue = 100 - loadValue;         // value for the yellow
      loadWidth = map(loadValue, 0, 100, 0, LCD_WIDTH);
      tft.fillRect(0, 84, LCD_WIDTH, sectionHeight, BLACK);
      tft.fillRect(0, 84, loadWidth, sectionHeight, loadColor);
      tft.fillRect(loadWidth - offset, 84, 160, sectionHeight, RED);
    }
  default:
    break;
  }
  // Draw the load bar
}
void textbg()
{
  tft.fillRect(20, 10, 45, 23, BLACK);
  tft.fillRect(20, 50, 45, 23, BLACK);
  tft.fillRect(20, 93, 45, 23, BLACK);
}

int greatLoad(int section, int load)
{
  for (int i = 0; i < 3; i++)
  {
    if (section == i)
    {
      if (load > loads[i])
      {
        loads[i] = load;
        return load;
      }
      else
      {
        return loads[i];
      }
    }
  }
}
void loop()
{
  int loadS = random(LCD_WIDTH); // Replace with your actual load values
  int loadZ = random(LCD_WIDTH);
  int loadX = random(120);
  tft.fillScreen(BLACK);
  // Draw load bars
  textbg();
  drawLoadBar(0, loadS);
  drawLoadBar(1, loadZ);
  drawLoadBar(2, loadX);
  // Clear the screen

  textbg();
  // Draw section labels and load values
  Paint_DrawString_EN(2, 15, "S", &Font24, 0x0000, BLUE);
  Paint_DrawNum(5, 15, loadS, &Font24, BLACK, WHITE);
  Paint_DrawNum(120, 15, greatLoad(0, loadS), &Font24, 0x0000, BLUE);

  // tft.println("");
  // Draw section labels and load values
  Paint_DrawString_EN(2, 55, "Z", &Font24, 0x0000, BLUE);
  Paint_DrawNum(5, 55, loadZ, &Font24, BLACK, WHITE);
  Paint_DrawNum(120, 55, greatLoad(0, loadZ), &Font24, 0x0000, BLUE);


  Paint_DrawString_EN(2, 98, "X", &Font24, 0x0000, BLUE);
  Paint_DrawNum(5, 98, loadX, &Font24, BLACK, WHITE);
  Paint_DrawNum(120, 98, greatLoad(0, loadX), &Font24, 0x0000, BLUE);
  delay(5000); // Adjust the update interval as needed
}
