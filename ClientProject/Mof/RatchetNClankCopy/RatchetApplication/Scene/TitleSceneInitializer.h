#ifndef RATCHET_SCENE_TITLE_SCENE_INITIALIZER_H
#define RATCHET_SCENE_TITLE_SCENE_INITIALIZER_H


#include "TitleScene.h"


namespace ratchet::scene {
class TitleSceneInitializer {
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    TitleSceneInitializer();
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="out">�Ώ�</param>
    /// <returns></returns>
    bool Execute(std::shared_ptr<ratchet::scene::TitleScene>& out);
};
}
#endif // !RATCHET_SCENE_TITLE_SCENE_INITIALIZER_H