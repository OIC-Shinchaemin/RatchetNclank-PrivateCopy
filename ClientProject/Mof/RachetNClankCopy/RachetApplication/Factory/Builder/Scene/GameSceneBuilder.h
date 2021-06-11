#ifndef BUILDER_GAME_SCENE_BUILDER_H
#define BUILDER_GAME_SCENE_BUILDER_H


#include "SceneBuilder.h"

#include <memory>

#include "../../../Scene/GameScene.h"
#include "../../../Game/GameManager.h"
#include "../../../Event/EventManager.h"


namespace builder {
class GameSceneBuilder : public builder::SceneBuilder {
    using super = builder::SceneBuilder;
private:
    //! ゲーム
    std::weak_ptr<rachet::GameManager> _game;
    //! イベント
    std::weak_ptr<rachet::EventManager> _event;
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
    void SetGameManager(std::weak_ptr<rachet::GameManager> ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetEventManager(std::weak_ptr<rachet::EventManager> ptr);
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
#endif // !BUILDER_GAME_SCENE_BUILDER_H