// This is a blank code example
// Author: Dhairya Shah ( dhairya@nus.edu.sg )
//*****************************************************************************
// This code is intended to evauate power consumed by the Apollo3 MCU
// in various modes and clock frequencies with peripherals disabled
//*****************************************************************************

#include "am_mcu_apollo.h"
#include "am_bsp.h"
#include "am_util.h"

// UNCOMMENT only one of the below lines to activate the respective mode
//*****************************************************************************
#define normal_mode "48_MHZ"                    // Normal Mode@ 48 MHz
// #define div2_mode "24_MHZ"                   // Normal Mode@ 24 MHz
// #define turbo_spot_mode "96_MHZ"             // High-performance Mode@ 96 MHz
// #define normal_sleep "normal_sleep"          // Normal Sleeo Mode@ 48 MHz
// #define deep_sleep "deep_sleep"              // Deep Sleep Mode@48 MHz
//*****************************************************************************

int
main(void)
{
    // Select the clock source corresponding to the mode
    //*****************************************************************************
    #ifdef div2_mode
        am_hal_clkgen_control(AM_HAL_CLKGEN_CONTROL_SYSCLK_DIV2, 0);
    #elif defined (turbo_spot_mode)
    #else
        am_hal_clkgen_control(AM_HAL_CLKGEN_CONTROL_SYSCLK_MAX, 0);
    #endif
    //*****************************************************************************

    // Set the default cache configuration
    //*****************************************************************************
    am_hal_cachectrl_config(&am_hal_cachectrl_defaults);
    am_hal_cachectrl_enable();
    //*****************************************************************************

    // Turbo-Spot Mode
    //*****************************************************************************
    #ifdef turbo_spot_mode
        am_hal_burst_avail_e          eBurstModeAvailable;
        am_hal_burst_mode_e           eBurstMode;
        if ( am_hal_burst_mode_initialize(&eBurstModeAvailable) == AM_HAL_STATUS_SUCCESS )
        {
            am_hal_burst_mode_enable(AM_HAL_STATUS_SUCCESS);
        }
    #endif
    //*****************************************************************************

    // Select Sleep mode
    //*****************************************************************************
    #ifdef deep_sleep
        // deep sleep mode
        am_hal_sysctrl_sleep(AM_HAL_SYSCTRL_SLEEP_DEEP);
    #elif defined(normal_sleep)
        // normal sleep mode
        am_hal_sysctrl_sleep(AM_HAL_SYSCTRL_SLEEP_NORMAL);
    #endif
    //*****************************************************************************

    //*****************************************************************************
    // Disable UART prints
    am_bsp_uart_printf_disable();

    // Disable Debug prints
    am_bsp_debug_printf_disable();

    // Disable the debugger GPIOs saves about 1.2 uA total
    am_hal_gpio_pinconfig(20 /* SWDCLK */, g_AM_HAL_GPIO_DISABLE);
    am_hal_gpio_pinconfig(21 /* SWDIO */, g_AM_HAL_GPIO_DISABLE);

    // These two GPIOs are critical: the TX/RX connections between the Artemis module and the CH340S on the Blackboard
    // are prone to backfeeding each other. To stop this from happening, we must reconfigure those pins as GPIOs
    // and then disable them completely:
    am_hal_gpio_pinconfig(48 /* TXO-0 */, g_AM_HAL_GPIO_DISABLE);
    am_hal_gpio_pinconfig(49 /* RXI-0 */, g_AM_HAL_GPIO_DISABLE);
    //*****************************************************************************

    // Disable MCU peripherals
    //*****************************************************************************
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_IOS);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_IOM0);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_IOM1);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_IOM2);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_IOM3);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_IOM4);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_IOM5);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_UART0);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_UART1);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_ADC);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_SCARD);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_MSPI);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_PDM);
    am_hal_pwrctrl_periph_disable(AM_HAL_PWRCTRL_PERIPH_BLEL);
    //*****************************************************************************

    // Blank while loop
    //*****************************************************************************
    while (1)
    {
        // Do nothing
    }
    //*****************************************************************************
}
