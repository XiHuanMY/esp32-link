#include "LogicAnalyzer.h"
#include <cstdio>


using namespace Page;

LogicAnalyzer::LogicAnalyzer()
{
}

LogicAnalyzer::~LogicAnalyzer()
{
}

void LogicAnalyzer::onCustomAttrConfig()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_TOP, 500, lv_anim_path_ease_in);
}

void LogicAnalyzer::onViewLoad()
{
    
    //StatusBar::Appear(false);
    Model.Init();
    View.Create(root);
    AttachEvent(root);
    // AttachEvent(View.switch_cont);
    Model.LACommand(1); // crash
}

void LogicAnalyzer::onViewDidLoad()
{
}

void LogicAnalyzer::onViewWillAppear()
{
    lv_obj_set_style_opa(root, LV_OPA_TRANSP, 0);
    lv_obj_fade_in(root, 300, 0);
}

void LogicAnalyzer::onViewDidAppear()
{
    
}

void LogicAnalyzer::onViewWillDisappear()
{
    lv_obj_fade_out(root, 300, 0);
}

void LogicAnalyzer::onViewDidDisappear()
{
}

void LogicAnalyzer::onViewDidUnload()
{
    Model.LACommand(0);
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 500, lv_anim_path_ease_in);
    View.Delete();
    Model.Deinit();
}

void LogicAnalyzer::AttachEvent(lv_obj_t *obj)
{
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_GESTURE, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void LogicAnalyzer::Update()
{

}

void LogicAnalyzer::onTimer(lv_timer_t *timer)
{

}

static int value = 0;

void LogicAnalyzer::enableHW(int value)
{
    Model.LACommand(value );
}



void LogicAnalyzer::onEvent(lv_event_t *event)
{

    lv_obj_t *obj = (lv_obj_t *)lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);
    LogicAnalyzer *instance = (LogicAnalyzer *)lv_obj_get_user_data(obj);

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
