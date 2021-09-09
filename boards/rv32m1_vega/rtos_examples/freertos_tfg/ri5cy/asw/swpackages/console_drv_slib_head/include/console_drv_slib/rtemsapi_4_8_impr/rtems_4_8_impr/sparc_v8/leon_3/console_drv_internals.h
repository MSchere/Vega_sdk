#ifndef CONSOLE_DRV_SLIB__RTEMSAPI_4_8_IMPR__RTEMS_4_8_IMPR_SPARC_V8__LEON_3__CONSOLE_DRV_INTERNALS_H
#define CONSOLE_DRV_SLIB__RTEMSAPI_4_8_IMPR__RTEMS_4_8_IMPR_SPARC_V8__LEON_3__CONSOLE_DRV_INTERNALS_H

/**
 * @brief get conf word
 */
#define amba_get_confword(tab, index, word) (*((tab).addr[(index)]+(word)))


/**
 * @brief get vendor
 */
#define amba_vendor(x) (((x) >> 24) & 0xff)


/**
 * @brief get device
 */
#define amba_device(x) (((x) >> 12) & 0xfff)


/**
 * @brief get membar
 */
#define amba_apb_get_membar(tab, index) (*((tab).addr[(index)]+1))


/**
 * @brief get start of iobar
 */
#define amba_iobar_start(base, iobar) ((base) | ((((iobar) & 0xfff00000)>>12) & (((iobar) & 0xfff0)<<4)) )


/**
 * @brief get interrupt number
 */
#define amba_irq(conf) ((conf) & 0x1f)


extern volatile LEON3_UART_Regs_Map *_LEON3_Console_Uart[LEON3_APBUARTS];

/**
 * @brief Console UARTs identifiers. These identifiers are used to index
 * the registers of the UARTs in the _LEON3_Console_Uart.
 */
#define CONSOLE_UART_A_ID 0
#define CONSOLE_UART_B_ID 1

int amba_find_apbslvs(amba_confarea_type * amba_conf, int vendor, int device ,
                                  amba_apb_device * devs, int maxno);

void console_outbyte_polled_uart_a(unsigned char ch);

void console_outbyte_polled_uart_b(unsigned char ch);

#endif // CONSOLE_DRV_SLIB__RTEMSAPI_4_8_IMPR__RTEMS_4_8_IMPR_SPARC_V8__LEON_3__CONSOLE_DRV_INTERNALS_H
