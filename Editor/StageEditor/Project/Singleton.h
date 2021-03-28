#pragma once

#include	<iostream>
#include	<cassert>

// ********************************************************************************
/// <summary>
/// Singleton�p�e���v���[�g
/// </summary>
// ********************************************************************************
template< typename T >
class Singleton {
private:
    
    // �R�s�[�A���[�u�֎~
    Singleton(const Singleton& obj) = delete;
    Singleton(Singleton&& obj) = delete;

    //! �C���X�^���X
    static T* _instance;

protected:

    // ********************************************************************************
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <created>���̂���,2021/03/18</created>
    /// <changed>���̂���,2021/03/18</changed>
    // ********************************************************************************
    Singleton(void) {
        assert(!_instance);
        int offset = (int)(T*)1 - (int)(Singleton<T>*)(T*)1;
        _instance  = (T*)((int)this + offset);
    }

public:

    // ********************************************************************************
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    /// <created>���̂���,2021/03/18</created>
    /// <changed>���̂���,2021/03/18</changed>
    // ********************************************************************************
    virtual ~Singleton(void) {
        assert(_instance);
        _instance = nullptr;
    }

    // ********************************************************************************
    /// <summary>
    /// �C���X�^���X�̎擾
    /// </summary>
    /// <returns>�C���X�^���X</returns>
    /// <created>���̂���,2021/03/18</created>
    /// <changed>���̂���,2021/03/18</changed>
    // ********************************************************************************
    static T& GetInstance(void) {
        assert(_instance);
        return *_instance;
    }
};
template< typename T > T* Singleton<T>::_instance = nullptr;
