#ifndef RATCHET_GAME_GAME_SYSTEM_SHOP_SHOP_ELEMENT_H
#define RATCHET_GAME_GAME_SYSTEM_SHOP_SHOP_ELEMENT_H


#include "Base/UI/UICanvas.h"
#include "../../../ResourceManager.h"
#include "../../../GameDefine.h"


namespace ratchet {
namespace game {
namespace gamesystem {
namespace shop {
class ShopSystemElement {
private:
    //! リソース
    std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ShopSystemElement();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~ShopSystemElement();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr);
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(void);
};
}
}
}
}
#endif // !RATCHET_GAME_GAME_SYSTEM_SHOP_SHOP_ELEMENT_H