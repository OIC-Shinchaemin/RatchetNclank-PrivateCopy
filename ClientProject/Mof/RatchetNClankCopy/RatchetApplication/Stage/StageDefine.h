#pragma once
#define STAGEEDITOR

/// <summary>
/// ステージオブジェクトの種類列挙
/// </summary>
enum class StageObjectType {
    None,              //! 設定なし
    StaticObject,      //! 静的オブジェクト
    EnemySpawnPoint,   //! 敵出現位置
    Elevator,          //! エレベーター
    Bridge,            //! 橋
    MoveCloud_Near,
    MoveCloud_Middle,
    MoveCloud_Far,
    BoxBullet,
    BoxBolt,
    BoxNanotech,
};