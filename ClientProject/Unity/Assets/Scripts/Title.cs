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
        this.pressA.text = "press the z key";
    }

    void Update()
    {
        if (Input.GetButtonDown("Attack"))
        {
            SceneManager.LoadScene("HalfScene");
        }
    }
}
