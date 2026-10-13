#include <libpynq.h>
#include "init.h"

void init(void)
{
    pynq_init();
    switchbox_set_pin(IO_PMODA1, SWB_UART0_RX);
    switchbox_set_pin(IO_PMODA2, SWB_UART1_RX);
    switchbox_set_pin(IO_PMODA7, SWB_UART0_TX);  // for coordinates
    switchbox_set_pin(IO_PMODA8, SWB_UART1_TX);  // for message
    uart_init(UART0);
    uart_init(UART1);
    uart_reset_fifos(UART0);
    uart_reset_fifos(UART1);
    buttons_init();
}