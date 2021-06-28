#ifndef RATCHET_FACTORY_BUILDER_SCENE_TITLE_SCENE_BUILDER_H
#define RATCHET_FACTORY_BUILDER_SCENE_TITLE_SCENE_BUILDER_H


#include "SceneBuilder.h"

#include <memory>

#include "../../../Scene/TitleScene.h"
#include "../../../Game/GameManager.h"


namespace ratchet {
namespace factory {
namespace builder {
namespace scene {
class TitleSceneBuilder : public  ratchet ::factory::builder::scene::SceneBuilder{
    using super = ratchet::factory::builder::scene::SceneBuilder;
private:
    //! �Q�[��
    std::weak_ptr<ratchet::game::GameManager> _game;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    TitleSceneBuilder();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~TitleSceneBuilder();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameManager(std::weak_ptr<ratchet::game::GameManager> ptr);
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
#endif // !RATCHET_FACTORY_BUILDER_SCENE_TITLE_SCENE_BUILDER_H