#ifndef MY_CLEAR_SCENE_H
#define MY_CLEAR_SCENE_H


#include "Scene.h"


namespace my {
class ClearScene : public my::Scene {
    using super = my::Scene;
protected:
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool SceneRender(void) override;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ClearScene();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~ClearScene();
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    virtual void OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetName(void) override;
    /// <summary>
    /// �ǂݍ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Load(std::shared_ptr<my::Scene::Param> param) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time">����</param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
};
}
#endif // !MY_CLEAR_SCENE_H