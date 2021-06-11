#ifndef RATCHET_SCENE_SCENE_MANAGER_H
#define RATCHET_SCENE_SCENE_MANAGER_H


#include <memory>
#include <string>
#include <vector>


#include "Base/Core/Observer.h"
#include "Scene.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "Base/UI/UICanvas.h"
#include "../Game/GameManager.h"
#include "../Event/EventManager.h"
#include "../Factory/Builder/IBuilder.h"
#include "../Factory/Builder/Scene/TitleSceneBuilder.h"
#include "../Factory/Builder/Scene/GameSceneBuilder.h"


namespace ratchet {
namespace scene {
class SceneManager : public std::enable_shared_from_this<ratchet::scene::SceneManager>, public base::core::Observer<const scene::SceneMessage&> {
    using this_type = ratchet::scene::SceneManager;
    struct ChangeMessage {
        std::string name;
        std::shared_ptr<ratchet::scene::Scene::Param> param;
    };
    struct Managers {
        //! ���\�[�X
        std::weak_ptr<ratchet::ResourceMgr> resource;
        //! UI
        std::weak_ptr<base::ui::UICanvas> ui_canvas;
        //! �Q�[��
        std::weak_ptr<ratchet::GameManager> game_manager;
        //! �Q�[���C�x���g
        std::weak_ptr<ratchet::event::EventManager> event_manager;
    };
    struct CreateStruct {
        //! �t�@�N�g���[
        ratchet::Factory<ratchet::scene::Scene> factory;
        //! �r���_�[
        std::unordered_map<std::string, std::shared_ptr<ratchet::factory::builder::IBuilder>> builders;
        //! �^�C�v,�p�X
        std::unordered_map<std::string, std::string> reousrce_paths;
    };
private:
    //! ����
    std::shared_ptr<ratchet::scene::Scene> _scene;
    //! �O
    std::shared_ptr<ratchet::scene::Scene> _prev_scene;
    //! ���b�Z�[�W
    std::optional<ChangeMessage> _change_message;
    //! �Ǘ��I�u�W�F�N�g
    this_type::Managers _managers;
    //! �쐬�I�u�W�F�N�g
    this_type::CreateStruct _create_struct;


    template<typename Builder>
    void RegisterBuilder(const std::string& name) {
            auto& [resource, ui_canvas, game_manager, event_manager] = _managers;
            auto ptr = ut::MakeSharedWithRelease<Builder>();
            ptr->SetResourceManager(resource);
            ptr->SetUICanvas(ui_canvas);
            _create_struct.builders.emplace(name, ptr); ;
    }
    template<>
    void RegisterBuilder<ratchet::factory::builder::scene::TitleSceneBuilder>(const std::string& name) {
        auto& [resource, ui_canvas, game_manager, event_manager] = _managers;
        auto ptr = ut::MakeSharedWithRelease<ratchet::factory::builder::scene::TitleSceneBuilder>();
        ptr->SetResourceManager(resource);
        ptr->SetUICanvas(ui_canvas);
        ptr->SetGameManager(game_manager);
        _create_struct.builders.emplace(name, ptr); ;
    }
    template<>
    void RegisterBuilder<ratchet::factory::builder::scene::GameSceneBuilder>(const std::string& name) {
        auto& [resource, ui_canvas, game_manager, event_manager] = _managers;
        auto ptr = ut::MakeSharedWithRelease<ratchet::factory::builder::scene::GameSceneBuilder>();
        ptr->SetResourceManager(resource);
        ptr->SetUICanvas(ui_canvas);
        ptr->SetGameManager(game_manager);
        ptr->SetEventManager(event_manager);
        _create_struct.builders.emplace(name, ptr); ;
    }

    /// <summary>
    /// �ύX
    /// </summary>
    /// <param name="name"></param>
    /// <param name="param"></param>
    void ChangeScene(const std::string& name, std::shared_ptr<ratchet::scene::Scene::Param> param);
    void RenderScene(void);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    SceneManager();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~SceneManager();
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name=""></param>
    virtual void OnNotify(const scene::SceneMessage& mesage) override;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(const std::shared_ptr<ratchet::ResourceMgr>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(const std::shared_ptr<base::ui::UICanvas>& ptr);
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
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Initialize(void);
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
    bool Update(float delta_time);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Render(void);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
};
}
}
#endif // !RATCHET_SCENE_SCENE_MANAGER_H