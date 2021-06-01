#ifndef MY_SHOP_SYSTEM_H
#define MY_SHOP_SYSTEM_H


#include "My/Core/Observer.h"

#include <string>
#include <vector>

#include "My/Core/Observable.h"
#include "../../ResourceManager.h"
#include "../../GameDefine.h"
#include "MY/UI/UICanvas.h"
#include "Save/SaveData.h"
#include "WeaponSystem.h"


namespace my {
class ShopSystem :
    public std::enable_shared_from_this<my::ShopSystem>, public my::Observer<bool> {
public:
    struct Info {
        //! 表示
        bool enable;
        //! アイテムのインデックス
        std::uint32_t index;
        //! 項目選択中
        bool select;
        //! 購入数
        std::uint32_t count;
        Info() :
            enable(false),
            index(0),
            select(false),
            count(0) {
        }
        Info(bool flag) :
            enable(flag),
            index(0),
            select(false),
            count(0){
        }
    };
    struct Item {
        std::string name;
        bool enable;
        Item() :
            name(),
            enable(false) {
        }
        Item(const char* str, bool flag) :
            name(str),
            enable(flag) {
        }
    };
private:
    //! 構成情報
    my::ShopSystem::Info _infomation;
    //! 通知用
    my::Observable<const my::ShopSystem::Info&> _subject;
    //! 通知用
    my::Observable<const my::ChargeInfo&> _buy_subject;
    //! セーブデータ
    my::SaveData _save_data;
    //! 購入可能ラインナップ
    std::vector<my::ShopSystem::Item> _items;
    //! リソース
    std::weak_ptr<my::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<my::UICanvas> _ui_canvas;

    /// <summary>
    /// 購入
    /// </summary>
    /// <param name=""></param>
    void Buy(void);
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
    my::Observable<const my::ChargeInfo&>* GetChargeInfoSubject(void);
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