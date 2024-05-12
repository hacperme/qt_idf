#define SYSTEM_GLOBAL

#include "wifi.h"

#if 1

#define __is_print(ch) ((unsigned int)((ch) - ' ') < 127u - ' ')

void dump_hex(const uint8_t *buf, uint32_t size, uint32_t number)
{
    int i, j;
    char buffer[128] = {0};
    int n = 0;

    for (i = 0; i < size; i += number)
    {
        n += snprintf(buffer + n, sizeof(buffer) - n - 1, "%08X: ", i);

        for (j = 0; j < number; j++)
        {
            if (j % 8 == 0)
            {
                n += snprintf(buffer + n, sizeof(buffer) - n - 1, " ");
            }
            if (i + j < size)
                n += snprintf(buffer + n, sizeof(buffer) - n - 1, "%02X ", buf[i + j]);
            else
                n += snprintf(buffer + n, sizeof(buffer) - n - 1, "   ");
        }
        n += snprintf(buffer + n, sizeof(buffer) - n - 1, " ");

        for (j = 0; j < number; j++)
        {
            if (i + j < size)
            {
                n += snprintf(buffer + n, sizeof(buffer) - n - 1, "%c", __is_print(buf[i + j]) ? buf[i + j] : '.');
            }
        }
        n += snprintf(buffer + n, sizeof(buffer) - n - 1, "\n");
        printf("%s", buffer);
        n = 0;
        memset(buffer, 0, sizeof(buffer));
    }
}

#endif


/**
 * @brief  写wifi_uart字节
 * @param[in] {dest} 缓存区其实地址
 * @param[in] {byte} 写入字节值
 * @return 写入完成后的总长度
 */
unsigned short set_wifi_uart_byte(unsigned short dest, unsigned char byte)
{
    unsigned char *obj = (unsigned char *)wifi_uart_tx_buf + DATA_START + dest;
    
    *obj = byte;
    dest += 1;
    
    return dest;
}

/**
 * @brief  写wifi_uart_buffer
 * @param[in] {dest} 目标地址
 * @param[in] {src} 源地址
 * @param[in] {len} 数据长度
 * @return 写入结束的缓存地址
 */
unsigned short set_wifi_uart_buffer(unsigned short dest, const unsigned char *src, unsigned short len)
{
    unsigned char *obj = (unsigned char *)wifi_uart_tx_buf + DATA_START + dest;
    
    my_memcpy(obj,src,len);
    
    dest += len;
    return dest;
}

/**
 * @brief  计算校验和
 * @param[in] {pack} 数据源指针
 * @param[in] {pack_len} 计算校验和长度
 * @return 校验和
 */
unsigned char get_check_sum(unsigned char *pack, unsigned short pack_len)
{
    unsigned short i;
    unsigned char check_sum = 0;
    
    for(i = 0; i < pack_len; i ++) {
        check_sum += *pack ++;
    }
    check_sum += 2;
    
    return check_sum;
}

/**
 * @brief  串口发送一段数据
 * @param[in] {in} 发送缓存指针
 * @param[in] {len} 数据发送长度
 * @return Null
 */
static void wifi_uart_write_data(unsigned char *in, unsigned short len)
{
    if((NULL == in) || (0 == len)) {
        return;
    }

    printf("tx:\r\n");
    dump_hex((const uint8_t *)in, len, 8);
}




/**
 * @brief  向wifi串口发送一帧数据
 * @param[in] {fr_type} 帧类型
 * @param[in] {fr_ver} 帧版本
 * @param[in] {len} 数据长度
 * @return Null
 */
void wifi_uart_write_frame(unsigned char fr_type, unsigned short len)
{
    unsigned char check_sum = 0;
    
    wifi_uart_tx_buf[HEAD_FIRST] = 0x5a;
    len += PROTOCOL_HEAD;
    wifi_uart_tx_buf[LENGTH_LOW] = len & 0xff;
    wifi_uart_tx_buf[FRAME_TYPE] = fr_type;

    check_sum = get_check_sum((unsigned char *)wifi_uart_tx_buf, len - 1);
    wifi_uart_tx_buf[len - 1] = check_sum;
    
    wifi_uart_write_data((unsigned char *)wifi_uart_tx_buf, len);
    
}


/**
 * @brief  数据帧处理
 * @param[in] {offset} 数据起始位
 * @return Null
 */
void data_handle(unsigned short offset)
{
    unsigned char cmd_type = wifi_data_process_buf[offset + FRAME_TYPE];


    printf("cmd_type:0x%0X\r\n",cmd_type );

    switch(cmd_type)
    {
    
        case PRODUCT_INFO_CMD:                                  //产品信息
        break;
        case WIFI_STATE_CMD:                                    //wifi工作状态	
            char test_cmd[] = {0x01, 20, 11,23,17,15,01};
            int len = set_wifi_uart_buffer(0, (const unsigned char *)test_cmd, sizeof(test_cmd));
            wifi_uart_write_frame(WIFI_STATE_CMD, len);

        break;  
        case DATA_QUERT_CMD:                                    //命令下发
            // handle_data_query(offset, wifi_data_process_buf[offset + LENGTH_LOW] - PROTOCOL_HEAD);
        break;
        default:break;
    }
}

/**
 * @brief  判断串口接收缓存中是否有数据
 * @param  Null
 * @return 是否有数据
 */
unsigned char with_data_rxbuff(void)
{
    if(rx_buf_in != rx_buf_out)
        return 1;
    else
        return 0;
}

/**
 * @brief  读取队列1字节数据
 * @param  Null
 * @return Read the data
 */
unsigned char take_byte_rxbuff(void)
{
    unsigned char value = 0;
    
    if(rx_buf_out != rx_buf_in) {
        //有数据
        if(rx_buf_out >= (unsigned char *)(wifi_uart_rx_buf + sizeof(wifi_uart_rx_buf))) {
            //数据已经到末尾
            rx_buf_out = (unsigned char *)(wifi_uart_rx_buf);
        }
        
        value = *rx_buf_out ++;   
    }
    
    return value;
}

