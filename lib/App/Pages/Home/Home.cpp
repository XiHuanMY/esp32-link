#include "Home.h"
#include <cstdio>


using namespace Page;

Home::Home()
{
}

Home::~Home()
{
}

void Home::onCustomAttrConfig()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_TOP, 500, lv_anim_path_ease_in);



    
}

void Home::onViewLoad()
{
     
    Model.Init();
    View.Create(root);
    AttachEvent(root);
    
    HomeView::item_t *item_grp = ((HomeView::item_t *)&View.ui);

    for (int i = 0; i < sizeof(View.ui) / sizeof(HomeView::item_t); i++)
    {
        AttachEvent(item_grp[i].cont);
    }
}

void Home::onViewDidLoad()
{
}

void Home::onViewWillAppear()
{
    lv_obj_set_style_opa(root, LV_OPA_TRANSP, 0);
    lv_obj_fade_in(root, 300, 0);
}

void Home::onViewDidAppear()
{
    
}

void Home::onViewWillDisappear()
{
    lv_obj_fade_out(root, 300, 0);
}

void Home::onViewDidDisappear()
{
}

void Home::onViewDidUnload()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 500, lv_anim_path_ease_in);
    View.Delete();
    Model.Deinit();
}

 void Home::AttachEvent(lv_obj_t *obj)
{
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void Home::Update()
{

}

void Home::onTimer(lv_timer_t *timer)
{

}




void Home::onEvent(lv_event_t *event)
{
    static uint16_t cnt = 0;
    lv_obj_t *obj = (lv_obj_t *)lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);
    Home *instance = (Home *)lv_obj_get_user_data(obj);
    //lv_event_code_t code = lv_event_get_code(event);
    //lv_obj_t * label = lv_event_get_user_data(event);
    if (obj == instance->View.ui.botton.cont)
    {
        switch(code) {
            case LV_EVENT_PRESSED:
                lv_label_set_text(instance->View.ui.lable.cont, "The last button event:\nLV_EVENT_PRESSED");       
                break;
            case LV_EVENT_CLICKED:
                instance->Model.Update(cnt);
                lv_label_set_text(instance->View.ui.lable.cont, "The last button event:\nLV_EVENT_CLICKED");
                cnt++;
                break;
            case LV_EVENT_LONG_PRESSED:
                lv_label_set_text(instance->View.ui.lable.cont, "The last button event:\nLV_EVENT_LONG_PRESSED");
                break;
            case LV_EVENT_LONG_PRESSED_REPEAT:
                lv_label_set_text(instance->View.ui.lable.cont, "The last button event:\nLV_EVENT_LONG_PRESSED_REPEAT");
                break;
            default:
                break;
        }
        
    }

    if (obj == instance->root)
    {
        if (LV_EVENT_GESTURE == code)
        {
            lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
            if (LV_DIR_LEFT == dir)
            {
                instance->Manager->Push("Pages/AppLumia");
            }
        }
    }
     
}
