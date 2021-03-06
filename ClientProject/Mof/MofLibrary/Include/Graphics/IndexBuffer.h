/*************************************************************************//*!
					
					@file	IndexBuffer.h
					@brief	インデックスバッファ基底インターフェイス。

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

//ONCE
#ifndef		__INDEXBUFFER__H__

#define		__INDEXBUFFER__H__

//INCLUDE
#include	"GraphicsCommon.h"

namespace Mof {
	
	/*******************************//*!
	@brief	インデックスバッファインターフェイス

			インデックスバッファの作成、設定を行うためのインターフェイス。

	@author	CDW
	*//********************************/
	class MOFLIBRARY_API IIndexBuffer : public IMofObject , public IMofCopyObject< IIndexBuffer > {
	protected:
	public:
		/*************************************************************************//*!
				@brief			バッファの作成
				@param			None
				
				@return			TRUE			正常終了<br>
								それ以外		エラー、エラーコードを返す。
		*//**************************************************************************/
		virtual MofBool CreateBuffer(void) = 0;
		/*************************************************************************//*!
				@brief			バッファの作成
				@param[in]		s				サイズ
				@param[in]		c				数
				@param[in]		pInd			インデックスデータ
				@param[in]		Usage			利用方法
				
				@return			TRUE			正常終了<br>
								それ以外		エラー、エラーコードを返す。
		*//**************************************************************************/
		virtual MofBool CreateBuffer(const MofU32 s,const MofU32 c,LPCMofVoid pInd,const BufferAccess Usage) = 0;
				
		/*************************************************************************//*!
				@brief			バッファのマップ
				@param[in]		mt				マップタイプ
				
				@return			マップされたメモリアドレスを返す。<br>
								失敗の場合NULLになる。
		*//**************************************************************************/
		virtual LPMofVoid Map(MofU32 mt) = 0;
		/*************************************************************************//*!
				@brief			バッファのアンマップ
				@param			None
				
				@return			TRUE			正常終了<br>
								それ以外		エラー、エラーコードを返す。
		*//**************************************************************************/
		virtual MofBool UnMap(void) = 0;
		/*************************************************************************//*!
				@brief			バッファの更新<br>
								バッファの生成方法がBUFFERACCESS_GPUREADWRITEの場合に自分のメンバーデータでバッファの内容を更新する。
				@param			None
				
				@return			TRUE			正常終了<br>
								それ以外		エラー、エラーコードを返す。
		*//**************************************************************************/
		virtual MofBool UpdateBuffer(void) = 0;
		
		//----------------------------------------------------------------------------
		////Set
		//----------------------------------------------------------------------------
		/*************************************************************************//*!
				@brief			バッファの設定
				@param[in]		s				サイズ
				@param[in]		c				数
				@param[in]		pInd			インデックスデータ
				@param[in]		Usage			利用方法
				
				@return			TRUE			正常終了<br>
								それ以外		エラー、エラーコードを返す。
		*//**************************************************************************/
		virtual MofBool SetBufferData(const MofU32 s, const MofU32 c, LPCMofVoid pInd, const BufferAccess Usage) = 0;

		//----------------------------------------------------------------------------
		////Get
		//----------------------------------------------------------------------------
		/*************************************************************************//*!
				@brief			インデックス取得
				@param			None

				@return			インデックスの取得
		*//**************************************************************************/
		virtual LPMofVoid GetIndex(void) const = 0;
		/*************************************************************************//*!
				@brief			インデックス取得
				@param			None

				@return			インデックスの取得<br>
								サイズが16bitインデックスではない場合NULL
		*//**************************************************************************/
		virtual LPMofU16 GetIndexU16(void) = 0;
		/*************************************************************************//*!
				@brief			インデックス取得
				@param			None

				@return			インデックスの取得<br>
								サイズが32bitインデックスではない場合NULL
		*//**************************************************************************/
		virtual LPMofU32 GetIndexU32(void) = 0;
		/*************************************************************************//*!
				@brief			インデックスサイズ取得
				@param			None

				@return			インデックスサイズの取得
		*//**************************************************************************/
		virtual MofU32 GetIndexSize(void) const = 0;
		/*************************************************************************//*!
				@brief			インデックス数取得
				@param			None

				@return			インデックス数の取得
		*//**************************************************************************/
		virtual MofU32 GetIndexCount(void) const = 0;
		/*************************************************************************//*!
				@brief			インデックスバッファ取得
				@param			None

				@return			インデックスバッファの取得
		*//**************************************************************************/
		virtual MofIndexBuffer GetBuffer(void) const = 0;
	};

	//ポインタ置き換え
	typedef IIndexBuffer*			LPIndexBuffer;
}

#endif

//[EOF]