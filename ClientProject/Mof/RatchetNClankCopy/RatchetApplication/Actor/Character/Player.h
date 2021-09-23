#ifndef RATCHET_ACTOR_CHARACTER_PLAYER_H
#define RATCHET_ACTOR_CHARACTER_PLAYER_H


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
#include "../../Game/GameSystem/Text/TextSystem.h"
#include "../../Stage/Gimmick/Elevator.h"
#include "../../Event/PlayerActionAfterGettingOffElevatorEvent.h"


namespace ratchet::actor::character {
class Player : public ratchet::actor::character::Character,
    public base::core::Observer<std::shared_ptr<ratchet::actor::weapon::Weapon>>,
    public base::core::Observer<const ratchet::game::gamesystem::QuickChangeSystem::Info&> ,
    public ratchet::game::gamesystem::text::TextSystemClosedMessageListener ,
    public ElevatorArrivalMessageListener ,
    public ratchet::event::PlayerActionAfterGettingOffElevatorEventEndListener {
    using super = ratchet::actor::character::Character;
    struct ObservablePair {
        std::string name;
        base::core::Observable<bool> subject;
        ObservablePair(const char* str) :
            name(str),
            subject() {
        }
    };
private:
    //! 武器
    std::weak_ptr<ratchet::actor::weapon::Mechanical> _current_mechanical;
    //! 武器
    std::shared_ptr<ratchet::actor::weapon::OmniWrench> _omniwrench;
    //! 武器
    std::vector<std::shared_ptr<ratchet::actor::Actor>> _children;
    //! 武器
    std::shared_ptr<ratchet::actor::weapon::Weapon> _current_weapon;
    //! プレイヤー
    std::weak_ptr<component::player::PlayerComponent> _player_com;
    //! 腕の位置
    Mof::LPBONEMOTIONSTATE _upp_bone_state;
    //! 有効
    //bool _enable;
    //! 通知用
    ObservablePair _shop_system_subject;
    //! 通知用
    ObservablePair _quick_change_subject;
    //! 通知用
    base::core::Observable<const ratchet::game::gamesystem::GameQuest&> _quest_subject;
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
    virtual void OnNotify(std::shared_ptr<ratchet::actor::weapon::Weapon> change) override;
    /// <summary>
    /// 通知
    /// </summary>
    /// <param name="change"></param>
    virtual void OnNotify(const ratchet::game::gamesystem::QuickChangeSystem::Info& info) override;
    /// <summary>
    /// 通知
    /// </summary>
    /// <param name="change"></param>
    virtual void OnNotify(const ratchet::game::gamesystem::text::TextSystemClosedMessage& message) override;
    /// <summary>
    /// 通知
    /// </summary>
    /// <param name="change"></param>
    virtual void OnNotify(const ElevatorArrivalMessage& message) override;
    /// <summary>
    /// 通知
    /// </summary>
    /// <param name="change"></param>
    virtual void OnNotify(const ratchet::event::PlayerActionAfterGettingOffElevatorEventEndMessage& message) override;
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
    base::core::Observable<const ratchet::game::gamesystem::GameQuest&>* GetQuestSubject(void);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name="tag"></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::actor::Actor> GetChild(const std::string& tag) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::actor::weapon::Mechanical> GetCurrentMechanical(void) const;
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void AddChild(const std::shared_ptr<ratchet::actor::Actor>& ptr);
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
    /// デリート
    /// </summary>
    /// <param name=""></param>
    virtual void End(void) override;
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
    virtual bool Initialize(ratchet::actor::Actor::Param* param) override;
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
#endif // !RATCHET_ACTOR_CHARACTER_PLAYER_H