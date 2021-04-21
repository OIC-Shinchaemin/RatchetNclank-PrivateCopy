#pragma once
#include "StageObject.h"

/// <summary>
/// �M�~�b�N�̊��N���X
/// </summary>
class GimmickBase : public StageObject {
public:
    virtual void Initialize(void) = 0;
    virtual void Update(void) = 0;
};

using GimmickPtr = std::shared_ptr<GimmickBase>;