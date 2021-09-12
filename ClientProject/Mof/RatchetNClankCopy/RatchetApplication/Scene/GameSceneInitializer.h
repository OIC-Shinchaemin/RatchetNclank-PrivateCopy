#ifndef RATCHET_SCENE_GAME_SCENE_INITIALIZER_H
#define RATCHET_SCENE_GAME_SCENE_INITIALIZER_H


#include "GameScene.h"
#include "../Event/EventManager.h"
#include "../Game/GameManager.h"


namespace ratchet::scene {
class GameSceneInitializer {
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GameSceneInitializer();
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="out">�Ώ�</param>
    /// <returns></returns>
    bool Execute(std::shared_ptr<ratchet::game::GameManager>& game, std::shared_ptr<ratchet::event::EventManager>& event, std::shared_ptr<ratchet::scene::GameScene>& out);
};
}
#endif // !RATCHET_SCENE_GAME_SCENE_INITIALIZER_H