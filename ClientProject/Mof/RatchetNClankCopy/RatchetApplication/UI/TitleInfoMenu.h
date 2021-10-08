#ifndef RATCHET_UI_TITLE_INFO_MENU_H
#define RATCHET_UI_TITLE_INFO_MENU_H


#include "Base/UI/UIPanel.h"

#include <memory>

#include "Base/Core/Observer.h"
#include "Base/UI/UICanvas.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "Base/Core/Timer.h"


namespace ratchet::ui {
class TitleInfoMenu : public base::ui::UIPanel, public base::core::Observer<bool> {
    using super = base::ui::UIPanel;
    //! 表示テキストの種類
    enum class TextType {
        Press,
        Start,
        Button,
        Or,
        Enter,
        Key,
        ExclamationMark,
        CountMax
    };
    struct TextElem {
        TextType type;
        std::string path;
        Mof::CVector2 position;

        TextElem(TextType t, std::string str, Mof::CVector2 pos) :
            type(t),
            path(str),
            position(pos) {
        }
    };
private:
    //! 表示
    bool _show;
    //! リソース
    std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;
    //! 表示
    base::core::Timer _show_timer;
    //! 開始
    bool _start;
    //! 点滅タイマー
    base::core::Timer _blinking_on_timer;
    //! 点滅タイマー
    base::core::Timer _blinking_off_timer;
    //! 点滅表示中
    bool _blinking_on;
    //! パス
    std::string _texture_path;
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
    void SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr);
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
#endif // !RATCHET_UI_TITLE_INFO_MENU_H