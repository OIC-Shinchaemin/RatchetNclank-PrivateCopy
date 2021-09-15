#ifndef RATCHET_FACTORY_COMPONENT_CREATOR_H
#define RATCHET_FACTORY_COMPONENT_CREATOR_H


#include <memory>

#include "rapidjson/document.h"

#include "../Component/Component.h"


namespace ratchet::factory {
class ComponentCreator {
private:
    //! �R�s�[��
    std::unique_ptr<ratchet::component::Component> _origin;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ComponentCreator();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~ComponentCreator();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::string GetComponentType(void);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name=""></param>
    template<typename T>
    void AddOrigin(void) {
        _origin = std::make_unique<T>(0);
    }
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::component::Component> Create(const rapidjson::Value& param) const;
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    void Release(void);
};
}
#endif // !RATCHET_FACTORY_COMPONENT_CREATOR_H