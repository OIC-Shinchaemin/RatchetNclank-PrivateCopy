/*************************************************************************//*!
					
					@file	WindowBase.h
					@brief	ウインドウズ用のウインドウの処理を行う基底クラス。<br>
							ウインドウズ用のウインドウやダイアログはすべてこのクラスを継承する。

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

//ONCE
#ifndef		__WINDOWBASE__H__

#define		__WINDOWBASE__H__

//INCLUDE
#include	"../Window.h"

namespace Mof {

	/*******************************//*!
	@brief	ウインドウズ用ウインドウ基底クラス

			ウインドウズ用のウインドウの処理を行う基底クラス。

	@author	CDW
	*//********************************/
	class MOFLIBRARY_API CWindowBase : public IWindow {
	protected:
		/*******************//*!
		インスタンスハンドル
		*//********************/
		MofInstanceHandle	m_hInstance;
		/*******************//*!
		ウインドウハンドル
		*//********************/
		MofWindowHandle		m_hWnd;
		/*******************//*!
		ウインドウハンドル
		*//********************/
		MofWindowHandle		m_hParentWnd;
		/*******************//*!
		ウインドウタイトル
		*//********************/
		CString				m_Title;
		/*******************//*!
		幅
		*//********************/
		MofS32				m_Width;
		/*******************//*!
		高さ
		*//********************/
		MofS32				m_Height;
		/*******************//*!
		スタイル
		*//********************/
		MofU32				m_Style;
		/*******************//*!
		プロシージャ
		*//********************/
		IWindowProc*		m_pProc;
	public:
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		CWindowBase();
		/*************************************************************************//*!
				@brief			デストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		virtual ~CWindowBase();
		/*************************************************************************//*!
				@brief			解放
				@param[in]		pData			解放追加データ

				@return			TRUE			正常終了<br>
								それ以外		解放エラー、エラーコードを返す。
		*//**************************************************************************/
		virtual MofBool Release(LPMofVoid pData = NULL);
		/*************************************************************************//*!
				@brief			コールされるプロシージャ
				@param[in]		hWnd		ウインドウハンドル
				@param[in]		msg			メッセージ
				@param[in]		wpar		パラメーター１
				@param[in]		lpar		パラメーター２
				
				@return			プロシージャの結果をそのまま返す。<br>
								プロシージャの指定を行った場合、プロシージャの関数を、それ以外はDefWindowProc関数を参照。
		*//**************************************************************************/
		static MofProcResult CALLBACK WindowProc(MofWindowHandle hWnd,MofUInt msg,MofProcParamW wpar,MofProcParamL lpar);
		
		//----------------------------------------------------------------------------
		////Set
		//----------------------------------------------------------------------------
		/*************************************************************************//*!
				@brief			名前設定
				@param[in]		pName			設定する名前
				
				@return			TRUE			正常終了<br>
								それ以外		設定エラー、エラーコードを返す。
		*//**************************************************************************/
		virtual MofBool SetName(LPCMofChar pName);

		//----------------------------------------------------------------------------
		////Get
		//----------------------------------------------------------------------------
		/*************************************************************************//*!
				@brief			インスタンスハンドル取得
				@param			None

				@return			インスタンスハンドル
		*//**************************************************************************/
		virtual MofInstanceHandle GetInstanceHandle(void);
		/*************************************************************************//*!
				@brief			ウインドウハンドル取得
				@param			None

				@return			ウインドウハンドル
		*//**************************************************************************/
		virtual MofWindowHandle GetWindowHandle(void);
		/*************************************************************************//*!
				@brief			名前取得
				@param			None

				@return			名前の取得
		*//**************************************************************************/
		virtual LPString GetName(void);
		/*************************************************************************//*!
				@brief			ウインドウタイトル取得
				@param			None

				@return			ウインドウタイトル
		*//**************************************************************************/
		virtual LPString GetTitle(void);
		/*************************************************************************//*!
				@brief			ウインドウ幅取得
				@param			None

				@return			ウインドウ幅
		*//**************************************************************************/
		virtual MofS32 GetWidth(void) const;
		/*************************************************************************//*!
				@brief			ウインドウ高さ取得
				@param			None

				@return			ウインドウ高さ
		*//**************************************************************************/
		virtual MofS32 GetHeight(void) const;
				
	private:
		//コピーを禁止する
		CWindowBase(const CWindowBase& pObj){};
	};
	
	#include	"WindowBase.inl"
}

#endif

//[EOF]