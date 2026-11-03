#include <libpynq.h>
#include <unistd.h>
#include "init.h"
#include "UART.h"

#define MAX_LENGTH 130 //should be modified according to the length of the JSON_string file

char JSON_string[MAX_LENGTH];
const char *msg = "{\"ping\": {\"id\": \"1748765334567\", \"timestamp_ms\": 1748765334567, \"payload\": \"ABCDEFAB\"}, \"coordinates\": {\"X\": 50.82, \"Y\": 20.5}}\n";//tbr

int main (void)
{
  init();
  pid_t p=fork(), dis=fork();
  if(p!=0 && dis!=0)
  {
    while(get_button_state(BUTTON0)==0)
    {
      UART0_receive(JSON_string);
      UART1_new_coord(JSON_string);
    }
  }
  
  else if(p==0 && dis!=0)
  {
    char message[256];
    while(1)
    {
      if(get button_state(BUTTON1)==1)
        message="1";
      if(get button_state(BUTTON2)==1)
        message="2";
      if(get button_state(BUTTON3)==1)
        message="3";
      
    }
    UART0_send_mess(message);
    exit(0);
  }
  
  else if(p!==0 && dis==0)
  {
    //display code
    exit(0);
  }
  
  /*else if(p==0 && dis!=0)
  {
    for(int i=0; i<=128; i++)
    {
      uart_send(UART0, *msg);
      msg++;
      }
    sleep_msec(500);
    exit(0);
  } *///fork for simulating the mainframe

      sleep_msec(400);
      pynq_destroy();
  return EXIT_SUCCESS;
}   
    /*coord_receive(&x, &y);
    printf("%.2f, %.2f", x, y);
    fflush(stdout);*/
    