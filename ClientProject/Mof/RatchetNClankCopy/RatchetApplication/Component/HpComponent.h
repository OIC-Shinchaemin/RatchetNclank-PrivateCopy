#ifndef RATCHET_COMPONENT_HP_COMPONENT_H
#define RATCHET_COMPONENT_HP_COMPONENT_H


#include "UpdateComponent.h"

#include "Base/Core/Observable.h"
#include "Base/Core/StateMachine.h"
#include "Base/Core/Timer.h"


namespace ratchet::component {
class HpComponent : public ratchet::component::UpdateComponent {
    using super = ratchet::component::UpdateComponent;
private:
    //! �ő�l
    int _hp_max;
    //! Hp
    int _hp;
    //! Hp
    base::core::Observable<int, int> _observable;
    //! UI�\��
    bool _ui_remove;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    HpComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    HpComponent(const HpComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~HpComponent();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="param"></param>
    virtual void SetParam(const rapidjson::Value& param) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    int GetHp(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    int GetHpMax(void) const;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
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
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
    /// <summary>
    /// ��
    /// </summary>
    /// <param name="value"></param>
    void Heal(int value);
    /// <summary>
    /// �_���[�W
    /// </summary>
    /// <param name="value"></param>
    void Damage(int value);
    /// <summary>
    /// UI�o�^
    /// </summary>
    /// <param name=""></param>
    void RegisterUI(void);
};
}
#endif // !RATCHET_COMPONENT_HP_COMPONENT_H