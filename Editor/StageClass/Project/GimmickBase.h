#pragma once
#include "StageObject.h"

/// <summary>
/// ギミックの基底クラス
/// </summary>
class GimmickBase : public StageObject {
public:
    virtual void Initialize(void) = 0;
    virtual void Update(void) = 0;
};

using GimmickPtr = std::shared_ptr<GimmickBase>;