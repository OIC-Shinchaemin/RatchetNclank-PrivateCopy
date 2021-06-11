#ifndef RATCHET_CHARACTER_COMPONENT_H
#define RATCHET_CHARACTER_COMPONENT_H


#include "UpdateComponent.h"

#include <memory>

#include "Base/Core/Observable.h"


namespace ratchet {
class CharacterComponent : public ratchet::UpdateComponent {
    using super = ratchet::UpdateComponent;
protected:
    //! �傫��
    float _volume;
    //! ����
    float _height;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    CharacterComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    CharacterComponent(const CharacterComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~CharacterComponent();
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
    float GetVolume(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetHeight(void) const;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
};
}
#endif // !RATCHET_CHARACTER_COMPONENT_H