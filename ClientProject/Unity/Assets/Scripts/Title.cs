using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;


public class Title : MonoBehaviour
{
    private Text pressA;
    void Start()
    {
        this.pressA = this.GetComponent<Text>();
        this.pressA.text = "press [z] key";
    }

    void Update()
    {
        if (Input.GetButtonDown("Attack"))
        {
            BGM.bgm.state = BGM.Musicstate.stop;
            SceneManager.LoadScene("HalfScene");
        }
    }
}
