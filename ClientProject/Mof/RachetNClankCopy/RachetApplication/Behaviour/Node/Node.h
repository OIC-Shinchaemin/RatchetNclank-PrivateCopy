<<<<<<< HEAD
<<<<<<< HEAD
#pragma once

#include		"../Executor/INodeExecutor.h"

namespace Behaviour {

	//ƒm[ƒhƒ|ƒCƒ“ƒ^’u‚«Š·‚¦‚Ì‚½‚ß‚Ì‘O•û’è‹`
template < typename T > class Node;
template < typename T > using NodePtr = std::shared_ptr<Node< T >>;
template < typename T > using NodeList = std::list<NodePtr< T >>;

template < typename T >
class Node : public std::enable_shared_from_this<Node<T>> {
protected:
	/** ƒm[ƒh–¼ */
	std::string _name;
public:
	Node(const std::string& name)
		: _name(name) {
	}
	virtual ~Node() = default;

	/**
	 * @brief		ƒm[ƒh‚ÌÀsˆ—
	 * @param[in]	actor		ÀsƒAƒNƒ^[
	 * @return		true		Às‚Ì¬Œ÷
	 *				false		Às‚Ì¸”s
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
// å‰æ–¹å®£è¨€
template<typename Actor> class Node;
template<typename Actor> using NodePtr = std::shared_ptr<Node<Actor>>;
template<typename Actor> using NodeList = std::list<NodePtr<Actor>>;
template<typename Actor>
class Node : public std::enable_shared_from_this<Node<Actor>> {
protected:
    //! åå‰
    std::string _name;
public:
    /// <summary>
    /// ã‚³ãƒ³ã‚¹ãƒˆãƒ©ã‚¯ã‚¿
    /// </summary>
    /// <param name="name"></param>
    Node(const std::string& name)
        : _name(name) {
    }
    /// <summary>
    /// ãƒ‡ã‚¹ãƒˆãƒ©ã‚¯ã‚¿
    /// </summary>
    virtual ~Node() = default;
    /// <summary>
    /// ã‚²ãƒƒã‚¿ãƒ¼
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const std::string& GetName(void)const noexcept { return _name; }
    /// <summary>
    /// ãƒãƒ¼ãƒ‰ã®å®Ÿè¡Œ
    /// </summary>
    /// <param name="actor">å®Ÿè¡Œã‚¢ã‚¯ã‚¿ãƒ¼</param>
    /// <returns>true:å®Ÿè¡Œã®æˆåŠŸ</returns>
    /// <returns>false:å®Ÿè¡Œã®å¤±æ•—</returns>
    virtual bool Execute(Actor& actor) { return false; }
    /// <summary>
    /// ä½œæˆ
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
