
#include "inc/display.h"
bool m_initFailed = false;
bool m_textWrap = true;

uint8_t *m_buffer1, *m_buffer2;
uint8_t *m_frameBuffer, *m_sentBuffer;
uint dma_tx;

bool m_currentBuffer = 0;

const char charSet[] = {

    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x5F, 0x00, 0x00,
    0x00, 0x07, 0x00, 0x07, 0x00,
    0x14, 0x7F, 0x14, 0x7F, 0x14,
    0x24, 0x2A, 0x7F, 0x2A, 0x12,
    0x23, 0x13, 0x08, 0x64, 0x62,
    0x36, 0x49, 0x56, 0x20, 0x50,
    0x00, 0x08, 0x07, 0x03, 0x00,
    0x00, 0x1C, 0x22, 0x41, 0x00,
    0x00, 0x41, 0x22, 0x1C, 0x00,
    0x2A, 0x1C, 0x7F, 0x1C, 0x2A,
    0x08, 0x08, 0x3E, 0x08, 0x08,
    0x00, 0x80, 0x70, 0x30, 0x00,
    0x08, 0x08, 0x08, 0x08, 0x08,
    0x00, 0x00, 0x60, 0x60, 0x00,
    0x20, 0x10, 0x08, 0x04, 0x02,
    0x3E, 0x51, 0x49, 0x45, 0x3E,
    0x00, 0x42, 0x7F, 0x40, 0x00,
    0x72, 0x49, 0x49, 0x49, 0x46,
    0x21, 0x41, 0x49, 0x4D, 0x33,
    0x18, 0x14, 0x12, 0x7F, 0x10,
    0x27, 0x45, 0x45, 0x45, 0x39,
    0x3C, 0x4A, 0x49, 0x49, 0x31,
    0x41, 0x21, 0x11, 0x09, 0x07,
    0x36, 0x49, 0x49, 0x49, 0x36,
    0x46, 0x49, 0x49, 0x29, 0x1E,
    0x00, 0x00, 0x14, 0x00, 0x00,
    0x00, 0x40, 0x34, 0x00, 0x00,
    0x00, 0x08, 0x14, 0x22, 0x41,
    0x14, 0x14, 0x14, 0x14, 0x14,
    0x00, 0x41, 0x22, 0x14, 0x08,
    0x02, 0x01, 0x59, 0x09, 0x06,
    0x3E, 0x41, 0x5D, 0x59, 0x4E,
    0x7C, 0x12, 0x11, 0x12, 0x7C,
    0x7F, 0x49, 0x49, 0x49, 0x36,
    0x3E, 0x41, 0x41, 0x41, 0x22,
    0x7F, 0x41, 0x41, 0x41, 0x3E,
    0x7F, 0x49, 0x49, 0x49, 0x41,
    0x7F, 0x09, 0x09, 0x09, 0x01,
    0x3E, 0x41, 0x41, 0x51, 0x73,
    0x7F, 0x08, 0x08, 0x08, 0x7F,
    0x00, 0x41, 0x7F, 0x41, 0x00,
    0x20, 0x40, 0x41, 0x3F, 0x01,
    0x7F, 0x08, 0x14, 0x22, 0x41,
    0x7F, 0x40, 0x40, 0x40, 0x40,
    0x7F, 0x02, 0x1C, 0x02, 0x7F,
    0x7F, 0x04, 0x08, 0x10, 0x7F,
    0x3E, 0x41, 0x41, 0x41, 0x3E,
    0x7F, 0x09, 0x09, 0x09, 0x06,
    0x3E, 0x41, 0x51, 0x21, 0x5E,
    0x7F, 0x09, 0x19, 0x29, 0x46, // R
    0x26, 0x49, 0x49, 0x49, 0x32, // S
    0x03, 0x01, 0x7F, 0x01, 0x03,
    0x3F, 0x40, 0x40, 0x40, 0x3F,
    0x1F, 0x20, 0x40, 0x20, 0x1F,
    0x3F, 0x40, 0x38, 0x40, 0x3F,
    0x63, 0x14, 0x08, 0x14, 0x63,
    0x03, 0x04, 0x78, 0x04, 0x03,
    0x61, 0x59, 0x49, 0x4D, 0x43,
    0x00, 0x7F, 0x41, 0x41, 0x41,
    0x02, 0x04, 0x08, 0x10, 0x20,
    0x00, 0x41, 0x41, 0x41, 0x7F,
    0x04, 0x02, 0x01, 0x02, 0x04,
    0x40, 0x40, 0x40, 0x40, 0x40,
    0x00, 0x03, 0x07, 0x08, 0x00,
    0x20, 0x54, 0x54, 0x78, 0x40,
    0x7F, 0x28, 0x44, 0x44, 0x38,
    0x38, 0x44, 0x44, 0x44, 0x28,
    0x38, 0x44, 0x44, 0x28, 0x7F,
    0x38, 0x54, 0x54, 0x54, 0x18,
    0x00, 0x08, 0x7E, 0x09, 0x02,
    0x18, 0xA4, 0xA4, 0x9C, 0x78,
    0x7F, 0x08, 0x04, 0x04, 0x78,
    0x00, 0x44, 0x7D, 0x40, 0x00,
    0x20, 0x40, 0x40, 0x3D, 0x00,
    0x7F, 0x10, 0x28, 0x44, 0x00,
    0x00, 0x41, 0x7F, 0x40, 0x00,
    0x7C, 0x04, 0x78, 0x04, 0x78,
    0x7C, 0x08, 0x04, 0x04, 0x78,
    0x38, 0x44, 0x44, 0x44, 0x38,
    0xFC, 0x18, 0x24, 0x24, 0x18,
    0x18, 0x24, 0x24, 0x18, 0xFC,
    0x7C, 0x08, 0x04, 0x04, 0x08,
    0x48, 0x54, 0x54, 0x54, 0x24,
    0x04, 0x04, 0x3F, 0x44, 0x24,
    0x3C, 0x40, 0x40, 0x20, 0x7C,
    0x1C, 0x20, 0x40, 0x20, 0x1C,
    0x3C, 0x40, 0x30, 0x40, 0x3C,
    0x44, 0x28, 0x10, 0x28, 0x44,
    0x4C, 0x90, 0x90, 0x90, 0x7C,
    0x44, 0x64, 0x54, 0x4C, 0x44,
    0x00, 0x08, 0x36, 0x41, 0x00,
    0x00, 0x00, 0x77, 0x00, 0x00,
    0x00, 0x41, 0x36, 0x08, 0x00,
    0x02, 0x01, 0x02, 0x04, 0x02};

