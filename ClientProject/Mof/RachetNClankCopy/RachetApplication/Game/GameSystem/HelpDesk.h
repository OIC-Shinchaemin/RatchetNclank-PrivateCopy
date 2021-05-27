#ifndef MY_HELP_DESK_H
#define MY_HELP_DESK_H


#include "My/Core/Observer.h"

#include <memory>
#include <string>

#include "My/Core/Observable.h"
#include "../../ResourceManager.h"
#include "../../GameDefine.h"
#include "MY/UI/UICanvas.h"
#include "GameQuest.h"


namespace my {
class HelpDesk :
    public std::enable_shared_from_this<my::HelpDesk>,
    public my::Observer<const my::GameQuest&> {
public:
    struct Info {
        std::string text;
    };
private:
    //! �B������������
    //my::GameQuest _current_quest;
    //! �ʒm�p
    my::Observable<const my::HelpDesk::Info&> _subject;
    //! ���\�[�X
    std::weak_ptr<my::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<my::UICanvas> _ui_canvas;
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
    virtual void OnNotify(const my::GameQuest& quest) override;
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
    /// <returns></returns>
    bool Initialize(void);
    /// <summary>
    /// ���
    /// </summary>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !MY_HELP_DESK_H