#ifndef RACHET_BULLET_ITEM_H
#define RACHET_BULLET_ITEM_H


#include "../../Actor.h"

#include "Base/Core/Observable.h"
#include "../../Game/GameSystem/WeaponSystem.h"


namespace rachet {
class BulletItem : public rachet::Actor {
    using super = rachet::Actor;
public:
    enum class Type {
        BombGlove,
        Pyrocitor,
        Blaster,
        CountMax
    };
    struct Param : public super::Param {
        //! 移動
        Mof::CVector3 speed;
        //! 回転
        Mof::CVector3 angle;
        //! タイプ
        Type type;
        //! 数
        int count = 0;
    };
private:
    //! 移動
    Mof::CVector3 _init_speed;
    //! 回転
    Mof::CVector3 _init_angle;
    //! タイプ
    Type _item_type;
    //! 数
    int _item_count;
    //! 通知用
    base::core::Observable<const rachet::ChargeInfo&> _weapon_system_subject;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    BulletItem();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~BulletItem();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::string GetTypeName(rachet::BulletItem::Type type) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<const rachet::ChargeInfo&>* GetWeaponSystemSubject(void);
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
#endif // !RACHET_BULLET_ITEM_H