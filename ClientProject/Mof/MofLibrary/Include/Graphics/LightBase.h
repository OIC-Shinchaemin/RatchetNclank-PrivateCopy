/*************************************************************************//*!
					
					@file	LightBase.h
					@brief	ライト基底クラス。

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

//ONCE
#ifndef		__LIGHTBASE__H__

#define		__LIGHTBASE__H__

//INCLUDE
#include	"Light.h"

namespace Mof {
	
	/*******************************//*!
	@brief	ライト基底クラス

			ライト基底となるクラス。

	@author	CDW
	*//********************************/
	class MOFLIBRARY_API CLightBase : public ILight {
	protected:
		/*******************//*!
		名前
		*//********************/
		CString						m_Name;
		/*******************//*!
		ディフューズ
		*//********************/
		CVector4					m_Diffuse;
		/*******************//*!
		アンビエント
		*//********************/
		CVector4					m_Ambient;
		/*******************//*!
		スペキュラ
		*//********************/
		CVector4					m_Speculer;
	public:
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		CLightBase();
		/*************************************************************************//*!
				@brief			コピーコンストラクタ
				@param[in]		pObj		コピーマテリアル

				@return			None
		*//**************************************************************************/
		CLightBase(const CLightBase& pObj);
		/*************************************************************************//*!
				@brief			デストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		virtual ~CLightBase();

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
	};

	#include	"LightBase.inl"
}

#endif

//[EOF]