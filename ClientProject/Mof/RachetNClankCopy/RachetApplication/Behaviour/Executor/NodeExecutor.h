<<<<<<< HEAD
<<<<<<< HEAD
#pragma once

#include		"INodeExecutor.h"
#include		"../Node/Node.h"

namespace Behaviour {
	/** ノード実行用クラス */
template < typename T >
class NodeExecutor : public INodeExecutor< T > {
protected:
	/** 状態 */
	State						_state;
	/** 対応ノード */
	NodePtr< T >				_node;
	/** 親ノード */
	NodeExecutorWeakPtr< T >	_parent;
	/** 子ノード */
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
	 * @brief		ノードの実行処理
	 * @param[in]	actor		実行アクター
	 * @return		Succeeded	実行の成功
	 *				Failed		実行の失敗
	 */
	virtual Result Exec(T& actor) { return Result::Failure; }

	/**
	 * @brief		ノードの実行状態を全てリセットして
	 *				状態をInactiveに設定する
	 */
	virtual void Reset() {
		_state = State::Inactive;
	}

	/**
	 * @brief		親の設定
	 * @param[in]	ptr			親アクター
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
    //! 迥ｶ諷�
    super::State _state;
    //! 蟇ｾ蠢懊ヮ繝ｼ繝�
    NodePtr<Actor> _node;
    //! 隕ｪ
    NodeExecutorWeakPtr<Actor> _parent;
    //! 蟄蝉ｾ�
    NodeExecutorList<Actor> _children;
public:
    /// <summary>
    /// 繧ｳ繝ｳ繧ｹ繝医Λ繧ｯ繧ｿ
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
    /// 繝�繧ｹ繝医Λ繧ｯ繧ｿ
    /// </summary>
    virtual ~NodeExecutor() = default;
    /// <summary>
    /// 繧ｻ繝�繧ｿ繝ｼ
    /// </summary>
    /// <param name="ptr"></param>
    void SetParent(NodeExecutorWeakPtr<Actor> ptr) override {
        _parent = ptr;
    }
    /// <summary>
    /// 繝弱�ｼ繝峨�ｮ螳溯｡悟�ｦ逅�
    /// </summary>
    /// <param name="actor">螳溯｡後い繧ｯ繧ｿ繝ｼ</param>
    /// <returns>Succeeded:螳溯｡後�ｮ謌仙粥</returns>
    /// <returns>Failed:螳溯｡後�ｮ螟ｱ謨�</returns>
    virtual behaviour::INodeExecutor<Actor>::Result Execute(Actor& actor) override { return behaviour::INodeExecutor<Actor>::Result::Failure; }
    /// <summary>
    /// 螳溯｡檎憾諷九ｒ蜈ｨ縺ｦ繝ｪ繧ｻ繝�繝�
    /// 迥ｶ諷九ｒInactive縺ｫ險ｭ螳�
    /// </summary>
    /// <param name=""></param>
    virtual void Reset(void) override {
        _state = super::State::Inactive;
    }
    /// <summary>
    /// デバッグ
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
