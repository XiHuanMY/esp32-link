#include "HomeView.h"
#include <cstdio>
 
using namespace Page;

 
const char car[] = "{\"nm\":\"Main Scene\",\"ddd\":0,\"h\":500,\"w\":500,\"meta\":{\"g\":\"@lottiefiles/creator 1.15.0\"},\"layers\":[{\"ty\":4,\"nm\":\"Ellipse 1\",\"sr\":1,\"st\":0,\"op\":120,\"ip\":0,\"hd\":false,\"ddd\":0,\"bm\":0,\"hasMask\":false,\"ao\":0,\"ks\":{\"a\":{\"a\":0,\"k\":[0,0]},\"s\":{\"a\":0,\"k\":[80,80]},\"sk\":{\"a\":0,\"k\":0},\"p\":{\"a\":0,\"k\":[246,247]},\"r\":{\"a\":1,\"k\":[{\"o\":{\"x\":0,\"y\":0},\"i\":{\"x\":1,\"y\":1},\"s\":[160],\"t\":0},{\"s\":[-200],\"t\":119}]},\"sa\":{\"a\":0,\"k\":0},\"o\":{\"a\":0,\"k\":100}},\"ef\":[],\"shapes\":[{\"ty\":\"sh\",\"bm\":0,\"hd\":false,\"nm\":\"Ellipse Path 1\",\"d\":1,\"ks\":{\"a\":0,\"k\":{\"c\":true,\"i\":[[-73.9546,0],[0,-73.9546],[73.9546,0],[0,73.9546]],\"o\":[[73.9546,0],[0,73.9546],[-73.9546,0],[0,-73.9546]],\"v\":[[0,-134],[134,0],[0,134],[-134,0]]}}},{\"ty\":\"tm\",\"bm\":0,\"hd\":false,\"nm\":\"Trim Path\",\"e\":{\"a\":1,\"k\":[{\"o\":{\"x\":0.65,\"y\":0},\"i\":{\"x\":0.36,\"y\":1},\"s\":[100],\"t\":4},{\"s\":[0],\"t\":120}]},\"o\":{\"a\":0,\"k\":0},\"s\":{\"a\":1,\"k\":[{\"o\":{\"x\":0.55,\"y\":0.06},\"i\":{\"x\":0.36,\"y\":1},\"s\":[100],\"t\":0},{\"s\":[0],\"t\":116}]},\"m\":1},{\"ty\":\"st\",\"bm\":0,\"hd\":false,\"nm\":\"Stroke\",\"lc\":2,\"lj\":2,\"ml\":1,\"o\":{\"a\":0,\"k\":100},\"w\":{\"a\":0,\"k\":28},\"c\":{\"a\":0,\"k\":[0,0.8667,0.702,1]}}],\"ind\":1},{\"ty\":4,\"nm\":\"Ellipse 1\",\"sr\":1,\"st\":0,\"op\":120,\"ip\":0,\"hd\":false,\"ddd\":0,\"bm\":0,\"hasMask\":false,\"ao\":0,\"ks\":{\"a\":{\"a\":0,\"k\":[0,0]},\"s\":{\"a\":0,\"k\":[80,80]},\"sk\":{\"a\":0,\"k\":0},\"p\":{\"a\":0,\"k\":[246,247]},\"r\":{\"a\":1,\"k\":[{\"o\":{\"x\":0,\"y\":0},\"i\":{\"x\":1,\"y\":1},\"s\":[60],\"t\":0},{\"s\":[-300],\"t\":119}]},\"sa\":{\"a\":0,\"k\":0},\"o\":{\"a\":0,\"k\":100}},\"ef\":[],\"shapes\":[{\"ty\":\"sh\",\"bm\":0,\"hd\":false,\"nm\":\"Ellipse Path 1\",\"d\":1,\"ks\":{\"a\":0,\"k\":{\"c\":true,\"i\":[[-73.9546,0],[0,-73.9546],[73.9546,0],[0,73.9546]],\"o\":[[73.9546,0],[0,73.9546],[-73.9546,0],[0,-73.9546]],\"v\":[[0,-134],[134,0],[0,134],[-134,0]]}}},{\"ty\":\"tm\",\"bm\":0,\"hd\":false,\"nm\":\"Trim Path\",\"e\":{\"a\":1,\"k\":[{\"o\":{\"x\":0.65,\"y\":0},\"i\":{\"x\":0.36,\"y\":1},\"s\":[100],\"t\":26},{\"s\":[0],\"t\":120}]},\"o\":{\"a\":0,\"k\":0},\"s\":{\"a\":1,\"k\":[{\"o\":{\"x\":0.55,\"y\":0.06},\"i\":{\"x\":0.36,\"y\":1},\"s\":[100],\"t\":0},{\"s\":[0],\"t\":96}]},\"m\":1},{\"ty\":\"st\",\"bm\":0,\"hd\":false,\"nm\":\"Stroke\",\"lc\":2,\"lj\":2,\"ml\":1,\"o\":{\"a\":0,\"k\":100},\"w\":{\"a\":0,\"k\":28},\"c\":{\"a\":0,\"k\":[0,0.8667,0.702,1]}}],\"ind\":2},{\"ty\":4,\"nm\":\"Ellipse 1\",\"sr\":1,\"st\":0,\"op\":122,\"ip\":0,\"hd\":false,\"ddd\":0,\"bm\":0,\"hasMask\":false,\"ao\":0,\"ks\":{\"a\":{\"a\":0,\"k\":[0,0]},\"s\":{\"a\":0,\"k\":[100,100]},\"sk\":{\"a\":0,\"k\":0},\"p\":{\"a\":0,\"k\":[246,247]},\"r\":{\"a\":1,\"k\":[{\"o\":{\"x\":0,\"y\":0},\"i\":{\"x\":1,\"y\":1},\"s\":[0],\"t\":0},{\"s\":[-359],\"t\":120}]},\"sa\":{\"a\":0,\"k\":0},\"o\":{\"a\":0,\"k\":100}},\"ef\":[],\"shapes\":[{\"ty\":\"sh\",\"bm\":0,\"hd\":false,\"nm\":\"Ellipse Path 1\",\"d\":1,\"ks\":{\"a\":0,\"k\":{\"c\":true,\"i\":[[-73.9546,0],[0,-73.9546],[73.9546,0],[0,73.9546]],\"o\":[[73.9546,0],[0,73.9546],[-73.9546,0],[0,-73.9546]],\"v\":[[0,-134],[134,0],[0,134],[-134,0]]}}},{\"ty\":\"tm\",\"bm\":0,\"hd\":false,\"nm\":\"Trim Path\",\"e\":{\"a\":1,\"k\":[{\"o\":{\"x\":0.65,\"y\":0},\"i\":{\"x\":0.36,\"y\":1},\"s\":[100],\"t\":26},{\"s\":[0],\"t\":120}]},\"o\":{\"a\":0,\"k\":0},\"s\":{\"a\":1,\"k\":[{\"o\":{\"x\":0.55,\"y\":0.06},\"i\":{\"x\":0.36,\"y\":1},\"s\":[100],\"t\":0},{\"s\":[0],\"t\":96}]},\"m\":1},{\"ty\":\"st\",\"bm\":0,\"hd\":false,\"nm\":\"Stroke\",\"lc\":2,\"lj\":2,\"ml\":1,\"o\":{\"a\":0,\"k\":100},\"w\":{\"a\":0,\"k\":10},\"c\":{\"a\":0,\"k\":[0.8992,0.9808,0.9658,1]}}],\"ind\":3}],\"v\":\"5.7.0\",\"fr\":60,\"op\":120,\"ip\":0,\"assets\":[]}";
 
 
void HomeView::Create(lv_obj_t *root)
{
    lv_obj_set_style_border_width(root, 0, LV_PART_MAIN);
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(root, lv_color_hex(0), LV_PART_MAIN);
 
    /*lv_obj_t * info_label = lv_label_create(root);
    lv_label_set_text(info_label, "The last button event:\nNone");
    lv_obj_align(info_label, LV_ALIGN_BOTTOM_MID, 0, 0);
    ui.lable.cont = info_label;
    //lv_obj_add_event_cb(btn, event_cb, LV_EVENT_ALL, info_label);
    lv_obj_t *ui_Label5 = lv_label_create(root);
    lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label5, 0);
    lv_obj_set_y(ui_Label5,0);
    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label5, "12:12");
    lv_obj_set_style_text_color(ui_Label5, lv_color_hex(0xFF6610), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label5, &lv_font_montserrat_46, LV_PART_MAIN | LV_STATE_DEFAULT);
*/
 
 
    //lv_obj_t *ui_PinMapIMG2 = lv_image_create(root);
    //LV_IMG_DECLARE(img_src_car);
    //lv_image_set_src(ui_PinMapIMG2, ResourcePool::GetImage("canbus"));
    //lv_obj_align(ui_PinMapIMG2, LV_ALIGN_BOTTOM_MID, 0, 0);
 


    // 初始化 Lottie 动画
    lv_obj_t *lottie_obj = lv_rlottie_create_from_raw(root, 30, 30,(const char *) car);
    lv_obj_center(root);
 
}




void HomeView::Delete()
{
    printf("CandleLightView::Delete()\n");
}

