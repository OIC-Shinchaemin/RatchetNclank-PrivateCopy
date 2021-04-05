<<<<<<< HEAD
#pragma once

#include		<memory>
#include		<list>

namespace Behaviour {
//ノードポインタ置き換え
template < typename T > class INodeExecutor;
template < typename T > using NodeExecutorPtr = std::shared_ptr<INodeExecutor<T>>;
template < typename T > using NodeExecutorWeakPtr = std::weak_ptr<INodeExecutor<T>>;
template < typename T > using NodeExecutorList = std::list<NodeExecutorPtr<T>>;

/** ノード実行用クラス */
template < typename T >
class INodeExecutor : public std::enable_shared_from_this<INodeExecutor<T>> {
public:
	/**
	 * @brief		ノードの状態
	 */
	enum class State {
		Inactive,           //未実行
		Running,            //実行中
		Completed,          //実行終了
		Incompleted,		//実行失敗
	};

	/**
	 * @brief		ノードの結果
	 */
	enum class Result {
		None,               //まだ実行前/実行中
		Sucess,             //実行成功
		Failure,            //実行失敗
	};

	/**
	 * @brief		ノードの実行処理
	 * @param[in]	actor		実行アクター
	 * @return		Succeeded	実行の成功
	 *				Failed		実行の失敗
	 */
	virtual Result Exec(T& actor) = 0;

	/**
	 * @brief		ノードの実行状態を全てリセットして
	 *				状態をInactiveに設定する
	 */
	virtual void Reset() = 0;

	/**
	 * @brief		親の設定
	 * @param[in]	ptr			親アクター
	 */
	virtual void SetParent(NodeExecutorWeakPtr<T>& ptr) = 0;
};
}
=======
#ifndef BEHAVIOUR_INODE_EXECUTOR_H
#define BEHAVIOUR_INODE_EXECUTOR_H


#include <memory>
#include <list>

#include <Mof.h>


namespace behaviour {
// 前方宣言
template<typename Actor> class INodeExecutor;
template<typename Actor> using NodeExecutorPtr = std::shared_ptr<INodeExecutor<Actor>>;
template<typename Actor> using NodeExecutorWeakPtr = std::weak_ptr<INodeExecutor<Actor>>;
template<typename Actor> using NodeExecutorList = std::list<NodeExecutorPtr<Actor>>;
template<typename Actor>
class INodeExecutor : public std::enable_shared_from_this<INodeExecutor<Actor>> {
public:
    enum class State {
        Inactive, //未実行
        Running, //実行中
        Completed, //実行終了
        Incompleted, //実行失敗
    };
    enum class Result {
        None, //まだ実行前/実行中
        Sucess, //実行成功
        Failure, //実行失敗
    };
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    virtual void SetParent(NodeExecutorWeakPtr<Actor> ptr) = 0;
    /// <summary>
    /// ノードの実行処理
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>Succeeded:実行の成功</returns>
    /// <returns>Failed:実行の失敗</returns>
    virtual INodeExecutor<Actor>::Result Execute(Actor& actor) = 0;
    /// <summary>
    /// 実行状態を全てリセット
    /// 状態をInactiveに設定
    /// </summary>
    /// <param name=""></param>
    virtual void Reset(void) = 0;
    /// <summary>
    /// デバッグ
    /// </summary>
    /// <typeparam name="Actor"></typeparam>
    virtual void DebugRender(Mof::CVector2 position) = 0;
    virtual void DebugRender(void) = 0;
};
}
#endif // !BEHAVIOUR_INODE_EXECUTOR_H
>>>>>>> origin/Ex55_WeaponAction
