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
        //! リソース
        std::weak_ptr<ratchet::ResourceMgr> resource;
        //! UI
        std::weak_ptr<base::ui::UICanvas> ui_canvas;
        //! ゲーム
        std::weak_ptr<ratchet::GameManager> game_manager;
        //! ゲームイベント
        std::weak_ptr<ratchet::event::EventManager> event_manager;
    };
    struct CreateStruct {
        //! ファクトリー
        ratchet::Factory<ratchet::scene::Scene> factory;
        //! ビルダー
        std::unordered_map<std::string, std::shared_ptr<ratchet::factory::builder::IBuilder>> builders;
        //! タイプ,パス
        std::unordered_map<std::string, std::string> reousrce_paths;
    };
private:
    //! 現在
    std::shared_ptr<ratchet::scene::Scene> _scene;
    //! 前
    std::shared_ptr<ratchet::scene::Scene> _prev_scene;
    //! メッセージ
    std::optional<ChangeMessage> _change_message;
    //! 管理オブジェクト
    this_type::Managers _managers;
    //! 作成オブジェクト
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
    /// 変更
    /// </summary>
    /// <param name="name"></param>
    /// <param name="param"></param>
    void ChangeScene(const std::string& name, std::shared_ptr<ratchet::scene::Scene::Param> param);
    void RenderScene(void);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SceneManager();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~SceneManager();
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name=""></param>
    virtual void OnNotify(const scene::SceneMessage& mesage) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(const std::shared_ptr<ratchet::ResourceMgr>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(const std::shared_ptr<base::ui::UICanvas>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameManager(std::weak_ptr<ratchet::GameManager> ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetEventManager(std::weak_ptr<ratchet::event::EventManager> ptr);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Initialize(void);
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time">時間</param>
    /// <returns></returns>
    bool Update(float delta_time);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Render(void);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
};
}
}
#endif // !RATCHET_SCENE_SCENE_MANAGER_H