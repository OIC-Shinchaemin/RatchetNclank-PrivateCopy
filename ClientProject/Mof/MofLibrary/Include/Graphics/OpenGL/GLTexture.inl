/*************************************************************************//*!
					
					@file	GLTexture.inl
					@brief	OpenGLテクスチャ基底クラス。

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

/*************************************************************************//*!
		@brief			テクスチャ取得
		@param			None

		@return			テクスチャ
*//**************************************************************************/
FORCE_INLINE MofTexture CGLTexture::GetTexture(void){
	return m_TexId;
}
/*************************************************************************//*!
		@brief			テクスチャ取得
		@param			None

		@return			テクスチャ
*//**************************************************************************/
FORCE_INLINE MofTextureHandle CGLTexture::GetTextureHandle(void){
	return m_TexId;
}
/*************************************************************************//*!
		@brief			テクスチャへ描画するための描画ターゲットを作成
				
		@return			描画ターゲットを返す。
						失敗の場合NULLになる。
*//**************************************************************************/
FORCE_INLINE LPRenderTarget CGLTexture::GetRenderTarget(void){
	return m_pRenderTarget;
}

//[EOF]
