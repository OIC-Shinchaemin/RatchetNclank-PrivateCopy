/*************************************************************************//*!
					
					@file	ShaderEffect_DepthOutput.h
					@brief	マルチレンダリングによる深度テクスチャ描画シェーダークラス。

															@author	CDW
															@date	2015.05.01
*//**************************************************************************/

//ONCE
#ifndef		__SHADEREFFECT_DEPTHOUTPUT__H__

#define		__SHADEREFFECT_DEPTHOUTPUT__H__

//INCLUDE
#include	"ShaderEffect_3DBase.h"

namespace Mof {
	
	/*******************************//*!
	@brief	マルチレンダリングによる深度テクスチャ描画シェーダークラス。

	@author	CDW
	*//********************************/
	class MOFLIBRARY_API CShaderEffect_DepthOutput : public CShaderEffect_3DBase {
	protected:
		/*******************//*!
		深度テクスチャ
		*//********************/
		LPTexture m_pDepthTex;
		/*******************//*!
		マルチレンダリングフラグ
		*//********************/
		MofBool m_MultiRender;
		/*******************//*!
		深度テクスチャ描画用深度バッファ
		*//********************/
		LPDepthTarget m_pDepthTarget;

		LPRenderTarget m_pOrigRenderTarget;	//<!退避
		LPDepthTarget m_pOrigDepthTarget;	//<!退避
	public:
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		CShaderEffect_DepthOutput();
		/*************************************************************************//*!
				@brief			デストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		virtual ~CShaderEffect_DepthOutput();
		
		/*************************************************************************//*!
				@brief			シェーダーエフェクトの作成。
				@param			None

				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool Create();
		/*************************************************************************//*!
				@brief			シェーダーエフェクトの作成。
				@param[in]		TexFormat		深度テクスチャのフォーマット
				@param[in]		DepthFormat		深度テクスチャ描画用の深度バッファフォーマット
				@param[in]		MultiRender		マルチレンダリングフラグ

				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool Create(PixelFormat TexFormat,PixelFormat DepthFormat,MofBool MultiRender);
		/*************************************************************************//*!
				@brief			解放
				@param[in]		pData			解放追加データ

				@return			TRUE			正常終了<br>
								それ以外		解放エラー、エラーコードを返す。
		*//**************************************************************************/
		virtual MofBool Release(LPMofVoid pData = NULL);
		
		/*************************************************************************//*!
				@brief			開始
				@param			None
				
				@return			TRUE			正常終了<br>
								それ以外		解放エラー、エラーコードを返す。
		*//**************************************************************************/
		virtual MofBool Begin();
		/*************************************************************************//*!
				@brief			終了
				@param			None
				
				@return			TRUE			正常終了<br>
								それ以外		解放エラー、エラーコードを返す。
		*//**************************************************************************/
		virtual MofBool End();

		//----------------------------------------------------------------------------
		////Set
		//----------------------------------------------------------------------------

		//----------------------------------------------------------------------------
		////Get
		//----------------------------------------------------------------------------
		/*************************************************************************//*!
				@brief			テクスチャの取得
				@param[in]		n			番号
					
				@return			テクスチャ
		*//**************************************************************************/
		virtual LPTexture GetTexture(MofU32 n);
		/*************************************************************************//*!
				@brief			深度テクスチャの取得
				@param			None
				
				@return			深度テクスチャ
		*//**************************************************************************/
		virtual LPTexture GetDepthTexture();

		//クラス基本定義
		MOF_LIBRARYCLASS(CShaderEffect_DepthOutput,MOF_SHADEREFFECTDEPTHOUTPUTCLASS_ID);
	};

	// 置き換え
	typedef CShaderEffect_DepthOutput*			LPShaderEffect_DepthOutput;

#include	"ShaderEffect_DepthOutput.inl"

}

#endif

//[EOF]