bool canWriteOnBuffer = false;
bool invertNibble = true;

int swapNibbles(int x)
{
    return ((x & 0x0F) << 4 | (x & 0xF0) >> 4);
}

void buffer_setPixel(int x, int y, uint16_t col)
{
    uint8_t lo = (col & 0xFF);
    m_frameBuffer[y * TFT_WIDTH * 2 + x *2] = col >> 8;
    m_frameBuffer[y * TFT_WIDTH * 2 + x *2 + 1] = lo;
}
void buffer_drawFastHLine(uint8_t x, uint8_t y, uint8_t w, uint16_t color)
{
    uint8_t hi, lo;
    if ((x >= TFT_WIDTH) || (y >= TFT_HEIGHT))
        return;
    if ((x + w - 1) >= TFT_WIDTH)
        w = TFT_WIDTH - x;
    while (w--)
    {
        buffer_setPixel(x + w, y, color);
    }
}
void buffer_drawFastVLine(uint8_t x, uint8_t y, uint8_t h, uint16_t color)
{
    if ((x >= TFT_WIDTH) || (y >= TFT_HEIGHT))
        return;
    if ((y + h - 1) >= TFT_HEIGHT)
        h = TFT_HEIGHT - y;
    while (h--)
    {
        buffer_setPixel(x, y + h, color);
    }
}
void buffer_fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color)
{
    int16_t i;
    for (i = x; i < x + w; i++)
    {
        buffer_drawFastVLine(i, y, h, color);
    }
}

void buffer_setTextWrap(bool w)
{
    m_textWrap = w;
}

void buffer_drawChar(uint8_t x, uint8_t y, uint8_t c, uint16_t color, uint16_t bg, uint8_t size)
{
    int8_t i, j;
    if ((x >= TFT_WIDTH) || (y >= TFT_HEIGHT))
        return;
    if (size < 1)
        size = 1;
    if ((c < ' ') || (c > '~'))
        c = '?';
    for (i = 0; i < 5; i++)
    {
        uint8_t line;
        line = charSet[(c - LCD_ASCII_OFFSET) * 5 + i];
        for (j = 0; j < 7; j++, line >>= 1)
        {
            if (line & 0x01)
            {
                if (size == 1)
                    buffer_setPixel(x + i, y + j, color);
                else
                    buffer_fillRect(x + (i * size), y + (j * size), size, size, color);
            }
            else if (bg != color)
            {
                if (size == 1)
                    buffer_setPixel(x + i, y + j, bg);
                else
                    buffer_fillRect(x + i * size, y + j * size, size, size, bg);
            }
        }
    }
}

