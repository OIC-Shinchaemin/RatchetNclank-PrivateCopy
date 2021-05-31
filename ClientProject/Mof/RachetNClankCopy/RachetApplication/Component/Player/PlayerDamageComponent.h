#ifndef MY_PLAYER_DAMAGE_COMPONENT_H
#define MY_PLAYER_DAMAGE_COMPONENT_H


#include "PlayerActionComponent.h"

#include <memory>


namespace my {
class PlayerDamageComponent : public my::PlayerActionComponent {
    using super = my::PlayerActionComponent;
private:
    //! 被弾量
    int _damage_value;
    //! 被弾速度
    float _damage_speed;
    //! 被弾角度
    Mof::CVector3 _damage_angle;
    //! Hp
    std::weak_ptr<class HpComponent> _hp_com;
    /// <summary>
    /// 吹っ飛ぶ
    /// </summary>
    /// <param name=""></param>
    void DamegeAccele(void);
    /// <summary>
    /// ダメージ
    /// </summary>
    /// <param name=""></param>
    void Damege(void);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    PlayerDamageComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    PlayerDamageComponent(const PlayerDamageComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerDamageComponent();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string_view GetStateType(void) const override;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time">時間</param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
    /// <summary>
    /// 複製
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<my::Component> Clone(void) override;
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool Start(void) override;
};
}
#endif // !MY_PLAYER_DAMAGE_COMPONENT_H