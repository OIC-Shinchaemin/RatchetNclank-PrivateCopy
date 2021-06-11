#ifndef MY_ACTOR_FACTORY_H
#define MY_ACTOR_FACTORY_H


#include <memory>
#include <string>
#include <map>

#include "Base/Core/Define.h"
#include "../Game/GameManager.h"
#include "../Actor.h"
#include "Builder/IBuilder.h"
#include "BuilderFactory.h"
#include "Factory.h"
#include "../Actor/Weapon/Mechanical.h"
#include "../Actor/Item/Bolt.h"
#include "../Actor/Item/BulletItem.h"


namespace my {
class ActorFactory {
private:
    //! ファクトリー
    my::BuilderFactory* _builder_factory;
    //! 保持しているBulder
    std::map<std::string, std::shared_ptr<my::IBuilder>> _builders;
    //! Mechanical
    my::Factory<my::Mechanical> _mechanical_factory;
    //! ゲーム
    std::weak_ptr<my::GameManager> _game;
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
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameManager(std::weak_ptr<my::GameManager> ptr);
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
        
        if constexpr (std::is_same<T, my::Bolt>::value) {
            if (auto game = _game.lock()) {
                ptr->GetMoneySubject()->AddObserver(game->GetGameMoney());
            } // if
        } // if
        else if constexpr (std::is_same<T, my::BulletItem>::value) {
            if (auto game = _game.lock()) {
                ptr->GetWeaponSystemSubject()->AddObserver(game->GetWeaponSystem());
            } // if
        } // else if



        ptr->Construct(_builders.at(builder_key));
        ptr->Initialize(param);
        return ptr;
    }
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="type"></param>
    /// <param name="builder_key"></param>
    /// <param name="param"></param>
    /// <returns></returns>
    std::shared_ptr<my::Mechanical> CreateMechanicalWeapon(const char* type,const std::string& builder_key, my::Actor::Param* param);
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    void Release(void);
};
}
#endif // !MY_ACTOR_FACTORY_H