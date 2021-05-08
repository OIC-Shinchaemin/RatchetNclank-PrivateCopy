using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameOver : MonoBehaviour
{
    [SerializeField] private GameObject GOC;
    [SerializeField] private GameObject ResultManager;
    private float sec;
    private bool canresult;
    // Start is called before the first frame update
    void Start()
    {
        BGM.bgm.state = BGM.Musicstate.gameover;
    }

    // Update is called once per frame
    void Update()
    {
        sec += Time.deltaTime;

        if(sec >=2.0f)
        {
            GOC.SetActive(true);
        }
        if (sec>= 5.0f)
        {
            GOC.SetActive(false);
            ResultManager.SetActive(true);
            Destroy(gameObject);
        }

    }
}
