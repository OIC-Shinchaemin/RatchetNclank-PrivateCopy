#ifndef MY_BUILDER_FACTORY_H
#define MY_BUILDER_FACTORY_H


#include <memory>
#include <string>
#include <map>

#include "My/Core/Define.h"
#include "IBuilder.h"
#include "ComponentFactory.h"


namespace my {
class BuilderFactory {
private:
    //! 保持しているBulder
    std::map<std::string, std::shared_ptr<my::IBuilder>> _builders;
    //! コンポーネント
    my::ComponentFactory* _component_factory;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="component_factory"></param>
    BuilderFactory(my::ComponentFactory* component_factory);
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~BuilderFactory();
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    void Release(void);
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    std::shared_ptr<my::IBuilder> Create(const char* path) const;
};
}
#endif // !MY_ACTOR_FACTORY_H