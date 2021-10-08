 /*
 *  Tenda W12 access point support
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/leds.h>
#include <linux/platform_device.h>
#include <linux/string.h>
#include <generated/autoconf.h>

#include "gpio.h"
#include "bspchip.h"
#include "machtypes.h"
#include "dev_leds_gpio.h"
#include "dev-gpio-buttons.h"


#define W12_BUTTONS_POLL_INTERVAL		100
#define W12_BUTTONS_DEBOUNCE_INTERVAL	(3 * W12_BUTTONS_POLL_INTERVAL)
extern void rtl819x_gpio_pin_enable(u32 pin);
extern void rtl819x_gpio_pin_set_val(u32 pin, unsigned val);

#if defined(CONFIG_RTL_8367R_SUPPORT)
#define BSP_RESET_BTN_PIN		BSP_GPIO_PIN_G6
#define BSP_8367R_RST_PIN		BSP_GPIO_PIN_H2
#define BSP_8367R_I2C_PIN1		BSP_GPIO_PIN_C2
#define BSP_8367R_I2C_PIN2		BSP_GPIO_PIN_C3
#else
#define BSP_RESET_BTN_PIN		BSP_GPIO_PIN_C3
#endif

static struct gpio_led w12_leds_gpio[] __initdata = {
	// {
		// .name		= "rtl819x:blue:lan",
		// .gpio		= BSP_LAN_LED_PIN,
		// .active_low	= 0,
	// },
	// {
		// .name		= "rtl819x:blue:wifi",
		// .gpio		= BSP_WIFI_LED_PIN,
		// .active_low	= 1,
	// }
// };

static struct gpio_keys_button w12_buttons[] __initdata = {
	{
		.desc		= "reset",
		.type		= EV_KEY,
		.code		= KEY_RESTART,
		.debounce_interval = W12_BUTTONS_DEBOUNCE_INTERVAL,
		//.threshold	= 3,
		.gpio		= BSP_RESET_BTN_PIN,		
		.active_low	= 1,
	}
};

struct gpio w12_phy_reset_pin_data = {
	.gpio		= BSP_GPIO_PIN_H2,
	.flags          = GPIOF_ACTIVE_LOW,
	.label		= "GPIO_H2",
};

static struct platform_device __initdata *w12_devs[] = {
	&rtl819x_phy_reset_pin,
};

#define SET_PINMUX(reg, field, val)\
	REG32(reg) = (REG32(reg) & (~(0xF << field))) | (val << field)



static void __init w12_setup(void)
{
	int i;


	rtl819x_phy_reset_pin.dev.platform_data = &w12_phy_reset_pin_data;

	platform_add_devices(w12_devs, ARRAY_SIZE(w12_devs));
	
	rtl819x_register_leds_gpio(-1, ARRAY_SIZE(w12_leds_gpio),
		w12_leds_gpio);

	for (i=0; i<ARRAY_SIZE(w12_leds_gpio); i++) {
		rtl819x_gpio_pin_enable(w12_leds_gpio[i].gpio);
	}

	for (i=0; i<ARRAY_SIZE(w12_buttons); i++) {
		rtl819x_gpio_pin_enable(w12_buttons[i].gpio);
	}
	rtl819x_add_device_gpio_buttons(-1, W12_BUTTONS_POLL_INTERVAL,
				       ARRAY_SIZE(w12_buttons),
				       w12_buttons);

//	w12_set_sd_pinmux();
}

MIPS_MACHINE(RTL8197_MACH_W12, "W12", "TENDA W12",
			 w12_setup);
