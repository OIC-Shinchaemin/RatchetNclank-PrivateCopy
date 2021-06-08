#ifndef MY_LOCK_ON_CURSOR_MENU_H
#define MY_LOCK_ON_CURSOR_MENU_H


#include "My/UI/UIItem.h"
#include "My/UI/UIPanel.h"

#include <optional>
#include <memory>

#include "My/Core/Observer.h"
#include "My/UI/UICanvas.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"


namespace my {
class LockOnCursorMenu : public my::UIPanel, public my::Observer<std::optional<Mof::CVector3>> {
    using super = my::UIPanel;
private:
    //! 位置
    std::optional<Mof::CVector3> _position;
    //! リソース
    std::weak_ptr<my::ResourceMgr> _resource_manager;
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
    void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    //void SetUICanvas(std::weak_ptr<my::UICanvas> ptr);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
}
#endif // !MY_NANOTECH_MENU_H