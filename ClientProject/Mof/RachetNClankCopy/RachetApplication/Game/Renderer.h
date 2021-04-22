#ifndef MY_RENDERER_H
#define MY_RENDERER_H


#include <memory>
#include <vector>

#include "../GameDefine.h"
#include "../Actor.h"
#include "../ResourceManager.h"


namespace my {
class Renderer {
    //! �L�����N�^
    std::vector<std::shared_ptr<my::Actor>> _actors;
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
    void AddElement(const std::shared_ptr<my::Actor>& ptr);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void RemoveElement(const std::shared_ptr<my::Actor>& ptr);
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
#endif // !MY_RENDERER_H