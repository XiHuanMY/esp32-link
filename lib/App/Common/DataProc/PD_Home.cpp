#include "DataProc.h"
#include "../HAL/HAL.h"

#include "stdio.h"



static void onTimer(Account* account)
{
    HAL::Home_Info_t TSinfo;
    HAL::Home_Update(&TSinfo);
    account->Commit(&TSinfo, sizeof(TSinfo));
    account->Publish();
    
}

static int onEvent(Account* account, Account::EventParam_t* param)
{
    if (param->event == Account::EVENT_TIMER)
    {
        onTimer(account);
        return Account::ERROR_NONE;
    }
    if (param->event != Account::EVENT_NOTIFY)
    {
        printf("Account::ERROR_UNSUPPORTED_REQUEST\r\n");
        return Account::ERROR_UNSUPPORTED_REQUEST;
    }

    if (param->size != sizeof(HAL::Home_Info_t))
    {
        printf("Account::ERROR_SIZE_MISMATCH\r\n");
        return Account::ERROR_SIZE_MISMATCH;
    }

    printf("power pd event!!!\r\n");
    HAL::Home_Info_t *info = (HAL::Home_Info_t *)param->data_p;

    switch (info->home_cmd)
    {
        case HAL::Ts_START:
            HAL::Home_Init(info);
            break;

        case HAL::Ts_UPDATE:
            HAL::Home_Update(info);
            break;

        case HAL::Ts_STOP:
            //HAL::PowerPD_Deinit();
            break;


        default:
            break;
    }

    return 0;
}

DATA_PROC_INIT_DEF(Home)
{
    account->SetEventCallback(onEvent);
    account->SetTimerPeriod(100);
}