#include "HomeModel.h"
#include "stdio.h"
using namespace Page;

void HomeModel::Init()
{
    account = new Account("HomeModel", DataProc::Center(), 0, this);
    account->Subscribe("Home");
    account->SetEventCallback(onEvent);


    HAL::Home_Info_t info_val;
    info_val.home_cmd = HAL::HM_START;
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
 
}