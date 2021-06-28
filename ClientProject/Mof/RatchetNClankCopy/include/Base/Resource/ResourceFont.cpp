#include "ResourceFont.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <created>���̂���,2020/11/11</created>
	/// <changed>���̂���,2020/11/11</changed>
	// ********************************************************************************
	CResourceFont::CResourceFont(void)
		: CFont()
		, m_hResourceFontHandle(NULL)
	{
		m_FontInfo.lfHeight         = 24;
		m_FontInfo.lfWidth          = 24;
		m_FontInfo.lfEscapement     = 0;
		m_FontInfo.lfOrientation    = 0;
		m_FontInfo.lfWeight         = FW_REGULAR;
		m_FontInfo.lfItalic         = FALSE;
		m_FontInfo.lfUnderline      = FALSE;
		m_FontInfo.lfStrikeOut      = FALSE;
		m_FontInfo.lfCharSet        = DEFAULT_CHARSET;
		m_FontInfo.lfOutPrecision   = OUT_DEFAULT_PRECIS;
		m_FontInfo.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
		m_FontInfo.lfQuality        = PROOF_QUALITY;
		m_FontInfo.lfPitchAndFamily = DEFAULT_PITCH;
	}

	// ********************************************************************************
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	/// <created>���̂���,2020/11/11</created>
	/// <changed>���̂���,2020/11/11</changed>
	// ********************************************************************************
	CResourceFont::~CResourceFont(void)
	{
		DeleteHandle();
	}

	// ********************************************************************************
	/// <summary>
	/// �t�@�C���̓ǂݍ���
	/// </summary>
	/// <param name="pFile">�ǂݍ��ރt�@�C����\0�t�H���g��\0\0</param>
	/// <returns>true : ����, false : ���s</returns>
	/// <created>���̂���,2020/11/11</created>
	/// <changed>���̂���,2020/11/11</changed>
	// ********************************************************************************
	bool CResourceFont::Load(LPCMofChar pFileName)
	{
		// �t�@�C�����̃R�s�[
		char tok        = '\\';
		std::string tmp = pFileName;
		int first_len   = tmp.find_first_of(tok);
		m_FileName      = tmp.substr(0, first_len);
		std::string str = tmp.substr(first_len + 1);
		
		// �t�H���g�t�@�C�����g����悤�ɒǉ�����B
		AddFontResourceEx(TEXT(m_FileName.c_str()), FR_PRIVATE, NULL);
		
		// �t�H���g���𐶐����ɓo�^�B
		strcpy(m_FontInfo.lfFaceName, TEXT(str.c_str()));
		
		// �t�H���g�̐���
		if (m_hResourceFontHandle != NULL)
		{
			DeleteObject(m_hResourceFontHandle);
		}
		m_hResourceFontHandle = CreateFontIndirect(&m_FontInfo);
		return CFont::Create((MofFont)m_hResourceFontHandle);
	}

	// ********************************************************************************
	/// <summary>
	/// �T�C�Y�̐ݒ�
	/// </summary>
	/// <param name="s">�t�H���g�T�C�Y</param>
	/// <returns>true : ����, ����ȊO : ���s</returns>
	/// <created>���̂���,2020/11/11</created>
	/// <changed>���̂���,2020/11/11</changed>
	// ********************************************************************************
	MofBool CResourceFont::SetSize(MofS32 sx, MofS32 sy)
	{
		m_FontInfo.lfWidth  = sx;
		m_FontInfo.lfHeight = sy;
		// �t�H���g�̐���
		if (m_hResourceFontHandle != NULL)
		{
			DeleteObject(m_hResourceFontHandle);
		}
		m_hResourceFontHandle = CreateFontIndirect(&m_FontInfo);
		return CFont::Create((MofFont)m_hResourceFontHandle);
	}

	// ********************************************************************************
	/// <summary>
	/// �t�H���g�n���h���̌�n��
	/// </summary>
	/// <returns>true : ����, ����ȊO : ���s</returns>
	/// <created>���̂���,2020/11/11</created>
	/// <changed>���̂���,2020/11/11</changed>
	// ********************************************************************************
	MofBool CResourceFont::DeleteHandle(void)
	{
		if (m_hResourceFontHandle != NULL)
		{
			DeleteObject(m_hResourceFontHandle);
		}
		RemoveFontResourceEx(TEXT(m_FileName.c_str()), FR_PRIVATE, NULL);
		return TRUE;
	}
}
