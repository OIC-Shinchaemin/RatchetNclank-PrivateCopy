#ifndef RATCHET_UI_USER_ACTION_HELPER_MENU_H
#define RATCHET_UI_USER_ACTION_HELPER_MENU_H


#include "Base/UI/UIItem.h"
#include "Base/UI/UIPanel.h"

#include <memory>

#include "../ResourceManager.h"
#include "../GameDefine.h"


namespace ratchet::ui {
class UserActionHelperMenu : public base::ui::UIPanel {
    using super = base::ui::UIPanel;
private:
    //! リソース
    std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! 
    std::string _text;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    UserActionHelperMenu(const char* name);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="text"></param>
    void SetText(const std::string& text);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
}
#endif // !RATCHET_UI_USER_ACTION_HELPER_MENU_H