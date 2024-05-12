#define MCU_API_GLOBAL

#include "wifi.h"

/**
 * @brief  hex转bcd
 * @param[in] {Value_H} 高字节
 * @param[in] {Value_L} 低字节
 * @return 转换完成后数据
 */
unsigned char hex_to_bcd(unsigned char Value_H,unsigned char Value_L)
{
    unsigned char bcd_value;
    
    if((Value_H >= '0') && (Value_H <= '9'))
        Value_H -= '0';
    else if((Value_H >= 'A') && (Value_H <= 'F'))
        Value_H = Value_H - 'A' + 10;
    else if((Value_H >= 'a') && (Value_H <= 'f'))
        Value_H = Value_H - 'a' + 10;
     
    bcd_value = Value_H & 0x0f;
    
    bcd_value <<= 4;
    if((Value_L >= '0') && (Value_L <= '9'))
        Value_L -= '0';
    else if((Value_L >= 'A') && (Value_L <= 'F'))
        Value_L = Value_L - 'a' + 10;
    else if((Value_L >= 'a') && (Value_L <= 'f'))
        Value_L = Value_L - 'a' + 10;
    
    bcd_value |= Value_L & 0x0f;

    return bcd_value;
}

/**
 * @brief  求字符串长度
 * @param[in] {str} 字符串地址
 * @return 数据长度
 */
unsigned long my_strlen(unsigned char *str)  
{
    unsigned long len = 0;
    if(str == NULL) { 
        return 0;
    }
    
    for(len = 0; *str ++ != '\0'; ) {
        len ++;
    }
    
    return len;
}

/**
 * @brief  把src所指内存区域的前count个字节设置成字符c
 * @param[out] {src} 待设置的内存首地址
 * @param[in] {ch} 设置的字符
 * @param[in] {count} 设置的内存长度
 * @return 待设置的内存首地址
 */
void *my_memset(void *src,unsigned char ch,unsigned short count)
{
    unsigned char *tmp = (unsigned char *)src;
    
    if(src == NULL) {
        return NULL;
    }
    
    while(count --) {
        *tmp ++ = ch;
    }
    
    return src;
}

/**
 * @brief  内存拷贝
 * @param[out] {dest} 目标地址
 * @param[in] {src} 源地址
 * @param[in] {count} 拷贝数据个数
 * @return 数据处理完后的源地址
 */
void *my_memcpy(void *dest, const void *src, unsigned short count)  
{  
    unsigned char *pdest = (unsigned char *)dest;  
    const unsigned char *psrc  = (const unsigned char *)src;  
    unsigned short i;
    
    if(dest == NULL || src == NULL) { 
        return NULL;
    }
    
    if((pdest <= psrc) || (pdest > psrc + count)) {  
        for(i = 0; i < count; i ++) {  
            pdest[i] = psrc[i];  
        }  
    }else {
        for(i = count; i > 0; i --) {  
            pdest[i - 1] = psrc[i - 1];  
        }  
    }  
    
    return dest;  
}

/**
 * @brief  字符串拷贝
 * @param[in] {dest} 目标地址
 * @param[in] {src} 源地址
 * @return 数据处理完后的源地址
 */
char *my_strcpy(char *dest, const char *src)  
{
    if((NULL == dest) || (NULL == src)) {
        return NULL;
    }
    
    char *p = dest;
    while(*src!='\0') {
        *dest++ = *src++;
    }
    *dest = '\0';
    return p;
}

/**
 * @brief  拷贝指定长度字符串
 * @param[in] {dest} 目标地址
 * @param[in] {src} 源地址
 * @param[in] {len} 长度
 * @return 数据处理完后的源地址
 */
char *my_strncpy(char *dest, const char *src, unsigned int len)
{
    if (NULL == dest || NULL == src)
	{
		return NULL;
	}
	char *r = dest;
	while (len-- > 0 && (*r++ = *src++) != '\0')
		;
	return dest;
}

/**
 * @brief  查找字符串
 * @param[in] {str} 要进行搜索的字符串
 * @param[in] {subStr} 要搜索的目标字符串
 * @return 数据处理完后的源地址
 */
char *my_strstr(const char *str, const char *subStr)
{
	if (NULL == str || NULL == subStr)
	{
		return NULL;
	}
	while (*str)
	{
		const char *s1 = str;
		const char *s2 = subStr;
		while ('\0' != *s1 && '\0' != *s2 && *s1 == *s2)
		{
			s1++;
			s2++;
		}
		if ('\0' == *s2)
		{
			return (char *)str;
		}
		else if ('\0' == *s1)
		{
			return NULL;
		}
		str++;
	}
	return NULL;
}

/**
 * @brief  字符串比较
 * @param[in] {s1} 字符串 1
 * @param[in] {s2} 字符串 2
 * @return 大小比较值
 * -         0:s1=s2
 * -         <0:s1<s2
 * -         >0:s1>s2
 */
