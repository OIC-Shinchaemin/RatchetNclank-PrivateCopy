using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class AttackTutorial : MonoBehaviour
{
    GameObject player;
    PlayerController playerController;

    private TextMesh attackTutorial;

    [HideInInspector] public Vector3 defaultScale = Vector3.zero;
    int attackCount = 0;

    void Start()
    {
        player = GameObject.Find("Player");
        this.attackTutorial = this.GetComponent<TextMesh>();

        playerController = player.GetComponent<PlayerController>();

        defaultScale = transform.lossyScale;
    }

    void Update()
    {
        if (playerController.CanAtack == true)
        {
            this.attackTutorial.text = "press Z to attack";

            if (Input.GetButtonDown("Attack"))
            {
                attackCount++;
            }
        }

        Vector2 lossScale = transform.lossyScale;
        Vector2 localScale = transform.localScale;

        transform.localScale = new Vector2(
                localScale.x / lossScale.x * defaultScale.x,
                1);

        if (attackCount >= 3)
        {
            Destroy(gameObject);
        }
    }
}
