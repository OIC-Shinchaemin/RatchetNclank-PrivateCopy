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
    //! �\���e�L�X�g
    std::string _text;
    //! �t�H���g
    Mof::CFont* _font;
    //! �I��
    bool _selected;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    OptionSystemMenuItem(const char* name);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~OptionSystemMenuItem();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="text"></param>
    void SetText(const std::string& text);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetFont(Mof::CFont* ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="flag"></param>
    void SetSelect(const bool flag);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual Mof::CVector2 GetSize(void) const override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<Mof::CTexture> GetTexture(void) const;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>s
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
class OptionSystemMenu : public base::ui::UIPanel,
    public base::core::Observer<const ratchet::game::gamesystem::OptionSystem::Info&> {
    using super = base::ui::UIPanel;
private:
    //! ���
    ratchet::game::gamesystem::OptionSystem::Info _infomation;
    //! ���\�[�X
    std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;
    //! �t�H���g
    Mof::CFont _font;
    //! �]��
    float _element_margin_y;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    std::shared_ptr<Mof::CTexture> GetTexture(const std::string& type);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    OptionSystemMenu(const char* name);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    ~OptionSystemMenu();
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="info"></param>
    virtual void OnNotify(const ratchet::game::gamesystem::OptionSystem::Info& info) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="in"></param>
    void AddItem(const ratchet::game::gamesystem::OptionSystemItem& in);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
}
}
#endif // !RATCHET_UI_OPTION_SYSTEM_MENU_H