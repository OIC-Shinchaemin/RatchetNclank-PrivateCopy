#ifndef RACHET_HELP_DESK_H
#define RACHET_HELP_DESK_H


#include "Base/Core/Observer.h"

#include <memory>
#include <string>

#include "Base/Core/Observable.h"
#include "../../ResourceManager.h"
#include "../../GameDefine.h"
#include "Base/UI/UICanvas.h"
#include "GameQuest.h"


namespace rachet {
class HelpDesk :
    public std::enable_shared_from_this<rachet::HelpDesk>,
    public base::core::Observer<const rachet::GameQuest&> {
public:
    struct Info {
        std::string text;
    };
private:
    //! ���
    Info _info;
    //! ���
    Info _prev_info;
    //! �B������������
    //rachet::GameQuest _current_quest;
    //! �ʒm�p
    base::core::Observable<const rachet::HelpDesk::Info&> _subject;
    //! ���\�[�X
    std::weak_ptr<rachet::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<base::ui::UICanvas> _ui_canvas;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    HelpDesk();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~HelpDesk();
    /// <summary>
    /// �ʒm
    /// </summary>
    /// <param name=""></param>
    virtual void OnNotify(const rachet::GameQuest& quest) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<rachet::ResourceMgr> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<base::ui::UICanvas> ptr);
    /// <summary>
    /// ������
    /// </summary>
    /// <returns></returns>
    bool Initialize(void);
    /// <summary>
    /// ���
    /// </summary>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !RACHET_HELP_DESK_H