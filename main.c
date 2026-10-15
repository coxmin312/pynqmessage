#include <libpynq.h>
#include <unistd.h>
#include "init.h"
#include "UART.h"

#define MAX_LENGTH 130 //should be modified according to the length of the JSON_string file
#define OFFSET 0 //in case there is an adittion for the message, OFFSET shall be used to increase the max length of the string. In case the message is not predifined, another function shall be used

int lun=MAX_LENGTH+OFFSET;
char JSON_string[MAX_LENGTH+OFFSET];
const char *msg = "{\"ping\": {\"id\": \"1748765334567\", \"timestamp_ms\": 1748765334567, \"payload\": \"ABCDEFAB\"}, \"coordinates\": {\"X\": 109.82, \"Y\": 15.66}}\n";//tbr
int l;
float x=0, y=0;

int main (void)
{
  init();
  pid_t p1=fork();
  if(p1!=0)
  {
    char message[256];
    printf("Message? :");
    fflush(stdout);   
    scanf(" %s", message);
    UART0_send_mess(message);
    while(get_button_state(BUTTON0)==0)
    {
      UART0_receive(JSON_string);
      UART1_send_coord(JSON_string, OFFSET);
    }
  }
  
  /*else if(p1==0)
  {
    exit(0);
  }*/
  
  
  else if(p1==0)
  {
    for(int i=0; i<=128; i++)
    {
      uart_send(UART0, *msg);
      msg++;
      }
    sleep_msec(500);
    exit(0);
  } //fork for simulating the mainframe

      sleep_msec(400);
      pynq_destroy();
  return EXIT_SUCCESS;
}   
    /*coord_receive(&x, &y);
    printf("%.2f, %.2f", x, y);
    fflush(stdout);*/
    