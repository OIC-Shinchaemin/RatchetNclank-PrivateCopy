using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Lift : MonoBehaviour
{
    //速度
    [SerializeField] private float moveSpeed = 5;
    //上限
    [SerializeField] private float topCap;
    //下限
    [SerializeField] private float underCap;
    //左限
    [SerializeField] private float leftCap;
    //右限
    [SerializeField] private float rightCap;




    [SerializeField] bool Leftmode = false;
    [SerializeField] bool Upmode = false;

    [SerializeField] bool canMoveX = false;
    [SerializeField] bool canMoveY = true;

    private Rigidbody2D rb;
    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody2D>();
    }

    // Update is called once per frame
    private void Update()
    {
        if(canMoveX)
        {
            MoveX();
        }
        if (canMoveY)
        {
            MoveY();
        }
        
    }

    private void MoveY()
    {
        if (Upmode)
        {
            rb.velocity = new Vector2(0, moveSpeed);
        }
        else
        {

            rb.velocity = new Vector2(0, -moveSpeed);

        }
        if (transform.position.y > topCap)
        {
            Upmode = false;
        }
        else if (transform.position.y < underCap)
        {
            Upmode = true;
        }

    }
    private void MoveX()
    {
        if (Leftmode)
        {
            rb.velocity = new Vector2(-moveSpeed,0);
        }
        else
        {

            rb.velocity = new Vector2( moveSpeed,0);

        }
        if (transform.position.x < rightCap)
        {
            Leftmode = false;
        }
        else if (transform.position.x > leftCap)
        {
            Leftmode = true;
        }
    }


}
