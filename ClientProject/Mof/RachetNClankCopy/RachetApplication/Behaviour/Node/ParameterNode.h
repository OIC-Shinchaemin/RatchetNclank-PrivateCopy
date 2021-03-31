#ifndef BEHAVIOUR_PARAMETER_NODE_H
#define BEHAVIOUR_PARAMETER_NODE_H


#include "Node.h"


namespace behaviour {
template<typename Actor, typename Value>
class IParameterNode {
public:
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name="actor"></param>
    /// <returns></returns>
    virtual const Value GetValue(Actor& actor) const = 0;
};
template< typename Actor, typename Value> using ParameterNodePtr = std::shared_ptr<IParameterNode<Actor, Value>>;

template < typename Actor, typename Value >
class ValueNode : public behaviour::IParameterNode<Actor, Value> {
private:
    Value _value;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="v"></param>
    ValueNode(const Value& v) :
        _value(v) {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~ValueNode() = default;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name="actor"></param>
    /// <returns></returns>
    const Value GetValue(Actor& actor) const override {
        return _value;
    }
};
template < typename Actor, typename Value >
class GetNode : public behaviour::IParameterNode<Actor, Value> {
    //! �Q�b�^�[
    using OnGetFunction = std::function<Value(Actor&)>;
private:
    //! �Q�b�g
    OnGetFunction OnGet;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="get"></param>
    GetNode(OnGetFunction get) : 
        OnGet(get) {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~GetNode() = default;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name="actor"></param>
    /// <returns></returns>
    const Value GetValue(Actor& actor) const override {
        return OnGet(actor);
    }
};
}
#endif // !BEHAVIOUR_PARAMETER_NODE_H