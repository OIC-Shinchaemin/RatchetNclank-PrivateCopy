/*************************************************************************//*!
					
					@file	StringImpl.h
					@brief	文字列関連のクラス内部定義。

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

/*******************************//*!
@brief	文字列クラス

@author	CDW
*//********************************/
class MOFLIBRARY_API MOF_STRINGIMPL_NAME : public IMofBase {
protected:
	/*******************//*!
	内部文字列
	*//********************/
	MOF_STRINGIMPL_TYPE*	m_pStr;
	/*******************//*!
	内部文字列文字数
	*//********************/
	MofU32					m_StrLength;
public:
	/*************************************************************************//*!
			@brief			コンストラクタ
			@param			None

			@return			None
	*//**************************************************************************/
	MOF_STRINGIMPL_NAME();
	/*************************************************************************//*!
			@brief			コンストラクタ
			@param[in]		str			文字列

			@return			None
	*//**************************************************************************/
	MOF_STRINGIMPL_NAME(const MOF_STRINGIMPL_TYPE* str);
	/*************************************************************************//*!
			@brief			コピーコンストラクタ
			@param[in]		str			コピー文字列

			@return			None
	*//**************************************************************************/
	MOF_STRINGIMPL_NAME(const MOF_STRINGIMPL_NAME& str);
	/*************************************************************************//*!
			@brief			デストラクタ
			@param			None

			@return			None
	*//**************************************************************************/
	virtual ~MOF_STRINGIMPL_NAME();
	
	/*************************************************************************//*!
			@brief			文字列の追加<br>
							現在の文字列の後ろに引数の文字列を追加する。
			@param[in]		str			文字列
			
			@return			TRUE		正常に追加された<br>
							FALSE		追加の失敗
	*//**************************************************************************/
	MofBool Add(const MOF_STRINGIMPL_TYPE* str);
	/*************************************************************************//*!
			@brief			文字列の追加<br>
							指定位置に引数の文字列を追加する。
			@param[in]		str			文字列
			@param[in]		in			挿入位置
			
			@return			TRUE		正常に追加された<br>
							FALSE		追加の失敗
	*//**************************************************************************/
	MofBool Insert(const MOF_STRINGIMPL_TYPE* str, MofU32 in);
	
	/*************************************************************************//*!
			@brief			文字列の削除<br>
							現在の文字列の指定位置から後ろの文字列を削除する。
			@param[in]		s			開始位置
			
			@return			TRUE		正常に削除された<br>
							FALSE		追加の失敗
	*//**************************************************************************/
	MofBool Delete(const MofU32 s);
	/*************************************************************************//*!
			@brief			文字列の削除<br>
							現在の文字列の指定位置から指定位置までの文字列を削除する。
			@param[in]		s			開始位置
			
			@return			TRUE		正常に削除された<br>
							FALSE		追加の失敗
	*//**************************************************************************/
	MofBool Delete(const MofU32 s,const MofU32 e);
	
	/*************************************************************************//*!
			@brief			文字列の前後の空白除去<br>
							現在の文字列の前後に存在する空白を削除する。
			@param			None
			
			@return			TRUE		正常に削除された<br>
							FALSE		追加の失敗
	*//**************************************************************************/
	MofBool Trim(void);
	/*************************************************************************//*!
			@brief			文字列の前後の空白除去<br>
							現在の文字列の前後に存在する空白を削除する。
			@param[in]		s			削除文字列
			
			@return			TRUE		正常に削除された<br>
							FALSE		追加の失敗
	*//**************************************************************************/
	static MofBool Trim(MOF_STRINGIMPL_TYPE* s);
	/*************************************************************************//*!
			@brief			現在の文字列のファイル名+拡張子以外を削除する。
			@param[in]		pName		削除文字列
			@param[out]		oName		削除後文字列
			
			@return			TRUE		正常に削除された<br>
							FALSE		追加の失敗
	*//**************************************************************************/
	static MofBool TrimFile(const MOF_STRINGIMPL_TYPE* pName,MOF_STRINGIMPL_TYPE* oName);
	/*************************************************************************//*!
			@brief			ファイル名以外のパス、拡張子除去<br>
							現在の文字列のファイル名以外を削除する。
			@param[in]		pName		削除文字列
			@param[out]		oName		削除後文字列
			
			@return			TRUE		正常に削除された<br>
							FALSE		追加の失敗
	*//**************************************************************************/
	static MofBool TrimFileName(const MOF_STRINGIMPL_TYPE* pName,MOF_STRINGIMPL_TYPE* oName);
	/*************************************************************************//*!
			@brief			ファイル名のパス以外除去<br>
							現在の文字列のパス以外を削除する。
			@param[in]		pName		削除文字列
			@param[out]		oName		削除後文字列
			
			@return			TRUE		正常に削除された<br>
							FALSE		追加の失敗
	*//**************************************************************************/
	static MofBool TrimFilePath(const MOF_STRINGIMPL_TYPE* pName,MOF_STRINGIMPL_TYPE* oName);

