#ifndef __Home_VIEW_H
#define __Home_VIEW_H

#include "../Page.h"

namespace Page
{

class HomeView
{
public:
    void Create(lv_obj_t* root);
    void Delete();

public:
    typedef struct
    {
        lv_obj_t *cont;
        const char *name;
    } item_t;

    struct
    {
        item_t lable;
        item_t botton;
    } ui;

public:

private:
};

}

#endif // !__VIEW_H
