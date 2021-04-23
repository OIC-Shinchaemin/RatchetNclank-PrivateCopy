#ifndef MY_SCENE_H
#define MY_SCENE_H


#include <memory>
#include <string>
#include <vector>

#include <Mof.h>

#include "SceneDefine.h"
#include "../Actor.h"


namespace my {
enum class SceneState {
    Active,
    Pause,
    End
};
class Scene : public std::enable_shared_from_this<my::Scene>, public my::Observer<const char*, const std::shared_ptr<my::Actor>&> {
public:
    struct Param {
        //! ���O
        std::string name;
        //! �p�X
        std::string resource;
    };
protected:
    //! ���
    my::SceneState _state;
    //! �J���[���\�[�X
    Mof::CTexture _rendar_target;
    //! �f�t�H���g�̃����_�[�^�[�Q�b�g
    Mof::LPRenderTarget _default;
    //! �|�X�g�G�t�F�N�g
    std::optional<my::SceneEffect> _effect;
    //! �J��
    my::Observable<const SceneMessage&> _subject;
protected:
    Mof::LPRenderTarget GetDefaultRendarTarget(void) const;
    virtual bool PreRender(void);
    virtual bool SceneRender(void);
    virtual bool PostRender(void);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Scene();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Scene();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetName(void) = 0;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void AddSceneObserver(const std::shared_ptr<my::Observer<const SceneMessage&>>& ptr);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Load(std::shared_ptr<my::Scene::Param> param);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time">����</param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void);
};
}
#endif // !MY_SCENE_H