int my_strcmp(char *s1 , char *s2)
{
    while( *s1 && *s2 && *s1 == *s2 ) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

/**
 * @brief  将int类型拆分四个字节
 * @param[in] {number} 4字节原数据
 * @param[out] {value} 处理完成后4字节数据
 * @return Null
 */
void int_to_byte(unsigned long number,unsigned char value[4])
{
    value[0] = number >> 24;
    value[1] = number >> 16;
    value[2] = number >> 8;
    value[3] = number & 0xff;
}

/**
 * @brief  将4字节合并为1个32bit变量
 * @param[in] {value} 4字节数组
 * @return 合并完成后的32bit变量
 */
unsigned long byte_to_int(const unsigned char value[4])
{
    unsigned long nubmer = 0;

    nubmer = (unsigned long)value[0];
    nubmer <<= 8;
    nubmer |= (unsigned long)value[1];
    nubmer <<= 8;
    nubmer |= (unsigned long)value[2];
    nubmer <<= 8;
    nubmer |= (unsigned long)value[3];
    
    return nubmer;
}


/**
 * @brief  串口接收数据暂存处理
 * @param[in] {value} 串口收到的1字节数据
 * @return Null
 * @note   在MCU串口处理函数中调用该函数,并将接收到的数据作为参数传入
 */
void uart_receive_input(unsigned char value)
{
    // #error "请在串口接收中断中调用uart_receive_input(value),串口数据由MCU_SDK处理,用户请勿再另行处理,完成后删除该行" 
    
    if(1 == rx_buf_out - rx_buf_in) {
        //串口接收缓存已满
    }else if((rx_buf_in > rx_buf_out) && ((rx_buf_in - rx_buf_out) >= sizeof(wifi_uart_rx_buf))) {
        //串口接收缓存已满
    }else {
        //串口接收缓存未满
        if(rx_buf_in >= (unsigned char *)(wifi_uart_rx_buf + sizeof(wifi_uart_rx_buf))) {
            rx_buf_in = (unsigned char *)(wifi_uart_rx_buf);
        }
        
        *rx_buf_in ++ = value;
    }
}

/**
 * @brief  串口接收多个字节数据暂存处理
 * @param[in] {value} 串口要接收的数据的源地址
 * @param[in] {data_len} 串口要接收的数据的数据长度
 * @return Null
 * @note   如需要支持一次多字节缓存，可调用该函数
 */
void uart_receive_buff_input(unsigned char value[], unsigned short data_len)
{
    // #error "请在需要一次缓存多个字节串口数据处调用此函数,串口数据由MCU_SDK处理,用户请勿再另行处理,完成后删除该行" 
    
    unsigned short i = 0;
    for(i = 0; i < data_len; i++) {
        uart_receive_input(value[i]);
    }
}

/**
 * @brief  wifi串口数据处理服务
 * @param  Null
 * @return Null
 * @note   在MCU主函数while循环中调用该函数
 */
void wifi_uart_service(void)
{
    // #error "请直接在main函数的while(1){}中添加wifi_uart_service(),调用该函数不要加任何条件判断,完成后删除该行" 
    static unsigned short rx_in = 0;
    unsigned short offset = 0;
    unsigned short rx_value_len = 0;
    
    while((rx_in < sizeof(wifi_data_process_buf)) && with_data_rxbuff() > 0) {
        wifi_data_process_buf[rx_in ++] = take_byte_rxbuff();
    }
    
    if(rx_in < PROTOCOL_HEAD)
        return;
    
    while((rx_in - offset) >= PROTOCOL_HEAD) {
        if(wifi_data_process_buf[offset + HEAD_FIRST] != FRAME_FIRST) {
            offset ++;
            continue;
        }
        
        rx_value_len += (wifi_data_process_buf[offset + LENGTH_LOW]);
        if(rx_value_len > sizeof(wifi_data_process_buf)) {
            offset ++;
            continue;
        }

        
        if((rx_in - offset) < rx_value_len) {
            break;
        }
        
        //数据接收完成
        if(get_check_sum((unsigned char *)wifi_data_process_buf + offset,rx_value_len - 1) != wifi_data_process_buf[offset + rx_value_len - 1]) {
            //校验出错
            //printf("crc error (crc:0x%X  but data:0x%X)\r\n",get_check_sum((unsigned char *)wifi_data_process_buf + offset,rx_value_len - 1),wifi_data_process_buf[offset + rx_value_len - 1]);
            offset += 3;
            continue;
        }
        
        extern void dump_hex(const uint8_t *buf, uint32_t size, uint32_t number);
        printf("rx:\r\n");
        dump_hex((const uint8_t *)wifi_data_process_buf + offset, rx_value_len, 8);
        
        data_handle(offset);
        offset += rx_value_len;
    }//end while

    rx_in -= offset;
    if(rx_in > 0) {
        my_memcpy((char *)wifi_data_process_buf, (const char *)wifi_data_process_buf + offset, rx_in);
    }
}

/**
 * @brief  协议串口初始化函数
 * @param  Null
 * @return Null
 * @note   在MCU初始化代码中调用该函数
 */
void wifi_protocol_init(void)
{
    // #error " 请在main函数中添加wifi_protocol_init()完成wifi协议初始化,并删除该行"
    rx_buf_in = (unsigned char *)wifi_uart_rx_buf;
    rx_buf_out = (unsigned char *)wifi_uart_rx_buf;
}



