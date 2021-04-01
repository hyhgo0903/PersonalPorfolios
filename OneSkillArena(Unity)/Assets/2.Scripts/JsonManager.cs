using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

public class JsonManager : MonoBehaviour
{
    public static JsonManager jm = null;
    public static JsonManager Instance
    {
        get
        {
            if (null == jm) { return null; }
            return jm;
        }
    }

    public void Save() {
        if (!Directory.Exists(Application.dataPath + "/Save"))
            Directory.CreateDirectory(Application.dataPath + "/Save");
        string path = Application.dataPath + "/Save/" + GameDataManager.gdm.ID + ".json";
        File.WriteAllText(path, JsonUtility.ToJson(GameDataManager.gdm));
        //string str = JsonUtility.ToJson(GameDataManager.gdm);
        //GameDataManager data2 = JsonUtility.FromJson<GameDataManager>(str);
    }

    public void Load() {
        string path = Application.dataPath + "/Save/" + GameDataManager.gdm.ID + ".json";
        string str = File.ReadAllText(path);
        GameDataManager.gdm = JsonUtility.FromJson<GameDataManager>(str);
    }

    private void Awake()
    {
        GameDataManager.GetInstance();
        if (null == jm)
        {
            jm = this;
            DontDestroyOnLoad(this.gameObject);
        }
        else
        {
            Destroy(this.gameObject);
        }
    }
}
