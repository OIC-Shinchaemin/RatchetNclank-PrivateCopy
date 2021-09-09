#ifndef RATCHET_UI_OPTION_SYSTEM_MENU_H
#define RATCHET_UI_OPTION_SYSTEM_MENU_H


#include "Base/UI/UIItem.h"
#include "Base/UI/UIPanel.h"

#include <memory>

#include "Base/Core/Observer.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "../Game/GameSystem/OptionSystem.h"


namespace ratchet {
namespace ui {
class OptionSystemMenuItem : public base::ui::UIItem {
    using super = base::ui::UIItem;
private:
    //! 表示テキスト
    std::string _text;
    //! フォント
    Mof::CFont* _font;
    //! 選択中
    bool _selected;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    OptionSystemMenuItem(const char* name);
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~OptionSystemMenuItem();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="text"></param>
    void SetText(const std::string& text);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetFont(Mof::CFont* ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="flag"></param>
    void SetSelect(const bool flag);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual Mof::CVector2 GetSize(void) const override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<Mof::CTexture> GetTexture(void) const;
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name=""></param>s
    /// <returns></returns>
    virtual bool Input(void) override;
    /// <summary>
    /// 更新
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
class OptionSystemMenu : public base::ui::UIPanel,
    public base::core::Observer<const ratchet::game::gamesystem::OptionSystem::Info&> {
    using super = base::ui::UIPanel;
private:
    //! 情報
    ratchet::game::gamesystem::OptionSystem::Info _infomation;
    //! リソース
    std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;
    //! フォント
    Mof::CFont _font;
    //! 余白
    float _element_margin_y;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    std::shared_ptr<Mof::CTexture> GetTexture(const std::string& type);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    OptionSystemMenu(const char* name);
    /// <summary>
    /// デストラクタ
    /// </summary>
    /// <param name="name"></param>
    ~OptionSystemMenu();
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="info"></param>
    virtual void OnNotify(const ratchet::game::gamesystem::OptionSystem::Info& info) override;
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
    /// 追加
    /// </summary>
    /// <param name="in"></param>
    void AddItem(const ratchet::game::gamesystem::OptionSystemItem& in);
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
}
#endif // !RATCHET_UI_OPTION_SYSTEM_MENU_H