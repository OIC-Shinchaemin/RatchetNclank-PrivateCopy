<<<<<<< HEAD
<<<<<<< HEAD
#pragma once

#include		<memory>
#include		<list>

namespace Behaviour {
//ƒm[ƒhƒ|ƒCƒ“ƒ^’u‚«Š·‚¦
template < typename T > class INodeExecutor;
template < typename T > using NodeExecutorPtr = std::shared_ptr<INodeExecutor<T>>;
template < typename T > using NodeExecutorWeakPtr = std::weak_ptr<INodeExecutor<T>>;
template < typename T > using NodeExecutorList = std::list<NodeExecutorPtr<T>>;

/** ƒm[ƒhÀs—pƒNƒ‰ƒX */
template < typename T >
class INodeExecutor : public std::enable_shared_from_this<INodeExecutor<T>> {
public:
	/**
	 * @brief		ƒm[ƒh‚Ìó‘Ô
	 */
	enum class State {
		Inactive,           //–¢Às
		Running,            //Às’†
		Completed,          //ÀsI—¹
		Incompleted,		//Às¸”s
	};

	/**
	 * @brief		ƒm[ƒh‚ÌŒ‹‰Ê
	 */
	enum class Result {
		None,               //‚Ü‚¾Às‘O/Às’†
		Sucess,             //Às¬Œ÷
		Failure,            //Às¸”s
	};

	/**
	 * @brief		ƒm[ƒh‚ÌÀsˆ—
	 * @param[in]	actor		ÀsƒAƒNƒ^[
	 * @return		Succeeded	Às‚Ì¬Œ÷
	 *				Failed		Às‚Ì¸”s
	 */
	virtual Result Exec(T& actor) = 0;

	/**
	 * @brief		ƒm[ƒh‚ÌÀsó‘Ô‚ğ‘S‚ÄƒŠƒZƒbƒg‚µ‚Ä
	 *				ó‘Ô‚ğInactive‚Éİ’è‚·‚é
	 */
	virtual void Reset() = 0;

	/**
	 * @brief		e‚Ìİ’è
	 * @param[in]	ptr			eƒAƒNƒ^[
	 */
	virtual void SetParent(NodeExecutorWeakPtr<T>& ptr) = 0;
};
}
=======
=======
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
#ifndef BEHAVIOUR_INODE_EXECUTOR_H
#define BEHAVIOUR_INODE_EXECUTOR_H


#include <memory>
#include <list>

#include <Mof.h>


namespace behaviour {
// å‰æ–¹å®£è¨€
template<typename Actor> class INodeExecutor;
template<typename Actor> using NodeExecutorPtr = std::shared_ptr<INodeExecutor<Actor>>;
template<typename Actor> using NodeExecutorWeakPtr = std::weak_ptr<INodeExecutor<Actor>>;
template<typename Actor> using NodeExecutorList = std::list<NodeExecutorPtr<Actor>>;
template<typename Actor>
class INodeExecutor : public std::enable_shared_from_this<INodeExecutor<Actor>> {
public:
    enum class State {
        Inactive, //æœªå®Ÿè¡Œ
        Running, //å®Ÿè¡Œä¸­
        Completed, //å®Ÿè¡Œçµ‚äº†
        Incompleted, //å®Ÿè¡Œå¤±æ•—
    };
    enum class Result {
        None, //ã¾ã å®Ÿè¡Œå‰/å®Ÿè¡Œä¸­
        Sucess, //å®Ÿè¡ŒæˆåŠŸ
        Failure, //å®Ÿè¡Œå¤±æ•—
    };
    /// <summary>
    /// ã‚»ãƒƒã‚¿ãƒ¼
    /// </summary>
    /// <param name="ptr"></param>
    virtual void SetParent(NodeExecutorWeakPtr<Actor> ptr) = 0;
    /// <summary>
    /// ãƒãƒ¼ãƒ‰ã®å®Ÿè¡Œå‡¦ç†
    /// </summary>
    /// <param name="actor">å®Ÿè¡Œã‚¢ã‚¯ã‚¿ãƒ¼</param>
    /// <returns>Succeeded:å®Ÿè¡Œã®æˆåŠŸ</returns>
    /// <returns>Failed:å®Ÿè¡Œã®å¤±æ•—</returns>
    virtual INodeExecutor<Actor>::Result Execute(Actor& actor) = 0;
    /// <summary>
    /// å®Ÿè¡ŒçŠ¶æ…‹ã‚’å…¨ã¦ãƒªã‚»ãƒƒãƒˆ
    /// çŠ¶æ…‹ã‚’Inactiveã«è¨­å®š
    /// </summary>
    /// <param name=""></param>
    virtual void Reset(void) = 0;
    /// <summary>
    /// ƒfƒoƒbƒO
    /// </summary>
    /// <typeparam name="Actor"></typeparam>
    virtual void DebugRender(Mof::CVector2 position) = 0;
    virtual void DebugRender(void) = 0;
};
}
#endif // !BEHAVIOUR_INODE_EXECUTOR_H
<<<<<<< HEAD
>>>>>>> origin/Ex55_WeaponAction
=======
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
