using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HpEnemy : MonoBehaviour
{
    protected Animator anim;
    protected AudioSource death;
    protected Rigidbody2D rb;
    
    [SerializeField] private float health = 1;

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "Throw")
        {
            health -= 1;
        }

        if (health == 0)
        {
            anim.SetTrigger("Death");
            death.Play();
            rb.velocity = Vector2.zero;
            rb.bodyType = RigidbodyType2D.Kinematic;
            GetComponent<Collider2D>().enabled = false;

        }
    }

    void Start()
    {
        anim = GetComponent<Animator>();
        death = GetComponent<AudioSource>();
        rb = GetComponent<Rigidbody2D>();
    }

    void Update()
    {
        Debug();
        
    }

    private void Debug()
    {
        UnityEngine.Debug.Log(health);
    }

    public void Death()
    {
        Destroy(this.gameObject);
    }
}
