using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Ghetsis : MonoBehaviour
{
    float speed = 0;
    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        transform.Rotate(0, 0, this.speed);
    }
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "Throw")
        {
            speed += 20;
        }
    }
}