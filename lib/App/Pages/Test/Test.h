#ifndef __Test_PRESENTER_H
#define __Test_PRESENTER_H

#include "TestView.h"
#include "TestModel.h"

namespace Page
{

class Test : public PageBase
{
public:

public:
Test();
    virtual ~Test();

    virtual void onCustomAttrConfig();
    virtual void onViewLoad();
    virtual void onViewDidLoad();
    virtual void onViewWillAppear();
    virtual void onViewDidAppear();
    virtual void onViewWillDisappear();
    virtual void onViewDidDisappear();
    virtual void onViewDidUnload();

private:
    void Update();
    void AttachEvent(lv_obj_t *obj);
    void ViewUpdatePos(lv_event_t *event);
    static void onTimer(lv_timer_t* timer);
    static void onEvent(lv_event_t* event);

private:
    TestView View;
    TestModel Model;
};

}

#endif
