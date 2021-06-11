using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

namespace YSNet
{
    public static class ApiConnection
    {
        /// <summary>
        /// レスポンス時のJsonデータ展開クラス
        /// </summary>
        [Serializable]
        public class ResponseObjects
        {
            public UserProfileModel user_profile;
        }

        /// <summary>
        /// 接続状態の列挙
        /// </summary>
        public enum StatusConnect
        {
            NONE,
            ERROR,      //エラー
            CONNECT     //接続
        };

        private static string userID = null;
        private static StatusConnect ConectStatus = StatusConnect.NONE;
        private static bool login = false;

        /// <summary>
        /// サーバーへの接続
        /// </summary>
        /// <param name="endpoint">操作をしたいエンドポイント</param>
        /// <param name="paramater">操作する処理に必要なパラメータ</param>
        /// <param name="succeedAction">成功時のAction処理  引数に string型を指定</param>
        /// <param name="failureAction">失敗時のAction処理</param>
        /// <returns></returns>
        public static IEnumerator ConnectServer(string endpoint, string paramater, Action<string> succeedAction = null, Action failureAction = null)
        {
            UnityEngine.Debug.Log(YSNetConfigs.URL + endpoint + paramater);
            //WebRquest送信
            UnityWebRequest WebRquest = UnityWebRequest.Get(YSNetConfigs.URL + endpoint + paramater);
            yield return WebRquest.SendWebRequest();

            //結果の成否によりActionを実行
            if (!string.IsNullOrEmpty(WebRquest.error))
            {
                UnityEngine.Debug.LogError(WebRquest.error);
                ConectStatus = StatusConnect.ERROR;
                failureAction?.Invoke();
            }
            else
            {
                ConectStatus = StatusConnect.CONNECT;
                string text = WebRquest.downloadHandler.text;
                succeedAction?.Invoke(text);
            }
        }

        /// <summary>
        /// サーバーへのログインする
        /// </summary>
        /// <param name="behaviour"></param>
        /// <param name="succeedAction">成功時のAction処理  引数に UserProfileModel型を指定</param>
        /// <param name="failureAction">失敗時のAction処理</param>
        public static void Login(MonoBehaviour behaviour, Action<UserProfileModel> succeedAction = null, Action failureAction = null)
        {
            ConectStatus = StatusConnect.NONE;
            userID = PlayerPrefs.GetString("YSNet_User_Id", null);
            if (userID == null || userID == "")
            {
                Registration(behaviour, succeedAction, failureAction);
            }
            else
            {
                GetUserData(behaviour, 
                    (UserProfileModel model) => {
                        login = true;
                        succeedAction?.Invoke(model);
                    },
                    () => {
                        login = false;
                        failureAction?.Invoke();
                    });
            }
        }

        /// <summary>
        /// ユーザー登録
        /// </summary>
        /// <param name="behaviour"></param>
        /// <param name="succeedAction">成功時のAction処理  引数に UserProfileModel型を指定</param>
        /// <param name="failureAction">失敗時のAction処理</param>
        public static void Registration(MonoBehaviour behaviour, Action<UserProfileModel> succeedAction = null, Action failureAction = null)
        {
            Action<string> saction = (string text) =>
            {
                login = true;
                ResponseObjects obj = JsonUtility.FromJson<ResponseObjects>(text);
                userID = obj.user_profile.user_id;
                PlayerPrefs.SetString("YSNet_User_Id", userID);
                succeedAction?.Invoke(obj.user_profile);
            };
            Action faction = () =>
            {
                login = false;
                failureAction?.Invoke();
            };
            behaviour.StartCoroutine(
                ConnectServer(ApiCommand.REGISTRATION, "", saction, faction));
        }

        /// <summary>
        /// ユーザー名の変更
        /// </summary>
        /// <param name="behaviour"></param>
        /// <param name="user_name">変更するユーザー名</param>
        /// <param name="succeedAction">成功時のAction処理  引数に UserProfileModel型を指定</param>
        /// <param name="failureAction">失敗時のAction処理</param>
        public static void ChangeUserName(MonoBehaviour behaviour, string user_name, Action<UserProfileModel> succeedAction = null, Action failureAction = null)
        {
            behaviour.StartCoroutine(
                ApiConnection.ConnectServer(ApiCommand.USER_NAME_CHANGE, "?user_id=" + userID + "&user_name=" + user_name,
                (string text) => { succeedAction?.Invoke(JsonUtility.FromJson<ResponseObjects>(text).user_profile); },
                failureAction));
        }

        /// <summary>
        /// ユーザーデータの取得
        /// </summary>
        /// <param name="behaviour"></param>
        /// <param name="succeedAction">成功時のAction処理  引数に UserProfileModel型を指定</param>
        /// <param name="failureAction">失敗時のAction処理</param>
        public static void GetUserData(MonoBehaviour behaviour, Action<UserProfileModel> succeedAction = null, Action failureAction = null)
        {
            behaviour.StartCoroutine(
                ApiConnection.ConnectServer(ApiCommand.USER_DATA_GET, "?user_id=" + userID,
                (string text) => { succeedAction?.Invoke(JsonUtility.FromJson<ResponseObjects>(text).user_profile); },
                failureAction));
        }

        /// <summary>
        /// 接続してるか否か
        /// </summary>
        /// <returns>
        /// ConnectStatusがStatusConnect.CONNECTの場合：TRUE
        /// それ以外:FALSE
        /// </returns>
        public static bool IsConnect()
        {
            return ConectStatus == StatusConnect.CONNECT;
        }

        /// <summary>
        /// 接続ステータスの取得
        /// </summary>
        /// <returns>
        /// 
        /// </returns>
        public static StatusConnect GetConnectStatus()
        {
            return ConectStatus;
        }

        /// <summary>
        /// ログインしているか否か
        /// </summary>
        /// <returns>
        /// ログインに成功の場合：TRUE
        /// </returns>
        public static bool IsLogin()
        {
            return login;
        }

        /// <summary>
        /// ユーザーIDの取得
        /// </summary>
        /// <returns>
        /// 登録されているユーザーID
        /// ユーザーIDが登録されていない場合 null
        /// </returns>
        public static string GetUserId()
        {
            if (userID == null)
            {
                userID = PlayerPrefs.GetString("YSNet_User_Id", null);
            }
            return userID;
        }
    }
}