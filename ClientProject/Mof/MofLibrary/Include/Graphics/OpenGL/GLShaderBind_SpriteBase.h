/*************************************************************************//*!
					
					@file	GLShaderBind_SpriteBase.h
					@brief	基本スプライトシェーダーバインド。<br>
							標準的なスプライト描画シェーダーにパラメーターを関連付けるためのクラス。

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

//ONCE
#ifndef		__GLSHADERBIND_SPRITEBASE__H__

#define		__GLSHADERBIND_SPRITEBASE__H__

//INCLUDE
#include	"../ShaderBindBase.h"

namespace Mof {

	/*******************************//*!
	@brief	シェーダーバインド基底インターフェイス

			シェーダーのためのバッファの設定を行うインターフェイス。

	@author	CDW
	*//********************************/
	class MOFLIBRARY_API CGLShaderBind_SpriteBase : public CShaderBindBase {
	public:
		/*******************************//*!
		@brief	スプライト描画入力頂点バッファ列挙

		@author	CDW
		*//********************************/
		enum VertexAttribute
		{
			ATTRIBUTE_POSITION,
			ATTRIBUTE_TEXCOORDS,

			ATTRIBUTE_COUNT,
		};
		/*******************************//*!
		@brief	スプライト描画入力コンスタントバッファ列挙

		@author	CDW
		*//********************************/
		enum ConstParam
		{
			PARAM_SCENE,
			PARAM_MESH,

			PARAM_MAX,
		};
		/*******************************//*!
		@brief	スプライト描画シーン情報入力コンスタントバッファ

		@author	CDW
		*//********************************/
		struct ConstSceneParam
		{
			Matrix44	mtxView;
			Matrix44	mtxProj;
		};
		/*******************//*!
		プリミティブ描画シーン情報設定
		*//********************/
		ConstSceneParam							m_SceneParam;
		/*******************************//*!
		@brief	スプライト描画スプライト情報入力コンスタントバッファ

		@author	CDW
		*//********************************/
		struct ConstMeshParam
		{
			Vector4		cbvOffset;
			Vector4		cbvSize;
			Vector4		cbtOffset;
			Vector4		cbtSize;
			Vector4		cbColor;
			Matrix44	mtxWorld;
		};
		/*******************//*!
		プリミティブ描画プリミティブ情報設定
		*//********************/
		ConstMeshParam							m_MeshParam;
	protected:
		/*******************//*!
		シェーダーID
		*//********************/
		GLuint									m_ShaderID;
		/*******************//*!
		頂点ロケーション
		*//********************/
		GLuint									m_Attribute[ATTRIBUTE_COUNT];
		/*******************//*!
		テクスチャロケーション
		*//********************/
		GLuint									m_TexLocation;
		/*******************//*!
		プリミティブパラメータロケーション
		*//********************/
		GLuint									m_OffsetLocation;
		/*******************//*!
		プリミティブパラメータロケーション
		*//********************/
		GLuint									m_SizeLocation;
		/*******************//*!
		プリミティブパラメータロケーション
		*//********************/
		GLuint									m_TOffsetLocation;
		/*******************//*!
		プリミティブパラメータロケーション
		*//********************/
		GLuint									m_TSizeLocation;
		/*******************//*!
		プリミティブパラメータロケーション
		*//********************/
		GLuint									m_ColorLocation;
		/*******************//*!
		ワールドマトリクスロケーション
		*//********************/
		GLuint									m_WorldLocation;
		/*******************//*!
		ビューマトリクスロケーション
		*//********************/
		GLuint									m_ViewLocation;
		/*******************//*!
		プロジェクションマトリクスロケーション
		*//********************/
		GLuint									m_ProjectionLocation;
	public:
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		CGLShaderBind_SpriteBase();
		/*************************************************************************//*!
				@brief			コピーコンストラクタ
				@param			pObj		コピーシェーダー

				@return			None
		*//**************************************************************************/
		CGLShaderBind_SpriteBase(const CGLShaderBind_SpriteBase& pObj);
		/*************************************************************************//*!
				@brief			デストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		virtual ~CGLShaderBind_SpriteBase();
		
		/*************************************************************************//*!
				@brief			バインダの生成
				@param[in]		pShader		シェーダー
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool Create(LPShader pShader);
		/*************************************************************************//*!
				@brief			バインダの生成
				@param[in]		pvb			頂点バッファ配列
				@param[in]		Cnt			頂点バッファ配列数
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool CreateVertexLayout(LPVertexBuffer* pvb, MofU32 Cnt = 0);

		/*************************************************************************//*!
				@brief			バインドの実行
				@param[in]		pGeom		ジオメトリ
				
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool Bind(LPGeometry pGeom = NULL);

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
				@brief			バッファの設定
				@param[in]		n			番号
					
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetBuffer(MofU32 n);
		/*************************************************************************//*!
				@brief			バッファの設定
				@param[in]		n			番号
				@param[in]		pData		データ
					
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetBuffer(MofU32 n,LPMofVoid pData);
		/*************************************************************************//*!
				@brief			サンプラの設定<br>
								OpenGLで実行時のみ有効<br>
								DirectX9の場合はシェーダーでの指定が、OpenGL系の場合はテクスチャでの指定が有効になる。
				@param[in]		n			番号
				@param[in]		st			サンプラタイプ
					
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetSamplerType(MofU32 n,MofU32 st);
		/*************************************************************************//*!
				@brief			サンプラの設定<br>
								OpenGLで実行時のみ有効<br>
								DirectX9の場合はシェーダーでの指定が、OpenGL系の場合はテクスチャでの指定が有効になる。
				@param[in]		n			番号
				@param[in]		pSamp		サンプラ
					
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetSamplerState(MofU32 n,MofSamplerState pSamp);
		/*************************************************************************//*!
				@brief			テクスチャの設定
				@param[in]		n			番号
				@param[in]		pTex		テクスチャ
					
				@return			TRUE		成功<br>
								それ以外	失敗、エラーコードが戻り値となる
		*//**************************************************************************/
		virtual MofBool SetTexture(MofU32 n,LPTexture pTex);

		/*************************************************************************//*!
				@brief			描画用行列を設定する
				@param[in]		wMat			行列

				@return			None
		*//**************************************************************************/
		virtual void SetWorldMatrix(const Matrix44& wMat);
		/*************************************************************************//*!
				@brief			描画用行列を設定する
				@param[in]		pMotion		モーションコントローラ
				@param[in]		pGeom		ジオメトリ
				
				@return			None
		*//**************************************************************************/
		virtual void SetWorldMatrix(LPMeshMotionController pMotion,LPGeometry pGeom);
		/*************************************************************************//*!
				@brief			描画用マテリアルを設定する
				@param[in]		pMat			マテリアル

				@return			None
		*//**************************************************************************/
		virtual void SetMaterial(LPMaterial pMat);
		/*************************************************************************//*!
				@brief			描画用プリミティブパラメーターを設定する
				@param[in]		pPar			テクスチャパラメーター

				@return			None
		*//**************************************************************************/
		virtual void SetPrimitiveParameter(LPPrimitiveRenderParameter pPar);
		/*************************************************************************//*!
				@brief			描画用テクスチャパラメーターを設定する
				@param[in]		pPar			テクスチャパラメーター

				@return			None
		*//**************************************************************************/
		virtual void SetTextureParameter(LPTextureRenderParameter pPar);
		/*************************************************************************//*!
				@brief			描画用カメラを設定する
				@param[in]		pc				カメラ

				@return			None
		*//**************************************************************************/
		virtual void SetCamera(LPCamera pc);
		/*************************************************************************//*!
				@brief			描画用カメラを設定する
				@param[in]		mv				カメラ
				@param[in]		mp				プロジェクション

				@return			None
		*//**************************************************************************/
		virtual void SetCamera(Matrix44& mv,Matrix44& mp);
		/*************************************************************************//*!
				@brief			描画用基本ライトを設定する
				@param[in]		pl				ライト

				@return			None
		*//**************************************************************************/
		virtual void SetDirectionalLight(LPDirectionalLight pl);
		
		//----------------------------------------------------------------------------
		////Get
		//----------------------------------------------------------------------------
		/*************************************************************************//*!
				@brief			設定パラメーター数を取得する
				@param			None

				@return			パラメーターの数
		*//**************************************************************************/
		virtual MofS32 GetParamCount(void) const { return PARAM_MAX; }

		//クラス基本定義
		MOF_LIBRARYCLASS(CGLShaderBind_SpriteBase,MOF_GLSHADERBINDSPRITEBASECLASS_ID);
	};

	#include	"GLShaderBind_SpriteBase.inl"

	//置き換え
	typedef CGLShaderBind_SpriteBase		CShaderBind_SpriteBase;
	typedef CShaderBind_SpriteBase*			LPShaderBind_SpriteBase;
}

#endif

//[EOF]
