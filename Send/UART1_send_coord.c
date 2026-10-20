#include<libpynq.h>

int xy_axis[13]={109, 110, 111, 112, 113, 114, 115, 122, 123, 124, 125, 126, 127};

void UART1_send_coord(char JSON_string[], int off)
{
    uart_send(UART1, 255);//for failsafe
    for(int i=0; i<=13; i++)
    {
        if(JSON_string[xy_axis[i]+off]>='0' && JSON_string[xy_axis[i]+off]<='9')
            uart_send(UART1, JSON_string[xy_axis[i]+off]-48);
        else if(JSON_string[xy_axis[i]+off]==',')
            uart_send(UART1, JSON_string[xy_axis[i]+off]);
    }     
    uart_send(UART1, 255);
    printf("\n");
}