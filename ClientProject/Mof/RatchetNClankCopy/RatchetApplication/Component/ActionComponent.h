#ifndef RATCHET_COMPONENT_ACTION_COMPONENT_H
#define RATCHET_COMPONENT_ACTION_COMPONENT_H


#include "UpdateComponent.h"

#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>


namespace ratchet {
namespace component {
class ActionComponent : public ::ratchet::component::UpdateComponent {
    using super = ::ratchet::component::UpdateComponent;
private:
    //! ���݂̃A�N�V����
    std::shared_ptr<::ratchet::component::ActionComponent> _current_action;
    //! �A�N�V����
    std::unordered_map<std::string, std::shared_ptr<::ratchet::component::ActionComponent>> _children;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    ActionComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    ActionComponent(const ActionComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~ActionComponent();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    virtual void SetOwner(const std::shared_ptr<::ratchet::actor::Actor>& ptr) override;
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
    virtual std::string_view GetStateType(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name=""></param>
    /// <returns></returns>
    template<typename T>
    std::shared_ptr<T>GetComponent(void) const {
        for (auto& child : _children) {
            auto ret = std::dynamic_pointer_cast<T>(child.second);
            if (ret) {
                return ret;
            } // if
        } // for
        return nullptr;
    }
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const std::unordered_map<std::string, std::shared_ptr<::ratchet::component::ActionComponent>>& GetChildren(void);
    /// <summary>
    /// ���͔���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsInput(void) const override;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
    /// <summary>
    /// �J�n
    /// </summary>
    /// <param name=""></param>
    /// <returns>����</returns>
    virtual bool Start(void);
    /// <summary>
    /// �I��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool End(void);
    /// <summary>
    /// �ύX
    /// </summary>
    /// <param name="name"></param>
    void ChangeAction(std::string_view name);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<::ratchet::component::Component> Clone(void) override;
};
}
}
#endif // !RATCHET_COMPONENT_ACTION_COMPONENT_H