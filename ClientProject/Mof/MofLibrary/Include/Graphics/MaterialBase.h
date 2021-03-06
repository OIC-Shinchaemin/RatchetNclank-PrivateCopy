/*************************************************************************//*!
					
					@file	MaterialBase.h
					@brief	マテリアル基底クラス。

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

//ONCE
#ifndef		__MATERIALBASE__H__

#define		__MATERIALBASE__H__

//INCLUDE
#include	"Material.h"

namespace Mof {
	
	/*******************************//*!
	@brief	マテリアルクラス

			マテリアルの読み込み、設定を行うためのクラス。<br>
			設定値MaterialParameterとインターフェイスIMaterialを多重継承する。

	@author	CDW
	*//********************************/
	class MOFLIBRARY_API CMaterialBase : public IMaterial , public MaterialParameter {
	protected:
	public:
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		CMaterialBase();
		/*************************************************************************//*!
				@brief			コピーコンストラクタ
				@param[in]		pObj		コピーマテリアル

				@return			None
		*//**************************************************************************/
		CMaterialBase(const CMaterialBase& pObj);
		/*************************************************************************//*!
				@brief			デストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		virtual ~CMaterialBase();

		/*************************************************************************//*!
				@brief			解放
				@param[in]		pData			解放追加データ

				@return			TRUE			正常終了<br>
								それ以外		解放エラー、エラーコードを返す。
		*//**************************************************************************/
		virtual MofBool Release(LPMofVoid pData = NULL);
		
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
		/*************************************************************************//*!
				@brief			ディフューズ色設定
				@param[in]		c			色
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetDiffuse(const Vector4& c);
		/*************************************************************************//*!
				@brief			ディフューズ色設定
				@param[in]		c			色
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetDiffuse(const MofU32 c);
		/*************************************************************************//*!
				@brief			アンビエント色設定
				@param[in]		c			色
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetAmbient(const Vector4& c);
		/*************************************************************************//*!
				@brief			アンビエント色設定
				@param[in]		c			色
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetAmbient(const MofU32 c);
		/*************************************************************************//*!
				@brief			スペキュラ色設定
				@param[in]		c			色
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetSpeculer(const Vector4& c);
		/*************************************************************************//*!
				@brief			スペキュラ色設定
				@param[in]		c			色
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetSpeculer(const MofU32 c);
		/*************************************************************************//*!
				@brief			エミッシブ色設定
				@param[in]		c			色
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetEmissive(const Vector4& c);
		/*************************************************************************//*!
				@brief			エミッシブ色設定
				@param[in]		c			色
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetEmissive(const MofU32 c);
		/*************************************************************************//*!
				@brief			スペキュラ強度設定
				@param			pow			強度
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetPower(MofFloat pow);
		/*************************************************************************//*!
				@brief			ブレンディング設定
				@param			bld			ブレンディング
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetBlending(Blending bld);
		/*************************************************************************//*!
				@brief			テクスチャ設定
				@param			pTex		テクスチャ
				@param			n			番号
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetTexture(LPTexture pTex,MofU32 n);

		//----------------------------------------------------------------------------
		////Get
		//----------------------------------------------------------------------------
		/*************************************************************************//*!
				@brief			名前取得
				@param			None

				@return			名前の取得
		*//**************************************************************************/
		virtual LPString GetName(void);
		/*************************************************************************//*!
				@brief			ディフューズ色取得
				@param			None

				@return			ディフューズ色
		*//**************************************************************************/
		virtual CVector4& GetDiffuse(void);
		/*************************************************************************//*!
				@brief			ディフューズ色取得
				@param			None

				@return			ディフューズ色
		*//**************************************************************************/
		virtual const CVector4& GetDiffuse(void) const;
		/*************************************************************************//*!
				@brief			ディフューズ色取得
				@param			None

				@return			ディフューズ色
		*//**************************************************************************/
		virtual MofU32 GetDiffuseU32(void) const;
		/*************************************************************************//*!
				@brief			アンビエント色取得
				@param			None

				@return			アンビエント色
		*//**************************************************************************/
		virtual CVector4& GetAmbient(void);
		/*************************************************************************//*!
				@brief			アンビエント色取得
				@param			None

				@return			アンビエント色
		*//**************************************************************************/
		virtual const CVector4& GetAmbient(void) const;
		/*************************************************************************//*!
				@brief			アンビエント色取得
				@param			None

				@return			アンビエント色
		*//**************************************************************************/
		virtual MofU32 GetAmbientU32(void) const;
		/*************************************************************************//*!
				@brief			スペキュラ色取得
				@param			None

				@return			スペキュラ色
		*//**************************************************************************/
		virtual CVector4& GetSpeculer(void);
		/*************************************************************************//*!
				@brief			スペキュラ色取得
				@param			None

				@return			スペキュラ色
		*//**************************************************************************/
		virtual const CVector4& GetSpeculer(void) const;
		/*************************************************************************//*!
				@brief			スペキュラ色取得
				@param			None

				@return			スペキュラ色
		*//**************************************************************************/
		virtual MofU32 GetSpeculerU32(void) const;
		/*************************************************************************//*!
				@brief			エミッシブ色取得
				@param			None

				@return			エミッシブ色
		*//**************************************************************************/
		virtual CVector4& GetEmissive(void);
		/*************************************************************************//*!
				@brief			エミッシブ色取得
				@param			None

				@return			エミッシブ色
		*//**************************************************************************/
		virtual const CVector4& GetEmissive(void) const;
		/*************************************************************************//*!
				@brief			エミッシブ色取得
				@param			None

				@return			エミッシブ色
		*//**************************************************************************/
		virtual MofU32 GetEmissiveU32(void) const;
		/*************************************************************************//*!
				@brief			スペキュラ強度取得
				@param			None

				@return			スペキュラ強度
		*//**************************************************************************/
		virtual MofFloat GetPower(void) const;
		/*************************************************************************//*!
				@brief			ブレンディング取得
				@param			None

				@return			ブレンディング
		*//**************************************************************************/
		virtual Blending GetBlending(void) const;
		/*************************************************************************//*!
				@brief			テクスチャ配列取得
				@param			None

				@return			テクスチャ配列
		*//**************************************************************************/
		virtual LPTextureArray GetTextureArray(void);
		/*************************************************************************//*!
				@brief			テクスチャ取得
				@param			n			番号
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual LPTexture GetTexture(MofU32 n);
		/*************************************************************************//*!
				@brief			テクスチャ取得
				@param			n			番号

				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual const LPTexture GetTexture(MofU32 n) const;
	};

	#include	"MaterialBase.inl"
}

#endif

//[EOF]