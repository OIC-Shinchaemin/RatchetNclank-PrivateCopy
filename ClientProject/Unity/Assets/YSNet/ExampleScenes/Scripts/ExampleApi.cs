using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using YSNet;

public class ExampleApi : MonoBehaviour
{

    /// <summary>
    /// ユーザーID表示テキスト
    /// </summary>
    [SerializeField]
    Text userID;

    /// <summary>
    /// ユーザー名表示テキスト
    /// </summary>
    [SerializeField]
    Text userName;

    /// <summary>
    /// スコア表示テキスト
    /// </summary>
    [SerializeField]
    Text scoreText;

    /// <summary>
    /// ユーザー名入力ボックス
    /// </summary>
    [SerializeField]
    InputField userNameInput;

    /// <summary>
    /// スコア入力ボックス
    /// </summary>
    [SerializeField]
    InputField scoreInput;

    void Start()
    {
        ApiConnection.Login(this,
            (UserProfileModel user) =>
            {
                Debug.Log("Login Succeed UserId : " + user.user_id + " / UserName" + user.user_name);
                userID.text = "User ID :" + user.user_id;
                userName.text = "User Name :" + user.user_name;
            },
            () =>
            {
                Debug.Log("Login Failed");
            }
            );
    }

    /// <summary>
    /// ユーザーネーム変更処理
    /// </summary>
    public void OnChangeName()
    {
        ApiConnection.ChangeUserName(this, userNameInput.text,
            (UserProfileModel user) =>
            {
                Debug.Log("ChangeUserName Succeed UserId : " + user.user_id + " / UserName" + user.user_name);
                userID.text = "User ID :" + user.user_id;
                userName.text = "User Name :" + user.user_name;
            },
            () =>
            {
                Debug.Log("ChangeUserName Failed");
            }
            );
    }

    /// <summary>
    /// ユーザー登録処理
    /// </summary>
    public void OnRegistration()
    {
        ApiConnection.Registration(this,
            (UserProfileModel user) =>
            {
                Debug.Log("Registration Succeed UserId : " + user.user_id + " / UserName" + user.user_name);
                userID.text = "User ID :" + user.user_id;
                userName.text = "User Name :" + user.user_name;
            },
            () =>
            {
                Debug.Log("Registration Failed");
            }
            );
    }

    /// <summary>
    /// スコア設定処理
    /// </summary>
    public void OnSetScore()
    {
        ApiRanking.SetScore(this, uint.Parse(scoreInput.text),
            (ApiRanking.ScoreResponseObject re) =>
            {
                Debug.Log("SetScore Succeed UserId : " + re.user_profile.user_id + " / UserName" + re.user_profile.user_name + " / Score" + re.ranking.high_score);
                scoreText.text = "Score :" + re.ranking.high_score.ToString();
            },
            () =>
            {
                Debug.Log("SetScore Failed");
            }
            );
    }

    /// <summary>
    /// ランキング表示処理
    /// </summary>
    public void OnRankingShow()
    {
        ApiRanking.GetRanking(this, 10,
            (ApiRanking.RankingResponseObject re) =>
            {
                Debug.Log("GetRanking Succeed");
                for (int i = 0; i < re.ranking.Length; i++)
                {
                    int no = i + 1;
                    GameObject TextObj = GameObject.Find("Text" + no);
                    Text txt = TextObj.GetComponent<Text>();
                    txt.text = no + "位：" + re.ranking[i].high_score;
                }
            },
            () =>
            {
                Debug.Log("GetRanking Failed");
            }
            );
    }
}
