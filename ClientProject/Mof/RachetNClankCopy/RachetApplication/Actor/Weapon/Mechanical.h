#ifndef MY_MECHANICAL_H
#define MY_MECHANICAL_H


#include "Weapon.h"


namespace my {
class Mechanical : public my::Weapon {
    using super = my::Weapon;
protected:
    //! ����
    float _shot_speed;
    //! �Ԋu
    float _interval;
    //! �Ԋu
    float _interval_max;
    //! �T�C�Y
    int _bullet_count;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Mechanical();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Mechanical();
    /// <summary>
    /// ���͔���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsAction(void) const;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool CanFire(void) const;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="transform"></param>
    /// <returns></returns>
    virtual bool Fire(const def::Transform& transform);
};
}
#endif // !MY_MECHANICAL_H