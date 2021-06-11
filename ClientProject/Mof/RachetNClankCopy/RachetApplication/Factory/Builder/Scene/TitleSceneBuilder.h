#ifndef BUILDER_TITLE_SCENE_BUILDER_H
#define BUILDER_TITLE_SCENE_BUILDER_H


#include "SceneBuilder.h"

#include <memory>

#include "../../../Scene/TitleScene.h"
#include "../../../Game/GameManager.h"


namespace builder {
class TitleSceneBuilder : public builder::SceneBuilder {
    using super = builder::SceneBuilder;
private:
    //! �Q�[��
    std::weak_ptr<rachet::GameManager> _game;
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
    void SetGameManager(std::weak_ptr<rachet::GameManager> ptr);
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
#endif // !BUILDER_TITLE_SCENE_BUILDER_H