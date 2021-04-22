using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class JumpTurorial : MonoBehaviour
{
    private TextMesh tutorialText;
    void Start()
    {
        this.tutorialText = this.GetComponent<TextMesh>();
        this.tutorialText.text = "press x to jump";
    }

    void Update()
    {
        if (Input.GetButtonDown("Jump"))
        {
            Destroy(gameObject);
        }
    }
}
