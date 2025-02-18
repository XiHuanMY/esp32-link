#include "lvgl_indev_port.h"

static void keypad_init(void);
static void keypad_read(lv_indev_t * indev_drv, lv_indev_data_t * data);
static void touch_init(void);
static void touch_read(lv_indev_t * indev_drv, lv_indev_data_t * data);

lv_indev_t *indev_keypad;
lv_indev_t *indev_touch;
lv_group_t * group;

lv_group_t * group_touch;

void lv_port_indev_init(void)
{
    

    keypad_init();
    touch_init();

    /*Register a encoder input device*/
    indev_keypad = lv_indev_create();
    lv_indev_set_type(indev_keypad, LV_INDEV_TYPE_KEYPAD);
    lv_indev_set_read_cb(indev_keypad, keypad_read);

    /*Register a touch input device*/
    indev_touch = lv_indev_create();
    lv_indev_set_type(indev_touch, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev_touch, touch_read);

    group = lv_group_create();
    lv_indev_set_group(indev_keypad, group);
    lv_group_set_default(group);
    
}

static void keypad_init(void)
{
   keypad_driver_init(); 
}

static void touch_init(void)
{
    touch_driver_init();
}


uint32_t timeout=0;


static void touch_read(lv_indev_t * indev_drv, lv_indev_data_t * data)
{
    if(is_touched())
    {
        touch_driver_read(indev_drv, data);
        data->state = LV_INDEV_STATE_PR;
    }
    else
    {
        data->state = LV_INDEV_STATE_RELEASED;
        data->point.x = 0;
        data->point.y = 0;
    }
}


 

lv_indev_t* get_indev(void)
{
    return indev_keypad;
}

lv_group_t* get_group(void)
{
    return group;
}

static void keypad_read(lv_indev_t * indev_drv, lv_indev_data_t * data)
{
    static uint32_t last_key = 0;
    /*Get whether the a key is pressed and save the pressed key*/
    uint32_t act_key = keypad_get_key();
    if(act_key != 0) {
        data->state = LV_INDEV_STATE_PR;
        /*Translate the keys to LVGL control characters according to your key definitions*/
        switch(act_key) {
            case 1:
                act_key = LV_KEY_UP;
                break;
            case 2:
                act_key = LV_KEY_DOWN;
                break;
            case 3:
                act_key = LV_KEY_ENTER;
                break;
        }

        last_key = act_key;
    }
    else {
        data->state = LV_INDEV_STATE_REL;
    }

    data->key = last_key;
}
 