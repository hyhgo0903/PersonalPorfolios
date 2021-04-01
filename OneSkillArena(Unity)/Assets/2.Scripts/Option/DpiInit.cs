using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DpiInit : MonoBehaviour
{
    void Start()
    {
        GetComponent<UISlider>().value = OptionManager.om.getDpi() / 5f;
    }
}
