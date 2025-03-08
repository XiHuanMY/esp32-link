#include "HomeView.h"
#include <cstdio>
 
using namespace Page;


void HomeView::Create(lv_obj_t *root)
{
    lv_obj_set_style_border_width(root, 0, LV_PART_MAIN);
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(root, lv_color_hex(0), LV_PART_MAIN);
 
    lv_obj_t * info_label = lv_label_create(root);
    lv_label_set_text(info_label, "The last button event:\nNone");
    lv_obj_align(info_label, LV_ALIGN_BOTTOM_MID, 0, 0);
    ui.lable.cont = info_label;
    //lv_obj_add_event_cb(btn, event_cb, LV_EVENT_ALL, info_label);
    lv_obj_t *ui_Label5 = lv_label_create(root);
    lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label5, 0);
    lv_obj_set_y(ui_Label5,0);
    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label5, "12:12");
    lv_obj_set_style_text_color(ui_Label5, lv_color_hex(0xFF6610), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label5, &lv_font_montserrat_46, LV_PART_MAIN | LV_STATE_DEFAULT);
}




void HomeView::Delete()
{
    printf("CandleLightView::Delete()\n");
}

