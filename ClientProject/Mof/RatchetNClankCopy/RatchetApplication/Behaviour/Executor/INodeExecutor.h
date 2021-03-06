#ifndef RATCHET_BEHAVIOUR_INODE_EXECUTOR_H
#define RATCHET_BEHAVIOUR_INODE_EXECUTOR_H


#include <any>
#include <memory>
#include <list>

#include <Mof.h>


namespace ratchet { namespace behaviour {
// 前方宣言
class INodeExecutor;
using NodeExecutorPtr = std::shared_ptr<INodeExecutor>;
using NodeExecutorWeakPtr = std::weak_ptr<INodeExecutor>;
using NodeExecutorList = std::list<NodeExecutorPtr>;
class INodeExecutor : public std::enable_shared_from_this<ratchet::behaviour::INodeExecutor> {
public:
    enum class State {
        Inactive, // 未実行
        Running, // 実行中
        Completed, // 実行終了
        Incompleted, // 実行失敗
    };
    enum class Result {
        None, // 実行前/実行中
        Sucess, // 実行成功
        Failure, // 実行失敗
    };
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    virtual void SetParent(ratchet::behaviour::NodeExecutorWeakPtr ptr) = 0;
    /// <summary>
    /// 実行時必要なポインタをキャッシュ
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) = 0;
    /// <summary>
    /// ノードの実行処理
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>Succeeded:実行の成功</returns>
    /// <returns>Failed:実行の失敗</returns>
    virtual INodeExecutor::Result Execute(void) = 0;
    /// <summary>
    /// 実行状態を全てリセット
    /// 状態をInactiveに設定
    /// </summary>
    /// <param name=""></param>
    virtual void Reset(void) = 0;
#ifdef _DEBUG
    /// <summary>
    /// デバッグ
    /// </summary>
    /// <typeparam name="Actor"></typeparam>
    virtual void DebugRender(Mof::CVector2 position) = 0;
    virtual void DebugRender(void) = 0;
#endif // _DEBUG
};
}
}
#endif // !RATCHET_BEHAVIOUR_INODE_EXECUTOR_H