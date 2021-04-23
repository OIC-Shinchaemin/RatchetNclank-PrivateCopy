using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Opossum : Enemy
{
    [SerializeField] private float leftCap;
    [SerializeField] private float rightCap;

    [SerializeField] private int moveSpeed = 5;
    private bool facingLeft = true;
    // Start is called before the first frame update
    //protected override void Start()
    //{

    //}


    void Update()
    {

        if (facingLeft)
        {
            if (transform.position.x > leftCap)
            {
                if (transform.localScale.x != 1)
                {
                    transform.localScale = new Vector3(1, 1);
                }
                rb.velocity = new Vector2(-moveSpeed, rb.velocity.y);

            }
            else
            {
                facingLeft = false;
            }

        }
        else
        {
            if (transform.position.x < rightCap)
            {
                if (transform.localScale.x != -1)
                {
                    transform.localScale = new Vector3(-1, 1);
                }
                rb.velocity = new Vector2(moveSpeed, rb.velocity.y);
            }
            else
            {
                facingLeft = true;
            }
        }
    }
}
