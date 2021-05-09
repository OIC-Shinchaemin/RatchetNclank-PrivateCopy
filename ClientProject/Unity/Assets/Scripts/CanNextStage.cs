using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CanNextStage : MonoBehaviour
{
    public SceneChange sceneChange;
    private TextMesh textMesh;

    [HideInInspector] public Vector2 defaultScale = Vector2.zero;
    void Start()
    {
        this.textMesh = this.GetComponent<TextMesh>();

        defaultScale = transform.lossyScale;
    }

    // Update is called once per frame
    void Update()
    {
        if (sceneChange.stageChangeable)
        {
            this.textMesh.text = "up arrow to next";
        }
        else
        {
            this.textMesh.text = "";
        }

        Vector2 lossScale = transform.lossyScale;
        Vector2 localScale = transform.localScale;

        transform.localScale = new Vector2(
                localScale.x / lossScale.x * defaultScale.x,
                1);
    }
}
