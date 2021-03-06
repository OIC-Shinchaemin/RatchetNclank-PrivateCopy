/*************************************************************************//*!
					
					@file	GLShader.inl
					@brief	OpenGLシェーダークラス。

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

/*************************************************************************//*!
		@brief			シェーダーの取得
		@param			None

		@return			シェーダー
*//**************************************************************************/
FORCE_INLINE MofShaderEffect CGLShader::GetShader(void){
	return m_Shader;
}
/*************************************************************************//*!
		@brief			シェーダーの取得
		@param			None

		@return			シェーダー
*//**************************************************************************/
FORCE_INLINE MofVertexShader CGLShader::GetVertexShader(void){
	return m_VertexShader;
}
/*************************************************************************//*!
		@brief			シェーダーの取得
		@param			None

		@return			シェーダー
*//**************************************************************************/
FORCE_INLINE MofPixelShader CGLShader::GetPixelShader(void){
	return m_PixelShader;
}

//[EOF]