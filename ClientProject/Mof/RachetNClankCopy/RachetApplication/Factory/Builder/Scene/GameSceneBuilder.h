#ifndef BUILDER_GAME_SCENE_BUILDER_H
#define BUILDER_GAME_SCENE_BUILDER_H


#include "SceneBuilder.h"

#include <memory>

#include "../../../Scene/GameScene.h"
#include "My/UI/UICanvas.h"
#include "../../../Game/GameManager.h"
#include "../../../Event/EventManager.h"


namespace builder {
class GameSceneBuilder : public builder::SceneBuilder {
    using super = builder::SceneBuilder;
private:
    //! UI
    std::weak_ptr<my::UICanvas> _ui_canvas;
    //! �Q�[��
    std::weak_ptr<my::GameManager> _game;
    //! �C�x���g
    std::weak_ptr<my::EventManager> _event;
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
    void SetUICanvas(std::weak_ptr<my::UICanvas> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameManager(std::weak_ptr<my::GameManager> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetEventManager(std::weak_ptr<my::EventManager> ptr);
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
#endif // !BUILDER_GAME_SCENE_BUILDER_H