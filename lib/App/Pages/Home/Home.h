#ifndef __Home_PRESENTER_H
#define __Home_PRESENTER_H

#include "HomeView.h"
#include "HomeModel.h"

namespace Page
{

class Home : public PageBase
{
public:

public:
Home();
    virtual ~Home();

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
    HomeView View;
    HomeModel Model;
};

}

#endif
