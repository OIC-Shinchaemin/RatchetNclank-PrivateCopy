#ifndef MY_BEHAVIOUR_FACTORY_H
#define MY_BEHAVIOUR_FACTORY_H


#include <memory>
#include <string>
#include <unordered_map>

#include "../GameDefine.h"
#include "My/Core/FunctionPointerContainer.h"
#include "../Behaviour/Node/ParameterNode.h"
#include "../Behaviour/Node/CompositeNode.h"
#include "../Behaviour/Node/ConditionalNode.h"
#include "../Behaviour/Node/DecoratorNode.h"
#include "../Behaviour/Node/ActionNode.h"
#include "../Behaviour/Node/SequencerNode.h"
#include "../Behaviour/Node/SelectorNode.h"
#include "../Behaviour/Node/Action/AlwaysTrueNode.h"
#include "../Behaviour/Node/Action/AlwaysFalseNode.h"
#include "../Behaviour/Node/Action/GoHomeNode.h"
#include "../Behaviour/Node/Action/LookAroundNode.h"
#include "../Behaviour/Node/Action/MoveToEnemyNode.h"
#include "../Behaviour/Node/Action/MeleeAttackNode.h"
#include "../Behaviour/Node/Action/ChangePatrolNode.h"
#include "../Behaviour/Node/Condition/NotAwayFromHomeNode.h"
#include "../Behaviour/Node/Condition/TargetRecognitionNode.h"
#include "../Behaviour/Node/Condition/TargetInMeleeAttackRangeNode.h"
#include "../Behaviour/Node/Condition/TargetOutOfMeleeAttackRangeNode.h"
#include "../Actor/Character/Enemy.h"
#include "Factory.h"


