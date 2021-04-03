#include "BehaviourExecutorFactory.h"

#include "../Character/Enemy.h"

behaviour::ConditionalNodeBase < std::shared_ptr < my::Enemy >> ::Operator my::BehaviourExecutorFactory::GetConditionalOperator(std::string type) {
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

std::shared_ptr<behaviour::FunctionNode<std::shared_ptr<my::Enemy>>> my::BehaviourExecutorFactory::CreateFunctionNode(rapidjson::Value& behaviours, uint32_t index) {
    using namespace behaviour;

    auto function_key = behaviours[index]["function"].GetString();
    auto function_node = std::make_shared<FunctionNode<std::shared_ptr<my::Enemy> >>(
        _function_pointer_container.Get<my::FuncPtrEnemyBool>(function_key));
    return function_node;
}

std::shared_ptr<behaviour::SequencerNode<std::shared_ptr<my::Enemy>>> my::BehaviourExecutorFactory::CreateSequencerNode(rapidjson::Value& behaviours, uint32_t index) {
    using namespace behaviour;

    auto sequencer_node = std::make_shared<SequencerNode<std::shared_ptr<my::Enemy> >>();
    auto& children = behaviours[index]["children"];
    for (size_t i = 0, n = children.Size(); i < n; i++) {
        auto children_index = children[i].GetInt();
        if (behaviours[children_index]["type"] == "FunctionNode") {
            auto node = this->CreateFunctionNode(behaviours, children_index);
            sequencer_node->AddChild(node);
        } // if
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

    } // for
    return sequencer_node;
}

std::shared_ptr<behaviour::SelectorNode<std::shared_ptr<my::Enemy>>> my::BehaviourExecutorFactory::CreateSelectorNode(rapidjson::Value& behaviours, uint32_t index) {
    using namespace behaviour;

    auto selector_node = std::make_shared<SelectorNode<std::shared_ptr<my::Enemy> >>();
    auto& children = behaviours[index]["children"];
    for (size_t i = 0, n = children.Size(); i < n; i++) {
        auto children_index = children[i].GetInt();
        if (behaviours[children_index]["type"] == "FunctionNode") {
            auto node = this->CreateFunctionNode(behaviours, children_index);
            selector_node->AddChild(node);
        } // if
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
    } // for
    return selector_node;
}

behaviour::CompositeNodePtr<std::shared_ptr<my::Enemy> > my::BehaviourExecutorFactory::CreateRootNode(const char* path) {
    rapidjson::Document document;
    if (!ut::ParseJsonDocument(path, document)) {
        return nullptr;
    } // if
    using namespace behaviour;
    behaviour::CompositeNodePtr<std::shared_ptr<my::Enemy> > rootnode;
    _ASSERT_EXPR(document.HasMember("root"), L"ƒƒ“ƒo‚ð•ÛŽ‚µ‚Ä‚¢‚Ü‚¹‚ñ");
    _ASSERT_EXPR(document.HasMember("behaviours"), L"ƒƒ“ƒo‚ð•ÛŽ‚µ‚Ä‚¢‚Ü‚¹‚ñ");

    auto root_index = document["root"]["index"].GetInt();
    auto& behaviours = document["behaviours"];

    auto type = std::string(behaviours[root_index]["type"].GetString());
    if (type == "SequencerNode") {
        rootnode = this-> CreateSequencerNode(behaviours, root_index);
    } // if
    else if (type == "SelectorNode") {
        rootnode = this->CreateSelectorNode(behaviours, root_index);
    } // else if

    return rootnode;
}

my::BehaviourExecutorFactory::BehaviourExecutorFactory() :
    _behaviour_map() {

    _function_pointer_container.Register("Enemy::GoHome", &my::Enemy::GoHome);
    _function_pointer_container.Register("Enemy::OverLooking", &my::Enemy::OverLooking);
    _function_pointer_container.Register("Enemy::ChaseTarget", &my::Enemy::ChaseTarget);
    _function_pointer_container.Register("Enemy::Attack", &my::Enemy::Attack);
    _function_pointer_container.Register("Enemy::ChangeToPatrolState", &my::Enemy::ChangeToPatrolState);
    _function_pointer_container.Register("Enemy::HasTarget", &my::Enemy::HasTarget);
    _function_pointer_container.Register("Enemy::GetDistanceFromInitPosition", &my::Enemy::GetDistanceFromInitPosition);

    _behaviour_map.emplace("../Resource/behaviour/patrol.json", this->CreateRootNode("../Resource/behaviour/patrol.json"));
    _behaviour_map.emplace("../Resource/behaviour/combat.json", this->CreateRootNode("../Resource/behaviour/combat.json"));
}

behaviour::NodeExecutorPtr<std::shared_ptr<my::Enemy> > my::BehaviourExecutorFactory::Create(const char* key) {
    auto it = _behaviour_map.find(key);
    if (it != _behaviour_map.end()) {
        return it->second->CreateExecutor();
    } // if
    return nullptr;
}