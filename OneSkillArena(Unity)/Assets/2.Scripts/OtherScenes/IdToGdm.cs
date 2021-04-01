using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IdToGdm : MonoBehaviour
{
    public GameObject label;

    public void submit()
    {
        GameDataManager.gdm.ID = label.GetComponentInChildren<UILabel>().text;
    }

}
