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
    //! 状態
    std::weak_ptr<class PlayerStateComponent> _state_com;
    //! 地点
    std::string _next_terrain;
    //! アクションフラグ
    bool _action_enable;
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
    std::weak_ptr<my::Actor> GetTarget(void) const;
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
    bool IsActionEnable(void);
    /// <summary>
    /// 有効化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool EnableAction(void);
    /// <summary>
    /// 無効化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool DisableAction(void);
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