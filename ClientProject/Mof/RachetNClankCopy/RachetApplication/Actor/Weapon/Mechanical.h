#ifndef MY_MECHANICAL_H
#define MY_MECHANICAL_H


#include "Weapon.h"


namespace my {
class Mechanical : public my::Weapon {
    using super = my::Weapon;
public:
    struct Info {
        //! �e��
        int bullet_count;
        //! �e��
        std::string name;

        Info() = default;
        Info(int size, const char* str) :bullet_count(size), name(str) {
        };
    };
protected:
    //! ����
    float _shot_speed;
    //! �Ԋu
    float _interval;
    //! �Ԋu
    float _interval_max;
    //! �T�C�Y
    int _bullet_count_max;
    //! �T�C�Y
    int _bullet_count;
    //! �Ώۈʒu
    std::optional<Mof::CVector3> _lock_on_position;
    //! �ʒm�p
    my::Observable<const my::Mechanical::Info&> _subject;
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
    /// �Z�b�^�[
    /// </summary>
    /// <param name="position"></param>
    void SetLockOnPosition(Mof::CVector3 position);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    int GetBulletCount(void) const;
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
    /// ���U
    /// </summary>
    /// <param name="count"></param>
    void AddBullet(std::uint32_t count);
    /// <summary>
    /// �ǉ�
    /// </summary>
    void AddMechanicalInfoObserver(const std::shared_ptr<my::Observer<const my::Mechanical::Info&>>& ptr);
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
    /// <summary>
    /// ���Z�b�g
    /// </summary>
    /// <param name=""></param>
    void ResetTargetPosition(void);
};
}
#endif // !MY_MECHANICAL_H