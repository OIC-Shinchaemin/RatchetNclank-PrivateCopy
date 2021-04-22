using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Opossum : Enemy
{

    [SerializeField] private int moveSpeed = 5;
    // Start is called before the first frame update
    //protected override void Start()
    //{
        
    //}

    // Update is called once per frame
    void Update()
    {
        rb.velocity = new Vector2(moveSpeed, rb.velocity.y);
    }
}
