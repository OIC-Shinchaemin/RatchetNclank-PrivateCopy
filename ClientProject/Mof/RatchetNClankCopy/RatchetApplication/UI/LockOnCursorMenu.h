#ifndef RATCHET_UI_LOCK_ON_CURSOR_MENU_H
#define RATCHET_UI_LOCK_ON_CURSOR_MENU_H


#include "Base/UI/UIItem.h"
#include "Base/UI/UIPanel.h"

#include <optional>
#include <memory>

#include "Base/Core/Observer.h"
#include "Base/UI/UICanvas.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"


namespace ratchet::ui {
class LockOnCursorMenu : public base::ui::UIPanel, public base::core::Observer<std::optional<Mof::CVector3>> {
    using super = base::ui::UIPanel;
private:
    //! 位置
    std::optional<Mof::CVector3> _position;
    //! リソース
    std::weak_ptr<ratchet::ResourceMgr> _resource_manager;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    LockOnCursorMenu(const char* name);
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="position"></param>
    virtual void OnNotify(std::optional<Mof::CVector3> position) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    //void SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
}
#endif // !RATCHET_UI_NANOTECH_MENU_H