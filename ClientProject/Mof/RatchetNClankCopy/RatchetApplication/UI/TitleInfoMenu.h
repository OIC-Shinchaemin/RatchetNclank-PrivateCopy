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
    //! �\���e�L�X�g�̎��
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
    //! �\��
    bool _show;
    //! ���\�[�X
    std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;
    //! �\��
    base::core::Timer _show_timer;
    //! �J�n
    bool _start;
    //! �_�Ń^�C�}�[
    base::core::Timer _blinking_on_timer;
    //! �_�Ń^�C�}�[
    base::core::Timer _blinking_off_timer;
    //! �_�ŕ\����
    bool _blinking_on;
    //! �p�X
    std::string _texture_path;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    TitleInfoMenu(const char* name);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~TitleInfoMenu();
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="info"></param>
    virtual void OnNotify(bool show) override;
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
#endif // !RATCHET_UI_TITLE_INFO_MENU_H