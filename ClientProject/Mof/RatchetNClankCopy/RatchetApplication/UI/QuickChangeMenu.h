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
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    QuickChangeMenuItem(const char* name);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="rect"></param>
    void SetRectangle(Mof::CRectangle rect);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
class QuickChangeMenu : public base::ui::UIPanel, public base::core::Observer<const ratchet::QuickChangeSystem::Info&> {
    using super = base::ui::UIPanel;
private:
    //! ���a
    float _distance;
    //! ����
    std::optional<int> _current_index;
    //! �p�X
    std::unordered_map<std::string, std::string> _tex_names;
    //! ���\�[�X
    std::weak_ptr<ratchet::ResourceMgr> _resource;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    QuickChangeMenu(const char* name);
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="info"></param>
    virtual void OnNotify(const ratchet::QuickChangeSystem::Info& info) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="index"></param>
    /// <param name="name"></param>
    void AddWeaponInfo(uint32_t index, const char* name);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
}
#endif // !RATCHET_QUICK_CHANGE_MENU_H