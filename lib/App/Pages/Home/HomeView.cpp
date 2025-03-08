#include "HomeView.h"
#include <cstdio>
 
using namespace Page;


void HomeView::Create(lv_obj_t *root)
{
    lv_obj_set_style_border_width(root, 0, LV_PART_MAIN);
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(root, lv_color_hex(0), LV_PART_MAIN);
    //建立个按键和test
    lv_obj_t * btn = lv_button_create(root);
    lv_obj_set_size(btn, 100, 50);
    lv_obj_center(btn);

    lv_obj_t * btn_label = lv_label_create(btn);
    lv_label_set_text(btn_label, "Click me!");
    lv_obj_center(btn_label);
    ui.botton.cont = btn;

    lv_obj_t * info_label = lv_label_create(root);
    lv_label_set_text(info_label, "The last button event:\nNone");
    lv_obj_align(info_label, LV_ALIGN_BOTTOM_MID, 0, 0);
    ui.lable.cont = info_label;
    //lv_obj_add_event_cb(btn, event_cb, LV_EVENT_ALL, info_label);
    
}




void HomeView::Delete()
{
    printf("CandleLightView::Delete()\n");
}

