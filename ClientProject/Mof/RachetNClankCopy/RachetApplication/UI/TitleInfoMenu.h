#ifndef MY_TITLE_INFO_MENU_H
#define MY_TITLE_INFO_MENU_H


#include "My/UI/UIPanel.h"

#include <memory>

#include "My/Core/Observer.h"
#include "My/UI/UICanvas.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "My/Core/Timer.h"


namespace my {
class TitleInfoMenu : public my::UIPanel, public my::Observer<bool> {
    using super = my::UIPanel;
private:
    //! �\��
    bool _show;
    //! ���\�[�X
    std::weak_ptr<my::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<my::UICanvas> _ui_canvas;
    //! �t�H���g
    Mof::CFont _font;
    //! �\��
    my::Timer _show_timer;
    //! �J�n
    bool _start;
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
    void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<my::UICanvas> ptr);
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
#endif // !MY_TITLE_INFO_MENU_H