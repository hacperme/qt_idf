// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.2.0
// PROJECT: Smart_Gadget

#include "ui.h"
#include "ui_helpers.h"
#include "ui_comp.h"

///////////////////// VARIABLES ////////////////////
void Up_Animation(lv_obj_t * TargetObject, int delay);
void hour_Animation(lv_obj_t * TargetObject, int delay);
void min_Animation(lv_obj_t * TargetObject, int delay);
void sec_Animation(lv_obj_t * TargetObject, int delay);
void scrolldot_Animation(lv_obj_t * TargetObject, int delay);
void ui_event_Splash(lv_event_t * e);
lv_obj_t * ui_Splash;
lv_obj_t * ui_Demo;
lv_obj_t * ui_Smart_Gadget;
lv_obj_t * ui_SLS_Logo;
void ui_event_Clock(lv_event_t * e);
lv_obj_t * ui_Clock;
lv_obj_t * ui_Clock_Panel;
lv_obj_t * ui_Dot1;
lv_obj_t * ui_Dot2;
lv_obj_t * ui_Dot3;
lv_obj_t * ui_Dot4;
lv_obj_t * ui_Dot5;
lv_obj_t * ui_Dot6;
lv_obj_t * ui_Dot7;
lv_obj_t * ui_Dot8;
lv_obj_t * ui_Clock_Number1;
lv_obj_t * ui_Clock_Number2;
lv_obj_t * ui_Clock_Number3;
lv_obj_t * ui_Clock_Number4;
lv_obj_t * ui_Min;
lv_obj_t * ui_Hour;
lv_obj_t * ui_Sec;
lv_obj_t * ui_Clock_Center;
lv_obj_t * ui_Clock_Number;
lv_obj_t * ui_Date;
lv_obj_t * ui_Scrolldots;
void ui_event_Call(lv_event_t * e);
lv_obj_t * ui_Call;
lv_obj_t * ui_Elena;
lv_obj_t * ui_Incoming;
lv_obj_t * ui_Call_Incon1;
lv_obj_t * ui_Phone1;
lv_obj_t * ui_Call_Incon2;
lv_obj_t * ui_Phone2;
lv_obj_t * ui_Avatar;
lv_obj_t * ui_Scrolldots1;
void ui_event_Chat(lv_event_t * e);
lv_obj_t * ui_Chat;
lv_obj_t * ui_Chat_container;
lv_obj_t * ui_Chat_date;
lv_obj_t * ui_C1;
lv_obj_t * ui_Chat_Panel1;
lv_obj_t * ui_Chat1;
lv_obj_t * ui_Chat_Icon1;
lv_obj_t * ui_C2;
lv_obj_t * ui_Chat_Panel2;
lv_obj_t * ui_Chat2;
lv_obj_t * ui_Chat_Icon2;
lv_obj_t * ui_Delifered;
lv_obj_t * ui_C3;
lv_obj_t * ui_Chat_Panel3;
lv_obj_t * ui_Chat3;
lv_obj_t * ui_Chat_Icon3;
lv_obj_t * ui_Scrolldots2;
void ui_event_Music_Player(lv_event_t * e);
lv_obj_t * ui_Music_Player;
lv_obj_t * ui_Music_Title;
lv_obj_t * ui_Author;
lv_obj_t * ui_Play_btn;
lv_obj_t * ui_Play;
lv_obj_t * ui_Album;
lv_obj_t * ui_Backward;
lv_obj_t * ui_Forward;
lv_obj_t * ui_Scrolldots3;
void ui_event_Weather(lv_event_t * e);
lv_obj_t * ui_Weather;
lv_obj_t * ui_Pary_Cloud;
lv_obj_t * ui_New_York;
lv_obj_t * ui_Cloud;
lv_obj_t * ui_Celsius;
lv_obj_t * ui_Weather_Icons;
lv_obj_t * ui_w1;
lv_obj_t * ui_w2;
lv_obj_t * ui_w3;
lv_obj_t * ui_W1_Num;
lv_obj_t * ui_W2_Num;
lv_obj_t * ui_W3_Num;
lv_obj_t * ui_Scrolldots4;
void ui_event_Alarm(lv_event_t * e);
lv_obj_t * ui_Alarm;
lv_obj_t * ui_Alarm_container;
lv_obj_t * ui_Set_alarm;
lv_obj_t * ui_Alarm_Comp;
lv_obj_t * ui_Alarm_Comp1;
lv_obj_t * ui_Alarm_Comp2;
lv_obj_t * ui_Alarm_Comp3;
lv_obj_t * ui_Scrolldots5;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////
void Up_Animation(lv_obj_t * TargetObject, int delay)
{
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 200);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, -30, 0);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_out);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_y);
    lv_anim_start(&PropertyAnimation_0);
    lv_anim_t PropertyAnimation_1;
    lv_anim_init(&PropertyAnimation_1);
    lv_anim_set_time(&PropertyAnimation_1, 100);
    lv_anim_set_user_data(&PropertyAnimation_1, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_1, _ui_anim_callback_set_opacity);
    lv_anim_set_values(&PropertyAnimation_1, 0, 255);
    lv_anim_set_path_cb(&PropertyAnimation_1, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_1, delay + 0);
    lv_anim_set_playback_time(&PropertyAnimation_1, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_1, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_1, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_1, 0);
    lv_anim_set_early_apply(&PropertyAnimation_1, true);
    lv_anim_start(&PropertyAnimation_1);

}
void hour_Animation(lv_obj_t * TargetObject, int delay)
{
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 1000);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_image_angle);
    lv_anim_set_values(&PropertyAnimation_0, 0, 2800);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_out);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);
    lv_anim_t PropertyAnimation_1;
    lv_anim_init(&PropertyAnimation_1);
    lv_anim_set_time(&PropertyAnimation_1, 300);
    lv_anim_set_user_data(&PropertyAnimation_1, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_1, _ui_anim_callback_set_opacity);
    lv_anim_set_values(&PropertyAnimation_1, 0, 255);
    lv_anim_set_path_cb(&PropertyAnimation_1, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_1, delay + 0);
    lv_anim_set_playback_time(&PropertyAnimation_1, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_1, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_1, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_1, 0);
    lv_anim_set_early_apply(&PropertyAnimation_1, true);
    lv_anim_start(&PropertyAnimation_1);

}
void min_Animation(lv_obj_t * TargetObject, int delay)
{
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 1000);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_image_angle);
    lv_anim_set_values(&PropertyAnimation_0, 0, 2100);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_out);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);
    lv_anim_t PropertyAnimation_1;
    lv_anim_init(&PropertyAnimation_1);
    lv_anim_set_time(&PropertyAnimation_1, 200);
    lv_anim_set_user_data(&PropertyAnimation_1, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_1, _ui_anim_callback_set_opacity);
    lv_anim_set_values(&PropertyAnimation_1, 0, 255);
    lv_anim_set_path_cb(&PropertyAnimation_1, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_1, delay + 0);
    lv_anim_set_playback_time(&PropertyAnimation_1, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_1, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_1, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_1, 0);
    lv_anim_set_early_apply(&PropertyAnimation_1, true);
    lv_anim_start(&PropertyAnimation_1);

}
void sec_Animation(lv_obj_t * TargetObject, int delay)
{
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 60000);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_image_angle);
    lv_anim_set_values(&PropertyAnimation_0, 0, 3600);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_start(&PropertyAnimation_0);
    lv_anim_t PropertyAnimation_1;
    lv_anim_init(&PropertyAnimation_1);
    lv_anim_set_time(&PropertyAnimation_1, 1000);
    lv_anim_set_user_data(&PropertyAnimation_1, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_1, _ui_anim_callback_set_opacity);
    lv_anim_set_values(&PropertyAnimation_1, 0, 255);
    lv_anim_set_path_cb(&PropertyAnimation_1, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_1, delay + 0);
    lv_anim_set_playback_time(&PropertyAnimation_1, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_1, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_1, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_1, 0);
    lv_anim_set_early_apply(&PropertyAnimation_1, true);
    lv_anim_start(&PropertyAnimation_1);

}
void scrolldot_Animation(lv_obj_t * TargetObject, int delay)
{
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 300);
    lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_y);
    lv_anim_set_values(&PropertyAnimation_0, 30, -8);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_out);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, true);
    lv_anim_start(&PropertyAnimation_0);

}

