#ifndef RACHET_NANOTECH_ITEM_H
#define RACHET_NANOTECH_ITEM_H


#include "../../Actor.h"

#include "Base/Core/Observable.h"


namespace rachet {
class NanotechItem : public rachet::Actor {
    using super = rachet::Actor;
public:
    struct Param : public super::Param {
        //! 移動
        Mof::CVector3 speed;
        //! 回転
        Mof::CVector3 angle;
    };
private:
    //! 移動
    Mof::CVector3 _init_speed;
    //! 回転
    Mof::CVector3 _init_angle;
    //! 通知用
    base::core::Observable<int> _money_subject;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    NanotechItem();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~NanotechItem();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //base::core::Observable<int>* GetMoneySubject(void);
    /// <summary>
    /// デリート
    /// </summary>
    /// <param name=""></param>
    virtual void End(void) override;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    virtual bool Initialize(rachet::Actor::Param* param) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //virtual bool Update(float delta_time) override;
};
}
#endif // !RACHET_NANOTECH_ITEM_H