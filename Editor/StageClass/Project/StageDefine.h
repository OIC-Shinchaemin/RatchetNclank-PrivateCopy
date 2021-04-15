#pragma once

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
enum StageFileChank {
    StageFileChank_
};

/// <summary>
/// ステージファイル解析結果列挙
/// </summary>
enum StageFileResult {
    StageFileResult_Error_Unknown = 0,    //! よくわからないエラー
    StageFileResult_Success       = TRUE, //! 正常終了
    StageFileResult_Error_Open,           //! ファイルオープン失敗
    StageFileResult_Error_MeshLoad,       //! メッシュ読み込み失敗
};

/// <summary>
/// ステージオブジェクトの種類列挙
/// </summary>
enum StageObjectType {
    StageObjectType_None,              //! 設定なし
    StageObjectType_StaticObject,      //! 静的オブジェクト
    StageObjectType_EnemySpawnPoint,   //! 敵出現位置
};