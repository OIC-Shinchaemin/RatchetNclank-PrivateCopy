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
    //! �Q�[��
    std::weak_ptr<ratchet::GameManager> _game;
    //! �C�x���g
    std::weak_ptr<ratchet::event::EventManager> _event;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GameSceneBuilder();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~GameSceneBuilder();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameManager(std::weak_ptr<ratchet::GameManager> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetEventManager(std::weak_ptr<ratchet::event::EventManager> ptr);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    virtual void Release(void) override;
    /// <summary>
    /// �\�z
    /// </summary>
    /// <param name=""></param>
    virtual void Construct(std::any shared_this) override;
};
}
}
}
}
#endif // !RATCHET_FACTORY_BUILDER_SCENE_GAME_SCENE_BUILDER_H