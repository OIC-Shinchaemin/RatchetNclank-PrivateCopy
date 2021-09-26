#ifndef RATCHET_EVENT_HIT_STOP_EVENT_H
#define RATCHET_EVENT_HIT_STOP_EVENT_H


#include "Event.h"
#include "Base/Core/Observable.h"

#include <memory>


#include "Base/Core/ServiceLocator.h"
#include "../Scene/GameScene.h"


namespace ratchet::event {
class HitStopEvent : public ratchet::event::Event {
    using super = ratchet::event::Event;
private:
    //! 停止時間
    float _time;
    //! タイマー
    base::core::Timer _timer;
    //! 生成先
    std::weak_ptr<ratchet::scene::GameScene> _game_scene;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    HitStopEvent();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~HitStopEvent();
    /// <summary>
    /// セッター
    /// </summary>
    void SetGameScene(const std::shared_ptr<ratchet::scene::GameScene> ptr) {
        this->_game_scene = ptr;
    }
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
#endif // !RATCHET_EVENT_HIT_STOP_EVENT_H