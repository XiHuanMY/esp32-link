#include "HomeModel.h"
#include "stdio.h"
using namespace Page;

void HomeModel::Init()
{
    account = new Account("HomeModel", DataProc::Center(), 0, this);
    account->Subscribe("Home");
    account->SetEventCallback(onEvent);


    HAL::Test_Info_t info_val;
    info_val.test_cmd = HAL::Ts_START;
    info_val.data1 = 5000;
     
    account->Notify("Home", &info_val, sizeof(info_val));
}

void HomeModel::Deinit()
{

}
int HomeModel::onEvent(Account *account, Account::EventParam_t *param)
{
    return 1;
}

void HomeModel::Update(int cnt)
{
    HAL::Test_Info_t info_val;
    info_val.test_cmd = HAL::Ts_UPDATE;
    info_val.data1 = cnt;
    printf("data1 = %d\n", cnt);
    account->Notify("Home", &info_val, sizeof(info_val));
}