	/*************************************************************************//*!
			@brief			文字列の比較<br>
							指定された文字列が比較対象の文字列のと一致するかを判定する。<br>
							大文字、小文字の区別を行う、行わない場合はCompareCaseを利用する。
			@param[in]		s			比較文字列
			
			@return			0			一致
							> 0			先頭文字が自分が大きい
							< 0			先頭文字が比較文字列が大きい
	*//**************************************************************************/
	MofS32 Compare(const MOF_STRINGIMPL_TYPE* s) const;
	/*************************************************************************//*!
			@brief			文字列の比較<br>
							指定された文字列が比較対象の文字列のと一致するかを判定する。<br>
							大文字、小文字の区別を行う、行わない場合はCompareCaseを利用する。
			@param[in]		s			比較文字列
			@param[in]		l			比較文字列の長さ
			
			@return			0			一致
							> 0			先頭文字が自分が大きい
							< 0			先頭文字が比較文字列が大きい
	*//**************************************************************************/
	MofS32 Compare(const MOF_STRINGIMPL_TYPE* s,MofU32 l) const;
	/*************************************************************************//*!
			@brief			文字列の比較<br>
							指定された文字列が比較対象の文字列のと一致するかを判定する。<br>
							大文字、小文字の区別を行う、行わない場合はCompareCaseを利用する。
			@param[in]		s1			対象文字列
			@param[in]		s2			比較文字列
			
			@return			0			一致
							> 0			先頭文字が対象文字列が大きい
							< 0			先頭文字が比較文字列が大きい
	*//**************************************************************************/
	static MofS32 Compare(const MOF_STRINGIMPL_TYPE* s1,const MOF_STRINGIMPL_TYPE* s2);
	/*************************************************************************//*!
			@brief			文字列の比較<br>
							指定された文字列が比較対象の文字列のと一致するかを判定する。<br>
							大文字、小文字の区別を行う、行わない場合はCompareCaseを利用する。
			@param[in]		s1			対象文字列
			@param[in]		s2			比較文字列
			@param[in]		l			比較文字列の長さ
			
			@return			0			一致
							> 0			先頭文字が対象文字列が大きい
							< 0			先頭文字が比較文字列が大きい
	*//**************************************************************************/
	static MofS32 Compare(const MOF_STRINGIMPL_TYPE* s1,const MOF_STRINGIMPL_TYPE* s2,MofU32 l);
	/*************************************************************************//*!
			@brief			文字列の比較<br>
							指定された文字列が比較対象の文字列のと一致するかを判定する。<br>
							大文字、小文字の区別を行わない、行う場合はCompareを利用する。
			@param[in]		s			比較文字列
			
			@return			0			一致
							> 0			先頭文字が自分が大きい
							< 0			先頭文字が比較文字列が大きい
	*//**************************************************************************/
	MofS32 CompareCase(const MOF_STRINGIMPL_TYPE* s) const;
	/*************************************************************************//*!
			@brief			文字列の比較<br>
							指定された文字列が比較対象の文字列のと一致するかを判定する。<br>
							大文字、小文字の区別を行わない、行う場合はCompareを利用する。
			@param[in]		s			比較文字列
			@param[in]		l			比較文字列の長さ
			
			@return			0			一致
							> 0			先頭文字が自分が大きい
							< 0			先頭文字が比較文字列が大きい
	*//**************************************************************************/
	MofS32 CompareCase(const MOF_STRINGIMPL_TYPE* s,MofU32 l) const;
	/*************************************************************************//*!
			@brief			文字列の比較<br>
							指定された文字列が比較対象の文字列のと一致するかを判定する。<br>
							大文字、小文字の区別を行わない、行う場合はCompareを利用する。
			@param[in]		s1			対象文字列
			@param[in]		s2			比較文字列
			
			@return			0			一致
							> 0			先頭文字が対象文字列が大きい
							< 0			先頭文字が比較文字列が大きい
	*//**************************************************************************/
	static MofS32 CompareCase(const MOF_STRINGIMPL_TYPE* s1,const MOF_STRINGIMPL_TYPE* s2);
	/*************************************************************************//*!
			@brief			文字列の比較<br>
							指定された文字列が比較対象の文字列のと一致するかを判定する。<br>
							大文字、小文字の区別を行わない、行う場合はCompareを利用する。
			@param[in]		s1			対象文字列
			@param[in]		s2			比較文字列
			@param[in]		l			比較文字列の長さ
			
			@return			0			一致
							> 0			先頭文字が対象文字列が大きい
							< 0			先頭文字が比較文字列が大きい
	*//**************************************************************************/
	static MofS32 CompareCase(const MOF_STRINGIMPL_TYPE* s1,const MOF_STRINGIMPL_TYPE* s2,MofU32 l);

