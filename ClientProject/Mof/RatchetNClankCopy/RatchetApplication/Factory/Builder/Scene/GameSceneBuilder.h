#ifndef RATCHET_FACTORY_BUILDER_SCENE_GAME_SCENE_BUILDER_H
#define RATCHET_FACTORY_BUILDER_SCENE_GAME_SCENE_BUILDER_H


#include "SceneBuilder.h"

#include <memory>

#include "../../../Scene/GameScene.h"
#include "../../../Game/GameManager.h"
#include "../../../Event/EventManager.h"


namespace ratchet {
namespace factory {
namespace builder {
namespace scene {
class GameSceneBuilder : public ratchet::factory::builder::scene::SceneBuilder {
    using super = ratchet::factory::builder::scene::SceneBuilder;
private:
    //! ゲーム
    std::weak_ptr<ratchet::GameManager> _game;
    //! イベント
    std::weak_ptr<ratchet::event::EventManager> _event;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameSceneBuilder();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~GameSceneBuilder();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameManager(std::weak_ptr<ratchet::GameManager> ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetEventManager(std::weak_ptr<ratchet::event::EventManager> ptr);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    virtual void Release(void) override;
    /// <summary>
    /// 構築
    /// </summary>
    /// <param name=""></param>
    virtual void Construct(std::any shared_this) override;
};
}
}
}
}
#endif // !RATCHET_FACTORY_BUILDER_SCENE_GAME_SCENE_BUILDER_H