///////////////////// FUNCTIONS ////////////////////
void ui_event_Splash(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    // lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_SCREEN_LOADED) {
        Up_Animation(ui_SLS_Logo, 100);
        Up_Animation(ui_Smart_Gadget, 200);
        Up_Animation(ui_Demo, 300);
        _ui_screen_change(ui_Clock, LV_SCR_LOAD_ANIM_FADE_ON, 200, 1400);
    }
}
void ui_event_Clock(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    // lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_SCREEN_LOAD_START) {
        Up_Animation(ui_Clock_Panel, 100);
        Up_Animation(ui_Clock_Number, 300);
        Up_Animation(ui_Date, 200);
        scrolldot_Animation(ui_Scrolldots, 0);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        _ui_screen_change(ui_Call, LV_SCR_LOAD_ANIM_FADE_ON, 10, 0);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        _ui_screen_change(ui_Alarm, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0);
    }
    if(event_code == LV_EVENT_SCREEN_LOAD_START) {
        hour_Animation(ui_Hour, 200);
        min_Animation(ui_Min, 400);
        sec_Animation(ui_Sec, 0);
    }
}
void ui_event_Call(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    // lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_SCREEN_LOADED) {
        Up_Animation(ui_Avatar, 100);
        Up_Animation(ui_Elena, 200);
        Up_Animation(ui_Incoming, 300);
        Up_Animation(ui_Call_Incon1, 200);
        Up_Animation(ui_Call_Incon2, 300);
        scrolldot_Animation(ui_Scrolldots1, 0);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        _ui_screen_change(ui_Chat, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        _ui_screen_change(ui_Clock, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0);
    }
}
void ui_event_Chat(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    // lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_SCREEN_LOADED) {
        Up_Animation(ui_Chat_date, 100);
        Up_Animation(ui_C1, 200);
        Up_Animation(ui_C2, 300);
        Up_Animation(ui_C3, 400);
        scrolldot_Animation(ui_Scrolldots2, 0);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        _ui_screen_change(ui_Call, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        _ui_screen_change(ui_Music_Player, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0);
    }
}
void ui_event_Music_Player(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    // lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_SCREEN_LOADED) {
        Up_Animation(ui_Album, 100);
        Up_Animation(ui_Music_Title, 200);
        Up_Animation(ui_Author, 300);
        Up_Animation(ui_Play_btn, 200);
        Up_Animation(ui_Forward, 300);
        Up_Animation(ui_Backward, 400);
        scrolldot_Animation(ui_Scrolldots3, 0);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        _ui_screen_change(ui_Chat, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        _ui_screen_change(ui_Weather, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0);
    }
}
void ui_event_Weather(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    // lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_SCREEN_LOADED) {
        Up_Animation(ui_Cloud, 100);
        Up_Animation(ui_Pary_Cloud, 200);
        Up_Animation(ui_Celsius, 300);
        Up_Animation(ui_New_York, 400);
        Up_Animation(ui_Weather_Icons, 300);
        scrolldot_Animation(ui_Scrolldots4, 0);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        _ui_screen_change(ui_Music_Player, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        _ui_screen_change(ui_Alarm, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0);
    }
}
void ui_event_Alarm(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    // lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_SCREEN_LOADED) {
        Up_Animation(ui_Set_alarm, 100);
        Up_Animation(ui_Alarm_Comp, 200);
        Up_Animation(ui_Alarm_Comp1, 300);
        Up_Animation(ui_Alarm_Comp2, 400);
        Up_Animation(ui_Alarm_Comp3, 500);
        scrolldot_Animation(ui_Scrolldots5, 0);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
        _ui_screen_change(ui_Weather, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0);
    }
    if(event_code == LV_EVENT_GESTURE &&  lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        _ui_screen_change(ui_Clock, LV_SCR_LOAD_ANIM_FADE_ON, 0, 0);
    }
}