	/*************************************************************************//*!
			@brief			文字列の検索<br>
							指定された文字列が文字列の中に存在するかを検索する。<br>
							大文字、小文字の区別を行う、行わない場合はSearchCaseを利用する。
			@param[in]		s			文字列
			
			@return			NULL		存在しない
							存在する場合、指定された文字列の先頭アドレス
	*//**************************************************************************/
	MOF_STRINGIMPL_TYPE* Search(const MOF_STRINGIMPL_TYPE* s);
	/*************************************************************************//*!
			@brief			文字列の検索<br>
							指定された文字列が文字列の中に存在するかを検索する。<br>
							大文字、小文字の区別を行う、行わない場合はSearchCaseを利用する。
			@param[in]		s			文字列
			@param[in]		l			文字列の長さ
			
			@return			NULL		存在しない
							存在する場合、指定された文字列の先頭アドレス
	*//**************************************************************************/
	MOF_STRINGIMPL_TYPE* Search(const MOF_STRINGIMPL_TYPE* s,MofU32 l);
	/*************************************************************************//*!
			@brief			文字列の検索<br>
							指定された文字列が文字列の中に存在するかを検索する。<br>
							大文字、小文字の区別を行う、行わない場合はSearchCaseを利用する。
			@param[in]		s1			対象文字列
			@param[in]		s2			検索文字列
			
			@return			NULL		存在しない
							存在する場合、指定された文字列の先頭アドレス
	*//**************************************************************************/
	static MOF_STRINGIMPL_TYPE* Search(const MOF_STRINGIMPL_TYPE* s1,const MOF_STRINGIMPL_TYPE* s2);
	/*************************************************************************//*!
			@brief			文字列の検索<br>
							指定された文字列が文字列の中に存在するかを検索する。<br>
							大文字、小文字の区別を行う、行わない場合はSearchCaseを利用する。
			@param[in]		s1			対象文字列
			@param[in]		s2			検索文字列
			@param[in]		l			検索文字列の長さ
			
			@return			NULL		存在しない
							存在する場合、指定された文字列の先頭アドレス
	*//**************************************************************************/
	static MOF_STRINGIMPL_TYPE* Search(const MOF_STRINGIMPL_TYPE* s1,const MOF_STRINGIMPL_TYPE* s2,MofU32 l);
	/*************************************************************************//*!
			@brief			文字列の検索<br>
							指定された文字列が文字列の中に存在するかを検索する。<br>
							大文字、小文字の区別を行わない、行う場合はSearchを利用する。
			@param[in]		s			文字列
			
			@return			NULL		存在しない
							存在する場合、指定された文字列の先頭アドレス
	*//**************************************************************************/
	MOF_STRINGIMPL_TYPE* SearchCase(const MOF_STRINGIMPL_TYPE* s);
	/*************************************************************************//*!
			@brief			文字列の検索<br>
							指定された文字列が文字列の中に存在するかを検索する。<br>
							大文字、小文字の区別を行わない、行う場合はSearchを利用する。
			@param[in]		s			文字列
			@param[in]		l			文字列の長さ
			
			@return			NULL		存在しない
							存在する場合、指定された文字列の先頭アドレス
	*//**************************************************************************/
	MOF_STRINGIMPL_TYPE* SearchCase(const MOF_STRINGIMPL_TYPE* s,MofU32 l);
	/*************************************************************************//*!
			@brief			文字列の検索<br>
							指定された文字列が文字列の中に存在するかを検索する。<br>
							大文字、小文字の区別を行わない、行う場合はSearchを利用する。
			@param[in]		s1			対象文字列
			@param[in]		s2			検索文字列
			
			@return			NULL		存在しない
							存在する場合、指定された文字列の先頭アドレス
	*//**************************************************************************/
	static MOF_STRINGIMPL_TYPE* SearchCase(const MOF_STRINGIMPL_TYPE* s1,const MOF_STRINGIMPL_TYPE* s2);
	/*************************************************************************//*!
			@brief			文字列の検索<br>
							指定された文字列が文字列の中に存在するかを検索する。<br>
							大文字、小文字の区別を行わない、行う場合はSearchを利用する。
			@param[in]		s1			対象文字列
			@param[in]		s2			検索文字列
			@param[in]		l			検索文字列の長さ
			
			@return			NULL		存在しない
							存在する場合、指定された文字列の先頭アドレス
	*//**************************************************************************/
	static MOF_STRINGIMPL_TYPE* SearchCase(const MOF_STRINGIMPL_TYPE* s1,const MOF_STRINGIMPL_TYPE* s2,MofU32 l);
	
