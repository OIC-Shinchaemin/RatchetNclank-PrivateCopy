using System.Collections;
using System.Collections.Generic;

namespace YSNet
{
    public static class ApiCommand
    {
        /// <summary>
        /// 登録処理用エンドポイント
        /// </summary>
        public const string REGISTRATION = "registration";

        /// <summary>
        /// ユーザー名変更処理用エンドポイント
        /// </summary>
        public const string USER_NAME_CHANGE = "username_change";

        /// <summary>
        /// ユーザーデータ取得処理用エンドポイント
        /// </summary>
        public const string USER_DATA_GET = "userdata_get";

        /// <summary>
        /// ランキング取得処理用エンドポイント
        /// </summary>
        public const string RANKING_GET = "ranking_get";

        /// <summary>
        /// ランキング設定処理用エンドポイント
        /// </summary>
        public const string RANKING_SET = "ranking";

        /// <summary>
        /// スコア取得処理用エンドポイント
        /// </summary>
        public const string SCORE_GET = "socre_get";
    }
}