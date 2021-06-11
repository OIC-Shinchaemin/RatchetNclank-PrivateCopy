#ifndef MY_TITLE_INFO_MENU_H
#define MY_TITLE_INFO_MENU_H


#include "Base/UI/UIPanel.h"

#include <memory>

#include "Base/Core/Observer.h"
#include "Base/UI/UICanvas.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "Base/Core/Timer.h"


namespace my {
class TitleInfoMenu : public base::ui::UIPanel, public base::core::Observer<bool> {
    using super = base::ui::UIPanel;
private:
    //! 表示
    bool _show;
    //! リソース
    std::weak_ptr<my::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;
    //! フォント
    Mof::CFont _font;
    //! 表示
    base::core::Timer _show_timer;
    //! 開始
    bool _start;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    TitleInfoMenu(const char* name);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~TitleInfoMenu();
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="info"></param>
    virtual void OnNotify(bool show) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
}
#endif // !MY_TITLE_INFO_MENU_H