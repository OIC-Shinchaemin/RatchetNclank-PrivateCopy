using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameEnd : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        PermanentUI.perm.GameEnd();
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetButtonUp("Attack"))
        {
            SceneManager.LoadScene("TitleScene");
        }
    }
}
