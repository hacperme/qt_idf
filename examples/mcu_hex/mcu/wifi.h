

#ifndef __WIFI_H_
#define __WIFI_H_

#include "stdio.h"
#include "string.h"
#include "protocol.h"
#include "system.h"
#include "mcu_api.h"
#include "stdint.h"
#include "stdlib.h"

#define MCU_WIFI_SDK_VER "v1.0.4 2023/10/10"


//=============================================================================
//定义常量
//如果编译发生错误: #40: expected an identifier  DISABLE = 0, 类似这样的错误提示，可以包含头文件 #include "stm32f1xx.h" 来解决
//=============================================================================
#ifndef TRUE
#define      TRUE                1
#endif

#ifndef FALSE
#define         FALSE            0
#endif

#ifndef NULL
#define         NULL             ((void *) 0)
#endif

#ifndef SUCCESS
#define         SUCCESS          1
#endif

#ifndef ERROR
#define         ERROR            0
#endif

#ifndef INVALID
#define         INVALID          0xFF
#endif

#ifndef ENABLE
#define         ENABLE           1
#endif

#ifndef DISABLE
#define         DISABLE          0
#endif

//=============================================================================
//wifi复位状态
//=============================================================================
#define         RESET_WIFI_ERROR                0
#define         RESET_WIFI_SUCCESS              1


#endif
