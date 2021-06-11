#ifndef BUILDER_TITLE_SCENE_BUILDER_H
#define BUILDER_TITLE_SCENE_BUILDER_H


#include "SceneBuilder.h"

#include <memory>

#include "../../../Scene/TitleScene.h"
#include "../../../Game/GameManager.h"


namespace builder {
class TitleSceneBuilder : public builder::SceneBuilder {
    using super = builder::SceneBuilder;
private:
    //! ゲーム
    std::weak_ptr<rachet::GameManager> _game;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    TitleSceneBuilder();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~TitleSceneBuilder();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameManager(std::weak_ptr<rachet::GameManager> ptr);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    virtual void Release(void) override;
    /// <summary>
    /// 構築
    /// </summary>
    /// <param name=""></param>
    virtual void Construct(std::any shared_this) override;
};
}
#endif // !BUILDER_TITLE_SCENE_BUILDER_H