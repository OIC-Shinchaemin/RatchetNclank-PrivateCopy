#ifndef RATCHET_SCENE_CLEAR_SCENE_H
#define RATCHET_SCENE_CLEAR_SCENE_H


#include "Scene.h"


namespace ratchet::scene {
class ClearScene : public ratchet::scene::Scene {
    using super = ratchet::scene::Scene;
    //! テキスト
    std::string _clear_text;
    //! 位置
    Mof::CVector2 _clear_text_position;
    //! テキスト
    std::string _next_text;
    //! 位置
    Mof::CVector2 _next_text_position;
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
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ClearScene();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ClearScene();
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    virtual void OnNotify(const char* type, const std::shared_ptr<ratchet::actor::Actor>& ptr) override;
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
    virtual bool Load(std::shared_ptr<super::Param> param) override;
};
}
#endif // !RATCHET_SCENE_CLEAR_SCENE_H