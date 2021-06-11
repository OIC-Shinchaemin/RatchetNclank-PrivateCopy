#include "ResourceFont.h"

namespace sip
{
	// ********************************************************************************
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <created>いのうえ,2020/11/11</created>
	/// <changed>いのうえ,2020/11/11</changed>
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
	/// デストラクタ
	/// </summary>
	/// <created>いのうえ,2020/11/11</created>
	/// <changed>いのうえ,2020/11/11</changed>
	// ********************************************************************************
	CResourceFont::~CResourceFont(void)
	{
		DeleteHandle();
	}

	// ********************************************************************************
	/// <summary>
	/// ファイルの読み込み
	/// </summary>
	/// <param name="pFile">読み込むファイル名\0フォント名\0\0</param>
	/// <returns>true : 成功, false : 失敗</returns>
	/// <created>いのうえ,2020/11/11</created>
	/// <changed>いのうえ,2020/11/11</changed>
	// ********************************************************************************
	bool CResourceFont::Load(LPCMofChar pFileName)
	{
		// ファイル名のコピー
		char tok        = '\\';
		std::string tmp = pFileName;
		int first_len   = tmp.find_first_of(tok);
		m_FileName      = tmp.substr(0, first_len);
		std::string str = tmp.substr(first_len + 1);
		
		// フォントファイルを使えるように追加する。
		AddFontResourceEx(TEXT(m_FileName.c_str()), FR_PRIVATE, NULL);
		
		// フォント名を生成情報に登録。
		strcpy(m_FontInfo.lfFaceName, TEXT(str.c_str()));
		
		// フォントの生成
		if (m_hResourceFontHandle != NULL)
		{
			DeleteObject(m_hResourceFontHandle);
		}
		m_hResourceFontHandle = CreateFontIndirect(&m_FontInfo);
		return CFont::Create((MofFont)m_hResourceFontHandle);
	}

	// ********************************************************************************
	/// <summary>
	/// サイズの設定
	/// </summary>
	/// <param name="s">フォントサイズ</param>
	/// <returns>true : 成功, それ以外 : 失敗</returns>
	/// <created>いのうえ,2020/11/11</created>
	/// <changed>いのうえ,2020/11/11</changed>
	// ********************************************************************************
	MofBool CResourceFont::SetSize(MofS32 sx, MofS32 sy)
	{
		m_FontInfo.lfWidth  = sx;
		m_FontInfo.lfHeight = sy;
		// フォントの生成
		if (m_hResourceFontHandle != NULL)
		{
			DeleteObject(m_hResourceFontHandle);
		}
		m_hResourceFontHandle = CreateFontIndirect(&m_FontInfo);
		return CFont::Create((MofFont)m_hResourceFontHandle);
	}

	// ********************************************************************************
	/// <summary>
	/// フォントハンドルの後始末
	/// </summary>
	/// <returns>true : 成功, それ以外 : 失敗</returns>
	/// <created>いのうえ,2020/11/11</created>
	/// <changed>いのうえ,2020/11/11</changed>
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
