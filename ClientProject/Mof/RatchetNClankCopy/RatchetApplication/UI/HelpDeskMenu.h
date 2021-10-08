#ifndef RATCHET_UI_HELP_DESK_MENU_H
#define RATCHET_UI_HELP_DESK_MENU_H


#include "Base/UI/UIItem.h"
#include "Base/UI/UIPanel.h"

#include <optional>
#include <memory>
#include <unordered_map>

#include "Base/Core/Observer.h"
#include "Base/Core/Timer.h"
#include "Base/Core/Tween.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "../Game/GameSystem/HelpDesk.h"


namespace ratchet::ui {
class HelpDeskMenu : public base::ui::UIPanel, public base::core::Observer<const ratchet::game::gamesystem::HelpDesk::Info&> {
    using super = base::ui::UIPanel;
private:
    //! �\������
    ratchet::game::gamesystem::HelpDesk::Info _infomation;
    //! ���\�[�X
    std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! �_�Ń^�C�}�[
    base::core::Timer _blinking_on_timer;
    //! �_�Ń^�C�}�[
    base::core::Timer _blinking_off_timer;
    //! �_�ŕ\����
    bool _blinking_on;
    //! �X���C�h�J�n
    bool _slide_on;
    //! �X���C�h��
    Mof::CVector2 _move_destination;
    //! �X���C�h��
    Mof::CVector2 _move_source;
    //! �X���C�h����
    float _move_time_max;
    //! �X���C�h����
    float _move_time;

    base::core::Tween<float> _tween_pos_x;

    float Lerp(float time, float total_time, float max, float min) {
        return (max - min) * time / total_time + min;
    }
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    HelpDeskMenu(const char* name);
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="info"></param>
    virtual void OnNotify(const ratchet::game::gamesystem::HelpDesk::Info& info);
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
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
}
#endif // !RATCHET_UI_HELP_DESK_MENU_H