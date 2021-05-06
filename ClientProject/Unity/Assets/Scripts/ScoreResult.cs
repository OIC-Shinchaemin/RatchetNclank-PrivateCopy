using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using TMPro;
using UnityEngine.SceneManagement;
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
        
        ScoreLoad();
        ScoreJudge();
        ScoreText.text = PermanentUI.perm.ScoreText.text;
        HighScoreText.text = hiscore.ToString("D7");
        PermanentUI.perm.GameEnd();
    }
    private void Update()
    {
        scoreResult.SetActive(true);
        second += Time.deltaTime;
        if (Input.GetButtonUp("Attack"))
        {
            SceneManager.LoadScene("TitleScene");
        }
        if(Input.GetButtonUp("Jump"))
        {
            ResetScore();
        }
        if(second >2.0&& isScoreUpdate)
        {
            HighScoreText.text = PermanentUI.perm.ScoreText.text;
            NewRecordText.text = "NewRecord!!";
        }
    }


    private void ScoreLoad()
    {
        FileStream f = new FileStream("Assets/ScoreData/Scoretest.txt", FileMode.Open, FileAccess.Read);
        BinaryReader reader = new BinaryReader(f);

        if (reader != null)
        {
            hiscore = reader.ReadInt32();
            reader.Close();
        }
    }
    private void ResetScore()
    {
        FileStream f = new FileStream("Assets/ScoreData/Scoretest.txt", FileMode.Create, FileAccess.Write);
        BinaryWriter writer = new BinaryWriter(f);
        writer.Write(0);
        writer.Close();

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
        FileStream f = new FileStream("Assets/ScoreData/Scoretest.txt", FileMode.Create, FileAccess.Write);
        BinaryWriter writer = new BinaryWriter(f);
        writer.Write(PermanentUI.perm.scoreValue);
        writer.Close();
    }
}
