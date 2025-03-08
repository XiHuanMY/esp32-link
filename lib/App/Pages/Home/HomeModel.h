#ifndef __HomeModel_MODEL_H
#define __HomeModel_MODEL_H

#include "Common/DataProc/DataProc.h"
#include "Common/HAL/HAL.h"

namespace Page
{

class HomeModel
{
public:
    void Init();
    void Deinit();
    void Update(int cnt);
private:
    Account* account;

private:
    static int onEvent(Account *account, Account::EventParam_t *param);
};

}

#endif
