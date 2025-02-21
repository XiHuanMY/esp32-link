#include "TestModel.h"

using namespace Page;

void TestModel::Init()
{
    account = new Account("Test", DataProc::Center(), 0, this);
    account->Subscribe("Test");
   

    HAL::Test_Info_t info_val;
    info_val.test_cmd = HAL::Ts_START;
    info_val.data1 = 5000;
     
    account->Notify("Test", &info_val, sizeof(info_val));
}

void TestModel::Deinit()
{

}
 