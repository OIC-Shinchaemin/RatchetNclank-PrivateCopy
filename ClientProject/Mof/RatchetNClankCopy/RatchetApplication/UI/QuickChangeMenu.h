#ifndef RATCHET_QUICK_CHANGE_MENU_H
#define RATCHET_QUICK_CHANGE_MENU_H


#include "Base/UI/UIItem.h"
#include "Base/UI/UIPanel.h"

#include <optional>
#include <memory>
#include <unordered_map>

#include "Base/Core/Observer.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "../Game/GameSystem/QuickChangeSystem.h"


namespace ratchet {
class QuickChangeMenuItem : public base::ui::UIItem {
    using super = base::ui::UIItem;
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
class QuickChangeMenu : public base::ui::UIPanel, public base::core::Observer<const ratchet::QuickChangeSystem::Info&> {
    using super = base::ui::UIPanel;
private:
    //! 半径
    float _distance;
    //! 現在
    std::optional<int> _current_index;
    //! パス
    std::unordered_map<std::string, std::string> _tex_names;
    //! リソース
    std::weak_ptr<ratchet::ResourceMgr> _resource;
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
    virtual void OnNotify(const ratchet::QuickChangeSystem::Info& info) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr);
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
#endif // !RATCHET_QUICK_CHANGE_MENU_H