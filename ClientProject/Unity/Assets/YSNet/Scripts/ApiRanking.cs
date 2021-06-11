using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace YSNet
{
    public class ApiRanking
    {
        /// <summary>
        /// RankingModelのJsonデータ展開クラス
        /// </summary>
        [Serializable]
        public class RankingModel
        {
            public string user_id;
            public string high_score;
        }

        /// <summary>
        /// スコア取得レスポンス時のJsonデータ展開クラス
        /// </summary>
        [Serializable]
        public class ScoreResponseObject
        {
            public UserProfileModel user_profile;
            public RankingModel ranking;
        }

        /// <summary>
        /// ランキング取得レスポンス時のJsonデータ展開クラス
        /// </summary>
        [Serializable]
        public class RankingResponseObject
        {
            public RankingModel[] ranking;
        }

        /// <summary>
        /// ランキングの取得
        /// 取得するランキングデータが指定ランキング件数より少ない場合は
        /// 取得できた件数だけを返す
        /// </summary>
        /// <param name="behaviour"></param>
        /// <param name="ranking_cnt">取得するランキング数</param>
        /// <param name="succeedAction">成功時のAction処理  引数に RankingResponseObject型を指定</param>
        /// <param name="failureAction">失敗時のAction処理</param>
        public static void GetRanking(MonoBehaviour behaviour, int ranking_cnt, Action<RankingResponseObject> succeedAction = null, Action failureAction = null)
        {
            behaviour.StartCoroutine(
                ApiConnection.ConnectServer(ApiCommand.RANKING_GET, "?ranking_cnt=" + ranking_cnt,
                (string text) => { succeedAction?.Invoke(JsonUtility.FromJson<RankingResponseObject>(text)); },
                failureAction));
        }

        /// <summary>
        /// スコアの設定
        /// </summary>
        /// <param name="behaviour"></param>
        /// <param name="score">登録するスコアの値</param>
        /// <param name="succeedAction">成功時のAction処理  引数に ScoreResponseObject型を指定</param>
        /// <param name="failureAction">失敗時のAction処理</param>
        public static void SetScore(MonoBehaviour behaviour,uint score, Action<ScoreResponseObject> succeedAction = null, Action failureAction = null)
        {
            behaviour.StartCoroutine(
                ApiConnection.ConnectServer(ApiCommand.RANKING_SET, "?user_id=" + ApiConnection.GetUserId() + "&high_score=" + score,
                (string text) => { succeedAction?.Invoke(JsonUtility.FromJson<ScoreResponseObject>(text)); },
                failureAction));
        }

        /// <summary>
        /// スコアの取得
        /// </summary>
        /// <param name="behaviour"></param>
        /// <param name="succeedAction">成功時のAction処理  引数に ScoreResponseObject型を指定</param>
        /// <param name="failureAction">失敗時のAction処理</param>
        public static void GetScore(MonoBehaviour behaviour, Action<ScoreResponseObject> succeedAction = null, Action failureAction = null)
        {
            behaviour.StartCoroutine(
                ApiConnection.ConnectServer(ApiCommand.SCORE_GET, "?user_id=" + ApiConnection.GetUserId(),
                (string text) => { succeedAction?.Invoke(JsonUtility.FromJson<ScoreResponseObject>(text)); },
                failureAction));
        }
    }
}


