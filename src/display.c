
#include "inc/display.h"
bool m_initFailed = false;
uint16_t *_buffer;


bool lcdInit()
{
    printf("Initializing LCD\n");

    spi_init(LCD_SPI_PORT, LCD_CLK_SPD); // SPI with 1Mhz

    gpio_set_function(LCD_MISO, GPIO_FUNC_SPI);
    gpio_set_function(LCD_SCL, GPIO_FUNC_SPI);
    gpio_set_function(LCD_SDA, GPIO_FUNC_SPI);

    printf("Enabling SPI Protocol for TFT on CS[%d] \n", LCD_CS);
    printf("Enabling SPI Protocol for TFT on SCL[%d] \n", LCD_SCL);
    printf("Enabling SPI Protocol for TFT on TX[%d] \n", LCD_SDA);
    printf("Enabling SPI Protocol for TFT on RX[%d] \n", LCD_MISO);
    printf("Enabling SPI Protocol for TFT on DC[%d] \n", LCD_DC);
    printf("Enabling SPI Protocol for TFT on RST[%d] \n", LCD_RES);
    printf("Enabling SPI Protocol for TFT on PORT [SPI 0]\n");
    printf("Enabling SPI Protocol for TFT with Clock Speed [%d hz] \n", LCD_CLK_SPD);
    int cs = LCD_CS;
    int dc = LCD_DC;
    int rst = LCD_RES;

    tft_spi_init(LCD_CS, LCD_DC, LCD_RES);
    sleep_ms(100);
#ifdef TFT_ENABLE_BLACK
    printf("Black Tab Initializing. \n");
    TFT_BlackTab_Initialize();
#elif defined(TFT_ENABLE_GREEN)
    printf("Green Tab Initializing. \n");
    TFT_GreenTab_Initialize();
#elif defined(TFT_ENABLE_RED)
    printf("Red Tab Initializing. \n");
    TFT_RedTab_Initialize();
#elif defined(TFT_ENABLE_GENERIC)
    printf("Generic Tab Initializing. \n");
    TFT_ST7735B_Initialize();
#endif
    setRotation(1);
    fillScreen(ST7735_RED);
    sleep_ms(60);
    fillScreen(ST7735_BLUE);
    sleep_ms(60);
    fillScreen(ST7735_GREEN);
    sleep_ms(60);
    fillScreen(ST7735_BLACK);
    sleep_ms(60);
    printf("Setting up buffer \n");
    _buffer = (uint16_t *)malloc(sizeof(uint16_t) * (160 * 128));

    return true;
}

int testY = 0;
int spdY = 1;


void lcdUpdate(uint64_t u)
{
    testY += spdY;
    if (testY >= 30 || testY <= 0)
    {
        if (testY < 0)
            testY = 0;
        if (testY > 30)
            testY = 30;
        spdY = -spdY;
    }
    for (int i = 0; i < 20480; i++)
    {
       
    }

    fillScreen(ST7735_BLACK);
    drawText(20 + 35, 10 + testY + 20, "Working!", ST7735_RED, ST7735_BLACK, 1);
    drawFastHLine(0 + 35, 0 + testY + 20, 80, ST7735_CYAN);
    drawFastHLine(0 + 35, 25 + testY + 20, 80, ST7735_CYAN);
    drawFastVLine(0 + 35, 0 + testY + 20, 25, ST7735_CYAN);
    drawFastVLine(80 + 35, 0 + testY + 20, 25, ST7735_CYAN);
    drawBuffer(_buffer);
}