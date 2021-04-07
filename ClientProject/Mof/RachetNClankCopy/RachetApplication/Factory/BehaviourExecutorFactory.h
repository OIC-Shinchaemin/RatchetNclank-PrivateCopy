#ifndef MY_BEHAVIOUR_EXECUTOR_FACTORY_H
#define MY_BEHAVIOUR_EXECUTOR_FACTORY_H


#include <memory>
#include <string>
#include <unordered_map>

#include "My/Core/Header.h"
#include "../GameDefine.h"
#include "../Behaviour/Executor/INodeExecutor.h"
#include "../Behaviour/Node/ParameterNode.h"
#include "../Behaviour/Node/CompositeNode.h"
#include "../Behaviour/Node/ConditionalNode.h"
#include "../Behaviour/Node/DecoratorNode.h"
#include "../Behaviour/Node/ActionNode.h"
#include "../Behaviour/Node/SequencerNode.h"
#include "../Behaviour/Node/SelectorNode.h"
#include "../FunctionPointerContainer.h"


namespace my {
class BehaviourExecutorFactory {
    //! マップ
    std::unordered_map<std::string, behaviour::CompositeNodePtr<std::shared_ptr<class Enemy> > > _behaviour_map;
    //! コンテナ
    my::FuncPtrContainer _function_pointer_container;
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    behaviour::CompositeNodePtr<std::shared_ptr<class Enemy> > CreateRootNode(const char* path);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    behaviour::ConditionalNodeBase< std::shared_ptr<class Enemy> > ::Operator GetConditionalOperator(std::string type);
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="behaviours"></param>
    /// <param name="index"></param>
    /// <returns></returns>
    std::shared_ptr<behaviour::FunctionNode<std::shared_ptr<class Enemy> > > CreateFunctionNode(rapidjson::Value& behaviours, uint32_t index);
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="behaviours"></param>
    /// <param name="index"></param>
    /// <returns></returns>
    std::shared_ptr<behaviour::SequencerNode<std::shared_ptr<class Enemy> > > CreateSequencerNode(rapidjson::Value& behaviours, uint32_t index);
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="behaviours"></param>
    /// <param name="index"></param>
    /// <returns></returns>
    std::shared_ptr<behaviour::SelectorNode<std::shared_ptr<class Enemy> > > CreateSelectorNode(rapidjson::Value& behaviours, uint32_t index);

    /// <summary>
    /// 作成
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="behaviour"></param>
    /// <returns></returns>
    template <typename Type>
    std::shared_ptr<behaviour::GetNode<std::shared_ptr<class Enemy>, Type> > CreateGetNode(rapidjson::Value& behaviour) {
        auto function_key = std::string(behaviour["function"].GetString());
        std::string type_name = typeid(Type).name();
        if (type_name == "bool") {
            return std::make_shared<behaviour::GetNode<std::shared_ptr<class Enemy>, Type>>(
                _function_pointer_container.Get<FuncPtrEnemyBool>(function_key.c_str()));
        } // if
        else if (type_name == "float") {
            return std::make_shared<behaviour::GetNode<std::shared_ptr<class Enemy>, Type>>(
                _function_pointer_container.Get<FuncPtrEnemyFloat>(function_key.c_str()));
        } // else if
        return nullptr;
    } // if
    /// <summary>
    /// 作成
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="behaviour"></param>
    /// <returns></returns>
    template <typename Type>
    std::shared_ptr<behaviour::ValueNode<std::shared_ptr<class Enemy>, Type> > CreateValueNode(rapidjson::Value& behaviour) {
        auto& value = behaviour["value"];
        std::string type_name = typeid(Type).name();
        if (type_name == "bool") {
            return std::make_shared<behaviour::ValueNode<std::shared_ptr<class Enemy>, Type>>(value.GetBool());
        } // if
        else if (type_name == "float") {
            return std::make_shared<behaviour::ValueNode<std::shared_ptr<class Enemy>, Type>>(value.GetFloat());
        } // else if
        return nullptr;
    }
    /// <summary>
    /// 作成
    /// </summary>
    /// <typeparam name="Type"></typeparam>
    /// <param name="behaviours"></param>
    /// <param name="index"></param>
    /// <returns></returns>
    template<typename Type>
    std::shared_ptr<behaviour::DecoratorNode<std::shared_ptr<class Enemy>, Type > > CreateDecoratorNode(rapidjson::Value& behaviours, uint32_t index) {
        using namespace behaviour;

        auto operator_type = std::string(behaviours[index]["operator"].GetString());
        uint32_t left_index = behaviours[index]["left"].GetInt();
        uint32_t right_index = behaviours[index]["right"].GetInt();

        // left
        std::shared_ptr<behaviour::IParameterNode<std::shared_ptr<class Enemy>, Type> > left_node;
        auto left_type = std::string(behaviours[left_index]["type"].GetString());
        if (left_type == "GetNode") {
            left_node = this->CreateGetNode<Type>(behaviours[left_index]);
        } // if
        else if (left_type == "ValueNode") {
            left_node = this->CreateValueNode<Type>(behaviours[left_index]);
        } // else if
        // right
        std::shared_ptr<behaviour::IParameterNode<std::shared_ptr<class Enemy>, Type> > right_node;
        auto right_type = std::string(behaviours[right_index]["type"].GetString());
        if (right_type == "GetNode") {
            right_node = this->CreateGetNode<Type>(behaviours[right_index]);
        } // if
        else if (right_type == "ValueNode") {
            right_node = this->CreateValueNode<Type>(behaviours[right_index]);
        } // else if
        // create
        auto decorator_node = std::make_shared<DecoratorNode<std::shared_ptr<class Enemy>, Type>>(
            this->GetConditionalOperator(operator_type), left_node, right_node);
        uint32_t child_index = behaviours[index]["child"].GetInt();
        auto child_type = std::string(behaviours[child_index]["type"].GetString());
        if (child_type == "SequencerNode") {
            decorator_node->SetChild(this->CreateSequencerNode(behaviours, child_index));
        } // if
        else if (child_type == "SelectorNode") {
            decorator_node->SetChild(this->CreateSelectorNode(behaviours, child_index));
        } // else if
        else if (child_type == "FunctionNode") {
            decorator_node->SetChild(this->CreateFunctionNode(behaviours, child_index));
        } // else if
        else if (child_type == "DecoratorNode") {
            auto return_type = std::string(behaviours[child_index]["return"].GetString());
            if (return_type == "bool") {
                auto node = this->CreateDecoratorNode<bool>(behaviours, child_index);
                decorator_node->SetChild(node);
            } // if
            else if (return_type == "float") {
                auto node = this->CreateDecoratorNode<float>(behaviours, child_index);
                decorator_node->SetChild(node);
            } // if

        } // else if
        return decorator_node;
    }
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    BehaviourExecutorFactory();
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    behaviour::NodeExecutorPtr<std::shared_ptr<class Enemy> > Create(const char* key) const;
};
}
#endif // !MY_BEHAVIOUR_EXECUTOR_FACTORY_H