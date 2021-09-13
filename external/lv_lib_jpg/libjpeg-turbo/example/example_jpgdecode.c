#if 0
#include "jpeglib.h"
#include "example_testorigjpg.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <setjmp.h>


typedef struct {

  struct jpeg_error_mgr pub; /* "public" fields */

  jmp_buf setjmp_buffer; /* for return to caller */

} lv_jpeg_error_manager_t;


extern const raw_jpg_img_dsc_t test_jpg;

static lv_jpeg_error_manager_t jerr;


static void jpeg_error_exit(j_common_ptr cinfo)

{

  /* cinfo->err actually points to a jerr struct */

  lv_jpeg_error_manager_t * custom_err = (lv_jpeg_error_manager_t *) cinfo->err;

  printf("[%s]jpeg decoder exit!!\n", __func__);

  (*cinfo->err->output_message)(cinfo);

  /* Jump to the setjmp point */

  longjmp(custom_err->setjmp_buffer, 1);

}


static void example_jpeg_decode(void *arg)
{
  (void)arg;
  struct jpeg_decompress_struct *jpeg_info = NULL;
  uint8_t *rgb888_buf = NULL;

  jpeg_info = malloc(sizeof(struct jpeg_decompress_struct));
  if (jpeg_info == NULL)
  {
    printf("no mem\n");
    goto err;
  }

  memset(jpeg_info, 0, sizeof(struct jpeg_decompress_struct));

  memset(&jerr, 0, sizeof(lv_jpeg_error_manager_t));
  jpeg_create_decompress(jpeg_info);
  jpeg_info->err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = jpeg_error_exit;

  if (setjmp(jerr.setjmp_buffer))
  {
    printf("[%s]: JPEG code has signaled an error\n", __func__);
    goto err_jmp;
  }

  jpeg_mem_src(jpeg_info, test_jpg.data, test_jpg.size);

  if (jpeg_read_header(jpeg_info, TRUE) == -1)
  {

    printf("[%s]: read header err !!\n", __func__);
    goto err;
  }

  if ((jpeg_start_decompress(jpeg_info) == false))
  {

    printf("[%s]: decompress failed !!\n", __func__);

    goto err;
  }

  uint32_t out_buffer_size = jpeg_info->image_width * jpeg_info->image_height * jpeg_info->num_components;
  printf("jpeg info: jpeg_info->image_width:%d, jpeg_info->image_height:%d, " \
         "jpeg_info->num_components:%d, jpeg_info->jpeg_color_space:%d, " \
         "jpeg_info->out_color_space:%d\n",
         jpeg_info->image_width, jpeg_info->image_height,
         jpeg_info->num_components, jpeg_info->jpeg_color_space,
         jpeg_info->out_color_space);
  rgb888_buf = malloc(out_buffer_size);
  if (rgb888_buf == NULL)
  {
    printf("no mem\n");
    goto err;
  }

  while (jpeg_info->output_scanline < jpeg_info->output_height)
  {
    printf("1jpeg_info->output_scanline:%d, jpeg_info->output_height:%d\n", jpeg_info->output_scanline, jpeg_info->output_height);
    JSAMPROW out_str = (JSAMPROW)(rgb888_buf + jpeg_info->output_scanline * jpeg_info->image_width * jpeg_info->num_components);

    if ((jpeg_read_scanlines(jpeg_info, &out_str, 1) != 1))
    {

      printf("lv_img_decoder_open_jpeg: scan line failed!!\n");

      goto err;
    }

    printf("2jpeg_info->output_scanline:%d, jpeg_info->output_height:%d\n", jpeg_info->output_scanline, jpeg_info->output_height);
  }



  printf("start dump img color data\r\n");

  for(int i=0;i < out_buffer_size; i++)
  {
    printf("%02X", rgb888_buf[i]);
  }
  printf("\n");

  printf("end dump img color data\r\n");



  if (jpeg_info && jpeg_info->global_state != 0)
  {
    jpeg_finish_decompress(jpeg_info);
  }


  if (rgb888_buf)
  {
    free((void *)rgb888_buf);
    rgb888_buf = NULL;
  }

  if (jpeg_info)
  {
    jpeg_destroy_decompress(jpeg_info);
    free(jpeg_info);
    jpeg_info = NULL;
  }

  printf("jpg decode ok\n");


  return;



err:

  if (jpeg_info && jpeg_info->global_state != 0)
  {
    jpeg_finish_decompress(jpeg_info);
  }

err_jmp:

  printf("jpg decode error\n");

  if (rgb888_buf)
  {
    free((void *)rgb888_buf);
    rgb888_buf = NULL;
  }

  if (jpeg_info)
  {
    jpeg_destroy_decompress(jpeg_info);
    free(jpeg_info);
    jpeg_info = NULL;
  }

  return;
}

void examlpe_jpg_img_decode(void)
{
    example_jpeg_decode(NULL);
}
#endif