namespace my {
class BehaviourFactory {
private:
    //! コンテナ
    my::FuncPtrContainer _function_pointer_container;
    //! アクション
    my::Factory<behaviour::ActionNodeBase<std::shared_ptr<my::Enemy> >> _action_factory;
    //! アクション
    my::Factory<behaviour::ConditionalNodeBase<std::shared_ptr<my::Enemy> >> _condition_factory;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    BehaviourFactory() :
        _function_pointer_container() {
        _action_factory.Register<behaviour::AlwaysTrueNode<std::shared_ptr<my::Enemy>>>("AlwaysTrueNode");
        _action_factory.Register<behaviour::AlwaysFalseNode<std::shared_ptr<my::Enemy>>>("AlwaysFalseNode");
        _action_factory.Register<behaviour::GoHomeNode<std::shared_ptr<my::Enemy>>>("GoHomeNode");
        _action_factory.Register<behaviour::LookAroundNode<std::shared_ptr<my::Enemy>>>("LookAroundNode");
        _action_factory.Register<behaviour::MoveToEnemyNode<std::shared_ptr<my::Enemy>>>("MoveToEnemyNode");
        _action_factory.Register<behaviour::MeleeAttackNode<std::shared_ptr<my::Enemy>>>("MeleeAttackNode");
        _action_factory.Register<behaviour::ChangePatrolNode<std::shared_ptr<my::Enemy>>>("ChangePatrolNode");
        _condition_factory.Register<behaviour::NotAwayFromHomeNode<std::shared_ptr<my::Enemy>>>("NotAwayFromHomeNode");
        _condition_factory.Register<behaviour::TargetRecognitionNode<std::shared_ptr<my::Enemy>>>("TargetRecognitionNode");
        _condition_factory.Register<behaviour::TargetInMeleeAttackRangeNode<std::shared_ptr<my::Enemy>>>("TargetInMeleeAttackRangeNode");
        _condition_factory.Register<behaviour::TargetOutOfMeleeAttackRangeNode<std::shared_ptr<my::Enemy>>>("TargetOutOfMeleeAttackRangeNode");
    }
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    behaviour::CompositeNodePtr<std::shared_ptr<class Enemy> > CreateRootNode(const char* path) {
        rapidjson::Document document;
        if (!ut::ParseJsonDocument(path, document)) {
            return nullptr;
        } // if
        using namespace behaviour;
        behaviour::CompositeNodePtr<std::shared_ptr<my::Enemy> > rootnode;
        _ASSERT_EXPR(document.HasMember("root"), L"メンバを保持していません");
        _ASSERT_EXPR(document.HasMember("behaviours"), L"メンバを保持していません");

        auto root_index = document["root"]["index"].GetInt();
        auto& behaviours = document["behaviours"];

        auto type = std::string(behaviours[root_index]["type"].GetString());
        if (type == "SequencerNode") {
            rootnode = this->CreateSequencerNode(behaviours, root_index);
        } // if
        else if (type == "SelectorNode") {
            rootnode = this->CreateSelectorNode(behaviours, root_index);
        } // else if

        return rootnode;
    }
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name="type"></param>
    /// <returns></returns>
    behaviour::ConditionalNodeBase< std::shared_ptr<class Enemy> > ::Operator GetConditionalOperator(std::string type) {
        using Operator = behaviour::ConditionalNodeBase<std::shared_ptr<my::Enemy>>::Operator;
        if (type == "Equal") {
            return Operator::Equal;
        } // if
        else if (type == "NotEqual") {
            return Operator::NotEqual;
        } // else if
        else if (type == "Less") {
            return Operator::Less;
        } // else if
        else if (type == "LessEqual") {
            return Operator::LessEqual;
        } // else if
        else if (type == "Greater") {
            return Operator::Greater;
        } // else if
        else if (type == "GreaterEqual") {
            return Operator::GreaterEqual;
        } // else if
        // default 
        return Operator::Equal;
    }
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="behaviours"></param>
    /// <param name="index"></param>
    /// <returns></returns>
    std::shared_ptr<behaviour::FunctionNode<std::shared_ptr<class Enemy> > > CreateFunctionNode(rapidjson::Value& behaviours, uint32_t index) {
        using namespace behaviour;

        auto function_key = behaviours[index]["function"].GetString();
        auto function_node = std::make_shared<FunctionNode<std::shared_ptr<my::Enemy> >>(
            _function_pointer_container.Get<my::FuncPtrEnemyBool>(function_key));
        return function_node;
    }
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="behaviours"></param>
    /// <param name="index"></param>
    /// <returns></returns>
    std::shared_ptr<behaviour::ActionNodeBase<std::shared_ptr<class Enemy> > > CreateActionNode(rapidjson::Value& behaviours, uint32_t index) {
        using namespace behaviour;
        auto derived = behaviours[index]["derived"].GetString();
        return _action_factory.Create(derived);
    }
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="behaviours"></param>
    /// <param name="index"></param>
    /// <returns></returns>
    std::shared_ptr<behaviour::ConditionalNodeBase<std::shared_ptr<class Enemy> > > CreateConditionalNode(rapidjson::Value& behaviours, uint32_t index) {
        using namespace behaviour;
        auto derived = behaviours[index]["derived"].GetString();
        return _condition_factory.Create(derived);
        //auto& child = behaviours[index]["child"];
        //auto child_index = child.GetInt();
        /*
        if (behaviours[child_index]["type"] == "ActionNode") {
            auto node = this->CreateActionNode(behaviours, child_index);
            simplex_node->SetChild(node);
        } // if
        else if (behaviours[child_index]["type"] == "ConditionalNode") {
            auto node = this->CreateConditionalNode(behaviours, child_index);
            simplex_node->SetChild(node);
        } // if
        else if (behaviours[child_index]["type"] == "FunctionNode") {
            auto node = this->CreateFunctionNode(behaviours, child_index);
            simplex_node->SetChild(node);
        } // else if
        else if (behaviours[child_index]["type"] == "DecoratorNode") {
            auto return_type = std::string(behaviours[child_index]["return"].GetString());
            if (return_type == "bool") {
                auto node = this->CreateDecoratorNode<bool>(behaviours, child_index);
                simplex_node->SetChild(node);
            } // if
            else if (return_type == "float") {
                auto node = this->CreateDecoratorNode<float>(behaviours, child_index);
                simplex_node->SetChild(node);
            } // if
        } // else if
        else if (behaviours[child_index]["type"] == "SequencerNode") {
            auto node = this->CreateSequencerNode(behaviours, child_index);
            simplex_node->SetChild(node);
        } // if
        else if (behaviours[child_index]["type"] == "SelectorNode") {
            auto node = this->CreateSelectorNode(behaviours, child_index);
            simplex_node->SetChild(node);
        } // else if
        return conditional_node;
        */
    }
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="behaviours"></param>
    /// <param name="index"></param>
    /// <returns></returns>
    std::shared_ptr<behaviour::SequencerNode<std::shared_ptr<class Enemy> > > CreateSequencerNode(rapidjson::Value& behaviours, uint32_t index) {
        using namespace behaviour;

        auto sequencer_node = std::make_shared<SequencerNode<std::shared_ptr<my::Enemy> >>();
        auto& children = behaviours[index]["children"];
        for (size_t i = 0, n = children.Size(); i < n; i++) {
            auto children_index = children[i].GetInt();
            if (behaviours[children_index]["type"] == "ActionNode") {
                auto node = this->CreateActionNode(behaviours, children_index);
                sequencer_node->AddChild(node);
            } // if
            else if (behaviours[children_index]["type"] == "ConditionalNode") {
                auto node = this->CreateConditionalNode(behaviours, children_index);
                sequencer_node->AddChild(node);
            } // if
            else if (behaviours[children_index]["type"] == "FunctionNode") {
                auto node = this->CreateFunctionNode(behaviours, children_index);
                sequencer_node->AddChild(node);
            } // else if
            else if (behaviours[children_index]["type"] == "DecoratorNode") {
                auto return_type = std::string(behaviours[children_index]["return"].GetString());
                if (return_type == "bool") {
                    auto node = this->CreateDecoratorNode<bool>(behaviours, children_index);
                    sequencer_node->AddChild(node);
                } // if
                else if (return_type == "float") {
                    auto node = this->CreateDecoratorNode<float>(behaviours, children_index);
                    sequencer_node->AddChild(node);
                } // if

            } // else if

            else if (behaviours[children_index]["type"] == "SequencerNode") {
                auto node = this->CreateSequencerNode(behaviours, children_index);
                sequencer_node->AddChild(node);
            } // if
            else if (behaviours[children_index]["type"] == "SelectorNode") {
                auto node = this->CreateSelectorNode(behaviours, children_index);
                sequencer_node->AddChild(node);
            } // else if

        } // for
        return sequencer_node;
    }
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name="behaviours"></param>
    /// <param name="index"></param>
    /// <returns></returns>
    std::shared_ptr<behaviour::SelectorNode<std::shared_ptr<class Enemy> > > CreateSelectorNode(rapidjson::Value& behaviours, uint32_t index) {
        using namespace behaviour;

        auto selector_node = std::make_shared<SelectorNode<std::shared_ptr<my::Enemy> >>();
        auto& children = behaviours[index]["children"];
        for (size_t i = 0, n = children.Size(); i < n; i++) {
            auto children_index = children[i].GetInt();
            if (behaviours[children_index]["type"] == "ActionNode") {
                auto node = this->CreateActionNode(behaviours, children_index);
                selector_node->AddChild(node);
            } // if
            else if (behaviours[children_index]["type"] == "ConditionalNode") {
                auto node = this->CreateConditionalNode(behaviours, children_index);
                selector_node->AddChild(node);
            } // if
            else if (behaviours[children_index]["type"] == "FunctionNode") {
                auto node = this->CreateFunctionNode(behaviours, children_index);
                selector_node->AddChild(node);
            } // else if
            else if (behaviours[children_index]["type"] == "DecoratorNode") {
                auto return_type = std::string(behaviours[children_index]["return"].GetString());
                if (return_type == "bool") {
                    auto node = this->CreateDecoratorNode<bool>(behaviours, children_index);
                    selector_node->AddChild(node);
                } // if
                else if (return_type == "float") {
                    auto node = this->CreateDecoratorNode<float>(behaviours, children_index);
                    selector_node->AddChild(node);
                } // if

            } // else if

            else if (behaviours[children_index]["type"] == "SequencerNode") {
                auto node = this->CreateSequencerNode(behaviours, children_index);
                selector_node->AddChild(node);
            } // if
            else if (behaviours[children_index]["type"] == "SelectorNode") {
                auto node = this->CreateSelectorNode(behaviours, children_index);
                selector_node->AddChild(node);
            } // else if

        } // for
        return selector_node;
    }

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
};
}
#endif // !MY_BEHAVIOUR_FACTORY_H