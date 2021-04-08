using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//using UnityEngine.UI;
using TMPro;

public class PermanentUI : MonoBehaviour
{
    //Player State
    public int cherries = 0;
    public int health;
    public TextMeshProUGUI cherryTaxt;
    public TextMeshProUGUI healthAmount;

    private int defaultHealth;

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

        defaultHealth = health;
    }

    public void Reset()
    {
        cherries = 0;
        health = defaultHealth;
        cherryTaxt.text = cherries.ToString();
    }

    public void GameEnd()
    {
        cherries = 0;
        health = defaultHealth;
        cherryTaxt.text = cherries.ToString();

        Destroy(gameObject);
    }
}
