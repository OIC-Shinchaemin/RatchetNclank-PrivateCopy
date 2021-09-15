#ifndef RATCHET_GAME_GAME_SYSTEM_SHOP_SHOP_SYSTEM_ENTRY_H
#define RATCHET_GAME_GAME_SYSTEM_SHOP_SHOP_SYSTEM_ENTRY_H


#include "../../../GameDefine.h"
#include "../../../UI/UICreator.h"
#include "ShopSystemElement.h"


namespace ratchet::ui::shop { class ShopSystemMainMenu; }
namespace ratchet::game::gamesystem::shop {
class ShopSystemEntryItem {
public:
    std::string name;
    bool enable;
    int price;
    ShopSystemEntryItem() :
        name(),
        price(),
        enable(false) {
    }
    ShopSystemEntryItem(const char* str, int value, bool flag) :
        name(str),
        price(value),
        enable(flag) {
    }
};
class ShopSystemEntry : public ratchet::game::gamesystem::shop::ShopSystemElement {
private:
    //! アイテム
    std::vector<ratchet::game::gamesystem::shop::ShopSystemEntryItem> _items;
    //! UI管理
    ratchet::ui::UICreator<ratchet::ui::shop::ShopSystemMainMenu> _ui_creator;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ShopSystemEntry();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~ShopSystemEntry();
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(void) override;
};
}
#endif // !RATCHET_GAME_GAME_SYSTEM_SHOP_SHOP_SYSTEM_ENTRY_H