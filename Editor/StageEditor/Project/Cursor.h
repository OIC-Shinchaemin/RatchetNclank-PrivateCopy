#pragma once
#include <wuapi.h>
#include <vector>

// ********************************************************************************
/// <summary>
/// �J�[�\���̎��
/// </summary>
// ********************************************************************************
enum CursorType
{
	ARROW,            //! ���
	IBEAM,            //! �������͂̃A��
	WAIT,             //! �����O���O�����Ă���
	CROSS,            //! �\��
	UPARROW,          //! �A�Q�A�Q
	SIZENWSE,         //! �E�㍶��
	SIZENESW,         //! ����E��
	SIZEWE,           //! ���E
	SIZENS,           //! �㉺
	SIZEALL,          //! �㉺���E
	NO,               //! �֎~�}�[�N
	HAND,             //! �w�������
	APPSTARTING,      //! ���{���邮��
	HELP,             //! ���{�H
	PIN,              //! ���{�}�b�v���W�Ɏh����A��
	PERSON,           //! ���{�l

	DEFAULT = ARROW,  //! �f�t�H���g(���)
};

// ********************************************************************************
/// <summary>
/// �J�[�\���ύX�p�X�^�e�B�b�N�N���X
/// </summary>
// ********************************************************************************
class Cursor {
private:
	//�X�^�e�B�b�N�N���X�Ȃ̂ŏ�����Ă���ˁB
	Cursor(void) = delete;
	~Cursor(void) = delete;

protected:
	// ********************************************************************************
	/// <summary>
	/// �J�[�\���n���h�������̎擾�B
	/// </summary>
	/// <returns>�J�[�\���n���h���z��</returns>
	/// <created>���̂���,2020/11/23</created>
	/// <changed>���̂���,2020/11/23</changed>
	// ********************************************************************************
	static const std::vector<HCURSOR>& GetHandleArray(void) {
		static const std::vector<HCURSOR> map =
		{
			LoadCursor(NULL, IDC_ARROW),
			LoadCursor(NULL, IDC_IBEAM),
			LoadCursor(NULL, IDC_WAIT),
			LoadCursor(NULL, IDC_CROSS),
			LoadCursor(NULL, IDC_UPARROW),
			LoadCursor(NULL, IDC_SIZENWSE),
			LoadCursor(NULL, IDC_SIZENESW),
			LoadCursor(NULL, IDC_SIZEWE),
			LoadCursor(NULL, IDC_SIZENS),
			LoadCursor(NULL, IDC_SIZEALL),
			LoadCursor(NULL, IDC_NO),
			LoadCursor(NULL, IDC_HAND),
			LoadCursor(NULL, IDC_APPSTARTING),
			LoadCursor(NULL, IDC_HELP),
			LoadCursor(NULL, IDC_PIN),
			LoadCursor(NULL, IDC_PERSON),
		};

		return map;
	}

public:
	// ********************************************************************************
	/// <summary>
	/// �J�[�\���̕ύX
	/// </summary>
	/// <param name="type">�ύX����^�C�v</param>
	/// <created>���̂���,2020/11/23</created>
	/// <changed>���̂���,2020/11/23</changed>
	// ********************************************************************************
	static void ChangeCursor(const CursorType& type) {
		SetCursor(GetHandleArray()[type]);
	}
};