/*
 * MIT License
 * Copyright (c) 2021 _VIFEXTech
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <cstdio>
#include "Config/Config.h"

#include "Common/DataProc/DataProc.h"
#include "Resource/ResourcePool.h"
#include "Utils/PageManager/PageManager.h"

#include "Pages/AppFactory.hpp"
 
#include "Pages/CandleLight/CandleLight.h"
 
 

#if CONFIG_MONKEY_TEST_ENABLE
#include "Utils/lv_monkey/lv_monkey.h"
#endif

#define ACCOUNT_SEND_CMD(ACT, CMD)                                         \
    do                                                                     \
    {                                                                      \
        DataProc::ACT##_Info_t info;                                       \
        memset(&info, 0, sizeof(info));                                    \
        info.cmd = DataProc::CMD;                                          \
        DataProc::Center()->AccountMain.Notify(#ACT, &info, sizeof(info)); \
    } while (0)

    extern "C" void
    App_Init()
{
    static AppFactory factory;
    static PageManager manager(&factory);

 
 
    DataProc_Init();

    lv_obj_t *scr = lv_scr_act();
    lv_obj_remove_style_all(scr);
    // Disable all widgets scroll are IMPORTANT!!!
    lv_obj_clear_flag(scr, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(scr, LV_OBJ_FLAG_GESTURE_BUBBLE);
    //lv_disp_set_bg_color(lv_disp_get_default(), lv_color_black());

    ResourcePool::Init();

    //StatusBar::Init(lv_layer_top());
    // Lưu ý cần đúng tên class, sai tên load không ra, không chạy
    manager.Install("Startup", "Pages/Startup");
    manager.Install("CandleLight", "Pages/CandleLight");
    manager.Install("AppLumia", "Pages/AppLumia");

    manager.SetGlobalLoadAnimType(PageManager::LOAD_ANIM_OVER_TOP, 500);

    manager.Push("Pages/Startup");
}

extern "C" void App_Uninit()
{
}
