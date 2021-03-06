/*************************************************************************//*!
					
					@file	Sprite2D.h
					@brief	2Dスプライトクラス。

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

//ONCE
#ifndef		__SPRITE2D__H__

#define		__SPRITE2D__H__

//INCLUDE
#include	"SpriteBase.h"

namespace Mof {
	
	/*******************************//*!
	@brief	2Dスプライトクラス

			2Dスプライトクラス。

	@author	CDW
	*//********************************/
	class MOFLIBRARY_API CSprite2D : public CSpriteBase {
		//----------------------------------------------------------------------------
		////前ライブラリとの対応のためにも一般パラメーターをpublic対応にしておく
		//----------------------------------------------------------------------------
	public:
	public:
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		CSprite2D();
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param[in]		pName		テクスチャファイル名

				@return			None
		*//**************************************************************************/
		CSprite2D(LPCMofChar pName);
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param[in]		pTex		テクスチャ

				@return			None
		*//**************************************************************************/
		CSprite2D(LPTexture pTex);
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param[in]		pName		スプライト名
				@param[in]		pTex		テクスチャ

				@return			None
		*//**************************************************************************/
		CSprite2D(LPCMofChar pName,LPTexture pTex);
		/*************************************************************************//*!
				@brief			コピーコンストラクタ
				@param[in]		pObj		コピーテクスチャ

				@return			None
		*//**************************************************************************/
		CSprite2D(const CSprite2D& pObj);
		/*************************************************************************//*!
				@brief			デストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		virtual ~CSprite2D();
		
		/*************************************************************************//*!
				@brief			テクスチャのコピー生成
				@param			None
				
				@return			作成されたコピーテクスチャ<br>
								作成に失敗した場合NULLを返す
		*//**************************************************************************/
		virtual ISprite* CreateCopyObject(void) const;

		/*************************************************************************//*!
				@brief			スプライトの更新
				@param			None

				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool Update(void);

		/*************************************************************************//*!
				@brief			スプライトの描画
				@param			None

				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool Render(void);
		
		//----------------------------------------------------------------------------
		////Get
		//----------------------------------------------------------------------------
		/*************************************************************************//*!
				@brief			幅取得
				@param			None

				@return			画像の幅
		*//**************************************************************************/
		virtual MofFloat GetWidth(void);
		/*************************************************************************//*!
				@brief			高さ取得
				@param			None

				@return			画像の高さ
		*//**************************************************************************/
		virtual MofFloat GetHeight(void);

		//クラス基本定義
		MOF_LIBRARYCLASS(CSprite2D,MOF_SPRITE2DCLASS_ID);
	};

	#include	"Sprite2D.inl"

	//ポインタ置き換え
	typedef CSprite2D*			LPSprite2D;
	typedef CDynamicArray< LPSprite2D >		CSprite2DArray,*LPSprite2DArray;
}

#endif

//[EOF]