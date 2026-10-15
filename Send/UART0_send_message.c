#include<libpynq.h>
#include<string.h>

void UART0_send_mess(char message[256])
{
    size_t i;
    uart_send(UART0, 255);
    for(i=0; i<strlen(message); i++)
        uart_send(UART0, message[i]);
    uart_send(UART0, '\0');
}