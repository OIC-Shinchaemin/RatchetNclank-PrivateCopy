#ifndef RATCHET_SCENE_GAME_SCENE_H
#define RATCHET_SCENE_GAME_SCENE_H


#include "Scene.h"

#include <memory>
#include <vector>

#include "../Game/GameManager.h"
#include "../Event/EventManager.h"
#include "../Game/GameWorld.h"
#include "../Game/Renderer.h"
#include "../Game/PhysicsWorld.h"
#include "../Stage/Stage.h"
#include "../Game/GameSystem/ShopSystem.h"


#include "../Actor/Character/Player.h"

namespace ratchet {
namespace scene {
class GameScene : public ratchet::scene::Scene, public base::core::Observer<const ratchet::ShopSystem::Info&> {
    using super = ratchet::scene::Scene;
    using this_type = ratchet::scene::GameScene;
private:
    //! 追加
    std::vector<std::shared_ptr<ratchet::Actor>> _created_actors;
    //! 削除
    std::vector<std::shared_ptr<ratchet::Actor>> _delete_actors;
    //! ゲーム
    ratchet::GameWorld _game_world;
    //! レンダラー
    ratchet::Renderer _renderer;
    //! コリジョン
    ratchet::PhysicsWorld _physic_world;
    //! ステージ
    Stage _stage;
    //! 再初期化
    bool _re_initialize;
    //! メニュー
    base::core::Observable<bool> _pause_menu_subject;


    //! ゲーム
    std::weak_ptr<ratchet::GameManager> _game;
    //! イベント
    std::weak_ptr<ratchet::EventManager> _event;
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void AddElement(const std::shared_ptr<ratchet::Actor>& ptr);
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void RemoveElement(const std::shared_ptr<ratchet::Actor>& ptr);
    /// <summary>
    /// 再初期化
    /// </summary>
    void ReInitialize(void);
protected:
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool SceneUpdate(float delta_time) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool LoadingUpdate(float delta_time) override;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool SceneRender(void) override;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool LoadingRender(void) override;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameScene();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~GameScene();
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    virtual void OnNotify(const char* type, const std::shared_ptr<ratchet::Actor>& ptr) override;
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="info"></param>
    virtual void OnNotify(const ratchet::ShopSystem::Info& info) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameManager(std::weak_ptr<ratchet::GameManager> ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetEventManager(std::weak_ptr<ratchet::EventManager> ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetName(void) override;

    /// <summary>
    /// 読み込み
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Load(std::shared_ptr<super::Param>  param) override;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
};
}
}
#endif // !RATCHET_SCENE_GAME_SCENE_H