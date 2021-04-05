<<<<<<< HEAD
#pragma once

#include "NodeExecutor.h"

namespace Behaviour {

    /** �m�[�h���s�p�N���X */
template < typename T >
class ActionNodeExecutor : public NodeExecutor< T > {
public:
    ActionNodeExecutor(const NodePtr< T >& node)
        : NodeExecutor< T >(node) {
    }
    virtual ~ActionNodeExecutor() = default;

    /**
     * @brief		�m�[�h�̎��s����
     * @param[in]	actor		���s�A�N�^�[
     * @return		Succeeded	���s�̐���
     *				Failed		���s�̎��s
     */
    virtual Result Exec(T& actor) {
        //���s�ς�
        if (_state == State::Completed) {
            return Result::Sucess;
        }
        else if (_state == State::Incompleted) {
            return Result::Failure;
        }
        //���s�J�n
        _state = State::Running;
        if (_node->Exec(actor)) {
            _state = State::Completed;
            return Result::Sucess;
        }
        return Result::None;
    }
};
}
=======
#ifndef BEHAVIOUR_ACTION_NODE_EXECUTOR_H
#define BEHAVIOUR_ACTION_NODE_EXECUTOR_H


#include "NodeExecutor.h"


namespace behaviour {
template<typename Actor>
class ActionNodeExecutor : public behaviour::NodeExecutor<Actor> {
    using super = behaviour::NodeExecutor<Actor>;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="node"></param>
    ActionNodeExecutor(const NodePtr<Actor>& node) :
        super(node) {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ActionNodeExecutor() = default;
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual INodeExecutor<Actor>::Result Execute(Actor& actor) override {
        //実行済み
        if (super::_state == super::State::Completed) {
            return super::Result::Sucess;
        } // if
        else if (super::_state == super::State::Incompleted) {
            return super::Result::Failure;
        } // else if
        //実行開始
        super::_state = super::State::Running;
        if (super::_node->Execute(actor)) {
            super::_state = super::State::Completed;
            return super::Result::Sucess;
        } // if        
        return super::Result::None;
    }
};
}
#endif // !BEHAVIOUR_ACTION_NODE_EXECUTOR_H
>>>>>>> origin/Ex55_WeaponAction
