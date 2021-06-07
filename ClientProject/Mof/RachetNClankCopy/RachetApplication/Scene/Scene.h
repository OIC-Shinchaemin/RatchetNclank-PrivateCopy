#ifndef MY_SCENE_H
#define MY_SCENE_H


#include <optional>
#include <memory>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

#include <Mof.h>

#include "SceneDefine.h"
#include "../Actor.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "My/UI/UICanvas.h"


namespace my {
class Scene : public std::enable_shared_from_this<my::Scene>, public my::Observer<const char*, const std::shared_ptr<my::Actor>&> {
    using this_type = my::Scene;
public:
   enum class State {
        Active,    
        Sleep,
        Pause,
        End
    };
    struct Param {
        //! ���O
        std::string name;
        //! �p�X
        std::string resource;
    };
protected:
    //! ���
    this_type::State _state;
    //! �J���[���\�[�X
    Mof::CTexture _rendar_target;
    //! �f�t�H���g�̃����_�[�^�[�Q�b�g
    Mof::LPRenderTarget _default;
    //! �|�X�g�G�t�F�N�g
    std::optional<my::SceneEffect> _effect;
    //! �J��
    my::Observable<const scene::SceneMessage&> _subject;
    //! ���\�[�X
    std::weak_ptr<my::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<my::UICanvas> _ui_canvas;
    //! �ǂݍ��ݍς�
    bool _loaded;
    //! ����
    std::mutex _mutex;
    //! �X���b�h
    std::optional<std::thread> _load_thread;
protected:
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsLoaded(void);
    void LoadComplete(void);

    std::shared_ptr<my::ResourceMgr> GetResource(void) const;
    std::shared_ptr<my::UICanvas> GetUICanvas(void) const;
    Mof::LPRenderTarget GetDefaultRendarTarget(void) const;
    virtual bool LoadingUpdate(float delta_time);
    virtual bool SceneUpdate(float delta_time);
    virtual bool PreRender(void);
    virtual bool LoadingRender(void);
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
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<my::UICanvas> ptr);
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
    void AddSceneObserver(const std::shared_ptr<my::Observer<const scene::SceneMessage&>>& ptr);
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