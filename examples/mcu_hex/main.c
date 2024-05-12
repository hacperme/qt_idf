#include<stdio.h>
#include<stdlib.h>

#include "wifi.h"


int main(int argc, char *argv[])
{
    wifi_protocol_init();

    char test_cmd[] = {0x55, 0x0B, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x68};
    uart_receive_buff_input((unsigned char *)test_cmd, sizeof(test_cmd));

    while(1)
    {
        wifi_uart_service();
    }
    printf("Hello, World!\n");
    return 0;
}
