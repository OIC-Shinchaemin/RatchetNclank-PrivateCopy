/*************************************************************************//*!
					
					@file	XMLDocument.h
					@brief	XML関連

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

//ONCE
#ifndef		__XMLDOCUMENT__H__

#define		__XMLDOCUMENT__H__

//INCLUDE
#include	"../Math/Quaternion.h"
#include	"../Common/String.h"
#include	"tinyxml2.h"

namespace Mof {
	
	/*******************************//*!
	@brief	XMLドキュメントクラス

			XML形式のファイルを扱うクラス。

	@author	CDW
	*//********************************/
	class MOFLIBRARY_API CXmlDocument : public IMofNamedObject {
	protected:
		/*******************//*!
		名前
		*//********************/
		CString								m_Name;
		/*******************//*!
		内部ドキュメント
		*//********************/
		tinyxml2::XMLDocument*				m_pDocument;
		/*******************//*!
		内部選択エレメント
		*//********************/
		tinyxml2::XMLElement*				m_pNowElement;
	public:
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		CXmlDocument();
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param[in]		pName		ファイル名

				@return			None
		*//**************************************************************************/
		CXmlDocument(LPCMofChar pName);
		/*************************************************************************//*!
				@brief			デストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		virtual ~CXmlDocument();

		/*************************************************************************//*!
				@brief			ファイルを開く
				@param[in]		pName		ファイル名
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool Open(LPCMofChar pName) = 0;
		
		/*************************************************************************//*!
				@brief			選択エレメントの子を選択する
				@param[in]		pName		エレメント名
				
				@return			選択したエレメント<br>
								NULLの場合生成失敗
		*//**************************************************************************/
		virtual tinyxml2::XMLElement* PushElement(LPCMofChar pName);
		/*************************************************************************//*!
				@brief			選択エレメントの前を選択する
				@param[in]		pName		エレメント名
				
				@return			選択したエレメント<br>
								NULLの場合生成失敗
		*//**************************************************************************/
		virtual tinyxml2::XMLElement* PrevElement(LPCMofChar pName);
		/*************************************************************************//*!
				@brief			選択エレメントの次を選択する
				@param[in]		pName		エレメント名
				
				@return			選択したエレメント<br>
								NULLの場合生成失敗
		*//**************************************************************************/
		virtual tinyxml2::XMLElement* NextElement(LPCMofChar pName);
		/*************************************************************************//*!
				@brief			エレメントの選択を一つ上に戻す
				@param			None
				
				@return			選択したエレメント
		*//**************************************************************************/
		virtual tinyxml2::XMLElement* PopElement(void);

		/*************************************************************************//*!
				@brief			ファイルを閉じる
				@param			None
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool Close(void);
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
				@brief			アトリビュート存在判定
				@param[in]		pName			名前
				
				@return			TRUE			アトリビュートがある<br>
								FALSE			アトリビュートがない
		*//**************************************************************************/
		virtual MofBool IsAttribute(LPCMofChar pName) const;

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
				@brief			名前取得
				@param			None

				@return			名前の取得
		*//**************************************************************************/
		virtual LPString GetName(void);
		/*************************************************************************//*!
				@brief			アトリビュート取得
				@param[in]		pName			名前

				@return			アトリビュートの取得
		*//**************************************************************************/
		virtual LPCMofChar GetAttribute(LPCMofChar pName);
		/*************************************************************************//*!
				@brief			アトリビュート取得
				@param[in]		pName			名前
				@param[out]		v				出力用値

				@return			アトリビュートの取得
		*//**************************************************************************/
		virtual MofBool GetAttributeString(LPCMofChar pName,CString& v);
		/*************************************************************************//*!
				@brief			アトリビュート取得
				@param[in]		pName			名前
				@param[out]		v				出力用値

				@return			アトリビュートの取得
		*//**************************************************************************/
		virtual MofBool GetAttributeBOOL(LPCMofChar pName,MofBool& v);
		/*************************************************************************//*!
				@brief			アトリビュート取得
				@param[in]		pName			名前
				@param[out]		v				出力用値

				@return			アトリビュートの取得
		*//**************************************************************************/
		virtual MofBool GetAttributeS32(LPCMofChar pName,MofS32& v);
		/*************************************************************************//*!
				@brief			アトリビュート取得
				@param[in]		pName			名前
				@param[out]		v				出力用値

				@return			アトリビュートの取得
		*//**************************************************************************/
		virtual MofBool GetAttributeU32(LPCMofChar pName,MofU32& v);
		/*************************************************************************//*!
				@brief			アトリビュート取得
				@param[in]		pName			名前
				@param[out]		v				出力用値

				@return			アトリビュートの取得
		*//**************************************************************************/
		virtual MofBool GetAttributeFloat(LPCMofChar pName,MofFloat& v);
		/*************************************************************************//*!
				@brief			アトリビュート取得
				@param[in]		pName			名前
				@param[out]		v				出力用値

				@return			アトリビュートの取得
		*//**************************************************************************/
		virtual MofBool GetAttributeVector3(LPCMofChar pName,Vector3& v);
		/*************************************************************************//*!
				@brief			アトリビュート取得
				@param[in]		pName			名前
				@param[out]		v				出力用値

				@return			アトリビュートの取得
		*//**************************************************************************/
		virtual MofBool GetAttributeVector3(LPCMofChar pName,CVector3& v);
		/*************************************************************************//*!
				@brief			アトリビュート取得
				@param[in]		pName			名前
				@param[out]		v				出力用値

				@return			アトリビュートの取得
		*//**************************************************************************/
		virtual MofBool GetAttributeVector4(LPCMofChar pName,Vector4& v);
		/*************************************************************************//*!
				@brief			アトリビュート取得
				@param[in]		pName			名前
				@param[out]		v				出力用値

				@return			アトリビュートの取得
		*//**************************************************************************/
		virtual MofBool GetAttributeVector4(LPCMofChar pName,CVector4& v);
		/*************************************************************************//*!
				@brief			アトリビュート取得
				@param[in]		pName			名前
				@param[out]		v				出力用値

				@return			アトリビュートの取得
		*//**************************************************************************/
		virtual MofBool GetAttributeQuaternion(LPCMofChar pName,Quaternion& v);
		/*************************************************************************//*!
				@brief			アトリビュート取得
				@param[in]		pName			名前
				@param[out]		v				出力用値

				@return			アトリビュートの取得
		*//**************************************************************************/
		virtual MofBool GetAttributeQuaternion(LPCMofChar pName,CQuaternion& v);
		/*************************************************************************//*!
				@brief			アトリビュート取得
				@param[in]		pName			名前
				@param[out]		v				出力用値

				@return			アトリビュートの取得
		*//**************************************************************************/
		virtual MofBool GetAttributeMatrix44(LPCMofChar pName,Matrix44& v);
		/*************************************************************************//*!
				@brief			アトリビュート取得
				@param[in]		pName			名前
				@param[out]		v				出力用値

				@return			アトリビュートの取得
		*//**************************************************************************/
		virtual MofBool GetAttributeMatrix44(LPCMofChar pName,CMatrix44& v);

		/*************************************************************************//*!
				@brief			XMLドキュメントへのアクセス
		*//**************************************************************************/
		tinyxml2::XMLDocument* operator -> ( );
		/*************************************************************************//*!
				@brief			XMLドキュメントへのアクセス
		*//**************************************************************************/
		tinyxml2::XMLDocument* operator -> ( ) const;
	};
	//ポインタ置き換え
	typedef CXmlDocument*			LPXmlDocument;
	
	/*******************************//*!
	@brief	XMLドキュメントクラス

			XML形式のファイルを読み込むクラス。

	@author	CDW
	*//********************************/
	class MOFLIBRARY_API CWriteXmlDocument : public CXmlDocument {
	protected:
	public:
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		CWriteXmlDocument();
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param[in]		pName		ファイル名

				@return			None
		*//**************************************************************************/
		CWriteXmlDocument(LPCMofChar pName);
		/*************************************************************************//*!
				@brief			デストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		virtual ~CWriteXmlDocument();

		/*************************************************************************//*!
				@brief			ファイルを開く
				@param[in]		pName		ファイル名
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool Open(LPCMofChar pName);
		
		/*************************************************************************//*!
				@brief			新規エレメントを作成して選択する
				@param[in]		pName		エレメント名
				
				@return			生成したエレメント<br>
								NULLの場合生成失敗
		*//**************************************************************************/
		virtual tinyxml2::XMLElement* PushNewElement(LPCMofChar pName);
		
		/*************************************************************************//*!
				@brief			選択エレメントに新規アトリビュートを作成する
				@param[in]		pName		アトリビュート名
				@param[in]		val			アトリビュート
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool NewAttribute(LPCMofChar pName,LPCMofChar val);
		/*************************************************************************//*!
				@brief			指定エレメントに新規アトリビュートを作成する
				@param[in]		elm			追加エレメント
				@param[in]		pName		アトリビュート名
				@param[in]		val			アトリビュート
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool NewAttribute(tinyxml2::XMLElement* elm,LPCMofChar pName,LPCMofChar val);
		
		/*************************************************************************//*!
				@brief			ファイルを閉じる
				@param			None
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool Close(void);

		//クラス基本定義
		MOF_LIBRARYCLASS(CWriteXmlDocument, MOF_TEMPORARYCLASS_ID);
	};

	/*******************************//*!
	@brief	XMLドキュメントクラス

			XML形式のファイルを読み込むクラス。

	@author	CDW
	*//********************************/
	class MOFLIBRARY_API CReadXmlDocument : public CXmlDocument {
	protected:
	public:
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		CReadXmlDocument();
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param[in]		pName		ファイル名

				@return			None
		*//**************************************************************************/
		CReadXmlDocument(LPCMofChar pName);
		/*************************************************************************//*!
				@brief			デストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		virtual ~CReadXmlDocument();

		/*************************************************************************//*!
				@brief			ファイルを開く
				@param[in]		pName		ファイル名
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool Open(LPCMofChar pName);

		//クラス基本定義
		MOF_LIBRARYCLASS(CReadXmlDocument, MOF_TEMPORARYCLASS_ID);
	};

	//INLINE INCLUDE
	#include	"XMLDocument.inl"

}

#endif

//[EOF]