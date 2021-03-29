#ifndef MY_RENDERER_H
#define MY_RENDERER_H


#include <memory>
#include <vector>

#include "../Actor.h"
#include "../Character/Character.h"


namespace my {
class Renderer {
    //! �L�����N�^
    std::vector<std::shared_ptr<my::Character>> _characters;
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
    void AddElement(const std::shared_ptr<my::Character>& ptr);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void RemoveElement(const std::shared_ptr<my::Character>& ptr);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Render(void);
};
}
#endif // !MY_RENDERER_H