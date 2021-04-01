using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BillBoard : MonoBehaviour
{
    private Transform target;
    void Update()
    {
        target = Camera.main.transform;
        transform.forward = target.forward;
    }
}
