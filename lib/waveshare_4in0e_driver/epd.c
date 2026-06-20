/*****************************************************************************
* | File        :   EPD_4in0e.c
* | Author      :   Waveshare team
* | Function    :   4inch e-Paper (E) Driver
* | Info        :
*----------------
* | This version:   V1.0
* | Date        :   2024-08-20
* | Info        :
*----------------
* | Modified by :   Summerfirefly (GitHub)
* | Date        :   2026-06-16
* | Info        :
* 1.Remove:
*   Unused headers
* 2.Add:
*   Some function to support partial image data send. This is useful when load
*   image data with multiple read
* -----------------------------------------------------------------------------
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "epd.h"

#include "common_op.h"

static void EPD_SPI_SendData(UBYTE Reg) {
    UBYTE i, j = Reg;
    DEV_GPIO_Mode(EPD_MOSI_PIN, 1);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    for (i = 0; i < 8; i++)
    {
        DEV_Digital_Write(EPD_CLK_PIN, 0);
        if (j & 0x80)
        {
            DEV_Digital_Write(EPD_MOSI_PIN, 1);
        }
        else
        {
            DEV_Digital_Write(EPD_MOSI_PIN, 0);
        }

        DEV_Digital_Write(EPD_CLK_PIN, 1);
        j = j << 1;
    }
    DEV_Digital_Write(EPD_CLK_PIN, 0);
    DEV_Digital_Write(EPD_CS_PIN, 1);
}

static UBYTE EPD_SPI_ReadData() {
    UBYTE i, j = 0xff;
    DEV_GPIO_Mode(EPD_MOSI_PIN, 0);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    for (i = 0; i < 8; i++)
    {
        DEV_Digital_Write(EPD_CLK_PIN, 0);
        j = j << 1;
        if (DEV_Digital_Read(EPD_MOSI_PIN))
        {
                j = j | 0x01;
        }
        else
        {
                j= j & 0xfe;
        }
        DEV_Digital_Write(EPD_CLK_PIN, 1);
    }
    DEV_Digital_Write(EPD_CLK_PIN, 0);
    DEV_Digital_Write(EPD_CS_PIN, 1);
    return j;
}

/******************************************************************************
function :  Software reset
parameter:
******************************************************************************/
static void EPD_Reset(void)
{
    DEV_Digital_Write(EPD_RST_PIN, 1);
    DEV_Delay_ms(20);
    DEV_Digital_Write(EPD_RST_PIN, 0);
    DEV_Delay_ms(2);
    DEV_Digital_Write(EPD_RST_PIN, 1);
    DEV_Delay_ms(20);
}

/******************************************************************************
function :  send command
parameter:
     Reg : Command register
******************************************************************************/
static void EPD_SendCommand(UBYTE Reg)
{
    DEV_Digital_Write(EPD_DC_PIN, 0);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    EPD_SPI_SendData(Reg);
    DEV_Digital_Write(EPD_CS_PIN, 1);
}

/******************************************************************************
function :  send data
parameter:
    Data : Write data
******************************************************************************/
static void EPD_SendData(UBYTE Data)
{
    DEV_Digital_Write(EPD_DC_PIN, 1);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    EPD_SPI_SendData(Data);
    DEV_Digital_Write(EPD_CS_PIN, 1);
}

/******************************************************************************
function :  Wait until the busy_pin goes LOW
parameter:
******************************************************************************/
static void EPD_ReadBusyH(void)
{
    while(!DEV_Digital_Read(EPD_BUSY_PIN)) {      //LOW: busy, HIGH: idle
        DEV_Delay_ms(10);
    }
    DEV_Delay_ms(100);
}

/******************************************************************************
function :  Turn On Display
parameter:
******************************************************************************/
static void EPD_TurnOnDisplay(void)
{

    EPD_SendCommand(0x04); // POWER_ON
    EPD_ReadBusyH();
    DEV_Delay_ms(200);

    //Second setting
    EPD_SendCommand(0x06);
    EPD_SendData(0x6F);
    EPD_SendData(0x1F);
    EPD_SendData(0x17);
    EPD_SendData(0x27);
    DEV_Delay_ms(200);

    EPD_SendCommand(0x12); // DISPLAY_REFRESH
    EPD_SendData(0x00);
    EPD_ReadBusyH();

    EPD_SendCommand(0x02); // POWER_OFF
    EPD_SendData(0X00);
    EPD_ReadBusyH();
}

