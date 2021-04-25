#ifndef MY_PLAYER_COMPONENT_H
#define MY_PLAYER_COMPONENT_H


#include "../CharacterComponent.h"

#include <memory>

#include "My/Core/Observable.h"


namespace my {
class PlayerComponent : public my::CharacterComponent {
    using super = my::CharacterComponent;
private:
    //! 標的
    std::weak_ptr<my::Actor> _target;
    //! カーソル位置
    my::Observable<std::optional<Mof::CVector3>> _observable;
    //! 待機
    std::weak_ptr<class PlayerIdleComponent> _idle_com;
    //! 移動
    std::weak_ptr<class PlayerMoveComponent> _move_com;
    //! 移動
    std::weak_ptr<class PlayerDamageComponent> _damage_com;
    bool MoveByKeyboard(float angular_speed, float speed);
    void MoveByGamepad(float angular_speed, float speed);
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
    void SetTarget(const std::shared_ptr<my::Actor>& ptr);
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
    std::weak_ptr<my::Actor> GetTarget(void) const;
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
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool DebugRender(void) override;
};
}
#endif // !MY_PLAYER_COMPONENT_H