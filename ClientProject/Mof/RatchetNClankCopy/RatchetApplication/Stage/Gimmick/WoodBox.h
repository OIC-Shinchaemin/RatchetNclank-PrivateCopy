#pragma once
#include "GimmickBase.h"

class WoodBox;
using WoodBoxPtr   = std::shared_ptr<WoodBox>;
using WoodBoxArray = std::vector<WoodBoxPtr>;

class WoodBox : public GimmickBase {
protected:

    bool              _action_flag;
                      
    float             _gravity;
                      
    Vector3           _start_pos;

    StageObjectArray* _object_array_pointer;

    MeshArray*        _mesh_array_pointer;

    WoodBoxArray*     _box_array_pointer;

    bool CollisionStage(void);

    bool CollisionBox(WoodBoxPtr& box);

public:

    WoodBox(bool enable = true, bool collision = true,
        StageObjectType type = StageObjectType::None, std::string name = "",
        int mesh_no = -1,
        Vector3 pos = Vector3(),
        Vector3 scale = Vector3(1, 1, 1),
        Vector3 rotate = Vector3());

    ~WoodBox(void);

    virtual void Initialize(void) override;
    virtual void Update(float delta) override;

    virtual void ActionStart(void) override;
    virtual bool IsStart(void) const override;
    virtual void SetStageObjectData(bool enable, bool collision, StageObjectType type, std::string name, int mesh_no,
        Vector3 pos, Vector3 scale, Vector3 rotate) override;

    virtual void SetPosition(const Vector3& pos) override
        ;
    void SetBoxArray(WoodBoxArray* array_ptr);
    void SetObjectArray(StageObjectArray* array_pointer);
    void SetMeshArray(MeshArray* array_ptr);
};