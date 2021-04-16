using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GhetsisChild : MonoBehaviour
{
    //private Collider2D coll;

    float speed = 5f;
    private Vector2 Position;
    void Start()
    {
        
    }

    void Update()
    {
        float angleDir = transform.eulerAngles.z * (Mathf.PI / 180.0f);
        Vector3 dir = new Vector3(Mathf.Cos(angleDir), Mathf.Sin(angleDir), 0.0f);

        transform.position += dir * speed * Time.deltaTime *-1;
    }

    void OnTriggerEnter2D(Collider2D collider)
    {
        Debug.Log("すゲーチス");
        Destroy(gameObject);
    }

}
