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
    
    TestView::item_t *item_grp = ((TestView::item_t *)&View.ui);

    for (int i = 0; i < sizeof(View.ui) / sizeof(TestView::item_t); i++)
    {
        AttachEvent(item_grp[i].cont);
    }
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
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
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
    static uint16_t cnt = 0;
    lv_obj_t *obj = (lv_obj_t *)lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);
    Test *instance = (Test *)lv_obj_get_user_data(obj);
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
     
}
