#include<libpynq.h>

void UART0_pseudoreceive(int l, char JSON_string[])
{
    uint8_t msg = uart_recv(UART0);
    JSON_string[l]=msg;
    printf("%c", JSON_string[l]);
    fflush(stdout);
    
}