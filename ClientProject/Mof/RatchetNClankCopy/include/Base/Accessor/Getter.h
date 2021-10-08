/**
* @file Getter.h
* @brief ゲッター
* @author nameless
* @date unknown
* @details none
*/
#ifndef BASE_ACCESSOR_GETTER_H
#define BASE_ACCESSOR_GETTER_H


#include <memory>
#include <string>
#include <string_view>


namespace base::accessor {
template<typename T>
class Getter {
private:
    //! データ
    T* _value;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="value"></param>
    Getter(T& value) :
        _value(&value) {
    }
    ~Getter() {
        _value = nullptr;
    }
    Getter& operator =(const T& value) = delete;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    operator const T& (void) const {
        return *this->_value;
    }
    T* operator->(void) const {
        return this->_value;
    }
    bool operator == (const T& value) const {
        return *this->_value == value;
    }
    bool operator == (const Getter<T>& obj) const {
        return *this->_value == *obj._value;
    }
    Getter& operator += (T* value) {
        *this->_value += *value;
        return *this;
    }
    Getter& operator += (const T& value) {
        *this->_value += value;
        return *this;
    }
};
template<typename T>
class Getter<std::shared_ptr<T>> {
private:
    std::shared_ptr<T> _value;
public:
    Getter(std::shared_ptr<T>& value) :
        _value(value) {
    }
    ~Getter() {
        _value = nullptr;
    }
    Getter& operator =(const std::shared_ptr<T>& value) = delete;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    operator const std::shared_ptr<T>& (void) const {
        return this->_value;
    }
    std::shared_ptr<T> operator->(void) const {
        return this->_value;
    }
};
}
#endif // !BASE_ACCESSOR_GETTER_H