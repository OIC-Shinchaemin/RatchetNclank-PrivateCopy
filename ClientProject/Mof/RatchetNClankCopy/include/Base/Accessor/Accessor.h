/**
* @file Accessor.h
* @brief ゲッター
* @author nameless
* @date unknown
* @details none
*/
#ifndef BASE_ACCESSOR_ACCESSOR_H
#define BASE_ACCESSOR_ACCESSOR_H


#include <type_traits>
#include <memory>


namespace base::accessor {
template<typename T>
class Accessor {
private:
    //! データ
    T* _value;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="value"></param>
    Accessor(T& value) :
        _value(&value) {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    /// <param name="value"></param>
    ~Accessor() {
        _value = nullptr;
    }
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    Accessor& operator =(const T& value) {
        *this->_value = value;
        return *this;
    }
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    operator const T& (void) const {
        return *this->_value;
    }
    /// <summary>
    /// アクセス
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    T* operator->(void) const {
        return this->_value;
    }
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    bool operator == (const T& value) const {
        return *this->_value == value;
    }
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="obj"></param>
    /// <returns></returns>
    bool operator == (const Accessor<T>& obj) const {
        return *this->_value == *obj._value;
    }
    /// <summary>
    /// 加算
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    Accessor& operator += (T* value) {
        *this->_value += *value;
        return *this;
    }
    /// <summary>
    /// 加算
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    Accessor& operator += (const T& value) {
        *this->_value += value;
        return *this;
    }
};
template<typename T>
class Accessor<std::shared_ptr<T>> {
private:
    //! データ
    std::shared_ptr<T> _value;
public:
    Accessor(std::shared_ptr<T>& value) :
        _value(value) {
    }
    ~Accessor() {
        _value = nullptr;
    }
    Accessor& operator =(const T& value) {
        *this->_value = value;
        return *this;
    }
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    operator const std::shared_ptr<T>& (void) const {
        return this->_value;
    }
    /// <summary>
    /// アクセス
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<T> operator->(void) const {
        return this->_value;
    }
};
}
#endif // !BASE_ACCESSOR_ACCESSOR_H