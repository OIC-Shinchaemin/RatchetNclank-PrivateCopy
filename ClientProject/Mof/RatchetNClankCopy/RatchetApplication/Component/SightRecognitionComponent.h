#ifndef RATCHET_SIGHT_RECOGNITION_COMPONENT_H
#define RATCHET_SIGHT_RECOGNITION_COMPONENT_H


#include "UpdateComponent.h"

#include <memory>
#include <vector>

namespace ratchet {
class SightRecognitionComponent : public ratchet::UpdateComponent {
    using super = ratchet::UpdateComponent;
private:
    //! ����
    float _range;
    //! �F��
    std::vector<std::weak_ptr<ratchet::actor::Actor>> _recognized;
    //! �L����
    std::weak_ptr<class PlayerComponent> _player_com;
    //! �L����
    std::weak_ptr<class EnemyComponent> _ENEMY_com;
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name="ray"></param>
    /// <param name="length"></param>
    /// <param name="color"></param>
    void RenderRay(const Mof::CRay3D& ray, float length, int color);
    void RenderRay(Mof::Vector3 start, float degree_y);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority">�D��x</param>
    SightRecognitionComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    SightRecognitionComponent(const SightRecognitionComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~SightRecognitionComponent();
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
    float GetRange(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const std::vector<std::weak_ptr<ratchet::actor::Actor>>& GetRecognized(void) const;
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
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
};
}
#endif // !RATCHET_SIGHT_RECOGNITION_COMPONENT_H