#pragma once
#define TRUE 1

//! 独自ヘッダ
#define STAGE_FILE_HEADER     "STAGE_FILE_VER_0.01_FILE"

//! 独自ヘッダ長
#define STAGE_FILE_HEADER_LEN strlen(STAGE_FILE_HEADER)

//! 独自フッタ
#define STAGE_FILE_FOOTER     "EOF"

//! 独自フッタ長
#define STAGE_FILE_FOOTER_LEN strlen(STAGE_FILE_FOOTER)

/// <summary>
/// ステージファイル内のチャンク情報タイプ列挙
/// </summary>
enum class StageFileChank {
};

/// <summary>
/// ステージファイル解析結果列挙
/// </summary>
enum class StageFileResult : int {
    Error_Unknown = 0,    //! よくわからないエラー
    Success       = TRUE, //! 正常終了
    Error_Open,           //! ファイルオープン失敗
    Error_MeshLoad,       //! メッシュ読み込み失敗
};
