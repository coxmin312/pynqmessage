#ifndef UART
#define UART

void UART0_pseudoreceive(int l, char JSON_string[]);
void UART0_receive(char JSON_string[], int *offset);
void UART1_receive(char JSON_string[]);
void UART1_send_coord(char JSON_string[], int off);
void coord_receive(float *x, float *y);
void UART0_send_mess(char message[256]);

#endif