/*************************************************************************//*!
					
					@file	DX11ShaderPass.h
					@brief	DirectX11シェーダーパスクラス。

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

//ONCE
#ifndef		__DX11SHADERPASS__H__

#define		__DX11SHADERPASS__H__

//INCLUDE
#include	"../ShaderPassBase.h"

namespace Mof {
	
	/*******************************//*!
	@brief	DirectX11シェーダーパスクラス

			DirectX11でのシェーダーのパス設定を行うためのクラス。

	@author	CDW
	*//********************************/
	class MOFLIBRARY_API CDX11ShaderPass : public CShaderPassBase {
	protected:
		/*******************//*!
		シェーダーテクニック
		*//********************/
		ID3DX11EffectPass*			m_pPass;
	public:
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		CDX11ShaderPass();
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param[in]		pPass		パス

				@return			None
		*//**************************************************************************/
		CDX11ShaderPass(ID3DX11EffectPass* pPass);
		/*************************************************************************//*!
				@brief			コピーコンストラクタ
				@param[in]		pObj		コピーシェーダー

				@return			None
		*//**************************************************************************/
		CDX11ShaderPass(const CDX11ShaderPass& pObj);
		/*************************************************************************//*!
				@brief			デストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		virtual ~CDX11ShaderPass();
		
		/*************************************************************************//*!
				@brief			シェーダーパスの開始
				@param[in]		Flag		適用フラグ
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool Begin(MofU32 Flag);
		/*************************************************************************//*!
				@brief			シェーダーパスの終了
				@param			None
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool End(void);

		/*************************************************************************//*!
				@brief			解放
				@param[in]		pData			解放追加データ

				@return			TRUE			正常終了<br>
								それ以外		解放エラー、エラーコードを返す。
		*//**************************************************************************/
		virtual MofBool Release(LPMofVoid pData = NULL);

		//クラス基本定義
		MOF_LIBRARYCLASS(CDX11ShaderPass,MOF_DX11SHADERPASSCLASS_ID);
	};

#include	"DX11ShaderPass.h"

}

#endif

//[EOF]