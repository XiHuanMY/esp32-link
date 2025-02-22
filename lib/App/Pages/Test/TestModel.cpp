#include "TestModel.h"
#include "stdio.h"
using namespace Page;

void TestModel::Init()
{
    account = new Account("TestModel", DataProc::Center(), 0, this);
    account->Subscribe("Test");
    account->SetEventCallback(onEvent);


    HAL::Test_Info_t info_val;
    info_val.test_cmd = HAL::Ts_START;
    info_val.data1 = 5000;
     
    account->Notify("Test", &info_val, sizeof(info_val));
}

void TestModel::Deinit()
{

}
int TestModel::onEvent(Account *account, Account::EventParam_t *param)
{
    return 1;
}

void TestModel::Update(int cnt)
{
    HAL::Test_Info_t info_val;
    info_val.test_cmd = HAL::Ts_UPDATE;
    info_val.data1 = cnt;
    printf("data1 = %d\n", cnt);
    account->Notify("Test", &info_val, sizeof(info_val));
}