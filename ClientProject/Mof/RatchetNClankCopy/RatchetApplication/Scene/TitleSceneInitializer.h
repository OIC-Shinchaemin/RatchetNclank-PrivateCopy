#ifndef RATCHET_SCENE_TITLE_SCENE_INITIALIZER_H
#define RATCHET_SCENE_TITLE_SCENE_INITIALIZER_H


#include "TitleScene.h"


namespace ratchet::scene {
class TitleSceneInitializer {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    TitleSceneInitializer();
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="out">対象</param>
    /// <returns></returns>
    bool Execute(std::shared_ptr<ratchet::scene::TitleScene>& out);
};
}
#endif // !RATCHET_SCENE_TITLE_SCENE_INITIALIZER_H