/******************************************************************************
function :  Initialize the e-Paper register
parameter:
******************************************************************************/
void EPD_Init(void)
{
    EPD_Reset();
    EPD_ReadBusyH();
    DEV_Delay_ms(30);

    EPD_SendCommand(0xAA);    // CMDH
    EPD_SendData(0x49);
    EPD_SendData(0x55);
    EPD_SendData(0x20);
    EPD_SendData(0x08);
    EPD_SendData(0x09);
    EPD_SendData(0x18);

    EPD_SendCommand(0x01);
    EPD_SendData(0x3F);

    EPD_SendCommand(0x00);
    EPD_SendData(0x5F);
    EPD_SendData(0x69);

    EPD_SendCommand(0x05);
    EPD_SendData(0x40);
    EPD_SendData(0x1F);
    EPD_SendData(0x1F);
    EPD_SendData(0x2C);

    EPD_SendCommand(0x08);
    EPD_SendData(0x6F);
    EPD_SendData(0x1F);
    EPD_SendData(0x1F);
    EPD_SendData(0x22);

    EPD_SendCommand(0x06);
    EPD_SendData(0x6F);
    EPD_SendData(0x1F);
    EPD_SendData(0x17);
    EPD_SendData(0x17);

    EPD_SendCommand(0x03);
    EPD_SendData(0x00);
    EPD_SendData(0x54);
    EPD_SendData(0x00);
    EPD_SendData(0x44);

    EPD_SendCommand(0x60);
    EPD_SendData(0x02);
    EPD_SendData(0x00);

    EPD_SendCommand(0x30);
    EPD_SendData(0x08);

    EPD_SendCommand(0x50);
    EPD_SendData(0x3F);

    EPD_SendCommand(0x61);
    EPD_SendData(0x01);
    EPD_SendData(0x90);
    EPD_SendData(0x02);
    EPD_SendData(0x58);

    EPD_SendCommand(0xE3);
    EPD_SendData(0x2F);

    EPD_SendCommand(0x84);
    EPD_SendData(0x01);
    EPD_ReadBusyH();

}

/******************************************************************************
function :  Clear screen
parameter:
******************************************************************************/
void EPD_Clear(UBYTE color)
{
    UWORD Width, Height;
    Width = (EPD_WIDTH % 2 == 0)? (EPD_WIDTH / 2 ): (EPD_WIDTH / 2 + 1);
    Height = EPD_HEIGHT;

    EPD_SendCommand(0x10);
    for (UWORD j = 0; j < Height; j++) {
        for (UWORD i = 0; i < Width; i++) {
            EPD_SendData((color<<4)|color);
        }
    }

    EPD_TurnOnDisplay();
}

/******************************************************************************
function :  show 7 kind of color block
parameter:
******************************************************************************/
void EPD_Show7Block(void)
{
    unsigned long j, k;
    unsigned char const Color_seven[6] =
    {EPD_BLACK, EPD_YELLOW, EPD_RED, EPD_BLUE, EPD_GREEN, EPD_WHITE};

    EPD_SendCommand(0x10);
    for(k = 0 ; k < 6; k ++) {
        for(j = 0 ; j < 20000; j ++) {
            EPD_SendData((Color_seven[k]<<4) |Color_seven[k]);
        }
    }
    EPD_TurnOnDisplay();
}

/******************************************************************************
function :  Sends the image buffer in RAM to e-Paper and displays
parameter:
******************************************************************************/
void EPD_Display(UBYTE *Image)
{
    UWORD Width, Height;
    Width = (EPD_WIDTH % 2 == 0)? (EPD_WIDTH / 2 ): (EPD_WIDTH / 2 + 1);
    Height = EPD_HEIGHT;

    EPD_SendCommand(0x10);
    for (UWORD j = 0; j < Height; j++) {
        for (UWORD i = 0; i < Width; i++) {
            EPD_SendData(Image[i + j * Width]);
        }
    }
    EPD_TurnOnDisplay();
}

/******************************************************************************
function :  Enter sleep mode
parameter:
******************************************************************************/
void EPD_Sleep(void)
{
    EPD_SendCommand(0x07); // DEEP_SLEEP
    EPD_SendData(0XA5);
    // EPD_ReadBusyH();
}

void EPD_StartImageSend(void)
{
    EPD_SendCommand(0x10);
}

void EPD_SendImageData(UBYTE *image, UDOUBLE size)
{
    for (UDOUBLE i = 0; i < size; ++i) {
        EPD_SendData(image[i]);
    }
}

void EPD_EndImageSend(void)
{
    EPD_TurnOnDisplay();
}
