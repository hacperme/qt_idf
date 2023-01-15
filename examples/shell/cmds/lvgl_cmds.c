/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "nr_micro_shell.h"
#include <ctype.h>

#include <SDL2/SDL.h>
#include "lvgl.h"
#include "monitor.h"
#include "mouse.h"
#include "keyboard.h"
#include "mousewheel.h"

// #include "lv_demo.h"

// #if USE_LV_IMG_JPEG_DECODER
// #include "lv_img_jpeg_decoder.h"
// #endif

// #if USE_LV_IMG_PNG_DECODER
// #include "lv_img_png_decoder.h"
// #endif

// #if LV_USE_FS_IF
// #include "lv_fs_if/lv_fs_if.h"
// #endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void hal_init(void);
static int lv_tick_thread(void *data);
static void memory_monitor(lv_task_t *param);
static int lv_gui_main_thread(void *data);
static void lv_demo_task(lv_task_t *param);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_indev_t *kb_indev;
static SDL_Thread *lv_gui_main_thread_ref = NULL;
static SDL_Thread *lv_gui_tick_thread_ref = NULL;
static lv_task_t *lv_monitor_task = NULL;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

// int main(int argc, char **argv)
// {
//     (void)argc;
//     (void)argv;

//     /* Tick init.
//      * You have to call 'lv_tick_inc()' in periodically to inform LittelvGL about
//      * how much time were elapsed Create an SDL thread to do this */
//     lv_gui_tick_thread_ref = SDL_CreateThread(lv_tick_thread, "tick", NULL);

//     lv_gui_main_thread_ref = SDL_CreateThread(lv_gui_main_thread, "lv_gui_main", NULL);

//     while (1)
//     {

//         SDL_Delay(10000);
//     }

//     return 0;
// }

/**********************
 *   STATIC FUNCTIONS
 **********************/

static int lv_gui_main_thread(void *data)
{
    (void)data;

    /*Initialize LittlevGL*/
    lv_init();

    /*Initialize the HAL for LittlevGL*/
    hal_init();

    lv_task_t *lv_demo_task_p = lv_task_create(lv_demo_task, 50, LV_TASK_PRIO_MID, NULL);
    lv_task_once(lv_demo_task_p);

    while (1)
    {
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        lv_task_handler();
        SDL_Delay(5); /*Just to let the system breathe */
    }

    return 0;
}

void lv_demo_qrcode_barcode(void)
{
    lv_obj_t * btn = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_size(btn, 100, 50);
    lv_obj_align(btn, NULL, LV_ALIGN_CENTER, 0, 0);


}

static void lv_demo_task(lv_task_t *param)
{
    (void)param; /*Unused*/

    /*
     * Demos, benchmarks, and tests.
     *
     * Uncomment any one (and only one) of the functions below to run that
     * item.
     */

    // lv_demo_img_png();
    // lv_demo_img_jpg();
    lv_demo_qrcode_barcode();
}

/**
 * Initialize the Hardware Abstraction Layer (HAL) for the Littlev graphics library
 */
static void hal_init(void)
{
    /* Add a display
     * Use the 'monitor' driver which creates window on PC's monitor to simulate a display*/
    monitor_init();

    static lv_disp_buf_t disp_buf1;
    static lv_color_t buf1_1[LV_HOR_RES_MAX * 120];
    lv_disp_buf_init(&disp_buf1, buf1_1, NULL, LV_HOR_RES_MAX * 120);

    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv); /*Basic initialization*/
    disp_drv.buffer = &disp_buf1;
    disp_drv.flush_cb = monitor_flush;
    lv_disp_drv_register(&disp_drv);

    /* Add the mouse (or touchpad) as input device
     * Use the 'mouse' driver which reads the PC's mouse*/
#if 0
    mouse_init();
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv); /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = mouse_read; /*This function will be called periodically (by the library) to get the mouse position and state*/
    lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv);

    /*Set a cursor for the mouse*/
     LV_IMG_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
     lv_obj_t * cursor_obj = lv_img_create(lv_scr_act(), NULL); /*Create an image object for the cursor */
     lv_img_set_src(cursor_obj, &mouse_cursor_icon);           /*Set the image source*/
     lv_indev_set_cursor(mouse_indev, cursor_obj);             /*Connect the image  object to the driver*/
#endif

    /* If the PC keyboard driver is enabled in`lv_drv_conf.h`
     * add this as an input device. It might be used in some examples. */
#if USE_KEYBOARD
    lv_indev_drv_t kb_drv;
    lv_indev_drv_init(&kb_drv);
    kb_drv.type = LV_INDEV_TYPE_KEYPAD;
    kb_drv.read_cb = keyboard_read;
    kb_indev = lv_indev_drv_register(&kb_drv);
#endif

#if LV_USE_FS_IF
    // lv_fs_if_init();
#endif

    /*Add the mousewheel as input device.*/
    lv_indev_drv_t enc_drv;
    lv_indev_drv_init(&enc_drv);
    enc_drv.type = LV_INDEV_TYPE_ENCODER;
    enc_drv.read_cb = mousewheel_read;
    lv_indev_drv_register(&enc_drv);

    #if USE_LV_IMG_JPEG_DECODER
        // lv_jpeg_decoder_init();
    #endif

    #if USE_LV_IMG_PNG_DECODER
        // lv_png_decoder_init();
    #endif

}

/**
 * Print the memory usage periodically
 * @param param
 */
static void memory_monitor(lv_task_t *param)
{
    (void)param; /*Unused*/

    lv_mem_monitor_t mon;
    lv_mem_monitor(&mon);
    printf("used: %6d (%3d %%), frag: %3d %%, biggest free: %6d\n",
           (int)mon.total_size - mon.free_size, mon.used_pct, mon.frag_pct,
           (int)mon.free_biggest_size);
}

/**
 * A task to measure the elapsed time for LVGL
 * @param data unused
 * @return never return
 */
static int lv_tick_thread(void *data)
{
    (void)data;

    while (1)
    {
        SDL_Delay(5);   /*Sleep for 5 millisecond*/
        lv_tick_inc(5); /*Tell LittelvGL that 5 milliseconds were elapsed*/
    }

    return 0;
}

void shell_lvgl_cmd(int argc, char *argv)
{

    if (argc > 1)
    {
        if (strcmp(&(argv[(int)argv[1]]), "init") == 0)
        {
            if (lv_gui_tick_thread_ref == NULL)
                lv_gui_tick_thread_ref = SDL_CreateThread(lv_tick_thread, "lv_tick", NULL);

            if (lv_gui_main_thread_ref == NULL)
                lv_gui_main_thread_ref = SDL_CreateThread(lv_gui_main_thread, "lv_gui_main", NULL);
        }
        else if (strcmp(&(argv[(int)argv[1]]), "deinit") == 0)
        {
            shell_printf("not support now\r\n");
        }
        else if (strcmp(&(argv[(int)argv[1]]), "monitor") == 0)
        {
            if (argc != 3)
            {
                shell_printf("lvgl error\r\n");
                return;
            }
            if (strcmp(&(argv[(int)argv[2]]), "on") == 0)
            {
                if (lv_monitor_task == NULL)
                    lv_monitor_task = lv_task_create(memory_monitor, 5000, LV_TASK_PRIO_MID, NULL);
            }
            else if (strcmp(&(argv[(int)argv[2]]), "off") == 0)
            {
                if (lv_monitor_task != NULL)
                {
                    lv_task_del(lv_monitor_task);
                    lv_monitor_task = NULL;
                }
            }
        }
    }
    else
    {
        shell_printf("lvgl <cmds>\r\n");
    }
}
