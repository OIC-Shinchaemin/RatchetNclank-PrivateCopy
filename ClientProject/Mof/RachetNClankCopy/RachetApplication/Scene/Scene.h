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
        //! 名前
        std::string name;
        //! パス
        std::string resource;
    };
protected:
    //! 状態
    my::SceneState _state;
    //! カラーリソース
    Mof::CTexture _rendar_target;
    //! デフォルトのレンダーターゲット
    Mof::LPRenderTarget _default;
    //! ポストエフェクト
    std::optional<my::SceneEffect> _effect;
    //! 遷移
    my::Observable<const SceneMessage&> _subject;
protected:
    Mof::LPRenderTarget GetDefaultRendarTarget(void) const;
    virtual bool PreRender(void);
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
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetName(void) = 0;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void AddSceneObserver(const std::shared_ptr<my::Observer<const SceneMessage&>>& ptr);
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