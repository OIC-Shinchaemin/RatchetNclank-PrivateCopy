/*************************************************************************//*!
					
					@file	SoundUtilities.cpp
					@brief	サウンド関連の汎用処理をまとめたスタティッククラス。

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

/*************************************************************************//*!
		@brief			サウンドインターフェイスを設定する
		@param[in]		pg				サウンドインターフェイス

		@return			None
*//**************************************************************************/
FORCE_INLINE void CSoundUtilities::SetSound(LPSound pg){
	m_pSound = pg;
	return;
}
/*************************************************************************//*!
		@brief			サウンドインターフェイスを取得する
		@param			None

		@return			サウンドインターフェイス
*//**************************************************************************/
FORCE_INLINE  LPSound CSoundUtilities::GetSound(void){
	return m_pSound;
}

//[EOF]