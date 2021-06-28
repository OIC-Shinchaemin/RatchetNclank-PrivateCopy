#pragma once
#include "GimmickBase.h"

class Elevator : public GimmickBase {
protected:

    Vector3 _start_pos;

    Vector3 _end_pos;

    float   _now_timer;

    float   _request_time;

    bool    _start_flag;

    bool    _end_flag;

    //! 位置
    Mof::CVector3 _preview_position;
    //! 位置
    Mof::CVector3 _initial_position;
    //! フラグ
    bool _first_initialized;

public:
    Elevator(Vector3 end, float request, bool enable = true, bool collision = true,
        StageObjectType type = StageObjectType::None, std::string name = "",
        int mesh_no = -1,
        Vector3 pos = Vector3(),
        Vector3 scale = Vector3(1, 1, 1),
        Vector3 rotate = Vector3());
    virtual ~Elevator(void);

    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual Mof::CVector3 GetPreviewPosition(void) const override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual float GetRequestTime(void) const override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual Mof::CVector3 GetMoveValue(void) const override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual float GetVolume(void) const override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual float GetHeight(void) const override;
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

    virtual void Initialize(void) override;
    virtual void Update(float delta) override;

    virtual void ActionStart(void) override;
    virtual bool IsStart(void) const override;

    Vector3 GetEndPos(void) const;
    float GetRequest(void) const;

    virtual void SetPosition(const Vector3& pos) override;

    virtual void ReInitialize(void) override;

    virtual void SetStageObjectData(bool enable, bool collision, StageObjectType type, std::string name, int mesh_no,
        Vector3 pos, Vector3 scale, Vector3 rotate) override;

#ifdef STAGEEDITOR
    float* GetStartPosPointer(void);
    float* GetEndPosPointer(void);
    float* GetRequestPointer(void);
#endif//STAGEEDITOR
};

