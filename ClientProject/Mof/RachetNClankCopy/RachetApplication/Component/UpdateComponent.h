#ifndef RATCHET_UPDATE_COMPONENT_H
#define RATCHET_UPDATE_COMPONENT_H


#include "Component.h"


namespace ratchet {
class UpdateComponent : public ratchet::Component {
    using super = ratchet::Component;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    UpdateComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    UpdateComponent(const UpdateComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~UpdateComponent();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="param"></param>
    virtual void SetParam(const rapidjson::Value& param) override;
    /// <summary>
    /// �`�攻��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsUpdate(void) const override;
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
};
}
#endif // !RATCHET_UPDATE_COMPONENT_H