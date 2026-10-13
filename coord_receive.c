void coord_receive(float *x, float *y)
{
    *x=0;
    *y=0;
    bool c=false;
    uint8_t f_safe=0;
    do
    {
        while(!uart_has_data(UART0)){}
        f_safe=uart_recv(UART0);
    }while(f_safe!=255); //failsafe: The 2 boards are not syncronyzed. Coordinates might be lost or be read from the miidle. This failsafe makes the program wait untill a 255 is send than it start receiving the coordinates.


    for(int i=0; i<=13; i++)
    {
        if(c==false)
            *x=*x*10+(uart_recv(UART0));
        else if(c==true)
            *y=*y*10+(uart_recv(UART0));
        if(uart_recv(UART0)==',')
            c=true;
    }
    *x/=100.00;
    *y/=100.00;
}
