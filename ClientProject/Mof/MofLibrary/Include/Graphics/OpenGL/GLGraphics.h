/*************************************************************************//*!
					
					@file	GLGraphics.h
					@brief	OpenGLでのグラフィックスの処理を行う基底インターフェイス。

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

//ONCE
#ifndef		__GLGRAPHICS__H__

#define		__GLGRAPHICS__H__

//INCLUDE
#include	"../Graphics.h"
#include	"GLRenderTarget.h"
#include	"GLDepthTarget.h"

namespace Mof {
	
	/*******************************//*!
	@brief	OpenGLグラフィックスステータス構造体

			グラフィックスのステータスを表す構造体

	@author	CDW
	*//********************************/
	typedef struct MOFLIBRARY_API tag_OPENGLGRAPHICSSTATUS : public tag_GRAPHICSSTATUS {
		MofS32					ScreenWidth;			//!<幅
		MofS32					ScreenHeight;			//!<高さ
		
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		tag_OPENGLGRAPHICSSTATUS() :
		tag_GRAPHICSSTATUS(),
		ScreenWidth(0),
		ScreenHeight(0) {
		}
	}OPENGLGRAPHICSSTATUS,*LPOPENGLGRAPHICSSTATUS;

	/*******************************//*!
	@brief	グラフィックス基底インターフェイス

			グラフィックスの基底となるインターフェイス。

	@author	CDW
	*//********************************/
	class MOFLIBRARY_API CGLGraphics : public IGraphics {
	protected:
		/*******************//*!
		グラフィックスステータス
		*//********************/
		OPENGLGRAPHICSSTATUS	m_Status;
		/*******************//*!
		描画ターゲット
		*//********************/
		LPRenderTarget			m_pDefaultRenderTarget;
		/*******************//*!
		深度ターゲット
		*//********************/
		LPDepthTarget			m_pDefaultDepthTarget;
	public:
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		CGLGraphics();
		/*************************************************************************//*!
				@brief			デストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		virtual ~CGLGraphics();

		/*************************************************************************//*!
				@brief			グラフィックスオブジェクトの生成
				@param[in]		pInfo		グラフィックスの生成情報
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool Create(LPGRAPHICSCREATEINFO pInfo);
		
		/*************************************************************************//*!
				@brief			画面モードを設定する
				@param			None
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool ChangeScreenMode(void);

		/*************************************************************************//*!
				@brief			描画の開始
				@param			None
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool RenderStart(void);
		/*************************************************************************//*!
				@brief			全ターゲットのクリア
				@param[in]		d			深度
				@param[in]		s			ステンシル
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool ClearTarget(void);
		/*************************************************************************//*!
				@brief			全ターゲットのクリア
				@param[in]		r			赤
				@param[in]		g			緑
				@param[in]		b			青
				@param[in]		a			アルファ
				@param[in]		d			深度
				@param[in]		s			ステンシル
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool ClearTarget(MofFloat r,MofFloat g,MofFloat b,MofFloat a,MofFloat d,MofU32 s);
		/*************************************************************************//*!
				@brief			描画ターゲットのクリア
				@param[in]		r			赤
				@param[in]		g			緑
				@param[in]		b			青
				@param[in]		a			アルファ
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool ClearRenderTarget(MofFloat r,MofFloat g,MofFloat b,MofFloat a);
		/*************************************************************************//*!
				@brief			深度ステンシルターゲットのクリア
				@param[in]		d			深度
				@param[in]		s			ステンシル
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool ClearDepthStencilTarget(MofFloat d,MofU32 s);
		/*************************************************************************//*!
				@brief			深度ターゲットのクリア
				@param[in]		d			深度
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool ClearDepthTarget(MofFloat d);
		/*************************************************************************//*!
				@brief			ステンシルターゲットのクリア
				@param[in]		s			ステンシル
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool ClearStencilTarget(MofU32 s);
		/*************************************************************************//*!
				@brief			描画の終了
				@param			None
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool RenderEnd(void);
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
				@brief			描画用画面サイズを設定する
				@param[in]		sw				幅
				@param[in]		sh				高さ
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetScreenSize(MofS32 sw,MofS32 sh);
		/*************************************************************************//*!
				@brief			ビューポート設定
				@param[in]		px			X位置
				@param[in]		py			Y位置
				@param[in]		w			幅
				@param[in]		h			高さ
				@param[in]		n			最近
				@param[in]		f			最遠
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetViewPort(const MofFloat px,const MofFloat py,const MofFloat w,const MofFloat h,const MofFloat n,const MofFloat f);
		/*************************************************************************//*!
				@brief			ビューポート設定
				@param[in]		v			ビューポート
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetViewPort(const ViewPort& v);
		/*************************************************************************//*!
				@brief			ブレンドステートの設定
				@param[in]		Blend		ブレンド方法
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetBlending(Blending Blend);
		/*************************************************************************//*!
				@brief			色書き込みの設定
				@param[in]		bEnable		有効フラグ
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetColorWriteEnable(MofBool bEnable);
		/*************************************************************************//*!
				@brief			深度バッファの設定
				@param[in]		bEnable		判定有効フラグ
				@param[in]		bWEnable	書き込み有効フラグ
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetDepthEnable(MofBool bEnable,MofBool bWEnable);
		/*************************************************************************//*!
				@brief			深度バッファの設定
				@param[in]		bEnable		判定有効フラグ
				@param[in]		bWEnable	書き込み有効フラグ
				@param[in]		fn			比較関数
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetDepthEnable(MofBool bEnable,MofBool bWEnable,ComparisonFunc fn);
		/*************************************************************************//*!
				@brief			深度バッファの設定
				@param[in]		bEnable		有効フラグ
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetDepthEnable(MofBool bEnable);
		/*************************************************************************//*!
				@brief			深度バッファ書き込みの設定
				@param[in]		bEnable		有効フラグ
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetDepthWriteEnable(MofBool bEnable);
		/*************************************************************************//*!
				@brief			深度バッファの設定
				@param[in]		fn			比較関数
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetDepthFunction(ComparisonFunc fn);
		/*************************************************************************//*!
				@brief			ステンシルバッファの設定
				@param[in]		bEnable		有効フラグ
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetStencilEnable(MofBool bEnable);
		/*************************************************************************//*!
				@brief			ステンシルバッファの設定
				@param[in]		ref			設定数値
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetStencilValue(MofU32 ref);
		/*************************************************************************//*!
				@brief			ステンシルバッファの設定
				@param[in]		fn			置き換え比較関数
				@param[in]		PassOp		置き換え比較関数
				@param[in]		ZFailOp		置き換え比較関数
				@param[in]		FailOp		置き換え比較関数
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetStencilControl(ComparisonFunc fn,StencilOp PassOp,StencilOp ZFailOp,StencilOp FailOp);
		/*************************************************************************//*!
				@brief			プリミティブ描画方法設定
				@param[in]		Topology	描画方法
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetTopology(PrimitiveTopology Topology);
		/*************************************************************************//*!
				@brief			塗りつぶし描画方法設定
				@param[in]		Mode		塗りつぶし方法
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetFillMode(FillMode Mode);
		/*************************************************************************//*!
				@brief			カリング方法設定
				@param[in]		Mode		カリング方法
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetCullMode(CullMode Mode);
		/*************************************************************************//*!
				@brief			頂点バッファ設定
				@param[in]		pBuff		頂点バッファ
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetVertexBuffer(LPVertexBuffer pBuff);
		/*************************************************************************//*!
				@brief			頂点バッファ設定
				@param[in]		pBuff1		頂点バッファ
				@param[in]		pBuff2		頂点バッファ
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetVertexBuffer(LPVertexBuffer pBuff1, LPVertexBuffer pBuff2);
		/*************************************************************************//*!
				@brief			頂点レイアウト設定
				@param[in]		pLayout		頂点レイアウト
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetVertexLayout(MofVertexLayout pLayout);
		/*************************************************************************//*!
				@brief			インデックスバッファ設定
				@param[in]		pBuff		インデックスバッファ
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetIndexBuffer(LPIndexBuffer pBuff);
		/*************************************************************************//*!
				@brief			描画ターゲット設定
				@param[in]		pRenderTarget	描画ターゲット
				@param[in]		pDepthTarget	深度ターゲット
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetRenderTarget(LPRenderTarget pRenderTarget, LPDepthTarget pDepthTarget);
		/*************************************************************************//*!
				@brief			描画ターゲット設定
				@param[in]		NumViews		描画ターゲットの数
				@param[in]		ppRenderTarget	描画ターゲット配列へのポインタ
				@param[in]		pDepthTarget	深度ターゲット
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetMultiRenderTarget(MofU32 NumViews,LPRenderTarget* ppRenderTarget,LPDepthTarget pDepthTarget);
		/*************************************************************************//*!
				@brief			描画ターゲット数を変えずに指定した番号の描画ターゲットを差し替える
				@param[in]		index			インデックス
				@param[in]		pRenderTarget	描画ターゲット
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetRenderTargetAt(MofU32 index,LPRenderTarget pRenderTarget);
		/*************************************************************************//*!
				@brief			描画ターゲット数を変えずに指定した番号の描画ターゲットを差し替える
				@param[in]		index			インデックス
				@param[in]		pRenderTarget	描画ターゲット
				@param[in]		pDepthTarget	深度ターゲット
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetRenderTargetAt(MofU32 index,LPRenderTarget pRenderTarget, LPDepthTarget pDepthTarget);
		/*************************************************************************//*!
				@brief			描画ターゲット数設定
				@param			NumViews	描画ターゲット数
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetRenderTargetCount(MofU32 NumViews);

		//----------------------------------------------------------------------------
		////Get
		//----------------------------------------------------------------------------
		/*************************************************************************//*!
				@brief			グラフィックスデバイス取得<br>
								使用しない環境で呼び出した場合NULLを返す。
				@param			None

				@return			グラフィックスデバイス
		*//**************************************************************************/
		virtual MofGraphicsDevice GetDevice(void);
		/*************************************************************************//*!
				@brief			スワップチェイン取得<br>
								使用しない環境で呼び出した場合NULLを返す。
				@param			None

				@return			スワップチェイン
		*//**************************************************************************/
		virtual MofSwapChain GetSwapChain(void);
		/*************************************************************************//*!
				@brief			コンテキスト取得<br>
								使用しない環境で呼び出した場合NULLを返す。
				@param			None

				@return			コンテキスト
		*//**************************************************************************/
		virtual MofDeviceContext GetDeviceContext(void);
		/*************************************************************************//*!
				@brief			サンプラーステート取得<br>
								使用しない環境で呼び出した場合NULLを返す。
				@param			None

				@return			サンプラーステート
		*//**************************************************************************/
		virtual MofSamplerState GetSamplerState(MofU32 s);
		/*************************************************************************//*!
				@brief			ターゲットウインドウの幅取得
				@param			None

				@return			ターゲットウインドウの幅
		*//**************************************************************************/
		virtual MofS32 GetTargetWidth(void);
		/*************************************************************************//*!
				@brief			ターゲットウインドウの高さ取得
				@param			None

				@return			ターゲットウインドウの高さ
		*//**************************************************************************/
		virtual MofS32 GetTargetHeight(void);
		/*************************************************************************//*!
				@brief			対応画面サイズリスト取得設定
				@param[out]		pList		インデックスバッファ
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool GetDisplayModeList(LPDISPLAYMODELIST pList);
		/*************************************************************************//*!
				@brief			設定情報取得
				@param			None
				
				@return			グラフィック設定
		*//**************************************************************************/
		virtual const GRAPHICSSTATUS& GetStatus(void);
		/*************************************************************************//*!
				@brief			現在の描画ターゲット取得
				@param[out]		None
				
				@return			現在の描画ターゲット
		*//**************************************************************************/
		virtual LPRenderTarget GetRenderTarget(void);
		/*************************************************************************//*!
				@brief			指定した番号の描画ターゲット取得
				@param[in]		index		
				
				@return			現在の描画ターゲット
		*//**************************************************************************/
		virtual LPRenderTarget GetRenderTargetAt(MofU32 index);
		/*************************************************************************//*!
				@brief			現在の描画ターゲット数を取得
				@param			None
				
				@return			現在の描画ターゲット数
		*//**************************************************************************/
		virtual MofU32 GetRenderTargetCount(void);
		/*************************************************************************//*!
				@brief			現在の深度ターゲット取得
				@param[out]		None
				
				@return			現在の深度ターゲット
		*//**************************************************************************/
		virtual LPDepthTarget GetDepthTarget(void);
		/*************************************************************************//*!
				@brief			ブレンドステート取得
				@param[out]		None
				
				@return			現在のブレンドステート
		*//**************************************************************************/
		virtual Blending GetBlending(void);

		//クラス基本定義
		MOF_LIBRARYCLASS_NOTCOPY(CGLGraphics,MOF_GLGRAPHICSCLASS_ID);
	};
	
	#include	"GLGraphics.inl"

}

#endif

//[EOF]
