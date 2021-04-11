using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GhetsisChild : MonoBehaviour
{
    //public Vector2 speed = new Vector2(0.05f, 0.05f);
    float speed = 5f;
    private Vector2 Position;
    void Start()
    {
        
    }

    void Update()
    {

        //gameObject.transform.position = transform.position;
        //transform.Translate(speed, speed, 0);
        float angleDir = transform.eulerAngles.z * (Mathf.PI / 180.0f);
        Vector3 dir = new Vector3(Mathf.Cos(angleDir), Mathf.Sin(angleDir), 0.0f);

        transform.position += dir * speed * Time.deltaTime *-1;
    }

}
