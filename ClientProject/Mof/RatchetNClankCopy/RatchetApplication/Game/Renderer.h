#ifndef RATCHET_GAME_RENDERER_H
#define RATCHET_GAME_RENDERER_H


#include <memory>
#include <vector>

#include "../GameDefine.h"
#include "../Actor/Actor.h"
#include "../ResourceManager.h"


namespace ratchet {
namespace game {
class Renderer {
    //! �L�����N�^
    std::vector<std::shared_ptr<ratchet::actor::Actor>> _actors;
    //! �\��
    std::vector<std::shared_ptr<ratchet::actor::Actor>> _enable_actors;
    //! ��\��
    std::vector<std::shared_ptr<ratchet::actor::Actor>> _disable_actors;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Renderer();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Renderer();
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void AddElement(const std::shared_ptr<ratchet::actor::Actor>& ptr);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void RemoveElement(const std::shared_ptr<ratchet::actor::Actor>& ptr);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Render(void);
    /// <summary>
    /// ���Z�b�g
    /// </summary>
    /// <param name=""></param>
    void Reset(void);
};
}
}
#endif // !RATCHET_GAME_RENDERER_H