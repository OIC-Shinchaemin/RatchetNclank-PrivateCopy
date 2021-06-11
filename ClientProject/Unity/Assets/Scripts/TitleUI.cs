using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System;
using TMPro;
using YSNet;
public class TitleUI : MonoBehaviour
{
    private int hiscore = 404;
    [SerializeField] TextMeshProUGUI HighScoreText;
    // Start is called before the first frame update
    void Start()
    {
        Action<UserProfileModel> action = (UserProfileModel user) =>
        {
            ScoreLoad();
        };
        ApiConnection.Login(this, action);
    }


    // Update is called once per frame
    private void ScoreLoad()
    {
        //hiscore = PlayerPrefs.GetInt("HighScore", 0);
        Action<ApiRanking.ScoreResponseObject> action = (ApiRanking.ScoreResponseObject re) =>
        {
            hiscore = int.Parse(re.ranking.high_score);

            HighScoreText.text = hiscore.ToString("D7");
        };
        ApiRanking.GetScore(this, action);

        //FileStream f = new FileStream("Assets/ScoreData/Scoretest.txt", FileMode.Open, FileAccess.Read);
        //BinaryReader reader = new BinaryReader(f);

        //if (reader != null)
        //{
        //    hiscore = reader.ReadInt32();
        //    reader.Close();
        //}
    }
}
