#ifndef RACHET_PARTICLE_EFFECT_H
#define RACHET_PARTICLE_EFFECT_H


#include "../../Actor.h"

#include <Mof.h>

#include "Base/Core/Timer.h"


namespace rachet {
class ParticleEffect : public rachet::Actor {
    using super = rachet::Actor;
public:
    struct Param : public super::Param {
        //! 色
        Mof::CVector4 color;
        //! 時間
        float life_time;
    };
    struct UpdateParam {
        //! 位置
        Mof::CVector3 velocity;
        //! 回転
        Mof::CVector3 rotate;
        //! 拡大
        Mof::CVector3 scale;
        //! 加算色
        Mof::CVector4 color;
    };
    struct EnvironmentParam {
        bool gravity;
    };
    struct Info {
        Param init_param;
        UpdateParam update_param;
        EnvironmentParam environment_param;
    };
private:
    //! 色
    Mof::CVector4 _color;
    //! 時間
    base::core::Timer _life_time;
    //! デフォルトサイズ
    float _size;
    //! 更新パラメータ
    rachet::ParticleEffect::UpdateParam _update_param;
    //! 環境設定
    rachet::ParticleEffect::EnvironmentParam _environment_param;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ParticleEffect();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ParticleEffect();
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    virtual bool Render(void) override;
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name="info"></param>
    void Start(const rachet::ParticleEffect::Info& info);
};
}
#endif // !RACHET_PARTICLE_EFFECT_H