#ifndef MY_PLAYER_H
#define MY_PLAYER_H


#include "Character.h"
#include "My/Core/Observer.h"

#include "../Weapon/OmniWrench.h"
#include "../Weapon/Mechanical.h"
#include "../../Game/GameSystem/QuickChangeSystem.h"
#include "../../Component/Player/PlayerComponent.h"


namespace my {
class Player : public my::Character,
    public my::Observer<std::shared_ptr<my::Weapon>>,
    public my::Observer<const my::QuickChangeSystem::Info&> {
    using super = my::Character;
private:
    //! 武器
    std::weak_ptr<my::Mechanical> _current_mechanical;
    //! 武器
    std::shared_ptr<my::OmniWrench> _omniwrench;
    //! 武器
    std::vector<std::shared_ptr<my::Actor>> _children;
    //! 武器
    std::shared_ptr<my::Weapon> _current_weapon;
    //! プレイヤー
    std::weak_ptr<my::PlayerComponent> _player_com;
    //! 腕の位置
    Mof::LPBONEMOTIONSTATE _upp_bone_state;
    //! 有効
    bool _enable;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Player();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~Player();
    /// <summary>
    /// 通知
    /// </summary>
    /// <param name="change"></param>
    virtual void OnNotify(std::shared_ptr<my::Weapon> change) override;
    /// <summary>
    /// 通知
    /// </summary>
    /// <param name="change"></param>
    virtual void OnNotify(const my::QuickChangeSystem::Info& info) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name="tag"></param>
    /// <returns></returns>
    std::shared_ptr<my::Actor> GetChild(const std::string& tag) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<my::Mechanical> GetCurrentMechanical(void) const;
    /// <summary>
    /// デリート
    /// </summary>
    /// <param name=""></param>
    //virtual void End(void) override;
    /// <summary>
    /// 無効化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Disable(void);
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void AddChild(const std::shared_ptr<my::Actor>& ptr);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    virtual bool Initialize(my::Actor::Param* param) override;
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //virtual bool Input(void) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
};
}
#endif // !MY_PLAYER_H