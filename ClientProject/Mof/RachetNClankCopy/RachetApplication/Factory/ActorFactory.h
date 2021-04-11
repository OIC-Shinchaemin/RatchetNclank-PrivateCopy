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
    //! 保持しているBulder
    std::map<std::string, std::shared_ptr<my::IBuilder>> _builders;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="builder_factory"></param>
    ActorFactory(my::BuilderFactory* builder_factory);
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~ActorFactory();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    std::shared_ptr<my::IBuilder> GetBuilder(const std::string& key);
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="key"></param>
    /// <param name="builder"></param>
    void AddBuilder(const std::string& key, std::shared_ptr<my::IBuilder> builder);
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    bool Exist(const std::string& type) const;
    /// <summary>
    /// 作成
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
    /// 解放
    /// </summary>
    /// <param name=""></param>
    void Release(void);
};
}
#endif // !MY_ACTOR_FACTORY_H