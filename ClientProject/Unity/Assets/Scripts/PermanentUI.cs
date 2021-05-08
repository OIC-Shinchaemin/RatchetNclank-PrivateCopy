using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//using UnityEngine.UI;
using TMPro;

public class PermanentUI : MonoBehaviour
{
    private const int MaxHP = 3;

    //Player State
    private int JumpCount;
    public int cherries = 0;
    public int currentHP = 0;
    public int PlayerCount = 3;
    public int BeforeScore = 0;
    public int BeforePlayer = 3;
    public TextMeshProUGUI cherryTaxt;
    public TextMeshProUGUI healthAmount;
    public TextMeshProUGUI ScoreText;
    public TextMeshProUGUI stage;
    private AudioSource UP;
    public int scoreValue = 0;

    public string nowScene = "1-1";
    public TextMeshProUGUI SceneName;
    public static PermanentUI perm;
    
   
    private void Start()
    {
        UP = GetComponent<AudioSource>();
        DontDestroyOnLoad(gameObject);
        //前のシーンにpermUIがなければ
        if (!perm)
        {
            //自身を登録
            perm = this;
        }
        else
        {
            //すでに前のシーンの物があるので死ぬ
            Destroy(gameObject);
        }


        currentHP = MaxHP;
        healthAmount.text = currentHP.ToString();
    }

    public void Reset()
    {
        cherries = 0;
        currentHP = MaxHP;

        cherryTaxt.text = cherries.ToString();
        healthAmount.text = currentHP.ToString();
    }


    public void GameEnd()
    {
        Reset();
        ScoreText.text = scoreValue.ToString("D7");

        Destroy(gameObject);
    }
    public void CherryScore()       
    {
        scoreValue += 100+(cherries / 5) * 100;
        ScoreUpdate();
    }
    public void ScoreUpdate()
    {
        PermanentUI.perm.ScoreText.text = PermanentUI.perm.scoreValue.ToString("D7");
    }
    public void EnemyScore()
    {
        JumpCount++;
        if (JumpCount > 8)
        {
            JumpCount = 8;
        }
        switch(JumpCount)
        {
            case 1:
                PermanentUI.perm.scoreValue += 100;
                break;
            case 2:
                PermanentUI.perm.scoreValue += 200;
                break;
            case 3:
                PermanentUI.perm.scoreValue += 400;
                break;
            case 4:
                PermanentUI.perm.scoreValue += 800;
                break;
            case 5:
                PermanentUI.perm.scoreValue += 2000;
                break;
            case 6:
                PermanentUI.perm.scoreValue += 4000;
                break;
            case 7:
                PermanentUI.perm.scoreValue += 8000;
                break;
            case 8:
                UP.Play();
                PermanentUI.perm.PlayerCount += 1;
                break;

        }
        //PermanentUI.perm.scoreValue += JumpCount * 100;
        ScoreUpdate();
    }
    public void CountReset()
    {
        JumpCount = 0;
    }
    public void BeforeScoreUpdate()
    {
        BeforeScore = scoreValue;
    }
    public void BeforePlayerUpdate()
    {
        BeforePlayer = PlayerCount;
    }
}
