#ifndef RACHET_RENDERER_H
#define RACHET_RENDERER_H


#include <memory>
#include <vector>

#include "../GameDefine.h"
#include "../Actor.h"
#include "../ResourceManager.h"


namespace rachet {
class Renderer {
    //! �L�����N�^
    std::vector<std::shared_ptr<rachet::Actor>> _actors;
    //! �\��
    std::vector<std::shared_ptr<rachet::Actor>> _enable_actors;
    //! ��\��
    std::vector<std::shared_ptr<rachet::Actor>> _disable_actors;
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
    void AddElement(const std::shared_ptr<rachet::Actor>& ptr);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void RemoveElement(const std::shared_ptr<rachet::Actor>& ptr);
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
#endif // !RACHET_RENDERER_H