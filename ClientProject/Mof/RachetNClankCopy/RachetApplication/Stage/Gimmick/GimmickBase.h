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

    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual Mof::CVector3 GetPreviewPosition(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual float GetRequestTime(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual Mof::CVector3 GetMoveValue(void) const ;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual Mof::CSphere GetStartPositionSphere(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual Mof::CSphere GetEndPositionSphere(void) const;


    virtual void Initialize(void) = 0;
    virtual void Update(float delta) = 0;

    virtual void ActionStart(void);
    virtual bool IsStart(void) const;

    virtual void SetStageObjectData(bool enable, bool collision, StageObjectType type, std::string name, int mesh_no,
        Vector3 pos, Vector3 scale, Vector3 rotate);

    virtual void ReInitialize(void);
};

using GimmickPtr   = std::shared_ptr<GimmickBase>;
using GimmickArray = std::vector<GimmickPtr>;