	/*************************************************************************//*!
			@brief			文字列の置き換え<br>
							対象文字列を置き換え文字列に置き換える。
			@param[in]		s2			対象文字列
			@param[in]		s3			置き換え文字列
			
			@return			TRUE		正常に設定された<br>
							FALSE		追加の失敗
	*//**************************************************************************/
	MofBool Replace(const MOF_STRINGIMPL_TYPE* s2,const MOF_STRINGIMPL_TYPE* s3);

	//----------------------------------------------------------------------------
	////Set
	//----------------------------------------------------------------------------
	/*************************************************************************//*!
			@brief			文字列の設定<br>
							現在の文字列を削除して引数の文字列に置き換える。
			@param[in]		str			文字列
			
			@return			TRUE		正常に設定された<br>
							FALSE		追加の失敗
	*//**************************************************************************/
	MofBool SetString(const MOF_STRINGIMPL_TYPE* str);
	/*************************************************************************//*!
			@brief			文字列の設定<br>
							現在の文字列を削除して引数の文字列に置き換える。
			@param[in]		str			文字列
			@param[in]		l			文字列の長さ
			
			@return			TRUE		正常に設定された<br>
							FALSE		追加の失敗
	*//**************************************************************************/
	MofBool SetString(const MOF_STRINGIMPL_TYPE* str,MofU32 l);

	//----------------------------------------------------------------------------
	////Get
	//----------------------------------------------------------------------------
	/*************************************************************************//*!
			@brief			内部文字列取得
			@param			None

			@return			文字列
	*//**************************************************************************/
	MOF_STRINGIMPL_TYPE* GetString(void) const;
	/*************************************************************************//*!
			@brief			内部文字取得
			@param[in]		i			位置

			@return			文字列
	*//**************************************************************************/
	MOF_STRINGIMPL_TYPE GetAt(int i) const;
	/*************************************************************************//*!
			@brief			内部文字数取得
			@param			None

			@return			文字数
	*//**************************************************************************/
	MofU32 GetLength(void) const;
	/*************************************************************************//*!
			@brief			内部文字列バイト数取得
			@param			None

			@return			文字列バイト数
	*//**************************************************************************/
	MofU32 GetStringSize(void) const;
	
