#ifndef MY_SHOP_SYSTEM_H
#define MY_SHOP_SYSTEM_H


#include "My/Core/Observer.h"

#include <optional>
#include <string>
#include <vector>

#include "My/Core/Observable.h"
#include "../../ResourceManager.h"
#include "../../GameDefine.h"
#include "MY/UI/UICanvas.h"
#include "Save/SaveData.h"
#include "WeaponSystem.h"
#include "GameMoney.h"


namespace my {
class ShopSystem :
    public std::enable_shared_from_this<my::ShopSystem>, public my::Observer<bool> {
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
        Info() :
            enable(false),
            index(0),
            select(false),
            count(0),
            weapon() {
        }
        Info(bool flag) :
            enable(flag),
            index(0),
            select(false),
            count(0),
            weapon() {
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
    my::ShopSystem::Info _infomation;
    //! 通知用
    my::Observable<const std::shared_ptr<my::ShopSystem>&> _subject;
    //! 通知用
    my::Observable<const my::ShopSystem::Info&> _info_subject;
    //! 通知用
    my::Observable<const my::ChargeInfo&> _buy_subject;
    //! 通知用
    my::Observable<const my::Mechanical::Info&> _equipment_weapon_menu_subject;
    //! 通知用
    my::Observable<int> game_money_menu_subject;
    //! セーブデータ
    my::SaveData _save_data;
    //! 購入可能ラインナップ
    std::vector<my::ShopSystem::Item> _items;
    //! 武器
    std::optional<std::string>_prev_weapon;
    //! 武器
    std::weak_ptr<my::WeaponSystem> _weapon_system;
    //! お金
    std::weak_ptr<my::GameMoney> _game_money;
    //! リソース
    std::weak_ptr<my::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<my::UICanvas> _ui_canvas;

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
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetWeaponSystem(std::weak_ptr<my::WeaponSystem> ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameMoney(std::weak_ptr<my::GameMoney> ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<my::UICanvas> ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    my::Observable<const std::shared_ptr<my::ShopSystem>&>* GetSubject(void);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    my::Observable<const my::ChargeInfo&>* GetChargeInfoSubject(void);
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
    bool Load(my::SaveData& in);
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
    bool Update(float delta_time);
    /// <summary>
    /// 解放
    /// </summary>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !MY_SHOP_SYSTEM_H