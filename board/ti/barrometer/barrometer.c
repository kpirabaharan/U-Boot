/* This file hooks board_late_init() and causes the four AM335X Starter Kit LEDS to blink */

#include <common.h>

#define GPIO_1	(0x4804C000) 

#define GPIO_OE_OFFSET 		(0x134)
#define GPIO_DATAIN_OFFSET	(0x138)
#define GPIO_DATAOUT_OFFSET	(0x13C)

#define AM335X_LED1		(1 << 7)
#define AM335X_LED2		(1 << 6)
#define AM335X_LED3		(1 << 5)
#define AM335X_LED4		(1 << 4)

static volatile uint32_t * sp_gpio_reg_base = (volatile uint32_t *) GPIO_1;

static uint32_t read_gpio_reg (uint32_t offset)
{
	return *(sp_gpio_reg_base + (offset/4));
} 

static void write_gpio_reg (uint32_t offset, uint32_t value)
{
	*(sp_gpio_reg_base + (offset/4)) = value;
} 

static void set_gpio_reg_bits (uint32_t offset, uint32_t bitmap)
{
	uint32_t value = read_gpio_reg (offset);
	value |= bitmap;
	write_gpio_reg (offset, value);
}

static void clear_gpio_reg_bits (uint32_t offset, uint32_t bitmap)
{
	uint32_t value = read_gpio_reg (offset);
	value &= ~bitmap;
	write_gpio_reg (offset, value);
}

static void set_gpio_direction (uint32_t inputs, uint32_t outputs)
{
	set_gpio_reg_bits (GPIO_OE_OFFSET, inputs);
	clear_gpio_reg_bits (GPIO_OE_OFFSET, outputs);
}

static void set_gpio_state (uint32_t low, uint32_t high)
{
	clear_gpio_reg_bits (GPIO_DATAOUT_OFFSET, low);
	set_gpio_reg_bits (GPIO_DATAOUT_OFFSET, high);
}

static uint32_t get_gpio_direction (void)
{
	return read_gpio_reg (GPIO_DATAOUT_OFFSET);
}

int board_late_init(void)
{
        int x = 0;

        printf ("Barrometer board_late_init\n");
        
	while (x<10)
	{
		// Set all LEDs to outputs	
		set_gpio_direction (0, AM335X_LED1 | AM335X_LED2 | AM335X_LED3 | AM335X_LED4);

		// Turn all LEDs on
		set_gpio_state (0, AM335X_LED1 | AM335X_LED2 | AM335X_LED3 | AM335X_LED4);

		udelay(200000);

		// Turn all LEDs off
		set_gpio_state (AM335X_LED1 | AM335X_LED2 | AM335X_LED3 | AM335X_LED4, 0);

		udelay(200000);
		x++;
	}


        return 0;
}

