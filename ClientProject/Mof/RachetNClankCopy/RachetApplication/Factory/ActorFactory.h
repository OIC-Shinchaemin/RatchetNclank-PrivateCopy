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
    //! �t�@�N�g���[
    my::BuilderFactory* _builder_factory;
    //! �ێ����Ă���Bulder
    std::map<std::string, std::shared_ptr<my::IBuilder>> _builders;
    //! Mechanical
    my::Factory<my::Mechanical> _mechanical_factory;
    //! �Q�[��
    std::weak_ptr<my::GameManager> _game;
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
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetGameManager(std::weak_ptr<my::GameManager> ptr);
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
    /// �쐬
    /// </summary>
    /// <param name="type"></param>
    /// <param name="builder_key"></param>
    /// <param name="param"></param>
    /// <returns></returns>
    std::shared_ptr<my::Mechanical> CreateMechanicalWeapon(const char* type,const std::string& builder_key, my::Actor::Param* param);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    void Release(void);
};
}
#endif // !MY_ACTOR_FACTORY_H