	//----------------------------------------------------------------------------
	////Operator
	//----------------------------------------------------------------------------
	
	/*************************************************************************//*!
			@brief			文字列キャスト<br>
							内部のm_pStrをそのまま返す。
	*//**************************************************************************/
	operator MOF_STRINGIMPL_TYPE* ();
	/*************************************************************************//*!
			@brief			文字列キャスト<br>
							内部のm_pStrをそのまま返す。
	*//**************************************************************************/
	operator const MOF_STRINGIMPL_TYPE* () const;
	/*************************************************************************//*!
			@brief			+=演算
	*//**************************************************************************/
	MOF_STRINGIMPL_NAME& operator += ( const MOF_STRINGIMPL_TYPE* s );
	/*************************************************************************//*!
			@brief			+=演算
	*//**************************************************************************/
	MOF_STRINGIMPL_NAME& operator += ( const MofS32& s );
	/*************************************************************************//*!
			@brief			+=演算
	*//**************************************************************************/
	MOF_STRINGIMPL_NAME& operator += ( const MofU32& s );
	/*************************************************************************//*!
			@brief			+=演算
	*//**************************************************************************/
	MOF_STRINGIMPL_NAME& operator += ( const MofFloat& s );
	/*************************************************************************//*!
			@brief			+演算
	*//**************************************************************************/
	MOF_STRINGIMPL_NAME operator + ( const MOF_STRINGIMPL_TYPE* v ) const;
	/*************************************************************************//*!
			@brief			+演算
	*//**************************************************************************/
	MOF_STRINGIMPL_NAME operator + ( const MofS32& s ) const;
	/*************************************************************************//*!
			@brief			+演算
	*//**************************************************************************/
	MOF_STRINGIMPL_NAME operator + ( const MofU32& s ) const;
	/*************************************************************************//*!
			@brief			+演算
	*//**************************************************************************/
	MOF_STRINGIMPL_NAME operator + ( const MofFloat& s ) const;
	/*************************************************************************//*!
			@brief			配列指定による文字列へのアクセス
	*//**************************************************************************/
	MOF_STRINGIMPL_TYPE& operator [] ( int i );
	/*************************************************************************//*!
			@brief			配列指定による文字列へのアクセス
	*//**************************************************************************/
	const MOF_STRINGIMPL_TYPE& operator [] ( int i ) const;
	/*************************************************************************//*!
			@brief			文字列代入<br>
							SetString関数を内部で実行する。
	*//**************************************************************************/
	MOF_STRINGIMPL_NAME& operator = ( const MOF_STRINGIMPL_TYPE* s );
	/*************************************************************************//*!
			@brief			文字列代入<br>
							SetString関数を内部で実行する。
	*//**************************************************************************/
	MOF_STRINGIMPL_NAME& operator = ( const MOF_STRINGIMPL_NAME& s );
	/*************************************************************************//*!
			@brief			==判断
	*//**************************************************************************/
	bool operator == ( const MOF_STRINGIMPL_TYPE* v ) const;
	/*************************************************************************//*!
			@brief			==判断
	*//**************************************************************************/
	bool operator == ( const MOF_STRINGIMPL_NAME& v ) const;
	/*************************************************************************//*!
			@brief			!=判断
	*//**************************************************************************/
	bool operator != ( const MOF_STRINGIMPL_TYPE* v ) const;
	/*************************************************************************//*!
			@brief			!=判断
	*//**************************************************************************/
	bool operator != ( const MOF_STRINGIMPL_NAME& v ) const;
	
	//クラス基本定義
#ifdef		MOF_STRINGIMPL_UNICODE
	MOF_LIBRARYCLASS_NOTEQUAL(CStringW,MOF_WSTRINGCLASS_ID);
#else
	MOF_LIBRARYCLASS_NOTEQUAL(CStringA,MOF_ASTRINGCLASS_ID);
#endif
};

#include	"StringImpl.inl"

//[EOF]