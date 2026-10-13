#include<libpynq.h>

void coord_receive(float *x, float *y)
{
    *x=0;
    *y=0;
    int c=0;
    uint8_t f_safe=0;
        do
        {
            while(!uart_has_data(UART1)){}
            f_safe=uart_recv(UART1);
        }while(f_safe!=255); //failsafe: The 2 boards are not syncronyzed. Coordinates might be lost or be read from the midle. This failsafe makes the program wait untill a 255 is send than it start receiving the coordinates.

    while(1)
    {
        uint8_t current=uart_recv(UART1);
        if(current==255)
            break;
        if(current==',')
        {
            c=1;
            current=uart_recv(UART1);
        }

        if(c==0)
            *x=*x*10+current;
        else 
            *y=*y*10+current;
    }
    *x/=100.00;
    *y/=100.00;
}
