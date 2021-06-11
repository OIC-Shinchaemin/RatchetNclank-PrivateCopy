#ifndef MY_PLAYER_H
#define MY_PLAYER_H


#include "Character.h"
#include "Base/Core/Observer.h"

#include <stack>
#include <unordered_map>

#include "../Weapon/OmniWrench.h"
#include "../Weapon/Mechanical.h"
#include "../../Game/GameSystem/QuickChangeSystem.h"
#include "../../Game/GameSystem/ShopSystem.h"
#include "../../Component/Player/PlayerComponent.h"
#include "../../Game/GameSystem/GameQuest.h"


namespace my {
class Player : public my::Character,
    public base::core::Observer<std::shared_ptr<my::Weapon>>,
    public base::core::Observer<const my::QuickChangeSystem::Info&> {
    using super = my::Character;
    struct ObservablePair {
        std::string name;
        base::core::Observable<bool> subject;
        ObservablePair(const char* str) :
            name(str),
            subject (){
        }
    };
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
    //bool _enable;
    //! 通知用
    ObservablePair _shop_system_subject;
    //! 通知用
    ObservablePair _quick_change_subject;
    //! 通知用
    base::core::Observable<const my::GameQuest&> _quest_subject;
    //! 通知用
    std::unordered_map<std::string, ObservablePair* >_notificationable_subject_map;
    //! 通知用
    std::stack<ObservablePair*>_notificationable_subject_stack;
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
    /// 通知イベント
    /// </summary>
    /// <param name="info"></param>
    //virtual void OnNotify(const my::ShopSystem::Info& info) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<bool>* GetShopSystemSubject(void);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<bool>* GetQuickChangeSubject(void);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<const my::GameQuest&>* GetQuestSubject(void);
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
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void AddChild(const std::shared_ptr<my::Actor>& ptr);
    /// <summary>
    /// プッシュ
    /// </summary>
    /// <param name="name"></param>
    void PushNotificationableSubject(const std::string& name);
    /// <summary>
    /// ポップ
    /// </summary>
    /// <param name=""></param>
    void PopNotificationableSubject(void);
    /// <summary>
    /// プッシュ
    /// </summary>
    /// <param name="name"></param>
    void PopNotificationableSubject(const std::string& name);
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
    virtual bool Input(void) override;
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