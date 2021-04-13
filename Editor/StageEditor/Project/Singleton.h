#pragma once

#include	<iostream>
#include	<cassert>

// ********************************************************************************
/// <summary>
/// Singleton用テンプレート
/// </summary>
// ********************************************************************************
template< typename T >
class Singleton {
private:
    
    // コピー、ムーブ禁止
    Singleton(const Singleton& obj) = delete;
    Singleton(Singleton&& obj) = delete;

    //! インスタンス
    static T* _instance;

protected:

    // ********************************************************************************
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <created>いのうえ,2021/03/18</created>
    /// <changed>いのうえ,2021/03/18</changed>
    // ********************************************************************************
    Singleton(void) {
        assert(!_instance);
        int offset = (int)(T*)1 - (int)(Singleton<T>*)(T*)1;
        _instance  = (T*)((int)this + offset);
    }

public:

    // ********************************************************************************
    /// <summary>
    /// デストラクタ
    /// </summary>
    /// <created>いのうえ,2021/03/18</created>
    /// <changed>いのうえ,2021/03/18</changed>
    // ********************************************************************************
    virtual ~Singleton(void) {
        assert(_instance);
        _instance = nullptr;
    }

    // ********************************************************************************
    /// <summary>
    /// インスタンスの取得
    /// </summary>
    /// <returns>インスタンス</returns>
    /// <created>いのうえ,2021/03/18</created>
    /// <changed>いのうえ,2021/03/18</changed>
    // ********************************************************************************
    static T& GetInstance(void) {
        assert(_instance);
        return *_instance;
    }
};
template< typename T > T* Singleton<T>::_instance = nullptr;
