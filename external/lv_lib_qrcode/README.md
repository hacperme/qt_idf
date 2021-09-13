# lv_lib_qrcode
QR code genaration with LVGL, using  [libqrencode](https://github.com/fukuchi/libqrencode)  of the release version 4.1.1 .

## Usage

- Clone this repository.

  ```sh
  git clone https://github.com/hacperme/lv_lib_qrcode.git
  ```
  
- Define the global macro "HAVE_CONFIG_H=1"  with your compiler.

  For example,  config this macro in makefile.

  ```makefile
  #-------------------------------------------------------------------------------
  # Configure default macro define
  #-------------------------------------------------------------------------------
  DFLAGS+= \
    -DHAVE_CONFIG_H=1 \
  ```

  

- Test with the demo code.

  ```c
  #include "lvgl/lvgl.h"
  #include "lv_qrcode.h"
  
  void lv_demo_qrcode(void)
  {
      lv_obj_t *cont = NULL;
      lv_obj_t *qrcode = NULL;
      const char *data = "Hello, QRcode!";
  
      cont = lv_cont_create(lv_scr_act(), NULL);
      lv_obj_set_auto_realign(cont, true);                   
      lv_obj_align_origo(cont, NULL, LV_ALIGN_CENTER, 0, 0);  
      lv_cont_set_fit(cont, LV_FIT_TIGHT);
      lv_cont_set_layout(cont, LV_LAYOUT_COLUMN_MID);
  
      qrcode = lv_qrcode_create(cont, data, 0, 0, 8);
      lv_obj_align(qrcode, NULL, LV_ALIGN_CENTER, 0, 0);
  }
  ```

