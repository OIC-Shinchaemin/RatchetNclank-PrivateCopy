#ifndef MY_EQUIPMENT_WEAPON_MENU_H
#define MY_EQUIPMENT_WEAPON_MENU_H


#include "Base/UI/UIItem.h"
#include "Base/UI/UIPanel.h"

#include <memory>
#include <string>
#include <unordered_map>

#include "Base/Core/Observer.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "../Actor/Weapon/Mechanical.h"


namespace my {
class EquipmentWeaponMenu : public my::UIPanel, public my::Observer<const my::Mechanical::Info&> {
    using super = my::UIPanel;
private:
    //! 情報
    my::Mechanical::Info _info;
    //! パス
    std::unordered_map<std::string, std::string> _tex_names;
    //! リソース
    std::weak_ptr<my::ResourceMgr> _resource;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    EquipmentWeaponMenu(const char* name);
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="info"></param>
    virtual void OnNotify(const my::Mechanical::Info& info) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
}
#endif // !MY_EQUIPMENT_WEAPON_MENU_H