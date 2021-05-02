#ifndef MY_COMPONENT_FACTORY_H
#define MY_COMPONENT_FACTORY_H


#include <memory>
#include <string>
#include <unordered_map>

#include "My/Core/Define.h"
#include "ComponentCreator.h"


namespace my {
class ComponentFactory {
    using ComponentMap = std::unordered_map<std::string, std::shared_ptr<my::ComponentCreator>>;
private:
    //! ���L
    ComponentMap _component_creators;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ComponentFactory();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~ComponentFactory();
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    void Release(void);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name=""></param>
    /// <returns></returns>
    template<typename T>
    bool AddComponentCreator(void) {
        // �w��̃R���|�[�l���g��o�^����
        auto creator = std::make_shared<my::ComponentCreator>();
        creator->AddOrigin<T>();

        // ���ɂ���Ȃ�ǉ����Ȃ�
        auto key = creator->GetComponentType();
        auto it = _component_creators.find(key);
        if (it != _component_creators.end()) {
            return false;
        } // if
        _component_creators.emplace(key, creator);
        return true;
    }
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="key"></param>
    /// <param name="param"></param>
    /// <returns></returns>
    std::shared_ptr<my::Component> Create(const std::string& key, const rapidjson::Value& param) const;
};
}
#endif // !MY_COMPONENT_FACTORY_H