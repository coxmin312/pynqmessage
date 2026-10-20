#include <libpynq.h>
#include <pthread.h>
#include <string.h>
#include <UART.h>
#include <init.h>
// KEEP: your own #includes (the ones that provide init, UART0_receive, UART1_send_coord, ...)

#define MAX_LENGTH 130 // should be modified according to the length of the JSON_string file

/* ---------- Sender: replaces your fork() child (the mainframe) ---------- */
static void *sender_thread(void *arg) 
{
    (void)arg;

    const char *msg = "{\"ping\": {\"id\": \"56449812\", \"timestamp_ms\": 1748765334567, \"payload\": \"ABCDEFAB\"}, \"coordinates\": {\"X\": 89.75, \"Y\": 145.06}}\n"; // tbr
    for(int i=0; i<=128; i++)
    {
      uart_send(UART0, *msg);
      msg++;
    }
    sleep_msec(500);
    return NULL;                      
}

static uint8_t receive_byte(void)
{
    while (!uart_has_data(UART1)) {}
    return uart_recv(UART1);
}

int coord(double *x, double *y)
{
    static int synced = 0;      /* 'static': remembered between calls        */
    long value[2]  = {0, 0};    /* [0] = X, [1] = Y  (still x 100)           */
    int  digits[2] = {0, 0};    /* number of digits received for X and Y     */
    int  c = 0;                 /* 0 = reading X, 1 = reading Y              */
    int  error = 0;

    /* Failsafe, ONLY the first time: the boards are not synchronised, so
     * wait for a 255 before reading anything. After that we stay in step. */
    if (!synced) {
        while (receive_byte() != 255) {}
        synced = 1;
    }

    while (1)
    {
        uint8_t b = receive_byte();

        if (b == 255) {
            if (c == 0 && digits[0] == 0)
                continue;       /* 255 before any data = start marker: skip  */
            break;              /* 255 after data = end of the message       */
        }

        if (b == ',') {
            if (c == 1) error = 1;   /* second comma: not allowed            */
            c = 1;
            continue;
        }

        

        if (digits[c] >= 6) { error = 1; continue; }
        value[c] = value[c] * 10 + b ;
        digits[c]++;
    }

    /* Checks on the complete message */
    if (error)                          return 0;
    if (c != 1)                         return 0;   /* no comma          */
    if (digits[0] == 0 || digits[1] == 0) return 0; /* X or Y empty      */

    double new_x = value[0] / 100.0;
    double new_y = value[1] / 100.0;
    if (new_x < 0 || new_x > 200 || new_y < 0 || new_y > 200) return 0;

    *x = new_x;
    *y = new_y;
    return 1;
}

static void *receiver_thread(void *arg) {
    (void)arg;

    int offset=0;
    char JSON_string[MAX_LENGTH + offset];
    while (get_button_state(BUTTON0) == 0)
    {
        double x, y;
        UART0_receive(JSON_string, &offset);
        UART1_send_coord(JSON_string, offset);

        if (!coord(&x, &y)) {               /* wacht op een bericht */
            printf("Ongeldig bericht, genegeerd\n");
            continue;
        }
        printf("X=%.2f Y=%.2f\n",x, y);

    }
  return NULL;
}

int main(void) {
  init();                           
  pthread_t tx, rx;
  pthread_create(&rx, NULL, receiver_thread, NULL);
  pthread_create(&tx, NULL, sender_thread, NULL);

  pthread_join(tx, NULL);            
  pthread_join(rx, NULL);           

  sleep_msec(400);
  pynq_destroy();
  return EXIT_SUCCESS;
}