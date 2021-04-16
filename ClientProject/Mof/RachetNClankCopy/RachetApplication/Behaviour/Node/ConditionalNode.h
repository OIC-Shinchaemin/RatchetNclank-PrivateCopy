#ifndef BEHAVIOUR_CONDITIONAL_NODE_H
#define BEHAVIOUR_CONDITIONAL_NODE_H

#include "Node.h"

#include "../Executor/ConditionalNodeExecutor.h"
#include "ParameterNode.h"


namespace behaviour {
class ConditionalNodeBase : public behaviour::Node {
    using super = behaviour::Node;
public:
    enum class Operator {
        Equal, // ==
        NotEqual, // !=
        Less, // <
        LessEqual, // <=
        Greater, // >
        GreaterEqual, // >=
    };
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ConditionalNodeBase() :
        super("Conditional") {
    }
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    ConditionalNodeBase(const std::string& name) :
        super(name) {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ConditionalNodeBase() = default;
    /// <summary>
    /// 作成
    /// </summary>
    /// <returns></returns>
    virtual behaviour ::NodeExecutorPtr CreateExecutor(void) const override {
        auto ptr = std::const_pointer_cast<super>(super::shared_from_this());
        return std::make_shared<behaviour::ConditionalNodeExecutor>(ptr);
    }
};
//template < typename T, typename V >
//class ConditionalNode : public behaviour::ConditionalNodeBase< T > {
//    using super = behaviour::ConditionalNodeBase< T >;
//protected:
//    /** 判定子 */
//    super::Operator						_operator;
//    /** 比較用パラメーター */
//    ParameterNodePtr< T, V >		_param1;
//    /** 比較用パラメーター */
//    ParameterNodePtr< T, V >		_param2;
//public:
//    /// <summary>
//    /// コンストラクタ
//    /// </summary>
//    /// <param name="op"></param>
//    /// <param name="p1"></param>
//    /// <param name="p2"></param>
//    ConditionalNode(super::Operator op, ParameterNodePtr< T, V > p1, ParameterNodePtr< T, V > p2) :
//        super(), 
//        _operator(op),
//        _param1(p1), 
//        _param2(p2) {
//    }
//    /// <summary>
//    /// デストラクタ
//    /// </summary>
//    virtual ~ConditionalNode() = default;
//    /// <summary>
//    /// ノードの実行処理
//    /// </summary>
//    /// <param name="actor">実行アクター</param>
//    /// <returns>Succeeded:実行の成功</returns>
//    /// <returns>Failed:実行の失敗</returns>
//    virtual bool Execute(T& actor) override {
//        switch (_operator) {
//            case super::Operator::Equal:			// ==
//                return _param1->GetValue(actor) == _param2->GetValue(actor);
//            case super::Operator::NotEqual:		// !=
//                return _param1->GetValue(actor) != _param2->GetValue(actor);
//            case super::Operator::Less:			// <
//                return _param1->GetValue(actor) < _param2->GetValue(actor);
//            case super::Operator::LessEqual:		// <=
//                return _param1->GetValue(actor) <= _param2->GetValue(actor);
//            case super::Operator::Greater:			// >
//                return _param1->GetValue(actor) > _param2->GetValue(actor);
//            case super::Operator::GreaterEqual:	// >=
//                return _param1->GetValue(actor) >= _param2->GetValue(actor);
//        } // switch
//        return false;
//    }
//};
}
#endif // !BEHAVIOUR_CONDITIONAL_NODE_H