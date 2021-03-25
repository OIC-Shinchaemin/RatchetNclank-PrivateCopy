/*************************************************************************//*!
					
					@file	ShaderBindBase.h
					@brief	シェーダーバインド基底インターフェイス。<br>
							各設定バッファや入力レイアウトを定義し各利用シェーダー毎にパイプラインに設定する。

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

//ONCE
#ifndef		__SHADERBINDBASE__H__

#define		__SHADERBINDBASE__H__

//INCLUDE
#include	"ShaderBind.h"

namespace Mof {
	
	/*******************************//*!
	@brief	シェーダーバインド基底インターフェイス

			シェーダーのためのバッファの設定を行うインターフェイス。

	@author	CDW
	*//********************************/
	MOF_ALIGNED16_CLASS CShaderBindBase : public IShaderBind {
	protected:
		/*******************//*!
		シェーダー
		*//********************/
		LPShader								m_pShader;
		/*******************//*!
		頂点レイアウト
		*//********************/
		LPBindLayout							m_pLayout;
		/*******************//*!
		設定バッファ
		*//********************/
		LPShaderBufferArray						m_pBufferArray;
		/*******************//*!
		設定リソース
		*//********************/
		LPShaderResourceArray					m_pResourceArray;
	public:
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		CShaderBindBase();
		/*************************************************************************//*!
				@brief			コピーコンストラクタ
				@param[in]		pObj		コピーシェーダー

				@return			None
		*//**************************************************************************/
		CShaderBindBase(const CShaderBindBase& pObj);
		/*************************************************************************//*!
				@brief			デストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		virtual ~CShaderBindBase();
		
		/*************************************************************************//*!
				@brief			バインドの実行
				@param[in]		pGeom		ジオメトリ
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool Bind(LPGeometry pGeom);
		/*************************************************************************//*!
				@brief			バインドの実行
				@param[in]		pGeom		ジオメトリ
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool BindLayout(LPGeometry pGeom);
		
		/*************************************************************************//*!
				@brief			バッファの追加
				@param[in]		pName		名前
				@param[in]		size		サイズ
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool CreateShaderBuffer(LPCMofChar pName, MofU32 size);
		/*************************************************************************//*!
				@brief			バッファの追加
				@param[in]		pBuf		バッファ
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool AddShaderBuffer(LPShaderBuffer pBuf);
		/*************************************************************************//*!
				@brief			リソースの追加
				@param[in]		pName		名前
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool CreateShaderResource(LPCMofChar pName);
		/*************************************************************************//*!
				@brief			リソースの追加
				@param[in]		pRes		リソース
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool AddShaderResource(LPShaderResource pRes);

		/*************************************************************************//*!
				@brief			解放
				@param[in]		pData			解放追加データ

				@return			TRUE			正常終了<br>
								それ以外		解放エラー、エラーコードを返す。
		*//**************************************************************************/
		virtual MofBool Release(LPMofVoid pData = NULL);


		//----------------------------------------------------------------------------
		////Get
		//----------------------------------------------------------------------------
		/*************************************************************************//*!
				@brief			設定パラメーターを取得する
				@param			None

				@return			パラメーター
		*//**************************************************************************/
		virtual LPShaderBufferArray GetShaderBuffer(void);
		/*************************************************************************//*!
				@brief			設定パラメーターを取得する
				@param[in]		n				番号

				@return			パラメーター
		*//**************************************************************************/
		virtual LPShaderBuffer GetShaderBuffer(MofU32 n);
		/*************************************************************************//*!
				@brief			設定パラメーターを取得する
				@param[in]		pName			名前

				@return			パラメーター
		*//**************************************************************************/
		virtual LPShaderBuffer GetShaderBufferByName(LPCMofChar pName);
		/*************************************************************************//*!
				@brief			設定リソースを取得する
				@param			None

				@return			リソース
		*//**************************************************************************/
		virtual LPShaderResourceArray GetShaderResource(void);
		/*************************************************************************//*!
				@brief			設定リソースを取得する
				@param[in]		n				番号

				@return			リソース
		*//**************************************************************************/
		virtual LPShaderResource GetShaderResource(MofU32 n);
		/*************************************************************************//*!
				@brief			設定リソースを取得する
				@param[in]		pName			名前

				@return			リソース
		*//**************************************************************************/
		virtual LPShaderResource GetShaderResourceByName(LPCMofChar pName);
	};
	
	#include	"ShaderBindBase.inl"
}

#endif

//[EOF]