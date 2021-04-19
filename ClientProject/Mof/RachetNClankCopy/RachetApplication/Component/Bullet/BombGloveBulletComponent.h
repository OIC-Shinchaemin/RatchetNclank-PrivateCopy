#ifndef MY_BOMB_GLOVE_BULLET_COMPONENT_H
#define MY_BOMB_GLOVE_BULLET_COMPONENT_H


#include "../UpdateComponent.h"

#include <memory>


namespace my {
class BombGloveBulletComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    BombGloveBulletComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    BombGloveBulletComponent(const BombGloveBulletComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~BombGloveBulletComponent();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time">����</param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
#ifdef _DEBUG
    virtual bool Render(void) override;
#endif // _DEBUG
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<my::Component> Clone(void) override;
};
}
#endif // !MY_BOMB_GLOVE_BULLET_COMPONENT_H