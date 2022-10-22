#include<libpynq.h>

int xy_axis[13]={109, 110, 111, 112, 113, 114, 121, 122, 123, 124, 125, 126, 127};

void UART1_send_coord(char JSON_string[], int off)
{
for(int i=0; i<=13; i++)
    if(JSON_string[xy_axis[i]+off]!='}')
        uart_send(UART1, JSON_string[xy_axis[i]+off]);
uart_send(UART1, '\n');
}