//UART_Function.h
#ifndef UART_FUNCTION_H
#define UART_FUNCTION_H
#include <stdint.h>
#include "msp.h"
#include "CircBuf.h"
// enum to declare return states
typedef enum
{
	PASS = 0,
	ERR_GEN = 1,
	ERR_EXCEED_LENGTH,
	ERR_NO_VALUE,
	ERR_SYS_TIMEOUT
}UART_ERROR_VAL;
//enum to declare log states
typedef enum{
	PLAYSTART = 1,
	BUTTONPRESS,
	PITCHBEND,
	MODESWITCH,
	PLAYSTOP
}LogState;
typedef enum
{
	BAUD_VAL_38400,
	BAUD_VAL_19200
}UART_CONFIG_VAL;
void UART_Configure(UART_CONFIG_VAL UART_conf);
UART_ERROR_VAL UART_putchar(uint8_t tx_data);
UART_ERROR_VAL UART_putchar_n(uint8_t * data, uint32_t length);
void EUSCIA0_IRQHandler(void);
void configure_UART_clocks(void);
void UART_Print_Buffer(CircBuf * buf);
#endif /* UART_FUNCTION_H */
