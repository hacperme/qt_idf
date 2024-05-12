#ifndef __SYSTEM_H_
#define __SYSTEM_H_

#ifdef SYSTEM_GLOBAL
  #define SYSTEM_EXTERN
#else
  #define SYSTEM_EXTERN   extern
#endif

//=============================================================================
//Byte order of the frame
//=============================================================================
#define         HEAD_FIRST                      0
#define         FRAME_TYPE                      2
#define         LENGTH_LOW                      1
#define         DATA_START                      3

//=============================================================================
//Data frame type
//=============================================================================
#define         PRODUCT_INFO_CMD                0x01                               //产品信息
#define         WORK_MODE_CMD                   0x02                               //查询MCU 设定的模块工作模式	
#define         DATA_QUERT_CMD                  0x03                               //wifi工作状态	
#define         WIFI_STATE_CMD                  0x06                               //MCU 状态上报



//=============================================================================
#define PROTOCOL_HEAD           0x04                                            //固定协议头长度
#define FRAME_FIRST             0x55                                            //帧头第一字节

//============================================================================= 
SYSTEM_EXTERN volatile unsigned char wifi_data_process_buf[PROTOCOL_HEAD + WIFI_DATA_PROCESS_LMT];     //串口数据处理缓存
SYSTEM_EXTERN volatile unsigned char wifi_uart_rx_buf[PROTOCOL_HEAD + WIFI_UART_RECV_BUF_LMT];         //串口接收缓存
SYSTEM_EXTERN volatile unsigned char wifi_uart_tx_buf[PROTOCOL_HEAD + WIFIR_UART_SEND_BUF_LMT];        //串口发送缓存
//
SYSTEM_EXTERN volatile unsigned char *rx_buf_in;
SYSTEM_EXTERN volatile unsigned char *rx_buf_out;


/**
 * @brief  写wifi_uart字节
 * @param[in] {dest} 缓存区其实地址
 * @param[in] {byte} 写入字节值
 * @return 写入完成后的总长度
 */
unsigned short set_wifi_uart_byte(unsigned short dest, unsigned char byte);

/**
 * @brief  写wifi_uart_buffer
 * @param[in] {dest} 目标地址
 * @param[in] {src} 源地址
 * @param[in] {len} 数据长度
 * @return 写入结束的缓存地址
 */
unsigned short set_wifi_uart_buffer(unsigned short dest, const unsigned char *src, unsigned short len);

/**
 * @brief  计算校验和
 * @param[in] {pack} 数据源指针
 * @param[in] {pack_len} 计算校验和长度
 * @return 校验和
 */
unsigned char get_check_sum(unsigned char *pack, unsigned short pack_len);

/**
 * @brief  向wifi串口发送一帧数据
 * @param[in] {fr_type} 帧类型
 * @param[in] {fr_ver} 帧版本
 * @param[in] {len} 数据长度
 * @return Null
 */
void wifi_uart_write_frame(unsigned char fr_type, unsigned short len);


/**
 * @brief  数据帧处理
 * @param[in] {offset} 数据起始位
 * @return Null
 */
void data_handle(unsigned short offset);

/**
 * @brief  判断串口接收缓存中是否有数据
 * @param  Null
 * @return 是否有数据
 */
unsigned char with_data_rxbuff(void);

/**
 * @brief  读取队列1字节数据
 * @param  Null
 * @return Read the data
 */
unsigned char take_byte_rxbuff(void);
#endif
  
  
