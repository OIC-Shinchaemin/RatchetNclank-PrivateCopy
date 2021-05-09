using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Lift : MonoBehaviour
{
    //速度
    [SerializeField, Range(0.01f,0.1f)] private float moveSpeed = 0.5f;
    //上限
    [SerializeField] private float topCap;
    //下限
    [SerializeField] private float underCap;
    //左限
    [SerializeField] private float leftCap;
    //右限
    [SerializeField] private float rightCap;


    bool isPlayerRide = false;

    bool Leftmode = false;
    bool Upmode = false;

    [SerializeField] bool playerRideMove = false;
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
        if (playerRideMove == false)
        {
            if (canMoveX)
            {
                MoveX();
            }
            if (canMoveY)
            {
                MoveY();
            }
        }

        if (playerRideMove == true && isPlayerRide == true)
        {
            if (canMoveX)
            {
                MoveX();
            }
            if (canMoveY)
            {
                MoveY();
            }
        }
    }

    private void MoveY()
    {
        if (Upmode)
        {
            transform.Translate(0f, moveSpeed,0f);
        }
        else
        {

            transform.Translate(0f, -moveSpeed, 0f);

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
            if(transform.position.x >leftCap)
            {

                transform.Translate(-moveSpeed, 0f, 0f);
            }
            else
            {
                Leftmode = false;
            }
        }
        else
        {
            if(transform.position.x<rightCap)
            {
                transform.Translate(moveSpeed, 0f, 0f);

            }
            else
            {
                Leftmode = true;
            }

        }

    }

    void OnCollisionEnter2D(Collision2D collision)
    {
        isPlayerRide = true;
    }
}
