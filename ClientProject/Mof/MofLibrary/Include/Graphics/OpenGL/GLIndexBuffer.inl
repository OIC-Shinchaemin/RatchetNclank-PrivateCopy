/*************************************************************************//*!
					
					@file	GLIndexBuffer.inl
					@brief	OpenGLインデックスバッファクラス。

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

/*************************************************************************//*!
		@brief			インデックスバッファ取得
		@param			None

		@return			インデックスバッファの取得
*//**************************************************************************/
FORCE_INLINE MofIndexBuffer CGLIndexBuffer::GetBuffer(void) const{
	return m_Buffer;
}

//[EOF]