void buffer_drawText(uint8_t x, uint8_t y, const char *_text, uint16_t color, uint16_t bg, uint8_t size)
{
    uint8_t cursor_x, cursor_y;
    uint16_t textsize, i;
    cursor_x = x, cursor_y = y;
    textsize = strlen(_text);
    for (i = 0; i < textsize; i++)
    {
        if (m_textWrap && ((cursor_x + size * 5) > TFT_WIDTH))
        {
            cursor_x = 0;
            cursor_y = cursor_y + size * 7 + 3;
            if (cursor_y > TFT_HEIGHT)
                cursor_y = TFT_HEIGHT;
            if (_text[i] == LCD_ASCII_OFFSET)
            {
                continue;
            }
        }

        buffer_drawChar(cursor_x, cursor_y, _text[i], color, bg, size);
        cursor_x = cursor_x + size * 6;
        if (cursor_x > TFT_WIDTH)
        {
            cursor_x = TFT_WIDTH;
        }
    }
}

void buffer_fillBuffer(uint16_t color)
{
    memset(m_frameBuffer, color, BUFFER_SIZE * 2);
}

void swapBuffer()
{
    m_currentBuffer = !m_currentBuffer;
    if (m_currentBuffer)
    {
        m_frameBuffer = m_buffer1;
        m_sentBuffer = m_buffer2;
    }
    else
    {
        m_frameBuffer = m_buffer2;
        m_sentBuffer = m_buffer1;
    }

    tft_dc_high();
    tft_cs_low();

    dma_channel_set_read_addr(dma_tx, m_sentBuffer, true);
}

bool lcdInit()
{
    printf("Initializing LCD\n");

    uint baud = spi_init(LCD_SPI_PORT, LCD_CLK_SPD); // SPI with 1Mhz

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
    printf("Enabling SPI Protocol for TFT with Clock Speed [%d hz] \n", baud);

    tft_spi_init(LCD_CS, LCD_DC, LCD_RES);
    sleep_ms(60);

    printf("Setting up buffer \n");
    m_buffer1 = (uint8_t *)malloc(sizeof(uint8_t) * (160 * 128) * 2);
    m_buffer2 = (uint8_t *)malloc(sizeof(uint8_t) * (160 * 128) * 2);
    m_frameBuffer = m_buffer1;
    m_sentBuffer = m_buffer2;

    printf("Setup DMA\n");
    bi_decl(bi_3pins_with_func(LCD_MISO, LCD_SDA, LCD_SCL, GPIO_FUNC_SPI));
    bi_decl(bi_1pin_with_name(LCD_CS, "SPI CS"));

    dma_tx = dma_claim_unused_channel(true);
    hw_set_bits(&spi_get_hw(LCD_SPI_PORT)->cr1, SPI_SSPCR1_LBM_BITS);

    printf("Configure TX DMA\n");

    dma_channel_config c = dma_channel_get_default_config(dma_tx);
    channel_config_set_transfer_data_size(&c, DMA_SIZE_8);
    channel_config_set_bswap(&c, false);
    channel_config_set_dreq(&c, spi_get_dreq(LCD_SPI_PORT, true));

    dma_channel_configure(dma_tx, &c,
                          &spi_get_hw(LCD_SPI_PORT)->dr, // write address
                          m_frameBuffer,                 // read address
                          (160 * 128) * 2,               // element count (each element is of size transfer_data_size)
                          false);                        // don't start yet

    printf("Set up IRQ for DMA\n");

    dma_channel_set_irq0_enabled(dma_tx, true);
    irq_set_exclusive_handler(DMA_IRQ_0, updateBuffer);
    irq_set_enabled(DMA_IRQ_0, true);

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
    buffer_fillBuffer(ST7735_BLACK);
    sleep_ms(60);

    canWriteOnBuffer = true;
    
    return true;
}

int testY = 0;
int spdY = 1;

void lcdUpdate(uint64_t u)
{

    if (!canWriteOnBuffer)
        return;

    swapBuffer();
    testY += spdY;
    if (testY >= 30 || testY <= 0)
    {
        if (testY < 0)
            testY = 0;
        if (testY > 30)
            testY = 30;
        spdY = -spdY;
    }

    buffer_fillBuffer(ST7735_BLACK);

    buffer_drawText(20 + 35, 10 + testY + 20, "Working!", ST7735_GREEN, ST7735_BLACK, 1);
    buffer_drawFastHLine(0 + 35, 0 + testY + 20, 80, ST7735_GREEN);
    buffer_drawFastHLine(0 + 35, 25 + testY + 20, 80, ST7735_BLUE);
    buffer_drawFastVLine(0 + 35, 0 + testY + 20, 25, ST7735_YELLOW);
    buffer_drawFastVLine(80 + 35, 0 + testY + 20, 25, ST7735_RED);

    buffer_drawText(0, 0, "ngl it's pretty pogger with DMA", ST7735_GREEN, ST7735_BLACK, 1);
    canWriteOnBuffer = false;
}

void updateBuffer()
{
    dma_hw->ints0 = 1u << dma_tx;
    canWriteOnBuffer = true;
    tft_cs_high();
   setAddrWindow(0, 0, 0 + TFT_WIDTH - 1, 0 + TFT_HEIGHT - 1);
}
