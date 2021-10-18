## qt_idf 介绍

qt_idf 是一套在 PC 上调试和开发物联网相关功能组件的开发环境，原来是基于 QT 搭建的编译环境，所以叫 qt_idf ，后来编译方式改成 cmake + bat 脚本，通过命令行进行编译。

## 目的

主要目的是在PC上有一个 C 编译环境，方便调试和验证一些与硬件平台无关的软件功能；也便于开发新的功能组件，移植到嵌入式平台。对于一些与硬件无关，对平台依赖少的软件功能，优先考虑是否在PC上调试或者使用更高级的编程语言实现（比如python）可以更方便和节省时间。

使用 qt_idf 的作用主要有以下几点：

1. 缩短调试验证的时间

   节省软件调试时在特定硬件平台上编译、下载固件、抓log、导出dump这些步骤的时间

2. 双重验证环境

   软件功能在硬件平台上运行有问题，代码基本一样，可以在PC上也测试验证一下是否同样有问题。

3. 评估软件功能实现

   移植第三方库、开发功能组件，可以先尝试在PC上实现，确定没有问题和依赖，可以再移植到硬件平台环境。

   

## 演示



打开根目录的cmd，执行编译指令：

```bat
# 设置编译环境
env

# 加载不同平台的编译配置，目前只有Windows平台的编译工具链
config

# 编译
make -j32

# 清理
make clean
```



![xxx](https://raw.githubusercontent.com/hacperme/picx_hosting/master/20210507/xxx.1hxtou77tv1c.gif)



## 如何搭建这个环境

构建工具使用 cmake + bat 脚本。

- env.bat 设置环境变量
- config.bat 配置编译工具链
- scripts\boards\project_config.cmake 和 scripts\boards\project_default_config.h.in 功能编译开关
- .github\workflows\ci.yml GitHub 流水线配置

整体的目录结构：

![xxx](https://cdn.jsdelivr.net/gh/hacperme/picx_hosting@master/20210507/xxx.1kkn8n4kjvuo.png)

## 功能

- [ ] 多媒体
  - [ ] GUI 组件
    - [x] lvgl
    - [x] qrcode 二维码编码
    - [ ] code128 条形码编码
    - [x] lv_fs_if 文件系统
    - [x] lv_drivers 显示和输入设备驱动
    - [x] lv_lib_jpg jpg 图片解码
    - [x] lv_lib_png png 图片解码
    - [ ] gif 图片解码
    - [ ] bmp 图片解码
    - [ ] freetype 支持矢量字体
  - [ ] ZBAR
  - [x] SDL2 
  - [ ] audio codec
    - [ ] Speex 
    - [ ] Opus
    - [ ] fdk-aac
    - [ ] amrnb
    - [ ] amrwb
    - [ ] mp3dec
- [ ] 网络组件
  - [x] iotkit-embedded
  - [x] libwebsocket
  - [ ] http client
  - [ ] qcloud-iot-sdk-embedded-c
  - [ ] paho MQTT
- [ ] OSA 
- [ ] 加密套件
  - [x] mbedtls
  - [ ] wolfssl
  - [ ] micro-ecc
  - [ ] TOTP
- [ ] 构建工具
  - [x] windows_x86_mingw_gcc
  - [x] github workflows
  - [ ] ninja
  - [ ] kconfig
- [ ] 序列化和反序列化
  - [x] cJSON
  - [ ] protobuf-c
  - [ ] CBOR
- [ ] 其他
  - [ ] Unity
  - [ ] bsdiff
  - [ ] KISS FFT
  - [ ] JerryScript

