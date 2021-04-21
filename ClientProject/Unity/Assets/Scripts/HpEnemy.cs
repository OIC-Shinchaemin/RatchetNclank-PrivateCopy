using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class HpEnemy : MonoBehaviour
{
    protected Animator anim;
    protected AudioSource death;
    protected Rigidbody2D rb;


    [SerializeField, Range(1, 50)] private int health = 1;
    [SerializeField] private int getscore = 100;
    [SerializeField] UnityEvent deathEvent;

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "Throw")
        {
            health -= 1;
        }

        if (health == 0)
        {
            EbiScore();
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
        
    }

    public void Death()
    {
        Destroy(this.gameObject);
        deathEvent.Invoke();
    }
    private void EbiScore()
    {
        PermanentUI.perm.scoreValue += getscore;
        ScoreUpdate();
    }
    private void ScoreUpdate()
    {
        PermanentUI.perm.ScoreText.text = PermanentUI.perm.scoreValue.ToString("D7");
    }
}
