using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullet : MonoBehaviour
{

    private float activetime;
    // Start is called before the first frame update

    // Update is called once per frame
    void Update()
    {

        activetime += Time.deltaTime;
        if(activetime >=2.0)
        {
            Destroy(this.gameObject);
        }
    }

    private void OnCollisionEnter2D(Collision2D other)
    {
        if (other.gameObject.tag == "Player")
        {
            Destroy(this.gameObject);
        }
    }
}
