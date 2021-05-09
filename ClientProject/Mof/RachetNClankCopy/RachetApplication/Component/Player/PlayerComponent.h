#ifndef MY_PLAYER_COMPONENT_H
#define MY_PLAYER_COMPONENT_H


#include "../CharacterComponent.h"

#include <memory>

#include "My/Core/Observable.h"


namespace my {
class PlayerComponent : public my::CharacterComponent {
    using super = my::CharacterComponent;
private:
    //! �W�I
    std::weak_ptr<my::Actor> _target;
    //! �J�[�\���ʒu
    my::Observable<std::optional<Mof::CVector3>> _observable;
    //! ���
    std::weak_ptr<class PlayerStateComponent> _state_com;
    //! �n�_
    std::string _next_terrain;
    //! �A�N�V�����t���O
    bool _action_enable;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    PlayerComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    PlayerComponent(const PlayerComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerComponent();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetTarget(const std::shared_ptr<my::Actor>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetNextTerrain(const std::string& terrain);
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
    std::weak_ptr<my::Actor> GetTarget(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::string GetNextTerrain(void) const;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsActionEnable(void);
    /// <summary>
    /// �L����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool EnableAction(void);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool DisableAction(void);
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
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool DebugRender(void) override;
};
}
#endif // !MY_PLAYER_COMPONENT_H