using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneChange : MonoBehaviour
{
    [SerializeField] private string sceneName;
    [HideInInspector] public bool stageChangeable = false;

    private void Update()
    {
        if (stageChangeable == true)
            if (Input.GetKeyDown(KeyCode.UpArrow) || Input.GetKeyDown(KeyCode.W))
            {

                if (sceneName == "EndScene")
                {
                    SceneManager.LoadScene("EndScene");
                }
                else
                {
                    PermanentUI.perm.nowScene = sceneName;
                    PermanentUI.perm.SceneName.text = sceneName;
                    SceneManager.LoadScene("HalfScene");
                }      
            }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "Player")
        {
            stageChangeable = true;
        }
    }
    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "Player")
        {
            stageChangeable = false;
        }
    }
}
