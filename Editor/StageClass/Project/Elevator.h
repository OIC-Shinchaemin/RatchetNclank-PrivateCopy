#pragma once
#include "GimmickBase.h"

class Elevator : public GimmickBase {
protected:

public:
    Elevator(void);
    ~Elevator(void);

    virtual void Initialize(void) override;
    virtual void Update(void) override;
};

