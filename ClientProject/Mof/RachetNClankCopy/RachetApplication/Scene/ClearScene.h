#ifndef MY_CLEAR_SCENE_H
#define MY_CLEAR_SCENE_H


#include "Scene.h"


namespace my {
class ClearScene : public my::Scene {
    using super = my::Scene;
protected:
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
    virtual void OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) override;
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
    virtual bool Load(std::shared_ptr<my::Scene::Param> param) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time">時間</param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
};
}
#endif // !MY_CLEAR_SCENE_H