#include "BehaviourFactory.h"

#include "../Behaviour/Node/SequencerNode.h"
#include "../Behaviour/Node/SelectorNode.h"

#include "../Behaviour/Node/Action/AlwaysTrueNode.h"
#include "../Behaviour/Node/Action/AlwaysFalseNode.h"
#include "../Behaviour/Node/Action/GoHomeNode.h"
#include "../Behaviour/Node/Action/LookAroundNode.h"
#include "../Behaviour/Node/Action/MoveToEnemyNode.h"
#include "../Behaviour/Node/Action/MeleeAttackNode.h"
#include "../Behaviour/Node/Action/RangedAttackNode.h"
#include "../Behaviour/Node/Action/ChangePatrolNode.h"
#include "../Behaviour/Node/Action/ChangeCombatNode.h"

#include "../Behaviour/Node/Condition/NotAwayFromHomeNode.h"
#include "../Behaviour/Node/Condition/TargetRecognitionNode.h"
#include "../Behaviour/Node/Condition/NotTargetRecognitionNode.h"

#include "../Behaviour/Node/Decorator/TargetInMeleeAttackRange.h"
#include "../Behaviour/Node/Decorator/TargetInRangedAttackRange.h"
#include "../Behaviour/Node/Decorator/RecognizingTargetNode.h"
#include "../Behaviour/Node/Decorator/NotRecognizingTargetNode.h"


my::BehaviourFactory::BehaviourFactory() :
    _composite_factory(),
    _action_factory(),
    _condition_factory(),
    _decorator_factory() {
    _composite_factory.Register<behaviour::SequencerNode>("SequencerNode");
    _composite_factory.Register<behaviour::SelectorNode>("SelectorNode");
    
    _action_factory.Register<behaviour::AlwaysTrueNode>("AlwaysTrueNode");
    _action_factory.Register<behaviour::AlwaysFalseNode>("AlwaysFalseNode");
    _action_factory.Register<behaviour::GoHomeNode>("GoHomeNode");
    _action_factory.Register<behaviour::LookAroundNode>("LookAroundNode");
    _action_factory.Register<behaviour::MoveToEnemyNode>("MoveToEnemyNode");
    _action_factory.Register<behaviour::MeleeAttackNode>("MeleeAttackNode");
    _action_factory.Register<behaviour::RangedAttackNode>("RangedAttackNode");
    _action_factory.Register<behaviour::ChangePatrolNode>("ChangePatrolNode");
    _action_factory.Register<behaviour::ChangeCombatNode>("ChangeCombatNode");

    _condition_factory.Register<behaviour::NotAwayFromHomeNode>("NotAwayFromHomeNode");
    _condition_factory.Register<behaviour::TargetRecognitionNode>("TargetRecognitionNode");
    _condition_factory.Register<behaviour::NotTargetRecognitionNode>("NotTargetRecognitionNode");
    
    _decorator_factory.Register<behaviour::TargetInMeleeAttackRangeNode>("TargetInMeleeAttackRangeNode");
    _decorator_factory.Register<behaviour::TargetInRangedAttackRangeNode>("TargetInRangedAttackRangeNode");
    _decorator_factory.Register<behaviour::RecognizingTargetNode>("RecognizingTargetNode");

    _decorator_factory.Register<behaviour::NotRecognizingTargetNode>("NotRecognizingTargetNode");
}

behaviour::CompositeNodePtr my::BehaviourFactory::CreateRootNode(const char* path) {
    rapidjson::Document document;
    if (!ut::ParseJsonDocument(path, document)) {
        return nullptr;
    } // if
    using namespace behaviour;
    _ASSERT_EXPR(document.HasMember("root"), L"ƒƒ“ƒo‚ð•ÛŽ‚µ‚Ä‚¢‚Ü‚¹‚ñ");
    _ASSERT_EXPR(document.HasMember("behaviours"), L"ƒƒ“ƒo‚ð•ÛŽ‚µ‚Ä‚¢‚Ü‚¹‚ñ");

    auto root_index = document["root"]["index"].GetInt();
    auto& behaviours = document["behaviours"];
    auto type = std::string(behaviours[root_index]["type"].GetString());

    return this->CreateCompositeNode(behaviours, root_index);
}

std::shared_ptr<behaviour::CompositeNode> my::BehaviourFactory::CreateCompositeNode(rapidjson::Value& behaviours, uint32_t index) {
    auto derived = behaviours[index]["derived"].GetString();
    auto composite_node = _composite_factory.Create(derived);

    auto& children = behaviours[index]["children"];
    for (size_t i = 0, n = children.Size(); i < n; i++) {
        auto children_index = children[i].GetInt();
        if (behaviours[children_index]["type"] == "CompositeNode") {
            auto node = this->CreateCompositeNode(behaviours, children_index);
            composite_node->AddChild(node);
        } // if
        else if (behaviours[children_index]["type"] == "ActionNode") {
            auto node = this->CreateActionNode(behaviours, children_index);
            composite_node->AddChild(node);
        } // else if
        else if (behaviours[children_index]["type"] == "ConditionalNode") {
            auto node = this->CreateConditionalNode(behaviours, children_index);
            composite_node->AddChild(node);
        } // if
        else if (behaviours[children_index]["type"] == "DecoratorNode") {
            auto node = this->CreateDecoratorNode(behaviours, children_index);
            composite_node->AddChild(node);
        } // else if
    } // for
    return composite_node;
}

std::shared_ptr<behaviour::ActionNodeBase> my::BehaviourFactory::CreateActionNode(rapidjson::Value& behaviours, uint32_t index) {
    auto derived = behaviours[index]["derived"].GetString();
    return _action_factory.Create(derived);
}

std::shared_ptr<behaviour::ConditionalNodeBase> my::BehaviourFactory::CreateConditionalNode(rapidjson::Value& behaviours, uint32_t index) {
    auto derived = behaviours[index]["derived"].GetString();
    return _condition_factory.Create(derived);
}

std::shared_ptr<behaviour::DecoratorNodeBase> my::BehaviourFactory::CreateDecoratorNode(rapidjson::Value& behaviours, uint32_t index) {
    auto derived = behaviours[index]["derived"].GetString();
    auto decorator_node = _decorator_factory.Create(derived);

    auto& child = behaviours[index]["child"];
    auto child_index = child.GetInt();
    if (behaviours[child_index]["type"] == "CompositeNode") {
        auto node = this->CreateCompositeNode(behaviours, child_index);
        decorator_node->SetChild(node);
    } // if
    else if (behaviours[child_index]["type"] == "ActionNode") {
        auto node = this->CreateActionNode(behaviours, child_index);
        decorator_node->SetChild(node);
    } // else if
    else if (behaviours[child_index]["type"] == "ConditionalNode") {
        auto node = this->CreateConditionalNode(behaviours, child_index);
        decorator_node->SetChild(node);
    } // if
    else if (behaviours[child_index]["type"] == "DecoratorNode") {
        auto node = this->CreateDecoratorNode(behaviours, child_index);
        decorator_node->SetChild(node);
    } // else if
    return decorator_node;
}