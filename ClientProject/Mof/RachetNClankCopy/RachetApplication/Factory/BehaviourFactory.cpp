#include "BehaviourFactory.h"

#include "../Behaviour/Node/Action/AlwaysTrueNode.h"
#include "../Behaviour/Node/Action/AlwaysFalseNode.h"
#include "../Behaviour/Node/Action/GoHomeNode.h"
#include "../Behaviour/Node/Action/LookAroundNode.h"
#include "../Behaviour/Node/Action/MoveToEnemyNode.h"
#include "../Behaviour/Node/Action/MeleeAttackNode.h"
#include "../Behaviour/Node/Action/RangedAttackNode.h"
#include "../Behaviour/Node/Action/ChangePatrolNode.h"
#include "../Behaviour/Node/Condition/NotAwayFromHomeNode.h"
#include "../Behaviour/Node/Condition/TargetRecognitionNode.h"


my::BehaviourFactory::BehaviourFactory() :
    _action_factory(),
    _condition_factory() {
    _action_factory.Register<behaviour::AlwaysTrueNode>("AlwaysTrueNode");
    _action_factory.Register<behaviour::AlwaysFalseNode>("AlwaysFalseNode");
    _action_factory.Register<behaviour::GoHomeNode>("GoHomeNode");
    _action_factory.Register<behaviour::LookAroundNode>("LookAroundNode");
    _action_factory.Register<behaviour::MoveToEnemyNode>("MoveToEnemyNode");
    _action_factory.Register<behaviour::MeleeAttackNode>("MeleeAttackNode");
    _action_factory.Register<behaviour::RangedAttackNode>("RangedAttackNode");
    _action_factory.Register<behaviour::ChangePatrolNode>("ChangePatrolNode");
    _condition_factory.Register<behaviour::NotAwayFromHomeNode>("NotAwayFromHomeNode");
    _condition_factory.Register<behaviour::TargetRecognitionNode>("TargetRecognitionNode");
}

behaviour::CompositeNodePtr my::BehaviourFactory::CreateRootNode(const char* path) {
    rapidjson::Document document;
    if (!ut::ParseJsonDocument(path, document)) {
        return nullptr;
    } // if
    using namespace behaviour;
    behaviour::CompositeNodePtr rootnode;
    _ASSERT_EXPR(document.HasMember("root"), L"ƒƒ“ƒo‚ð•ÛŽ‚µ‚Ä‚¢‚Ü‚¹‚ñ");
    _ASSERT_EXPR(document.HasMember("behaviours"), L"ƒƒ“ƒo‚ð•ÛŽ‚µ‚Ä‚¢‚Ü‚¹‚ñ");

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

behaviour::ConditionalNodeBase::Operator my::BehaviourFactory::GetConditionalOperator(std::string type) {
    using Operator = behaviour::ConditionalNodeBase::Operator;
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

std::shared_ptr<behaviour::ActionNodeBase> my::BehaviourFactory::CreateActionNode(rapidjson::Value& behaviours, uint32_t index) {
    using namespace behaviour;
    auto derived = behaviours[index]["derived"].GetString();
    return _action_factory.Create(derived);
}

std::shared_ptr<behaviour::ConditionalNodeBase> my::BehaviourFactory::CreateConditionalNode(rapidjson::Value& behaviours, uint32_t index) {
    using namespace behaviour;
    auto derived = behaviours[index]["derived"].GetString();
    return _condition_factory.Create(derived);
}

std::shared_ptr<behaviour::SequencerNode> my::BehaviourFactory::CreateSequencerNode(rapidjson::Value& behaviours, uint32_t index) {
    using namespace behaviour;

    auto sequencer_node = std::make_shared<SequencerNode>();
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
        else if (behaviours[children_index]["type"] == "DecoratorNode") {
        
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

std::shared_ptr<behaviour::SelectorNode> my::BehaviourFactory::CreateSelectorNode(rapidjson::Value& behaviours, uint32_t index) {
    using namespace behaviour;

    auto selector_node = std::make_shared<SelectorNode>();
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
        else if (behaviours[children_index]["type"] == "DecoratorNode") {

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
