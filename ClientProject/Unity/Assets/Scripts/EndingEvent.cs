using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;

public class EndingEvent : MonoBehaviour
{
    [SerializeField] private TextMeshProUGUI ClearText;
    [SerializeField] private GameObject ResultController;
    private float second;
    private bool moved = false;
    private void Start()
    {
        PermanentUI.perm.stage.text = "";
        PermanentUI.perm.SceneName.text = "";
    }

    void Update()
    {
        second += Time.deltaTime;
        if (second > 4.5 && !moved)
        {

            second = 0f;
            moved = true;

        }
        else if (moved)
        {
            if (second > 1.0f)
            {
                BGM.bgm.state = BGM.Musicstate.gameend;
                ClearText.text = "Game Clear!!";
            }
            if(second >5f)
            {
                ResultController.SetActive(true);
                ClearText.text = "";
            }
        }
    }

}
