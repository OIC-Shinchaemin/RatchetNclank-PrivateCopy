#pragma once
#include "../StageObject.h"

/// <summary>
/// ギミックの基底クラス
/// </summary>
class GimmickBase : public StageObject {
public:
    GimmickBase(bool enable = true, bool collision = true,
        StageObjectType type = StageObjectType::None, std::string name = "",
        int mesh_no = -1,
        Vector3 pos = Vector3(),
        Vector3 scale = Vector3(1, 1, 1),
        Vector3 rotate = Vector3());
    virtual ~GimmickBase(void);

    virtual void Initialize(void) = 0;
    virtual void Update(float delta) = 0;

    virtual void ActionStart(void);
    virtual bool IsStart(void) const;

    virtual void SetStageObjectData(bool enable, bool collision, StageObjectType type, std::string name, int mesh_no,
        Vector3 pos, Vector3 scale, Vector3 rotate);
};

using GimmickPtr   = std::shared_ptr<GimmickBase>;
using GimmickArray = std::vector<GimmickPtr>;