#ifndef RATCHET_PLAYER_OMNI_WRENCH_COMPONENT_H
#define RATCHET_PLAYER_OMNI_WRENCH_COMPONENT_H


#include "../UpdateComponent.h"


namespace ratchet {
class PlayerOmniWrenchComponent : public ratchet::UpdateComponent {
    using super = ratchet::UpdateComponent;
private:
    //! 武器
    std::weak_ptr<ratchet::actor::Actor> _weapon;
    //! 状態
    std::weak_ptr<class PlayerThrowAttackComponent> _throw_attack_com;
    //! 状態
    std::weak_ptr<class OmniWrenchActionStateComponent> _weapon_action_state_com;
    //! 衝突制御
    std::weak_ptr<class OmniWrenchCollisionComponent> _weapon_coll_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    PlayerOmniWrenchComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    PlayerOmniWrenchComponent(const PlayerOmniWrenchComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerOmniWrenchComponent();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="param"></param>
    virtual void SetParam(const rapidjson::Value& param) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// 有効化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Activate(void) override;
    /// <summary>
    /// 無効化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Inactivate(void) override;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
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
    virtual std::shared_ptr<ratchet::Component> Clone(void) override;
};
}
#endif // !RATCHET_PLAYER_OMNI_WRENCH_COMPONENT_H