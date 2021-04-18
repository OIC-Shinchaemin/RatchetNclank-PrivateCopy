#ifndef MY_PLAYER_COMPONENT_H
#define MY_PLAYER_COMPONENT_H


#include "../UpdateComponent.h"

#include <memory>


namespace my {
class PlayerComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:
    //! 待機
    std::weak_ptr<class PlayerIdleComponent> _idle_com;
    //! 移動
    std::weak_ptr<class PlayerMoveComponent> _move_com;
    //! 移動
    std::weak_ptr<class PlayerDamageComponent> _damage_com;

    //! 大きさ
    float _volume;
    //! 高さ
    float _height;
    //! 標的
    //std::weak_ptr<my::Actor> _target;

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
    float GetVolume(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetHeight(void) const;
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
#ifdef _DEBUG
    virtual bool Render(void) override;
#endif // _DEBUG
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
};
}
#endif // !MY_PLAYER_COMPONENT_H