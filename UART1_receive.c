#include<libpynq.h>

void UART1_receive(char JSON_string[])
{
    int i=0;
    while(1)
    {
        JSON_string[i]=uart_recv(UART1);
        printf("%c", JSON_string[i]);
        fflush(stdout);
        //printf("-%d ", i);
        if(JSON_string[i]=='\0')
            break;
        i++;
    }
    printf("\n");
}