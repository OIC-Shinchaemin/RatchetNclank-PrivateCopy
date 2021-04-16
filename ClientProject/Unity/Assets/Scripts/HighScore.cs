using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using System.IO;

public class HighScore
{
    public static HighScore hscore;
    private int hiscore;

    void Start()
    {
        FileStream f = new FileStream("Assets/ScoreData/Scoretest.txt", FileMode.Create, FileAccess.Write);
        BinaryWriter writer = new BinaryWriter(f);
        writer.Write("test");
        writer.Close();
    }

    public void ScoreSave()
    {
        FileStream f = new FileStream("Assets/ScoreData/Scoretest.txt", FileMode.Create, FileAccess.Write);
        BinaryWriter writer = new BinaryWriter(f);
        writer.Write(PermanentUI.perm.scoreValue);
        writer.Close();
    }

    public void ScoreLoad()
    {
        FileStream f = new FileStream("Assets/ScoreData/Scoretest.txt", FileMode.Open, FileAccess.Read);
        BinaryReader reader = new BinaryReader(f);

        if (reader != null)
        {
            hiscore = reader.ReadInt32();
            reader.Close();
        }

        if (hiscore < PermanentUI.perm.scoreValue)
        {
            ScoreSave();
        }
    }
}
