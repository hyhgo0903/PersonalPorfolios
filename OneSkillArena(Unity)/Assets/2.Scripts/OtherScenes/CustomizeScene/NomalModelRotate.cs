using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NomalModelRotate : MonoBehaviour
{

    // Update is called once per frame
    void Update()
    {
        gameObject.transform.Rotate(Time.deltaTime * 60f * Vector3.up);
    }
}
