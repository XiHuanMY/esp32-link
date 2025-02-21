#ifndef __TestModel_MODEL_H
#define __TestModel_MODEL_H

#include "Common/DataProc/DataProc.h"
#include "Common/HAL/HAL.h"

namespace Page
{

class TestModel
{
public:
    void Init();
    void Deinit();

private:
    Account* account;
};

}

#endif
