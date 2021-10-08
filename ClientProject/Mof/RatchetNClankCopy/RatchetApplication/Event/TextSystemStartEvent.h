#ifndef RATCHET_EVENT_TEXT_SYSTEM_START_EVENT_H
#define RATCHET_EVENT_TEXT_SYSTEM_START_EVENT_H


#include "Event.h"
#include "Base/Core/Observable.h"

#include <memory>

#include "../Scene/GameScene.h"
#include "../Game/GameSystem/Text/TextSystem.h"
#include "StageViewEvent.h"


namespace ratchet::event {
class TextSystemStartEvent : public ratchet::event::Event {
    using super = ratchet::event::Event;
private:
    //! 開始までの時間
    base::core::Timer _timer;
    //! シーン
    std::weak_ptr<scene::Scene> _scene;
    //! テキスト
    std::weak_ptr<ratchet::game::gamesystem::text::TextSystem> _text_system;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    TextSystemStartEvent();
    /// <summary>
    /// デストラクタ
    /// </summary>
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name=""></param>
    void SetGameScene(const std::shared_ptr<ratchet::scene::Scene>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name=""></param>
    void SetTextSystem(const std::shared_ptr<ratchet::game::gamesystem::text::TextSystem>& ptr);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
};
}
#endif // !RATCHET_EVENT_TEXT_SYSTEM_START_EVENT_H