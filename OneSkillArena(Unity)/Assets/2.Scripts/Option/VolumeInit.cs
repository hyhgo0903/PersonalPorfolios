using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VolumeInit : MonoBehaviour
{
    void Start()
    {
        GetComponent<UISlider>().value = AudioListener.volume;
    }
}
