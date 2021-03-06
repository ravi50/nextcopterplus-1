//***********************************************************
//* display_status.c
//***********************************************************

//***********************************************************
//* Includes
//***********************************************************

#include <avr/io.h>
#include <stdlib.h>
#include "io_cfg.h"
#include "glcd_driver.h"
#include "mugui.h"
#include <avr/pgmspace.h>
#include "glcd_menu.h"
#include "main.h"
#include "vbat.h"
#include <util/delay.h>
#include "menu_ext.h"
#include "mixer.h"
#include "main.h"

//************************************************************
// Prototypes
//************************************************************

void Display_status(void);

//************************************************************
// Code
//************************************************************

void Display_status(void)
{
	int16_t temp;
	uint16_t vbat_temp; 
	int8_t	pos1, pos2, pos3;
	mugui_size16_t size;
	//uint16_t x_text = 0;

	clear_buffer(buffer);

	// Display text
	LCD_Display_Text(264,(const unsigned char*)Verdana8,0,0); 	// Version text
	LCD_Display_Text(266,(const unsigned char*)Verdana8,0,12); 	// RX sync
	LCD_Display_Text(267,(const unsigned char*)Verdana8,0,24); 	// Profile
	LCD_Display_Text(23,(const unsigned char*)Verdana8,88,24); 	// Pos
		
	// Display menu and markers
	LCD_Display_Text(9, (const unsigned char*)Wingdings, 0, 59);// Down
	LCD_Display_Text(14,(const unsigned char*)Verdana8,10,55);	// Menu

	// Display values
	print_menu_text(0, 1, (62 + Config.RxMode), 45, 12); // Rx mode
	mugui_lcd_puts(itoa(transition,pBuffer,10),(const unsigned char*)Verdana8,110,24); // Raw transition value

	if (Config.RxMode == PWM)
	{
		LCD_Display_Text(24,(const unsigned char*)Verdana8,77,12); // Interrupt counter text 
		mugui_lcd_puts(itoa(InterruptCount,pBuffer,10),(const unsigned char*)Verdana8,110,12); // Interrupt counter
	}

	// Display transition point
	if (transition <= 0)
	{
		LCD_Display_Text(48,(const unsigned char*)Verdana8,45,24);
	}
	else if (transition >= 100)
	{
		LCD_Display_Text(50,(const unsigned char*)Verdana8,45,24);
	}
	else if (transition == Config.Transition_P1n)
	{
		LCD_Display_Text(49,(const unsigned char*)Verdana8,45,24);
	}
	else if (transition < Config.Transition_P1n)
	{
		LCD_Display_Text(51,(const unsigned char*)Verdana8,45,24);
	}
	else
	{
		LCD_Display_Text(52,(const unsigned char*)Verdana8,45,24);
	}


	// Don't display battery text if there are error messages
	if (General_error == 0)
	{
		// Display voltage
		uint8_t x_loc = 45;		// X location of voltage display
		uint8_t y_loc = 36;		// Y location of voltage display

		LCD_Display_Text(133,(const unsigned char*)Verdana8,0,36); 	// Battery

		vbat_temp = GetVbat();
		temp = vbat_temp/100;	// Display whole decimal part first
		mugui_text_sizestring(itoa(temp,pBuffer,10), (const unsigned char*)Verdana8, &size);
		mugui_lcd_puts(itoa(temp,pBuffer,10),(const unsigned char*)Verdana8,x_loc,y_loc);
		pos1 = size.x;

		vbat_temp = vbat_temp - (temp * 100); // Now display the parts to the right of the decimal point

		LCD_Display_Text(268,(const unsigned char*)Verdana8,(x_loc + pos1),y_loc);
		mugui_text_sizestring(".", (const unsigned char*)Verdana8, &size);
		pos3 = size.x;
		mugui_text_sizestring("0", (const unsigned char*)Verdana8, &size);
		pos2 = size.x;

		if (vbat_temp >= 10)
		{
			mugui_lcd_puts(itoa(vbat_temp,pBuffer,10),(const unsigned char*)Verdana8,(x_loc + pos1 + pos3),y_loc);
		}
		else
		{
			LCD_Display_Text(269,(const unsigned char*)Verdana8,(x_loc + pos1 + pos3),y_loc);
			mugui_lcd_puts(itoa(vbat_temp,pBuffer,10),(const unsigned char*)Verdana8,(x_loc + pos1 + pos2 + pos3),y_loc);
		}
	}
	
	// Display error messages
	if (General_error != 0)
	{
		// Prioritise error from top to bottom
		if((General_error & (1 << LVA_ALARM)) != 0)
		{
			LCD_Display_Text(134,(const unsigned char*)Verdana14,15,37);	// Battery
			LCD_Display_Text(271,(const unsigned char*)Verdana14,79,37);	// low
		}
		else if((General_error & (1 << NO_SIGNAL)) != 0)
		{
			LCD_Display_Text(75,(const unsigned char*)Verdana14,30,37); 	// No
			LCD_Display_Text(272,(const unsigned char*)Verdana14,55,37);	// signal
		}
		else if((General_error & (1 << THROTTLE_HIGH)) != 0)
		{
			LCD_Display_Text(105,(const unsigned char*)Verdana14,11,37);	// Throttle
			LCD_Display_Text(270,(const unsigned char*)Verdana14,82,37);	// high
		}
		else if((General_error & (1 << DISARMED)) != 0)
		{
			LCD_Display_Text(18,(const unsigned char*)Verdana14,25,37); 	// Disarmed
		}
	}

	// Write buffer to complete
	write_buffer(buffer);
	clear_buffer(buffer);
}
