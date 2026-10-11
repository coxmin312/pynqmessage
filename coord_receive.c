#include<libpynq.h>

void coord_receive()
{
    float x=0, y=0;
    bool c=false;

    for(int i=0; i<=13; i++)
    {
        if(c==false)
            x+=(uart_recv(UART0)-48)*10;
        else if(c==true)
            y+=(uart_recv(UART0)-48)*10;
        if(uart_recv(UART0)==',')
            c=true;
    }
    x\=100;
    y\=100;
}