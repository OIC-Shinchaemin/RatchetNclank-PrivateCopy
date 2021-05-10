using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
public class ScorePop : MonoBehaviour
{
    Rigidbody2D rb;
    private TextMeshPro Pop;
    private float sec; 
    // Start is called before the first frame update
    void Start()
    {
        Pop = GetComponent<TextMeshPro>();
        rb = GetComponent<Rigidbody2D>();
        if (PermanentUI.perm.scoreValue - PermanentUI.perm.BeforeScore != 0)
        {
            Pop.text = (PermanentUI.perm.scoreValue - PermanentUI.perm.BeforeScore).ToString();
            PermanentUI.perm.BeforeScoreUpdate();
        }
        else if (PermanentUI.perm.PlayerCount - PermanentUI.perm.BeforePlayer == 1) 
        {
            Pop.text = "1UP";
            Pop.color = Color.red;
            PermanentUI.perm.BeforePlayerUpdate();
        }
    }

    // Update is called once per frame
    void Update()
    {
        sec += Time.deltaTime;

        rb.velocity = new Vector2(0, 5);
        if(sec >=0.5)
        {
            Destroy(gameObject);
        }
    }
}
