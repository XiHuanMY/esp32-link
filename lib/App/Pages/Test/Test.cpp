#include "Test.h"
#include <cstdio>


using namespace Page;

Test::Test()
{
}

Test::~Test()
{
}

void Test::onCustomAttrConfig()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_TOP, 500, lv_anim_path_ease_in);



    
}

void Test::onViewLoad()
{
     
    Model.Init();
    View.Create(root);

    AttachEvent(root);
}

void Test::onViewDidLoad()
{
}

void Test::onViewWillAppear()
{
    lv_obj_set_style_opa(root, LV_OPA_TRANSP, 0);
    lv_obj_fade_in(root, 300, 0);
}

void Test::onViewDidAppear()
{
    
}

void Test::onViewWillDisappear()
{
    lv_obj_fade_out(root, 300, 0);
}

void Test::onViewDidDisappear()
{
}

void Test::onViewDidUnload()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 500, lv_anim_path_ease_in);
    View.Delete();
    Model.Deinit();
}

void Test::AttachEvent(lv_obj_t *obj)
{
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_GESTURE, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void Test::Update()
{

}

void Test::onTimer(lv_timer_t *timer)
{

}




void Test::onEvent(lv_event_t *event)
{

    lv_obj_t *obj = (lv_obj_t *)lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);
    Test *instance = (Test *)lv_obj_get_user_data(obj);

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
}
