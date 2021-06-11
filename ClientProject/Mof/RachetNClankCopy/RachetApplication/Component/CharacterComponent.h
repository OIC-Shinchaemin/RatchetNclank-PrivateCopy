#ifndef RACHET_CHARACTER_COMPONENT_H
#define RACHET_CHARACTER_COMPONENT_H


#include "UpdateComponent.h"

#include <memory>

#include "Base/Core/Observable.h"


namespace rachet {
class CharacterComponent : public rachet::UpdateComponent {
    using super = rachet::UpdateComponent;
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
    virtual std::shared_ptr<rachet::Component> Clone(void) override;
};
}
#endif // !RACHET_CHARACTER_COMPONENT_H