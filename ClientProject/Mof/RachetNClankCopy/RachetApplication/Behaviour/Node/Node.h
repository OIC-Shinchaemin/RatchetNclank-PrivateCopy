<<<<<<< HEAD
<<<<<<< HEAD
#pragma once

#include		"../Executor/INodeExecutor.h"

namespace Behaviour {

	//ノードポインタ置き換えのための前方定義
template < typename T > class Node;
template < typename T > using NodePtr = std::shared_ptr<Node< T >>;
template < typename T > using NodeList = std::list<NodePtr< T >>;

template < typename T >
class Node : public std::enable_shared_from_this<Node<T>> {
protected:
	/** ノード名 */
	std::string _name;
public:
	Node(const std::string& name)
		: _name(name) {
	}
	virtual ~Node() = default;

	/**
	 * @brief		ノードの実行処理
	 * @param[in]	actor		実行アクター
	 * @return		true		実行の成功
	 *				false		実行の失敗
	 */
	virtual bool Exec(T& actor) { return false; }

	virtual NodeExecutorPtr< T > CreateExecutor() const = 0;
	const std::string& GetName() const noexcept { return _name; }
};
}
=======
=======
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
#ifndef BEHAVIOUR_NODE_H
#define BEHAVIOUR_NODE_H


#include "../Executor/INodeExecutor.h"


namespace behaviour {
// 蜑肴婿螳｣險�
template<typename Actor> class Node;
template<typename Actor> using NodePtr = std::shared_ptr<Node<Actor>>;
template<typename Actor> using NodeList = std::list<NodePtr<Actor>>;
template<typename Actor>
class Node : public std::enable_shared_from_this<Node<Actor>> {
protected:
    //! 蜷榊燕
    std::string _name;
public:
    /// <summary>
    /// 繧ｳ繝ｳ繧ｹ繝医Λ繧ｯ繧ｿ
    /// </summary>
    /// <param name="name"></param>
    Node(const std::string& name)
        : _name(name) {
    }
    /// <summary>
    /// 繝�繧ｹ繝医Λ繧ｯ繧ｿ
    /// </summary>
    virtual ~Node() = default;
    /// <summary>
    /// 繧ｲ繝�繧ｿ繝ｼ
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const std::string& GetName(void)const noexcept { return _name; }
    /// <summary>
    /// 繝弱�ｼ繝峨�ｮ螳溯｡�
    /// </summary>
    /// <param name="actor">螳溯｡後い繧ｯ繧ｿ繝ｼ</param>
    /// <returns>true:螳溯｡後�ｮ謌仙粥</returns>
    /// <returns>false:螳溯｡後�ｮ螟ｱ謨�</returns>
    virtual bool Execute(Actor& actor) { return false; }
    /// <summary>
    /// 菴懈��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual behaviour::NodeExecutorPtr<Actor> CreateExecutor(void) const = 0;
};
}
#endif // !BEHAVIOUR_NODE_H
<<<<<<< HEAD
>>>>>>> origin/Ex55_WeaponAction
=======
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
