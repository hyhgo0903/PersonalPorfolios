using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class DmgPrefabInit : MonoBehaviour
{
    void Start()
    {
        GetComponent<Text>().text = "" + GameSceneButtonManager.gm.calculatedDamage;
    }
    
}
