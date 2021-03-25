/*************************************************************************//*!
					
					@file	MeshBoneAnimationBase.h
					@brief	メッシュアニメーション基底クラス。

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

//ONCE
#ifndef		__MESHBONEANIMATIONBASE__H__

#define		__MESHBONEANIMATIONBASE__H__

//INCLUDE
#include	"MeshBoneAnimation.h"

namespace Mof {
	
	/*******************************//*!
	@brief	メッシュアニメーション基底クラス

			メッシュアニメーション基底となるクラス。

	@author	CDW
	*//********************************/
	class MOFLIBRARY_API CMeshBoneAnimation : public IMeshBoneAnimation {
	protected:
		/*******************//*!
		名前
		*//********************/
		CString						m_Name;
		/*******************//*!
		フラグ
		*//********************/
		MofU32						m_Flag;
		/*******************//*!
		座標キー
		*//********************/
		LPVector3KeyFrameArray		m_pPositionKey;
		/*******************//*!
		拡大キー
		*//********************/
		LPVector3KeyFrameArray		m_pScalingKey;
		/*******************//*!
		回転キー
		*//********************/
		LPQuaternionKeyFrameArray	m_pRotationKey;
	public:
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		CMeshBoneAnimation();
		/*************************************************************************//*!
				@brief			コピーコンストラクタ
				@param[in]		pObj		コピーメッシュアニメーション

				@return			None
		*//**************************************************************************/
		CMeshBoneAnimation(const CMeshBoneAnimation& pObj);
		/*************************************************************************//*!
				@brief			デストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		virtual ~CMeshBoneAnimation();
		
		/*************************************************************************//*!
				@brief			メッシュアニメーションのコピー生成
				@param			None
				
				@return			作成されたコピーCMeshBoneAnimation<br>
								作成に失敗した場合NULLを返す
		*//**************************************************************************/
		virtual IMeshBoneAnimation* CreateCopyObject(void) const;

		/*************************************************************************//*!
				@brief			解放
				@param[in]		pData			解放追加データ

				@return			TRUE			正常終了<br>
								それ以外		解放エラー、エラーコードを返す。
		*//**************************************************************************/
		virtual MofBool Release(LPMofVoid pData = NULL);
		
		//----------------------------------------------------------------------------
		////Is
		//----------------------------------------------------------------------------
		/*************************************************************************//*!
				@brief			ループフラグがあるかを判定する
				@param			None
				
				@return			TRUE			ループする<br>
								FALSE			ループしない
		*//**************************************************************************/
		virtual MofBool IsLoop(void);

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
				@brief			モーションのフラグの設定
				@param[in]		f				フラグ
				
				@return			TRUE			成功<br>
								それ以外		失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetFlag(MofU32 f);
		/*************************************************************************//*!
				@brief			座標キー設定<br>
								古いデータがある場合解放される
				@param[in]		pKey			設定するキー
				
				@return			TRUE			正常終了<br>
								それ以外		設定エラー、エラーコードを返す。
		*//**************************************************************************/
		virtual MofBool SetPositionKey(LPVector3KeyFrameArray pKey);
		/*************************************************************************//*!
				@brief			拡大キー設定<br>
								古いデータがある場合解放される
				@param[in]		pKey			設定するキー
				
				@return			TRUE			正常終了<br>
								それ以外		設定エラー、エラーコードを返す。
		*//**************************************************************************/
		virtual MofBool SetScalingKey(LPVector3KeyFrameArray pKey);
		/*************************************************************************//*!
				@brief			回転キー設定<br>
								古いデータがある場合解放される
				@param[in]		pKey			設定するキー
				
				@return			TRUE			正常終了<br>
								それ以外		設定エラー、エラーコードを返す。
		*//**************************************************************************/
		virtual MofBool SetRotationKey(LPQuaternionKeyFrameArray pKey);
		/*************************************************************************//*!
				@brief			モーションのループフラグの設定
				@param[in]		bLoop			ループフラグ
				
				@return			TRUE			成功<br>
								それ以外		失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetLoop(MofBool bLoop);

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
				@brief			アニメーションの時間取得
				@param			None

				@return			アニメーションの時間
		*//**************************************************************************/
		virtual MofFloat GetTime(void);
		/*************************************************************************//*!
				@brief			アニメーションのフラグ取得
				@param			None

				@return			アニメーションのフラグ
		*//**************************************************************************/
		virtual MofU32 GetFlag(void);
		/*************************************************************************//*!
				@brief			座標キー取得
				@param			None

				@return			座標キー
		*//**************************************************************************/
		virtual LPVector3KeyFrameArray GetPositionKey(void);
		/*************************************************************************//*!
				@brief			拡大キー取得
				@param			None

				@return			拡大キー
		*//**************************************************************************/
		virtual LPVector3KeyFrameArray GetScalingKey(void);
		/*************************************************************************//*!
				@brief			回転キー取得
				@param			None

				@return			回転キー
		*//**************************************************************************/
		virtual LPQuaternionKeyFrameArray GetRotationKey(void);

		//クラス基本定義
		MOF_LIBRARYCLASS(CMeshBoneAnimation,MOF_MESHBONEANIMATIONCLASS_ID);
	};

	#include	"MeshBoneAnimationBase.inl"

}

#endif

//[EOF]