#ifndef MY_BUILDER_FACTORY_H
#define MY_BUILDER_FACTORY_H


#include <memory>
#include <string>
#include <map>

#include "My/Core/Define.h"
#include "Builder/IBuilder.h"
#include "ComponentFactory.h"
#include "../ResourceManager.h"
#include "../GameDefine.h"
#include "Factory.h"


namespace my {
class BuilderFactory {
private:
    //! �ێ����Ă���Bulder
    std::map<std::string, std::shared_ptr<my::IBuilder>> _builders;
    //! �R���|�[�l���g
    my::ComponentFactory* _component_factory;
    //! ���\�[�X
    std::weak_ptr<my::ResourceMgr> _resource;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="component_factory"></param>
    BuilderFactory(my::ComponentFactory* component_factory);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~BuilderFactory();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetResourceManager(std::weak_ptr<my::ResourceMgr> ptr);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    void Release(void);
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    std::shared_ptr<my::IBuilder> Create(const char* path) const;
};
}
#endif // !MY_ACTOR_FACTORY_H