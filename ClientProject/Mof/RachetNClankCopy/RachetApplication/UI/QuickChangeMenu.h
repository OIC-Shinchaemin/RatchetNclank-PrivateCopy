#ifndef MY_QUICK_CHANGE_MENU_H
#define MY_QUICK_CHANGE_MENU_H


#include "My/UI/UIPanel.h"

#include "My/Core/Observable.h"
#include "../Game/GameSystem/QuickChangeSystem.h"


namespace my {
class QuickChangeMenuItem : public my::UIItem {
    using super = my::UIItem;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    QuickChangeMenuItem(const char* name);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="rect"></param>
    void SetRectangle(Mof::CRectangle rect);
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
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
class QuickChangeMenu : public my::UIPanel, public my::Observer<const my::QuickChangeSystem::Info&> {
    using super = my::UIPanel;
private:
    //! 半径
    float _distance;
    //! 現在
    std::optional<int> _current_index;
    //! パス
    std::unordered_map<std::string, std::string> _tex_names;
    //! リソース
    std::weak_ptr<my::ResourceMgr> _resource;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    QuickChangeMenu(const char* name);
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="info"></param>
    virtual void OnNotify(const my::QuickChangeSystem::Info& info) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="index"></param>
    /// <param name="name"></param>
    void AddWeaponInfo(uint32_t index, const char* name);
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
#endif // !MY_QUICK_CHANGE_MENU_H