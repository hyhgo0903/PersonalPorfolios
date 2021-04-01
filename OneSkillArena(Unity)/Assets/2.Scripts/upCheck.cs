using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class upCheck : MonoBehaviour
{
    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "Player")
        {
            GameSceneButtonManager.gm.blockRegen();
        }
    }
}
