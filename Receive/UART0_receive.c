#include<libpynq.h>

void UART0_receive(char JSON_string[], int *offset)
{
    int i=0;
    while(get_button_state(BUTTON0)==0)
    {
        JSON_string[i]=uart_recv(UART0);
        printf("%c", JSON_string[i]);
        fflush(stdout);
        //printf("%d ", i);
        //fflush(stdout);
        int j=i-1;
        if(JSON_string[i]=='}')
            if(JSON_string[j]=='}')
            {
                *offset=i;
                *offset-=128;
                printf("%d", *offset);
                fflush(stdout);
                break;
            }
        i++;
    }
}