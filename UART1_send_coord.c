#include<libpynq.h>

int xy_axis[12]={110, 111, 112, 113, 114, 115, 123, 124, 125, 126, 127, 128}

void UART1_send_coord(char JSON_string[], int off)
{
for(int i=0; i<=12; i++)
    if(JSON_string[xy_axis[i]+off]>='0' && JSON_string[xy_axis[i]+off]<='9')
        uart_send(UART1, JSON_string[xy_axis[i]+off]);
uart_send(UART1, '\n');
}