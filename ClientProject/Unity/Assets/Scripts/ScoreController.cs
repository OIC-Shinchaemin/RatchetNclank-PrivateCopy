using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScoreController : MonoBehaviour
{
    private int JumpCount;
    public static ScoreController score;
    void Start()
    {
        ScoreUpdate();
    }

    public void ScoreUpdate()
    {
        PermanentUI.perm.ScoreText.text = PermanentUI.perm.scoreValue.ToString("D7");
    }

    public void CherryScore()
    {
        PermanentUI.perm.scoreValue += PermanentUI.perm.cherries * 100;
        ScoreUpdate();
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

    public void EbiScore(int GetScore)
    {
        PermanentUI.perm.scoreValue += GetScore;
        ScoreUpdate();
    }
}
