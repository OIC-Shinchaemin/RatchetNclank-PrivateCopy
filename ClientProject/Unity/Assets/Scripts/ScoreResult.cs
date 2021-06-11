using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System;
using TMPro;
using UnityEngine.SceneManagement;
using YSNet;

public class ScoreResult : MonoBehaviour
{
    
    private bool isScoreUpdate = false;
    private int hiscore;
    private float second;

    [SerializeField] private GameObject scoreResult;
    [SerializeField] private TextMeshProUGUI ScoreText;
    [SerializeField] private TextMeshProUGUI HighScoreText;
    [SerializeField] private TextMeshProUGUI NewRecordText;

    void Start()
    {
        Action< UserProfileModel> action = (UserProfileModel user) =>
        {
            ScoreLoad();
        };
        ApiConnection.Login(this, action);

        
    }
    private void Update()
    {
        scoreResult.SetActive(true);
        //second += Time.deltaTime;
        if (Input.GetButtonUp("Attack"))
        {
            BGM.bgm.GameEnd();
            SceneManager.LoadScene("TitleScene");
        }
        if(Input.GetButtonUp("Jump"))
        {
            ResetScore();
        }
        if(/*second >5.0&& */isScoreUpdate)
        {
            HighScoreText.text = PermanentUI.perm.ScoreText.text;
            NewRecordText.text = "NewRecord!!";
        }
    }


    private void ScoreLoad()
    {
        // hiscore = PlayerPrefs.GetInt("HighScore", 0);

        Action<ApiRanking.ScoreResponseObject> action = (ApiRanking.ScoreResponseObject re) =>
        {
            hiscore = int.Parse(re.ranking.high_score);
            ScoreJudge();

            ScoreText.text = PermanentUI.perm.ScoreText.text;
            HighScoreText.text = hiscore.ToString("D7");
            PermanentUI.perm.GameEnd();
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
    private void ResetScore()
    {
        //FileStream f = new FileStream("Assets/ScoreData/Scoretest.txt", FileMode.Create, FileAccess.Write);
        //BinaryWriter writer = new BinaryWriter(f);
        //writer.Write(0);
        //writer.Close();

    }
    private void ScoreJudge()
    {

        if (hiscore < PermanentUI.perm.scoreValue)  //ロードしたスコアよりスコアが高かったらハイスコア書き換え
        {
            isScoreUpdate = true;
            ScoreSave();
        }

    }

    private void ScoreSave()
    {

        // PlayerPrefs.SetInt("HighScore", PermanentUI.perm.scoreValue);
        // PlayerPrefs.Save();

        ApiRanking.SetScore(this, (uint)PermanentUI.perm.scoreValue);
//
        //FileStream f = new FileStream("Assets/ScoreData/Scoretest.txt", FileMode.Create, FileAccess.Write);
        //BinaryWriter writer = new BinaryWriter(f);
        //writer.Write(PermanentUI.perm.scoreValue);
        //writer.Close();
    }
}
