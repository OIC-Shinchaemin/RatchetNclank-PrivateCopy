#ifndef MY_PARTICLE_EFFECT_H
#define MY_PARTICLE_EFFECT_H


#include "../Actor.h"

#include <Mof.h>


namespace my {
class ParticleEffect : public my::Actor {
    using super = my::Actor;
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
    float _life_time;
    //! デフォルトサイズ
    float _size;
    //! 更新パラメータ
    my::ParticleEffect::UpdateParam _update_param;
    //! 環境設定
    my::ParticleEffect::EnvironmentParam _environment_param;
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
    void Start(const my::ParticleEffect::Info& info);
};
}
#endif // !MY_PARTICLE_EFFECT_H