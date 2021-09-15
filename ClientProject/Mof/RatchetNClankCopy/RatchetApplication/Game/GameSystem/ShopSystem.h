#ifndef RATCHET_GAME_GAME_SYSTEM_SHOP_SYSTEM_H
#define RATCHET_GAME_GAME_SYSTEM_SHOP_SYSTEM_H


#include "GameSystem.h"

#include <optional>
#include <string>
#include <stack>
#include <vector>

#include "Base/Core/Observable.h"
#include "../../ResourceManager.h"
#include "../../GameDefine.h"
#include "Base/UI/UICanvas.h"
#include "Save/SaveData.h"
#include "WeaponSystem.h"
#include "GameMoney.h"
#include "../../UI/UICreator.h"
#include "Shop/ShopSystemElement.h"
#include "Shop/ShopSystemEntry.h"


namespace ratchet::ui { class ShopSystemMenu; }
namespace ratchet::game::gamesystem {
class ShopSystem :
    public ratchet::game::gamesystem::GameSystem,
    public base::core::Observer<const std::shared_ptr<ratchet::game::gamesystem::shop::ShopSystemElement>&> {
    using super = ratchet::game::gamesystem::GameSystem;
    using this_type = ratchet::game::gamesystem::ShopSystem;
public:
    struct Info {
        //! 表示
        bool enable;
        //! アイテムのインデックス
        int  index;
        //! 項目選択中
        bool select;
        //! 購入数
        int count;
        //! 名前
        std::string weapon;
        //! 閉じた
        bool close;
        Info() :
            enable(false),
            index(0),
            select(false),
            count(0),
            weapon(),
            close(false) {
        }
        Info(bool flag) :
            enable(flag),
            index(0),
            select(false),
            count(0),
            weapon(),
            close(false) {
        }
    };
    struct Item {
        std::string name;
        bool enable;
        int price;
        Item() :
            name(),
            price(),
            enable(false) {
        }
        Item(const char* str, int value, bool flag) :
            name(str),
            price(value),
            enable(flag) {
        }
    };
private:
    //! 構成情報
    this_type::Info _infomation;
    //! 通知用
    base::core::Observable<const this_type::Info&> _info_subject;
    //! 通知用
    base::core::Observable<const ratchet::game::gamesystem::ChargeInfo&> _buy_subject;
    //! 通知用
    base::core::Observable<const ratchet::actor::weapon::Mechanical::Info&> _equipment_weapon_menu_subject;
    //! 通知用
    base::core::Observable<int> _game_money_menu_subject;
    //! セーブデータ
    ratchet::game::gamesystem::save::SaveData _save_data;
    //! 購入可能ラインナップ
    std::vector<this_type::Item> _items;
    //! 武器
    std::optional<std::string>_prev_weapon;
    //! 武器
    std::weak_ptr<ratchet::game::gamesystem::WeaponSystem> _weapon_system;
    //! お金
    std::weak_ptr<ratchet::game::gamesystem::GameMoney> _game_money;
    //! UI管理
    ratchet::ui::UICreator<ratchet::ui::ShopSystemMenu> _ui_creator;
    //! 要素
    std::stack<std::shared_ptr<ratchet::game::gamesystem::shop::ShopSystemElement>> _element_stack;
    /// <summary>
    /// 終了
    /// </summary>
    /// <param name=""></param>
    bool Close(void);
    /// <summary>
    /// 購入
    /// </summary>
    /// <param name=""></param>
    void Buy(void);
    /// <summary>
    /// 通知
    /// </summary>
    /// <param name=""></param>
    void NotifyEquipmentWeaponMenu(void);
    /// <summary>
    /// 通知
    /// </summary>
    /// <param name=""></param>
    void NotifyGameMoneyMenu(void);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ShopSystem();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~ShopSystem();
    /// <summary>
    /// 通知
    /// </summary>
    /// <param name=""></param>
    virtual void OnNotify(bool flag) override;
    /// <summary>
    /// 通知
    /// </summary>
    /// <param name=""></param>
    virtual void OnNotify(const std::shared_ptr<ratchet::game::gamesystem::shop::ShopSystemElement>& add) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetWeaponSystem(std::weak_ptr<ratchet::game::gamesystem::WeaponSystem> ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameMoney(std::weak_ptr<ratchet::game::gamesystem::GameMoney> ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<const this_type::Info&>* GetInfoSubject(void);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<const ratchet::game::gamesystem::ChargeInfo&>* GetChargeInfoSubject(void);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsEnable(void) const;
    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name="in"></param>
    /// <returns></returns>
    bool Load(ratchet::game::gamesystem::save::SaveData& in);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <returns></returns>
    bool Initialize(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// 解放
    /// </summary>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !RATCHET_GAME_GAME_SYSTEM_SHOP_SYSTEM_H