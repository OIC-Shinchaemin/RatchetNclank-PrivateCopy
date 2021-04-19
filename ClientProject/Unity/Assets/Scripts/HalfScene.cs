using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
public class HalfScene : MonoBehaviour
{
    int delaytime;


    // Update is called once per frame
    void Update()
    {
        delaytime++;
        if (delaytime > 600)
        {
            SceneManager.LoadScene(PermanentUI.perm.nowScene);




        } 
    }
}
