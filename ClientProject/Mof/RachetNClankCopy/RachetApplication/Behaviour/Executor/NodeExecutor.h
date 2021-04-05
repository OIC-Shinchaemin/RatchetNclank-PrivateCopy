<<<<<<< HEAD
<<<<<<< HEAD
#pragma once

#include		"INodeExecutor.h"
#include		"../Node/Node.h"

namespace Behaviour {
	/** �m�[�h���s�p�N���X */
template < typename T >
class NodeExecutor : public INodeExecutor< T > {
protected:
	/** ��� */
	State						_state;
	/** �Ή��m�[�h */
	NodePtr< T >				_node;
	/** �e�m�[�h */
	NodeExecutorWeakPtr< T >	_parent;
	/** �q�m�[�h */
	NodeExecutorList< T >		_children;
public:
	NodeExecutor(const NodePtr< T >& node)
		: _state(State::Inactive)
		, _node(node)
		, _parent()
		, _children() {
	}
	virtual ~NodeExecutor() = default;

	/**
	 * @brief		�m�[�h�̎��s����
	 * @param[in]	actor		���s�A�N�^�[
	 * @return		Succeeded	���s�̐���
	 *				Failed		���s�̎��s
	 */
	virtual Result Exec(T& actor) { return Result::Failure; }

	/**
	 * @brief		�m�[�h�̎��s��Ԃ�S�ă��Z�b�g����
	 *				��Ԃ�Inactive�ɐݒ肷��
	 */
	virtual void Reset() {
		_state = State::Inactive;
	}

	/**
	 * @brief		�e�̐ݒ�
	 * @param[in]	ptr			�e�A�N�^�[
	 */
	void SetParent(NodeExecutorWeakPtr< T >& ptr) override {
		_parent = ptr;
	}
};
}
=======
=======
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
#ifndef BEHAVIOUR_NODE_EXECUTOR_H
#define BEHAVIOUR_NODE_EXECUTOR_H


#include "INodeExecutor.h"

#include "../Node/Node.h"

#include <Mof.h>


namespace behaviour {
template<typename Actor>
class NodeExecutor : public INodeExecutor<Actor> {
    using super = INodeExecutor<Actor>;
protected:
    //! 状態
    super::State _state;
    //! 対応ノード
    NodePtr<Actor> _node;
    //! 親
    NodeExecutorWeakPtr<Actor> _parent;
    //! 子供
    NodeExecutorList<Actor> _children;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="node"></param>
    NodeExecutor(const NodePtr<Actor>& node) :
        super(),
        _state(super::State::Inactive),
        _node(node),
        _parent(),
        _children() {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~NodeExecutor() = default;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetParent(NodeExecutorWeakPtr<Actor> ptr) override {
        _parent = ptr;
    }
    /// <summary>
    /// ノードの実行処理
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>Succeeded:実行の成功</returns>
    /// <returns>Failed:実行の失敗</returns>
    virtual behaviour::INodeExecutor<Actor>::Result Execute(Actor& actor) override { return behaviour::INodeExecutor<Actor>::Result::Failure; }
    /// <summary>
    /// 実行状態を全てリセット
    /// 状態をInactiveに設定
    /// </summary>
    /// <param name=""></param>
    virtual void Reset(void) override {
        _state = super::State::Inactive;
    }
    /// <summary>
    /// �f�o�b�O
    /// </summary>
    /// <typeparam name="Actor"></typeparam>
    virtual void DebugRender(Mof::CVector2 position) override {
        MofU32 color;
        if (_state == super::State::Inactive) {
            color = MOF_COLOR_WHITE;
        } // else if
        if (_state == super::State::Running) {
            color = MOF_COLOR_RED;
        } // if
        if (_state == super::State::Completed) {
            color = MOF_COLOR_GREEN;
        } // else if
        if (_state == super::State::Incompleted) {
            color = MOF_COLOR_BLUE;
        } // else if


        ::CGraphicsUtilities::RenderString(position.x, position.y, color, _node->GetName().c_str());
        auto pos = position;
        pos.x += 100.0f;
        for (auto ptr : _children) {
            ptr->DebugRender(pos);
            pos.y += 20.0f;
        } // for
    }
    virtual void DebugRender(void) override {
        this->DebugRender(Mof::CVector2(100.0f, 100.0f));
    }
};
}
#endif // !BEHAVIOUR_NODE_EXECUTOR_H
<<<<<<< HEAD
>>>>>>> origin/Ex55_WeaponAction
=======
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
