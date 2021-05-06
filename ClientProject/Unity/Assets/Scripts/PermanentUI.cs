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
    public TextMeshProUGUI cherryTaxt;
    public TextMeshProUGUI healthAmount;
    public TextMeshProUGUI ScoreText;
    public TextMeshProUGUI stage;
    
    public int scoreValue = 0;

    public string nowScene = "1-1";
    public TextMeshProUGUI SceneName;
    public static PermanentUI perm;
    
   
    private void Start()
    {                

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
        PermanentUI.perm.scoreValue += JumpCount * 100;
        ScoreUpdate();
    }
    public void CountReset()
    {
        JumpCount = 0;
    }
}
