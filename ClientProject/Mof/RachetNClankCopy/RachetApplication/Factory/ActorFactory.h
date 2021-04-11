#ifndef MY_ACTOR_FACTORY_H
#define MY_ACTOR_FACTORY_H


#include <memory>
#include <string>
#include <map>

#include "My/Core/Define.h"
#include "../Actor.h"
#include "IBuilder.h"
#include "BuilderFactory.h"


namespace my {
class ActorFactory {
private:
    my::BuilderFactory* _builder_factory;
    //! �ێ����Ă���Bulder
    std::map<std::string, std::shared_ptr<my::IBuilder>> _builders;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="builder_factory"></param>
    ActorFactory(my::BuilderFactory* builder_factory);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~ActorFactory();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    std::shared_ptr<my::IBuilder> GetBuilder(const std::string& key);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="key"></param>
    /// <param name="builder"></param>
    void AddBuilder(const std::string& key, std::shared_ptr<my::IBuilder> builder);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    bool Exist(const std::string& type) const;
    /// <summary>
    /// �쐬
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="key"></param>
    /// <param name="transform"></param>
    /// <returns></returns>
    template<typename T>
    std::shared_ptr<T> Create(const std::string& builder_key, my::Actor::Param* param) {
        if (!this->Exist(builder_key)) {
            auto builder = _builder_factory->Create(builder_key.c_str());
            this->AddBuilder(builder_key, builder);
        } // if

        auto ptr = ut::MakeSharedWithRelease<T>();
        ptr->Construct(_builders.at(builder_key));
        ptr->Initialize(param);
        return ptr;
    }
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    void Release(void);
};
}
#endif // !MY_ACTOR_FACTORY_H