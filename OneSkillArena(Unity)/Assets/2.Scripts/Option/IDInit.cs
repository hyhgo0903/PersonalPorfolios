using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IDInit : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        gameObject.GetComponent<UILabel>().text = "현재 ID : " + GameDataManager.gdm.ID;
    }
}
