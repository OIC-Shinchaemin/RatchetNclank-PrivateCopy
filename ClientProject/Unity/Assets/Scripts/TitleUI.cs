using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using TMPro;
public class TitleUI : MonoBehaviour
{
    private int hiscore = 404;
    [SerializeField] TextMeshProUGUI HighScoreText;
    // Start is called before the first frame update
    void Start()
    {
        ScoreLoad();
        HighScoreText.text = hiscore.ToString("D7");
    }

    // Update is called once per frame
    private void ScoreLoad()
    {
        FileStream f = new FileStream("Assets/ScoreData/Scoretest.txt", FileMode.Open, FileAccess.Read);
        BinaryReader reader = new BinaryReader(f);

        if (reader != null)
        {
            hiscore = reader.ReadInt32();
            reader.Close();
        }
    }
}
