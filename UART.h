#ifndef UART_RECEIVE
#define UART_RECEIVE

void UART0_pseudoreceive(int l, char JSON_string[]);
void UART0_receive(char JSON_string[]);
void UART1_receive(char JSON_string[]);
void UART1_send_coord(char JSON_string[], int off);

#endif