using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using TMPro;
public class HalfScene : MonoBehaviour
{
    private int delaytime;

    [SerializeField] private TextMeshProUGUI playerCount;
    [SerializeField] private GameObject GameOver;
    [SerializeField] private TextMeshProUGUI Name;
    private void Start()
    {
        playerCount.text = PermanentUI.perm.PlayerCount.ToString();
        if(PermanentUI.perm.PlayerCount<=0)
        {
            GameOver.SetActive(true);
        }
        Name.text = PermanentUI.perm.nowScene;
        PermanentUI.perm.SceneName.text = PermanentUI.perm.nowScene;
    }
    // Update is called once per frame
    void Update()
    {
        delaytime++;
        if (delaytime > 300)
        {


            if (PermanentUI.perm.PlayerCount <= 0)
            {
                PermanentUI.perm.GameEnd();
                SceneManager.LoadScene("TitleScene");

            }
            else
            {

                SceneManager.LoadScene(PermanentUI.perm.nowScene);

            }



        } 
    }
}
