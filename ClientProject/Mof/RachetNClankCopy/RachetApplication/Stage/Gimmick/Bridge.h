#pragma once
#include "GimmickBase.h"

class Bridge : public GimmickBase {
protected:

    Vector3 _start_pos;

    Vector3 _end_pos;

    float   _now_timer;

    bool    _start_flag;

public:
	Bridge(Vector3 start, bool enable = true, bool collision = true,
        StageObjectType type = StageObjectType::None, std::string name = "",
        int mesh_no = -1,
        Vector3 pos = Vector3(),
        Vector3 scale = Vector3(1, 1, 1),
        Vector3 rotate = Vector3());
	virtual ~Bridge(void);
 
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="pos"></param>
    void SetEndPosition(Mof::CVector3 pos);
    
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual Mof::CVector3 GetPreviewPosition(void) const override;

    virtual void Initialize(void) override;
    virtual void Update(float delta) override;

    virtual void ActionStart(void) override;
    virtual bool IsStart(void) const override;
};

