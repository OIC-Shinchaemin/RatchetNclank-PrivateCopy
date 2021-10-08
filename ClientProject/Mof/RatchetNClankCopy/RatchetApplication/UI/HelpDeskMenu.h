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
    //! 表示文字
    ratchet::game::gamesystem::HelpDesk::Info _infomation;
    //! リソース
    std::weak_ptr<ratchet::ResourceMgr> _resource;
    //! 点滅タイマー
    base::core::Timer _blinking_on_timer;
    //! 点滅タイマー
    base::core::Timer _blinking_off_timer;
    //! 点滅表示中
    bool _blinking_on;
    //! スライド開始
    bool _slide_on;
    //! スライド先
    Mof::CVector2 _move_destination;
    //! スライド元
    Mof::CVector2 _move_source;
    //! スライド時間
    float _move_time_max;
    //! スライド時間
    float _move_time;

    base::core::Tween<float> _tween_pos_x;

    float Lerp(float time, float total_time, float max, float min) {
        return (max - min) * time / total_time + min;
    }
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    HelpDeskMenu(const char* name);
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="info"></param>
    virtual void OnNotify(const ratchet::game::gamesystem::HelpDesk::Info& info);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<ratchet::ResourceMgr> ptr);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
};
}
#endif // !RATCHET_UI_HELP_DESK_MENU_H