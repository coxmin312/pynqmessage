#include<libpynq.h>
#include<string.h>

void UART0_send_mess()
{
    size_t i;
    char message[256];
    printf("Message? :");
    fflush(stdout);   
    scanf("%s", message);
    for(i=0; i<strlen(message); i++)
        uart_send(UART0, message[i]);
}