#ifndef MY_OPTION_SYSTEM_MENU_H
#define MY_OPTION_SYSTEM_MENU_H


#include "My/UI/UIItem.h"
#include "My/UI/UIPanel.h"

#include <memory>

#include "My/Core/Observer.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "../Game/GameSystem/OptionSystem.h"


namespace my {
class OptionSystemMenuItem : public my::UIItem {
    using super = my::UIItem;
private:
    //! 表示テキスト
    std::string _text;
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
    /// 初期化
    /// </summary>
    /// <param name="pos"></param>
    /// <param name="tex"></param>
    /// <param name="color"></param>
    /// <returns></returns>
    //bool Initialize(Mof::CVector2 pos, const std::shared_ptr<Mof::CTexture>& tex, const Mof::CVector4& color);
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
class OptionSystemMenu : public my::UIPanel,
    public my::Observer<const my::OptionSystem::Info&> {
    using super = my::UIPanel;
private:
    //! 情報
    my::OptionSystem::Info _infomation;
    //! リソース
    std::weak_ptr<my::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<my::UICanvas> _ui_canvas;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    OptionSystemMenu(const char* name);
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="info"></param>
    virtual void OnNotify(const my::OptionSystem::Info& info) override;
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
    /// 追加
    /// </summary>
    /// <param name="in"></param>
    void AddItem(const my::OptionSystemItem& in);
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
#endif // !MY_OPTION_SYSTEM_MENU_H