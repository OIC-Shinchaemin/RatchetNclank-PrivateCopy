#ifndef MY_SCENE_MANAGER_H
#define MY_SCENE_MANAGER_H


#include <memory>
#include <string>
#include <vector>


#include "My/Core/Observer.h"
#include "Scene.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "My/UI/UICanvas.h"
#include "../Game/GameManager.h"
#include "../Event/EventManager.h"
#include "../Factory/Builder/IBuilder.h"
#include "../Factory/Builder/Scene/TitleSceneBuilder.h"
#include "../Factory/Builder/Scene/GameSceneBuilder.h"


namespace my {
class SceneManager : public std::enable_shared_from_this<my::SceneManager>, public my::Observer<const scene::SceneMessage&> {
private:
    struct ChangeMessage {
        std::string name;
        std::shared_ptr<my::Scene::Param> param;
    };
    std::shared_ptr<my::Scene> _scene;
    std::shared_ptr<my::Scene> _prev_scene;
    //! メッセージ
    std::optional<ChangeMessage> _change_message;
    //! リソース
    std::weak_ptr<my::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<my::UICanvas> _ui_canvas;
    //! ゲーム
    std::weak_ptr<my::GameManager> _game_manager;
    //! ゲームイベント
    std::weak_ptr<my::EventManager> _event_manager;
    //! ファクトリー
    my::Factory<my::Scene> _factory;
    //! ビルダー
    std::unordered_map<std::string, std::shared_ptr<my::IBuilder>> _builders;
    //! タイプ,パス
    std::unordered_map<std::string, std::string> _reousrce_paths;

    template<typename Builder>
    void RegisterBuilder(const std::string& name) {
            auto ptr = ut::MakeSharedWithRelease<Builder>();
            ptr->SetResourceManager(_resource);
            _builders.emplace(name, ptr); ;
    }
    template<>
    void RegisterBuilder<builder::TitleSceneBuilder>(const std::string& name) {
        auto ptr = ut::MakeSharedWithRelease<builder::TitleSceneBuilder>();
        ptr->SetResourceManager(_resource);
        ptr->SetGameManager(_game_manager);
        _builders.emplace(name, ptr); ;
    }
    template<>
    void RegisterBuilder<builder::GameSceneBuilder>(const std::string& name) {
        auto ptr = ut::MakeSharedWithRelease<builder::GameSceneBuilder>();
        ptr->SetResourceManager(_resource);
        ptr->SetUICanvas(_ui_canvas);
        ptr->SetGameManager(_game_manager);
        ptr->SetEventManager(_event_manager);
        _builders.emplace(name, ptr); ;
    }

    /// <summary>
    /// 変更
    /// </summary>
    /// <param name="name"></param>
    /// <param name="param"></param>
    void ChangeScene(const std::string& name, std::shared_ptr<my::Scene::Param> param);
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
    void SetResourceManager(const std::shared_ptr<my::ResourceMgr>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(const std::shared_ptr<my::UICanvas>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameManager(std::weak_ptr<my::GameManager> ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetEventManager(std::weak_ptr<my::EventManager> ptr);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Initialize(void);
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
#endif // !MY_SCENE_MANAGER_H