#pragma once
#include "GimmickBase.h"

#include "Base/Core/Observable.h"


class Bridge : 
    public GimmickBase, 
    public base::core::Observable<const char*, const std::shared_ptr<StageObject>&> {
    using Observable = base::core::Observable<const char*, const std::shared_ptr<StageObject>&>;
protected:

    Vector3 _start_pos;

    Vector3 _end_pos;

    float   _now_timer;

    bool    _start_flag;

    float   _request_time;

    bool    _actioned;
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
    void SetEndPosition(Mof::Vector3 pos);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="time"></param>
    void SetTime(float time);
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

    virtual void Initialize(void) override;
    virtual void Update(float delta) override;

    virtual void ActionStart(void) override;
    virtual bool IsStart(void) const override;

    Vector3 GetEndPos(void) const;
    virtual void SetPosition(const Vector3& pos) override;

    virtual void SetStageObjectData(bool enable, bool collision, StageObjectType type, std::string name, int mesh_no,
                                    Vector3 pos, Vector3 scale, Vector3 rotate) override;

#ifdef STAGEEDITOR 
    float* GetStartPosPointer(void);
    float* GetEndPosPointer(void);
#endif //STAGEEDITOR
};

