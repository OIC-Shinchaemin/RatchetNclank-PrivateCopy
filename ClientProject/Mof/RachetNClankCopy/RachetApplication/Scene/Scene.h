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
#include "Base/UI/UICanvas.h"


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
        //! 名前
        std::string name;
        //! パス
        std::string resource;
    };
protected:
    //! 状態
    this_type::State _state;
    //! カラーリソース
    Mof::CTexture _rendar_target;
    //! デフォルトのレンダーターゲット
    Mof::LPRenderTarget _default;
    //! ポストエフェクト
    std::optional<my::SceneEffect> _effect;
    //! 遷移
    my::Observable<const scene::SceneMessage&> _subject;
    //! リソース
    std::weak_ptr<my::ResourceMgr> _resource;
    //! UI
    std::weak_ptr<my::UICanvas> _ui_canvas;
    //! 読み込み済み
    bool _loaded;
    //! 同期
    std::mutex _mutex;
    //! スレッド
    std::optional<std::thread> _load_thread;
protected:
    /// <summary>
    /// 判定
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
    /// コンストラクタ
    /// </summary>
    Scene();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Scene();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetUICanvas(std::weak_ptr<my::UICanvas> ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetName(void) = 0;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void AddSceneObserver(const std::shared_ptr<my::Observer<const scene::SceneMessage&>>& ptr);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Load(std::shared_ptr<my::Scene::Param> param);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void);
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
    virtual bool Update(float delta_time);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void);
};
}
#endif // !MY_SCENE_H