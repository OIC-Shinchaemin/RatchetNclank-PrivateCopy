#ifndef RATCHET_UI_EQUIPMENT_WEAPON_MENU_H
#define RATCHET_UI_EQUIPMENT_WEAPON_MENU_H


#include "Base/UI/UIItem.h"
#include "Base/UI/UIPanel.h"

#include <memory>
#include <string>
#include <unordered_map>

#include "Base/Core/Observer.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "../Actor/Weapon/Mechanical.h"


namespace ratchet::ui {
class EquipmentWeaponMenu : public base::ui::UIPanel, public base::core::Observer<const ratchet::actor::weapon::Mechanical::Info&> {
    using super = base::ui::UIPanel;
private:
    //! ���
    ratchet::actor::weapon::Mechanical::Info _info;
    //! �p�X
    std::unordered_map<std::string, std::string> _tex_names;
    //! ���\�[�X
    std::weak_ptr<ratchet::ResourceMgr> _resource;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    EquipmentWeaponMenu(const char* name);
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="info"></param>
    virtual void OnNotify(const ratchet::actor::weapon::Mechanical::Info& info) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
}
#endif // !RATCHET_UI_EQUIPMENT_WEAPON_MENU_H