///////////////////// SCREENS ////////////////////
void ui_Splash_screen_init(void)
{
    ui_Splash = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Splash, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Splash, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Splash, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Demo = ui_Small_Label_create(ui_Splash);
    lv_obj_set_x(ui_Demo, 0);
    lv_obj_set_y(ui_Demo, 75);
    lv_obj_set_align(ui_Demo, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Demo, "Demo");
    lv_obj_set_style_text_color(ui_Demo, lv_color_hex(0x9C9CD9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Demo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Smart_Gadget = ui_Small_Label_create(ui_Splash);
    lv_obj_set_x(ui_Smart_Gadget, 0);
    lv_obj_set_y(ui_Smart_Gadget, 50);
    lv_obj_set_align(ui_Smart_Gadget, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Smart_Gadget, "Smart Gadget");
    lv_obj_set_style_text_color(ui_Smart_Gadget, lv_color_hex(0x000746), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Smart_Gadget, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SLS_Logo = lv_img_create(ui_Splash);
    lv_img_set_src(ui_SLS_Logo, &ui_img_sls_logo_png);
    lv_obj_set_width(ui_SLS_Logo, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SLS_Logo, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SLS_Logo, 0);
    lv_obj_set_y(ui_SLS_Logo, -50);
    lv_obj_set_align(ui_SLS_Logo, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_SLS_Logo, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_SLS_Logo, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_add_event_cb(ui_Splash, ui_event_Splash, LV_EVENT_ALL, NULL);

}
void ui_Clock_screen_init(void)
{
    ui_Clock = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Clock, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_Clock, &ui_img_pattern_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_tiled(ui_Clock, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Clock_Panel = lv_obj_create(ui_Clock);
    lv_obj_set_width(ui_Clock_Panel, 180);
    lv_obj_set_height(ui_Clock_Panel, 180);
    lv_obj_set_x(ui_Clock_Panel, 0);
    lv_obj_set_y(ui_Clock_Panel, 40);
    lv_obj_set_align(ui_Clock_Panel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Clock_Panel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Clock_Panel, 500, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Clock_Panel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Clock_Panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Dot1 = ui_Clock_Dot_create(ui_Clock_Panel);
    lv_obj_set_x(ui_Dot1, -40);
    lv_obj_set_y(ui_Dot1, 15);
    lv_obj_set_align(ui_Dot1, LV_ALIGN_TOP_RIGHT);

    ui_Dot2 = ui_Clock_Dot_create(ui_Clock_Panel);
    lv_obj_set_x(ui_Dot2, -10);
    lv_obj_set_y(ui_Dot2, 50);

    ui_Dot3 = ui_Clock_Dot_create(ui_Clock_Panel);
    lv_obj_set_x(ui_Dot3, 40);
    lv_obj_set_y(ui_Dot3, 15);
    lv_obj_set_align(ui_Dot3, LV_ALIGN_TOP_LEFT);

    ui_Dot4 = ui_Clock_Dot_create(ui_Clock_Panel);
    lv_obj_set_x(ui_Dot4, 10);
    lv_obj_set_y(ui_Dot4, 50);
    lv_obj_set_align(ui_Dot4, LV_ALIGN_TOP_LEFT);

    ui_Dot5 = ui_Clock_Dot_create(ui_Clock_Panel);
    lv_obj_set_x(ui_Dot5, 10);
    lv_obj_set_y(ui_Dot5, -50);
    lv_obj_set_align(ui_Dot5, LV_ALIGN_BOTTOM_LEFT);

    ui_Dot6 = ui_Clock_Dot_create(ui_Clock_Panel);
    lv_obj_set_x(ui_Dot6, 40);
    lv_obj_set_y(ui_Dot6, -15);
    lv_obj_set_align(ui_Dot6, LV_ALIGN_BOTTOM_LEFT);

    ui_Dot7 = ui_Clock_Dot_create(ui_Clock_Panel);
    lv_obj_set_x(ui_Dot7, -10);
    lv_obj_set_y(ui_Dot7, -50);
    lv_obj_set_align(ui_Dot7, LV_ALIGN_BOTTOM_RIGHT);

    ui_Dot8 = ui_Clock_Dot_create(ui_Clock_Panel);
    lv_obj_set_x(ui_Dot8, -40);
    lv_obj_set_y(ui_Dot8, -15);
    lv_obj_set_align(ui_Dot8, LV_ALIGN_BOTTOM_RIGHT);

    ui_Clock_Number1 = ui_Small_Label_create(ui_Clock_Panel);
    lv_obj_set_x(ui_Clock_Number1, 0);
    lv_obj_set_y(ui_Clock_Number1, 0);

    ui_Clock_Number2 = ui_Small_Label_create(ui_Clock_Panel);
    lv_obj_set_x(ui_Clock_Number2, 0);
    lv_obj_set_y(ui_Clock_Number2, 0);
    lv_obj_set_align(ui_Clock_Number2, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_Clock_Number2, "6");

    ui_Clock_Number3 = ui_Small_Label_create(ui_Clock_Panel);
    lv_obj_set_x(ui_Clock_Number3, 0);
    lv_obj_set_y(ui_Clock_Number3, 0);
    lv_obj_set_align(ui_Clock_Number3, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_Clock_Number3, "9");

    ui_Clock_Number4 = ui_Small_Label_create(ui_Clock_Panel);
    lv_obj_set_x(ui_Clock_Number4, 0);
    lv_obj_set_y(ui_Clock_Number4, 0);
    lv_obj_set_align(ui_Clock_Number4, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(ui_Clock_Number4, "3");

    ui_Min = lv_img_create(ui_Clock_Panel);
    lv_img_set_src(ui_Min, &ui_img_clock_min_png);
    lv_obj_set_width(ui_Min, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Min, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Min, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Min, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Min, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Hour = lv_img_create(ui_Clock_Panel);
    lv_img_set_src(ui_Hour, &ui_img_clock_hour_png);
    lv_obj_set_width(ui_Hour, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Hour, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Hour, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Hour, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Hour, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Sec = lv_img_create(ui_Clock_Panel);
    lv_img_set_src(ui_Sec, &ui_img_clock_sec_png);
    lv_obj_set_width(ui_Sec, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Sec, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Sec, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Sec, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Sec, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_angle(ui_Sec, 150);

    ui_Clock_Center = lv_obj_create(ui_Clock_Panel);
    lv_obj_set_width(ui_Clock_Center, 8);
    lv_obj_set_height(ui_Clock_Center, 8);
    lv_obj_set_align(ui_Clock_Center, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Clock_Center, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Clock_Center, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Clock_Center, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Clock_Center, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Clock_Center, lv_color_hex(0x1937D2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Clock_Center, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Clock_Center, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Clock_Number = lv_label_create(ui_Clock);
    lv_obj_set_width(ui_Clock_Number, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Clock_Number, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Clock_Number, 0);
    lv_obj_set_y(ui_Clock_Number, 15);
    lv_obj_set_align(ui_Clock_Number, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Clock_Number, "09:25");
    lv_obj_set_style_text_color(ui_Clock_Number, lv_color_hex(0x293062), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Clock_Number, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Clock_Number, &ui_font_Number, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Date = ui_Small_Label_create(ui_Clock);
    lv_obj_set_x(ui_Date, 0);
    lv_obj_set_y(ui_Date, 76);
    lv_label_set_text(ui_Date, "Mon 28 Oct");
    lv_obj_set_style_text_color(ui_Date, lv_color_hex(0x9C9CD9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Date, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Scrolldots = ui_Scrolldots_create(ui_Clock);
    lv_obj_set_x(ui_Scrolldots, 0);
    lv_obj_set_y(ui_Scrolldots, -8);

    lv_obj_set_style_bg_color(ui_comp_get_child(ui_Scrolldots, UI_COMP_SCROLLDOTS_D1), lv_color_hex(0x101C52),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_comp_get_child(ui_Scrolldots, UI_COMP_SCROLLDOTS_D1), 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Clock, ui_event_Clock, LV_EVENT_ALL, NULL);

}
void ui_Call_screen_init(void)
{
    ui_Call = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Call, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Call, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Call, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Call, &ui_img_pattern_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_tiled(ui_Call, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Elena = ui_Small_Label_create(ui_Call);
    lv_obj_set_x(ui_Elena, 0);
    lv_obj_set_y(ui_Elena, 0);
    lv_obj_set_align(ui_Elena, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Elena, "Elena Smith Bergman");
    lv_obj_set_style_text_color(ui_Elena, lv_color_hex(0x000746), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Elena, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Incoming = ui_Small_Label_create(ui_Call);
    lv_obj_set_x(ui_Incoming, 0);
    lv_obj_set_y(ui_Incoming, 25);
    lv_obj_set_align(ui_Incoming, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Incoming, "Incoming Call");
    lv_obj_set_style_text_color(ui_Incoming, lv_color_hex(0x9C9CD9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Incoming, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Call_Incon1 = lv_obj_create(ui_Call);
    lv_obj_set_width(ui_Call_Incon1, 60);
    lv_obj_set_height(ui_Call_Incon1, 60);
    lv_obj_set_x(ui_Call_Incon1, -50);
    lv_obj_set_y(ui_Call_Incon1, -42);
    lv_obj_set_align(ui_Call_Incon1, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(ui_Call_Incon1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Call_Incon1, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Call_Incon1, lv_color_hex(0xE63431), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Call_Incon1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Call_Incon1, lv_color_hex(0xE63431), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Call_Incon1, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_Call_Incon1, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_Call_Incon1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_Call_Incon1, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_Call_Incon1, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Call_Incon1, lv_color_hex(0xFF5855), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_Call_Incon1, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    ui_Phone1 = lv_img_create(ui_Call_Incon1);
    lv_img_set_src(ui_Phone1, &ui_img_phone_png);
    lv_obj_set_width(ui_Phone1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Phone1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Phone1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Phone1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Phone1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_angle(ui_Phone1, 1360);

    ui_Call_Incon2 = lv_obj_create(ui_Call);
    lv_obj_set_width(ui_Call_Incon2, 60);
    lv_obj_set_height(ui_Call_Incon2, 60);
    lv_obj_set_x(ui_Call_Incon2, 50);
    lv_obj_set_y(ui_Call_Incon2, -42);
    lv_obj_set_align(ui_Call_Incon2, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(ui_Call_Incon2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Call_Incon2, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Call_Incon2, lv_color_hex(0x10D262), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Call_Incon2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Call_Incon2, lv_color_hex(0x10D262), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Call_Incon2, 150, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_Call_Incon2, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_Call_Incon2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_Call_Incon2, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_Call_Incon2, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Call_Incon2, lv_color_hex(0x31EF81), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_Call_Incon2, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    ui_Phone2 = lv_img_create(ui_Call_Incon2);
    lv_img_set_src(ui_Phone2, &ui_img_phone_png);
    lv_obj_set_width(ui_Phone2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Phone2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Phone2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Phone2, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Phone2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Avatar = lv_img_create(ui_Call);
    lv_img_set_src(ui_Avatar, &ui_img_avatar_png);
    lv_obj_set_width(ui_Avatar, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Avatar, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Avatar, 0);
    lv_obj_set_y(ui_Avatar, 20);
    lv_obj_set_align(ui_Avatar, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_Avatar, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Avatar, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Avatar, 300, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Avatar, lv_color_hex(0xD5D2D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Avatar, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_Avatar, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_Avatar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_Avatar, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_Avatar, 6, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Scrolldots1 = ui_Scrolldots_create(ui_Call);
    lv_obj_set_x(ui_Scrolldots1, 0);
    lv_obj_set_y(ui_Scrolldots1, -8);

    lv_obj_set_width(ui_comp_get_child(ui_Scrolldots1, UI_COMP_SCROLLDOTS_D1), 4);
    lv_obj_set_height(ui_comp_get_child(ui_Scrolldots1, UI_COMP_SCROLLDOTS_D1), 4);

    lv_obj_set_width(ui_comp_get_child(ui_Scrolldots1, UI_COMP_SCROLLDOTS_D2), 8);
    lv_obj_set_height(ui_comp_get_child(ui_Scrolldots1, UI_COMP_SCROLLDOTS_D2), 8);
    lv_obj_set_x(ui_comp_get_child(ui_Scrolldots1, UI_COMP_SCROLLDOTS_D2), 11);
    lv_obj_set_y(ui_comp_get_child(ui_Scrolldots1, UI_COMP_SCROLLDOTS_D2), 0);
    lv_obj_set_style_bg_color(ui_comp_get_child(ui_Scrolldots1, UI_COMP_SCROLLDOTS_D2), lv_color_hex(0x101C52),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_comp_get_child(ui_Scrolldots1, UI_COMP_SCROLLDOTS_D2), 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Call, ui_event_Call, LV_EVENT_ALL, NULL);

}
void ui_Chat_screen_init(void)
{
    ui_Chat = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Chat, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_src(ui_Chat, &ui_img_pattern_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_tiled(ui_Chat, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Chat_container = lv_obj_create(ui_Chat);
    lv_obj_set_width(ui_Chat_container, lv_pct(100));
    lv_obj_set_height(ui_Chat_container, lv_pct(100));
    lv_obj_set_align(ui_Chat_container, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_Chat_container, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Chat_container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Chat_date = ui_Small_Label_create(ui_Chat_container);
    lv_obj_set_x(ui_Chat_date, 0);
    lv_obj_set_y(ui_Chat_date, 17);
    lv_obj_set_align(ui_Chat_date, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Chat_date, "Yesterday 07:25 PM");
    lv_obj_set_style_text_color(ui_Chat_date, lv_color_hex(0x000746), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Chat_date, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_C1 = lv_obj_create(ui_Chat_container);
    lv_obj_set_height(ui_C1, 100);
    lv_obj_set_width(ui_C1, lv_pct(100));
    lv_obj_set_x(ui_C1, 0);
    lv_obj_set_y(ui_C1, 60);
    lv_obj_clear_flag(ui_C1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_C1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_C1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_C1, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_C1, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_C1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_C1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Chat_Panel1 = lv_obj_create(ui_C1);
    lv_obj_set_width(ui_Chat_Panel1, 169);
    lv_obj_set_height(ui_Chat_Panel1, 81);
    lv_obj_clear_flag(ui_Chat_Panel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Chat_Panel1, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Chat_Panel1, lv_color_hex(0x9C9CD9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Chat_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Chat_Panel1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Chat_Panel1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Chat_Panel1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Chat_Panel1, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Chat1 = ui_Small_Label_create(ui_Chat_Panel1);
    lv_obj_set_width(ui_Chat1, lv_pct(100));
    lv_obj_set_height(ui_Chat1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Chat1, 0);
    lv_obj_set_y(ui_Chat1, 0);
    lv_obj_set_align(ui_Chat1, LV_ALIGN_TOP_LEFT);
    lv_label_set_text(ui_Chat1, "Let's get some dinner, how about pizza?");
    lv_obj_set_style_text_color(ui_Chat1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Chat1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Chat_Icon1 = lv_img_create(ui_C1);
    lv_img_set_src(ui_Chat_Icon1, &ui_img_chatbox_png);
    lv_obj_set_width(ui_Chat_Icon1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Chat_Icon1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Chat_Icon1, 0);
    lv_obj_set_y(ui_Chat_Icon1, 80);
    lv_obj_add_flag(ui_Chat_Icon1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Chat_Icon1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_Chat_Icon1, lv_color_hex(0x9C9CD9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_Chat_Icon1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_C2 = lv_obj_create(ui_Chat_container);
    lv_obj_set_height(ui_C2, 100);
    lv_obj_set_width(ui_C2, lv_pct(100));
    lv_obj_set_x(ui_C2, 0);
    lv_obj_set_y(ui_C2, 160);
    lv_obj_clear_flag(ui_C2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_C2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_C2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_C2, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_C2, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_C2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_C2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Chat_Panel2 = lv_obj_create(ui_C2);
    lv_obj_set_width(ui_Chat_Panel2, 169);
    lv_obj_set_height(ui_Chat_Panel2, 81);
    lv_obj_set_align(ui_Chat_Panel2, LV_ALIGN_TOP_RIGHT);
    lv_obj_clear_flag(ui_Chat_Panel2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Chat_Panel2, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Chat_Panel2, lv_color_hex(0x293062), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Chat_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Chat_Panel2, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Chat_Panel2, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Chat_Panel2, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Chat_Panel2, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Chat2 = ui_Small_Label_create(ui_Chat_Panel2);
    lv_obj_set_width(ui_Chat2, lv_pct(100));
    lv_obj_set_height(ui_Chat2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Chat2, 0);
    lv_obj_set_y(ui_Chat2, 0);
    lv_obj_set_align(ui_Chat2, LV_ALIGN_TOP_LEFT);
    lv_label_set_text(ui_Chat2, "Sounds good! What about James?");
    lv_obj_set_style_text_color(ui_Chat2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Chat2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Chat_Icon2 = lv_img_create(ui_C2);
    lv_img_set_src(ui_Chat_Icon2, &ui_img_chatbox2_png);
    lv_obj_set_width(ui_Chat_Icon2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Chat_Icon2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Chat_Icon2, 0);
    lv_obj_set_y(ui_Chat_Icon2, 80);
    lv_obj_set_align(ui_Chat_Icon2, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(ui_Chat_Icon2, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Chat_Icon2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_Chat_Icon2, lv_color_hex(0x293062), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_Chat_Icon2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Delifered = ui_Small_Label_create(ui_C2);
    lv_obj_set_x(ui_Delifered, 47);
    lv_obj_set_y(ui_Delifered, 83);
    lv_obj_set_align(ui_Delifered, LV_ALIGN_TOP_LEFT);
    lv_label_set_text(ui_Delifered, "Delivered");
    lv_obj_set_style_text_color(ui_Delifered, lv_color_hex(0x9C9CD9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Delifered, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_C3 = lv_obj_create(ui_Chat_container);
    lv_obj_set_height(ui_C3, 100);
    lv_obj_set_width(ui_C3, lv_pct(100));
    lv_obj_set_x(ui_C3, 0);
    lv_obj_set_y(ui_C3, 270);
    lv_obj_clear_flag(ui_C3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_C3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_C3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_C3, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_C3, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_C3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_C3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Chat_Panel3 = lv_obj_create(ui_C3);
    lv_obj_set_width(ui_Chat_Panel3, 169);
    lv_obj_set_height(ui_Chat_Panel3, 81);
    lv_obj_clear_flag(ui_Chat_Panel3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Chat_Panel3, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Chat_Panel3, lv_color_hex(0x9C9CD9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Chat_Panel3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_Chat_Panel3, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_Chat_Panel3, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_Chat_Panel3, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_Chat_Panel3, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Chat3 = ui_Small_Label_create(ui_Chat_Panel3);
    lv_obj_set_width(ui_Chat3, lv_pct(100));
    lv_obj_set_height(ui_Chat3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Chat3, 0);
    lv_obj_set_y(ui_Chat3, 0);
    lv_obj_set_align(ui_Chat3, LV_ALIGN_TOP_LEFT);
    lv_label_set_text(ui_Chat3, "He likes it too! Where do we meet?");
    lv_obj_set_style_text_color(ui_Chat3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Chat3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Chat_Icon3 = lv_img_create(ui_C3);
    lv_img_set_src(ui_Chat_Icon3, &ui_img_chatbox_png);
    lv_obj_set_width(ui_Chat_Icon3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Chat_Icon3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Chat_Icon3, 0);
    lv_obj_set_y(ui_Chat_Icon3, 80);
    lv_obj_add_flag(ui_Chat_Icon3, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Chat_Icon3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_Chat_Icon3, lv_color_hex(0x9C9CD9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_Chat_Icon3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Scrolldots2 = ui_Scrolldots_create(ui_Chat);
    lv_obj_set_x(ui_Scrolldots2, 0);
    lv_obj_set_y(ui_Scrolldots2, -8);

    lv_obj_set_width(ui_comp_get_child(ui_Scrolldots2, UI_COMP_SCROLLDOTS_D1), 4);
    lv_obj_set_height(ui_comp_get_child(ui_Scrolldots2, UI_COMP_SCROLLDOTS_D1), 4);

    lv_obj_set_x(ui_comp_get_child(ui_Scrolldots2, UI_COMP_SCROLLDOTS_D2), 10);
    lv_obj_set_y(ui_comp_get_child(ui_Scrolldots2, UI_COMP_SCROLLDOTS_D2), 0);

    lv_obj_set_width(ui_comp_get_child(ui_Scrolldots2, UI_COMP_SCROLLDOTS_D3), 8);
    lv_obj_set_height(ui_comp_get_child(ui_Scrolldots2, UI_COMP_SCROLLDOTS_D3), 8);
    lv_obj_set_x(ui_comp_get_child(ui_Scrolldots2, UI_COMP_SCROLLDOTS_D3), 21);
    lv_obj_set_y(ui_comp_get_child(ui_Scrolldots2, UI_COMP_SCROLLDOTS_D3), 0);
    lv_obj_set_style_bg_color(ui_comp_get_child(ui_Scrolldots2, UI_COMP_SCROLLDOTS_D3), lv_color_hex(0x101C52),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_comp_get_child(ui_Scrolldots2, UI_COMP_SCROLLDOTS_D3), 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Chat, ui_event_Chat, LV_EVENT_ALL, NULL);

}
void ui_Music_Player_screen_init(void)
{
    ui_Music_Player = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Music_Player, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Music_Player, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Music_Player, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Music_Player, &ui_img_pattern_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_tiled(ui_Music_Player, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Music_Title = ui_Small_Label_create(ui_Music_Player);
    lv_obj_set_x(ui_Music_Title, 0);
    lv_obj_set_y(ui_Music_Title, 0);
    lv_obj_set_align(ui_Music_Title, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Music_Title, "Wood and forest");
    lv_obj_set_style_text_color(ui_Music_Title, lv_color_hex(0x000746), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Music_Title, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Author = ui_Small_Label_create(ui_Music_Player);
    lv_obj_set_x(ui_Author, 0);
    lv_obj_set_y(ui_Author, 25);
    lv_obj_set_align(ui_Author, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Author, "Alan Smith");
    lv_obj_set_style_text_color(ui_Author, lv_color_hex(0x9C9CD9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Author, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Play_btn = lv_obj_create(ui_Music_Player);
    lv_obj_set_width(ui_Play_btn, 60);
    lv_obj_set_height(ui_Play_btn, 60);
    lv_obj_set_x(ui_Play_btn, 0);
    lv_obj_set_y(ui_Play_btn, -42);
    lv_obj_set_align(ui_Play_btn, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(ui_Play_btn, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Play_btn, 60, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Play_btn, lv_color_hex(0x293062), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Play_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Play_btn, lv_color_hex(0x293062), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Play_btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_Play_btn, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_Play_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_Play_btn, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_Play_btn, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Play_btn, lv_color_hex(0x515EB5), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(ui_Play_btn, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    ui_Play = lv_img_create(ui_Play_btn);
    lv_img_set_src(ui_Play, &ui_img_play_png);
    lv_obj_set_width(ui_Play, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Play, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Play, 2);
    lv_obj_set_y(ui_Play, 0);
    lv_obj_set_align(ui_Play, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Play, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Play, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Album = lv_img_create(ui_Music_Player);
    lv_img_set_src(ui_Album, &ui_img_album_png);
    lv_obj_set_width(ui_Album, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Album, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Album, 0);
    lv_obj_set_y(ui_Album, 20);
    lv_obj_set_align(ui_Album, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_Album, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Album, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Album, 300, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_Album, lv_color_hex(0xD5D2D5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_Album, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_Album, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_Album, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui_Album, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui_Album, 6, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Backward = lv_img_create(ui_Music_Player);
    lv_img_set_src(ui_Backward, &ui_img_backward_png);
    lv_obj_set_width(ui_Backward, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Backward, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Backward, 30);
    lv_obj_set_y(ui_Backward, -60);
    lv_obj_set_align(ui_Backward, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_flag(ui_Backward, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Backward, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_Backward, lv_color_hex(0x293062), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_Backward, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui_Backward, lv_color_hex(0x515EB5), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui_Backward, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    ui_Forward = lv_img_create(ui_Music_Player);
    lv_img_set_src(ui_Forward, &ui_img_forward_png);
    lv_obj_set_width(ui_Forward, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Forward, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Forward, -30);
    lv_obj_set_y(ui_Forward, -60);
    lv_obj_set_align(ui_Forward, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(ui_Forward, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Forward, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_Forward, lv_color_hex(0x293062), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_Forward, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor(ui_Forward, lv_color_hex(0x515EB5), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_img_recolor_opa(ui_Forward, 255, LV_PART_MAIN | LV_STATE_PRESSED);

    ui_Scrolldots3 = ui_Scrolldots_create(ui_Music_Player);
    lv_obj_set_x(ui_Scrolldots3, 0);
    lv_obj_set_y(ui_Scrolldots3, -8);

    lv_obj_set_width(ui_comp_get_child(ui_Scrolldots3, UI_COMP_SCROLLDOTS_D1), 4);
    lv_obj_set_height(ui_comp_get_child(ui_Scrolldots3, UI_COMP_SCROLLDOTS_D1), 4);

    lv_obj_set_x(ui_comp_get_child(ui_Scrolldots3, UI_COMP_SCROLLDOTS_D2), 10);
    lv_obj_set_y(ui_comp_get_child(ui_Scrolldots3, UI_COMP_SCROLLDOTS_D2), 0);

    lv_obj_set_x(ui_comp_get_child(ui_Scrolldots3, UI_COMP_SCROLLDOTS_D3), 20);
    lv_obj_set_y(ui_comp_get_child(ui_Scrolldots3, UI_COMP_SCROLLDOTS_D3), 0);

    lv_obj_set_width(ui_comp_get_child(ui_Scrolldots3, UI_COMP_SCROLLDOTS_D4), 8);
    lv_obj_set_height(ui_comp_get_child(ui_Scrolldots3, UI_COMP_SCROLLDOTS_D4), 8);
    lv_obj_set_x(ui_comp_get_child(ui_Scrolldots3, UI_COMP_SCROLLDOTS_D4), 31);
    lv_obj_set_y(ui_comp_get_child(ui_Scrolldots3, UI_COMP_SCROLLDOTS_D4), 0);
    lv_obj_set_style_bg_color(ui_comp_get_child(ui_Scrolldots3, UI_COMP_SCROLLDOTS_D4), lv_color_hex(0x101C52),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_comp_get_child(ui_Scrolldots3, UI_COMP_SCROLLDOTS_D4), 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Music_Player, ui_event_Music_Player, LV_EVENT_ALL, NULL);

}
void ui_Weather_screen_init(void)
{
    ui_Weather = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Weather, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Weather, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Weather, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Weather, &ui_img_pattern_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_tiled(ui_Weather, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Pary_Cloud = ui_Small_Label_create(ui_Weather);
    lv_obj_set_x(ui_Pary_Cloud, 0);
    lv_obj_set_y(ui_Pary_Cloud, -67);
    lv_obj_set_align(ui_Pary_Cloud, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Pary_Cloud, "Party cloud");
    lv_obj_set_style_text_color(ui_Pary_Cloud, lv_color_hex(0x000746), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Pary_Cloud, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_New_York = ui_Small_Label_create(ui_Weather);
    lv_obj_set_x(ui_New_York, 0);
    lv_obj_set_y(ui_New_York, 37);
    lv_obj_set_align(ui_New_York, LV_ALIGN_CENTER);
    lv_label_set_text(ui_New_York, "New York");
    lv_obj_set_style_text_color(ui_New_York, lv_color_hex(0x9C9CD9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_New_York, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Cloud = lv_img_create(ui_Weather);
    lv_img_set_src(ui_Cloud, &ui_img_cloud_png);
    lv_obj_set_width(ui_Cloud, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Cloud, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Cloud, -2);
    lv_obj_set_y(ui_Cloud, 19);
    lv_obj_set_align(ui_Cloud, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_Cloud, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Cloud, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_Cloud, lv_color_hex(0x293062), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_Cloud, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Celsius = lv_label_create(ui_Weather);
    lv_obj_set_width(ui_Celsius, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Celsius, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Celsius, 0);
    lv_obj_set_y(ui_Celsius, 125);
    lv_obj_set_align(ui_Celsius, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Celsius, "26°");
    lv_obj_set_style_text_color(ui_Celsius, lv_color_hex(0x293062), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Celsius, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Celsius, &ui_font_Number, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Weather_Icons = lv_obj_create(ui_Weather);
    lv_obj_set_height(ui_Weather_Icons, 56);
    lv_obj_set_width(ui_Weather_Icons, lv_pct(100));
    lv_obj_set_x(ui_Weather_Icons, 0);
    lv_obj_set_y(ui_Weather_Icons, -33);
    lv_obj_set_align(ui_Weather_Icons, LV_ALIGN_BOTTOM_MID);
    lv_obj_clear_flag(ui_Weather_Icons, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Weather_Icons, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Weather_Icons, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_w1 = lv_img_create(ui_Weather_Icons);
    lv_img_set_src(ui_w1, &ui_img_weather_1_png);
    lv_obj_set_width(ui_w1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_w1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_w1, 40);
    lv_obj_set_y(ui_w1, 0);
    lv_obj_add_flag(ui_w1, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_w1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_w1, lv_color_hex(0x293062), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_w1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_w2 = lv_img_create(ui_Weather_Icons);
    lv_img_set_src(ui_w2, &ui_img_weather_2_png);
    lv_obj_set_width(ui_w2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_w2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_w2, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_w2, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_w2, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_w2, lv_color_hex(0x293062), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_w2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_w3 = lv_img_create(ui_Weather_Icons);
    lv_img_set_src(ui_w3, &ui_img_weather_3_png);
    lv_obj_set_width(ui_w3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_w3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_w3, -40);
    lv_obj_set_y(ui_w3, 0);
    lv_obj_set_align(ui_w3, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(ui_w3, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_w3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_w3, lv_color_hex(0x293062), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_w3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_W1_Num = ui_Small_Label_create(ui_Weather_Icons);
    lv_obj_set_x(ui_W1_Num, 35);
    lv_obj_set_y(ui_W1_Num, 25);
    lv_obj_set_align(ui_W1_Num, LV_ALIGN_TOP_LEFT);
    lv_label_set_text(ui_W1_Num, "65°");

    ui_W2_Num = ui_Small_Label_create(ui_Weather_Icons);
    lv_obj_set_x(ui_W2_Num, 0);
    lv_obj_set_y(ui_W2_Num, 25);
    lv_obj_set_align(ui_W2_Num, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_W2_Num, "24km/h");

    ui_W3_Num = ui_Small_Label_create(ui_Weather_Icons);
    lv_obj_set_x(ui_W3_Num, -30);
    lv_obj_set_y(ui_W3_Num, 25);
    lv_obj_set_align(ui_W3_Num, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(ui_W3_Num, "18%");

    ui_Scrolldots4 = ui_Scrolldots_create(ui_Weather);
    lv_obj_set_x(ui_Scrolldots4, 0);
    lv_obj_set_y(ui_Scrolldots4, -8);

    lv_obj_set_width(ui_comp_get_child(ui_Scrolldots4, UI_COMP_SCROLLDOTS_D1), 4);
    lv_obj_set_height(ui_comp_get_child(ui_Scrolldots4, UI_COMP_SCROLLDOTS_D1), 4);

    lv_obj_set_x(ui_comp_get_child(ui_Scrolldots4, UI_COMP_SCROLLDOTS_D2), 10);
    lv_obj_set_y(ui_comp_get_child(ui_Scrolldots4, UI_COMP_SCROLLDOTS_D2), 0);

    lv_obj_set_x(ui_comp_get_child(ui_Scrolldots4, UI_COMP_SCROLLDOTS_D3), 20);
    lv_obj_set_y(ui_comp_get_child(ui_Scrolldots4, UI_COMP_SCROLLDOTS_D3), 0);

    lv_obj_set_x(ui_comp_get_child(ui_Scrolldots4, UI_COMP_SCROLLDOTS_D4), 30);
    lv_obj_set_y(ui_comp_get_child(ui_Scrolldots4, UI_COMP_SCROLLDOTS_D4), 0);

    lv_obj_set_width(ui_comp_get_child(ui_Scrolldots4, UI_COMP_SCROLLDOTS_D5), 8);
    lv_obj_set_height(ui_comp_get_child(ui_Scrolldots4, UI_COMP_SCROLLDOTS_D5), 8);
    lv_obj_set_x(ui_comp_get_child(ui_Scrolldots4, UI_COMP_SCROLLDOTS_D5), 41);
    lv_obj_set_y(ui_comp_get_child(ui_Scrolldots4, UI_COMP_SCROLLDOTS_D5), 0);
    lv_obj_set_style_bg_color(ui_comp_get_child(ui_Scrolldots4, UI_COMP_SCROLLDOTS_D5), lv_color_hex(0x101C52),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_comp_get_child(ui_Scrolldots4, UI_COMP_SCROLLDOTS_D5), 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Weather, ui_event_Weather, LV_EVENT_ALL, NULL);

}
void ui_Alarm_screen_init(void)
{
    ui_Alarm = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Alarm, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Alarm, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Alarm, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_Alarm, &ui_img_pattern_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_tiled(ui_Alarm, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Alarm_container = lv_obj_create(ui_Alarm);
    lv_obj_set_width(ui_Alarm_container, lv_pct(100));
    lv_obj_set_height(ui_Alarm_container, lv_pct(100));
    lv_obj_set_align(ui_Alarm_container, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_Alarm_container, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Alarm_container, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Set_alarm = ui_Small_Label_create(ui_Alarm_container);
    lv_obj_set_x(ui_Set_alarm, 0);
    lv_obj_set_y(ui_Set_alarm, 17);
    lv_obj_set_align(ui_Set_alarm, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Set_alarm, "Set alarm");
    lv_obj_set_style_text_color(ui_Set_alarm, lv_color_hex(0x000746), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Set_alarm, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Alarm_Comp = ui_Alarm_Comp_create(ui_Alarm_container);
    lv_obj_set_x(ui_Alarm_Comp, 0);
    lv_obj_set_y(ui_Alarm_Comp, 43);

    ui_Alarm_Comp1 = ui_Alarm_Comp_create(ui_Alarm_container);
    lv_obj_set_x(ui_Alarm_Comp1, 0);
    lv_obj_set_y(ui_Alarm_Comp1, 128);

    lv_label_set_text(ui_comp_get_child(ui_Alarm_Comp1, UI_COMP_ALARM_COMP_ALARM_NUM2), "8:00");

    lv_label_set_text(ui_comp_get_child(ui_Alarm_Comp1, UI_COMP_ALARM_COMP_PERIOD), "Breakfast");

    lv_obj_add_state(ui_comp_get_child(ui_Alarm_Comp1, UI_COMP_ALARM_COMP_SWITCH1), LV_STATE_CHECKED);       /// States

    ui_Alarm_Comp2 = ui_Alarm_Comp_create(ui_Alarm_container);
    lv_obj_set_x(ui_Alarm_Comp2, 0);
    lv_obj_set_y(ui_Alarm_Comp2, 213);

    lv_label_set_text(ui_comp_get_child(ui_Alarm_Comp2, UI_COMP_ALARM_COMP_ALARM_NUM2), "9:30");

    lv_label_set_text(ui_comp_get_child(ui_Alarm_Comp2, UI_COMP_ALARM_COMP_PERIOD), "Yoga");

    ui_Alarm_Comp3 = ui_Alarm_Comp_create(ui_Alarm_container);
    lv_obj_set_x(ui_Alarm_Comp3, 0);
    lv_obj_set_y(ui_Alarm_Comp3, 298);
    lv_obj_set_style_border_color(ui_Alarm_Comp3, lv_color_hex(0x293062), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Alarm_Comp3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Alarm_Comp3, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_Alarm_Comp3, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_label_set_text(ui_comp_get_child(ui_Alarm_Comp3, UI_COMP_ALARM_COMP_ALARM_NUM2), "11:00");

    lv_label_set_text(ui_comp_get_child(ui_Alarm_Comp3, UI_COMP_ALARM_COMP_PERIOD), "Sleep");

    ui_Scrolldots5 = ui_Scrolldots_create(ui_Alarm);
    lv_obj_set_x(ui_Scrolldots5, 0);
    lv_obj_set_y(ui_Scrolldots5, -8);

    lv_obj_set_width(ui_comp_get_child(ui_Scrolldots5, UI_COMP_SCROLLDOTS_D1), 4);
    lv_obj_set_height(ui_comp_get_child(ui_Scrolldots5, UI_COMP_SCROLLDOTS_D1), 4);

    lv_obj_set_x(ui_comp_get_child(ui_Scrolldots5, UI_COMP_SCROLLDOTS_D2), 10);
    lv_obj_set_y(ui_comp_get_child(ui_Scrolldots5, UI_COMP_SCROLLDOTS_D2), 0);

    lv_obj_set_x(ui_comp_get_child(ui_Scrolldots5, UI_COMP_SCROLLDOTS_D3), 20);
    lv_obj_set_y(ui_comp_get_child(ui_Scrolldots5, UI_COMP_SCROLLDOTS_D3), 0);

    lv_obj_set_x(ui_comp_get_child(ui_Scrolldots5, UI_COMP_SCROLLDOTS_D4), 30);
    lv_obj_set_y(ui_comp_get_child(ui_Scrolldots5, UI_COMP_SCROLLDOTS_D4), 0);

    lv_obj_set_x(ui_comp_get_child(ui_Scrolldots5, UI_COMP_SCROLLDOTS_D5), 40);
    lv_obj_set_y(ui_comp_get_child(ui_Scrolldots5, UI_COMP_SCROLLDOTS_D5), 0);

    lv_obj_set_width(ui_comp_get_child(ui_Scrolldots5, UI_COMP_SCROLLDOTS_D6), 8);
    lv_obj_set_height(ui_comp_get_child(ui_Scrolldots5, UI_COMP_SCROLLDOTS_D6), 8);
    lv_obj_set_x(ui_comp_get_child(ui_Scrolldots5, UI_COMP_SCROLLDOTS_D6), 50);
    lv_obj_set_y(ui_comp_get_child(ui_Scrolldots5, UI_COMP_SCROLLDOTS_D6), 0);
    lv_obj_set_style_bg_color(ui_comp_get_child(ui_Scrolldots5, UI_COMP_SCROLLDOTS_D6), lv_color_hex(0x101C52),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_comp_get_child(ui_Scrolldots5, UI_COMP_SCROLLDOTS_D6), 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_Alarm, ui_event_Alarm, LV_EVENT_ALL, NULL);

}

void ui_init(void)
{
    LV_EVENT_GET_COMP_CHILD = lv_event_register_id();

    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_basic_init(dispp);
    lv_disp_set_theme(dispp, theme);
    ui_Splash_screen_init();
    ui_Clock_screen_init();
    ui_Call_screen_init();
    ui_Chat_screen_init();
    ui_Music_Player_screen_init();
    ui_Weather_screen_init();
    ui_Alarm_screen_init();
    lv_disp_load_scr(ui_Splash);
}
