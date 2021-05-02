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
class QuickChangeMenu : public my::UIPanel, public my::Observer<const my::QuickChangeSystem::Info&> {
    using super = my::UIPanel;
private:
    //! ���a
    float _distance;
    //! ����
    std::optional<int> _current_index;
    //! �p�X
    std::unordered_map<std::string, std::string> _tex_names;
    //! ���\�[�X
    std::weak_ptr<my::ResourceMgr> _resource;
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
    virtual void OnNotify(const my::QuickChangeSystem::Info& info) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
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
#endif // !MY_QUICK_CHANGE_MENU_H