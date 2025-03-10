#include "ServoCtrl.h"
#include <cstdio>


using namespace Page;

ServoCtrl::ServoCtrl()
{
}

ServoCtrl::~ServoCtrl()
{
}

void ServoCtrl::onCustomAttrConfig()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_TOP, 500, lv_anim_path_ease_in);



    
}

void ServoCtrl::onViewLoad()
{
    //StatusBar::Appear(false);
    Model.Init();
    View.Create(root);

    AttachGesture(root);
    ServoCtrlView::item_t *item_grp = ((ServoCtrlView::item_t *)&View.ui);

    for (int i = 0; i < sizeof(View.ui) / sizeof(ServoCtrlView::item_t); i++)
    {
        AttachEvent(item_grp[i].cont);
    }
}

void ServoCtrl::onViewDidLoad()
{
}

void ServoCtrl::onViewWillAppear()
{
    lv_obj_set_style_opa(root, LV_OPA_TRANSP, 0);
    lv_obj_fade_in(root, 300, 0);
}

void ServoCtrl::onViewDidAppear()
{
    
}

void ServoCtrl::onViewWillDisappear()
{
    lv_obj_fade_out(root, 300, 0);
}

void ServoCtrl::onViewDidDisappear()
{
}

void ServoCtrl::onViewDidUnload()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 500, lv_anim_path_ease_in);
    View.Delete();
    Model.Deinit();
}

void ServoCtrl::AttachGesture(lv_obj_t *obj)
{
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_GESTURE, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void ServoCtrl::AttachEvent(lv_obj_t *obj)
{
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
    // lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void ServoCtrl::Update()
{

}

void ServoCtrl::onTimer(lv_timer_t *timer)
{

}




void ServoCtrl::onEvent(lv_event_t *event)
{
    lv_obj_t *obj = (lv_obj_t *)lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);
    ServoCtrl *instance = (ServoCtrl *)lv_obj_get_user_data(obj);


    if (obj == instance->root)
    {
        if (LV_EVENT_GESTURE == code)
        {
            lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
            if (LV_DIR_RIGHT == dir)
            {
                instance->Manager->Pop();
            }
        }
    }

    if (obj == instance->View.ui.arc.cont)
    {
        if (code == LV_EVENT_VALUE_CHANGED)
        {
            int16_t angle = lv_arc_get_value(obj);
            lv_label_set_text_fmt(instance->View.ui.angle.cont, "%d", angle);
            printf("value changer %d\r\n", angle);
            instance->Model.ServoUpdateAngle(angle);
            lv_spinbox_set_value(instance->View.ui.spin.cont, angle);
        }
    }

    if (obj == instance->View.ui.spin.cont)
    {
        if (code == LV_EVENT_VALUE_CHANGED)
        {
            int16_t angle = lv_spinbox_get_value(obj);
            lv_arc_set_value(instance->View.ui.arc.cont, angle);
            lv_label_set_text_fmt(instance->View.ui.angle.cont, "%d", angle);
        }
    }
}