#ifndef RATCHET_PLAYER_COMPONENT_H
#define RATCHET_PLAYER_COMPONENT_H


#include "../CharacterComponent.h"

#include <memory>

#include "Base/Core/Observable.h"


namespace ratchet {
class PlayerComponent : public ratchet::CharacterComponent {
    using super = ratchet::CharacterComponent;
private:
    //! 標的
    std::weak_ptr<ratchet::actor::Actor> _target;
    //! カーソル位置
    base::core::Observable<std::optional<Mof::CVector3>> _observable;
    //! 状態
    std::weak_ptr<class PlayerStateComponent> _state_com;
    //! 地点
    std::string _next_terrain;
    //! アクションフラグ
    //bool _action_enable;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    PlayerComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    PlayerComponent(const PlayerComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerComponent();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetTarget(const std::shared_ptr<ratchet::actor::Actor>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetNextTerrain(const std::string& terrain);
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
    std::weak_ptr<ratchet::actor::Actor> GetTarget(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::string GetNextTerrain(void) const;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //bool IsActionEnable(void);
    /// <summary>
    /// 有効化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //bool EnableAction(void);
    /// <summary>
    /// 無効化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //bool DisableAction(void);
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
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
};
}
#endif // !RATCHET_PLAYER_COMPONENT_H