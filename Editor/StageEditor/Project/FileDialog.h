#pragma once
#include "Mof.h"
// ********************************************************************************
/// <summary>
/// �t�@�C���_�C�A���O�֘A�̃N���X
/// </summary>
// ********************************************************************************
class FileDialog {
public:

    // ********************************************************************************
    /// <summary>
    /// �_�C�A���O�̃��[�h
    /// </summary>
    // ********************************************************************************
    enum class Mode {
        Open,
        Save,
    };

private:

    FileDialog(void) = delete;         //! �X�^�e�B�b�N�N���X�̏h��

    ~FileDialog(void) = delete;        //! �X�^�e�B�b�N�N���X�̏h��

public:

    // ********************************************************************************
    /// <summary>
    /// 
    /// </summary>
    /// <param name="hWnd">�n���h��</param>
    /// <param name="mode">�_�C�A���O�̃��[�h</param>
    /// <param name="Title">�_�C�A���O�̃^�C�g��</param>
    /// <param name="Filter">�J���t�@�C���̃t�B���^</param>
    /// <param name="DefExt">�J���t�@�C���̊g���q</param>
    /// <param name="path">�p�X�̏o�͐�</param>
    /// <param name="bOutArray">�����t�@�C�����I������Ă��邩�̃t���O�o�͐�</param>
    /// <returns></returns>
    /// <created>���̂���,2020/11/11</created>
    /// <changed>���̂���,2020/11/11</changed>
    // ********************************************************************************
    static bool Open(HWND hWnd, Mode mode, const char* Title, const char* Filter, const char* DefExt, char* path, bool& bOutArray);

    // ********************************************************************************
    /// <summary>
    /// �g���q�̎擾
    /// </summary>
    /// <param name="path">�g���q�̎�肽���t�@�C��</param>
    /// <returns>�g���q</returns>
    /// <created>���̂���,2020/11/11</created>
    /// <changed>���̂���,2020/11/11</changed>
    // ********************************************************************************
    static std::string GetExt(LPCMofChar path);

#if _MSVC_LANG >= 201703L //! C++17�ȍ~�̋@�\���g�p
    // ********************************************************************************
    /// <summary>
    /// 
    /// </summary>
    /// <param name="path"></param>
    /// <returns></returns>
    /// <created>���̂���,2021/03/18</created>
    /// <changed>���̂���,2021/03/18</changed>
    // ********************************************************************************
    static std::string GetFileName(LPCMofChar path);

    // ********************************************************************************
    /// <summary>
    /// �J�����g�f�B���N�g������̑��΃p�X�֕ϊ�
    /// </summary>
    /// <param name="path">�ϊ���������΃p�X</param>
    /// <param name="base">�w��ʒu�F��������̑��΃p�X�ɂȂ�</param>
    /// <returns>�x�[�X����p�X�܂ł̑��΃p�X</returns>
    /// <created>���̂���,2020/11/11</created>
    /// <changed>���̂���,2020/11/11</changed>
    // ********************************************************************************
    static std::string ChangeRelativePath(LPCMofChar path, LPCMofChar base = CUtilities::GetCurrentDirectory());

    // ********************************************************************************
    /// <summary>
    /// ���΃p�X�����΃p�X�ւ̕ϊ�
    /// </summary>
    /// <param name="path">�ϊ����������΃p�X</param>
    /// <returns>��΃p�X</returns>
    /// <created>���̂���,2020/11/11</created>
    /// <changed>���̂���,2020/11/11</changed>
    // ********************************************************************************
    static std::string ChangeFullPath(LPCMofChar path);
#endif

    // ********************************************************************************
    /// <summary>
    /// �ŏ���\0�ȍ~��\0��؂�̕�����z���\0\0�܂ŕ�������B
    /// </summary>
    /// <param name="pPath">������z��</param>
    /// <param name="outArray">������̕�������i�[����z��</param>
    /// <param name="outCurrentDirPath">�ŏ���\0�܂ł̕�����̊i�[�ꏊ</param>
    /// <created>���̂���,2020/11/11</created>
    /// <changed>���̂���,2020/11/11</changed>
    // ********************************************************************************
    static void SeparatePath(LPCMofChar pPath, std::vector<std::string>& outArray, std::string* outCurrentDirPath = nullptr);
};