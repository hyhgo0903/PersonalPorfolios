using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Customize : MonoBehaviour
{
    public Transform pivotR;
    public Transform pivotL;
    public Transform pivotChest;
    public Transform pivotElbowL; public Transform pivotElbowR;
    public Transform pivotHead;
    public Transform pivotHipL; public Transform pivotHipR;
    public Transform pivotKneeL; public Transform pivotKneeR;
    public Transform pivotShoulderL; public Transform pivotShoulderR;
    public Transform pivotRoot;
    public Transform pivotSpine;
    CustomizeResources cr;
    GameDataManager gdm;

    private void Awake()
    {
        cr = CustomizeResources.cr;
        gdm = GameDataManager.GetInstance();
    }


    void Start()
    {
        if (gameObject.tag == "PlayerModel") playerInit();
        else if (gameObject.tag == "EnemyModel") enemyInit();
    }

    public void playerInit()
    {
        SetRightWeapon(gdm.playerWweaponIndex);
        SetLeftWeapon(gdm.playerLweaponIndex);
        SetChest(gdm.playerChestsIndex);
        SetElbow(gdm.playerElbowsIndex);
        SetHeadParts(gdm.playerAccessoriesIndex, gdm.playerHairsIndex, gdm.playerHeadsIndex);
        SetHip(gdm.playerHipsIndex);
        SetKnee(gdm.playerKneesIndex);
        SetRoot(gdm.playerRootsIndex);
        SetShoulder(gdm.playerShouldersIndex);
        SetSpines(gdm.playerSpinesIndex);
    }

    public void enemyInit()
    {
        SetRightWeapon(gdm.enemyWweaponIndex);
        SetLeftWeapon(gdm.enemyLweaponIndex);
        SetChest(gdm.enemyChestsIndex);
        SetElbow(gdm.enemyElbowsIndex);
        SetHeadParts(gdm.enemyAccessoriesIndex, gdm.enemyHairsIndex, gdm.enemyHeadsIndex);
        SetHip(gdm.enemyHipsIndex);
        SetKnee(gdm.enemyKneesIndex);
        SetRoot(gdm.enemyRootsIndex);
        SetShoulder(gdm.enemyShouldersIndex);
        SetSpines(gdm.enemySpinesIndex);
    }


    public void randomInit()
    {
        SetRightWeapon(Random.Range(0, 10));
        SetLeftWeapon(Random.Range(0, 10));
        SetChest(Random.Range(0, 10));
        SetElbow(Random.Range(0, 9));
        SetHeadParts(Random.Range(0, 10), Random.Range(0, 10), Random.Range(0, 10));
        SetHip(Random.Range(0, 10));
        SetKnee(Random.Range(0, 10));
        SetRoot(Random.Range(0, 10));
        SetShoulder(Random.Range(0, 9));
        SetSpines(Random.Range(0, 10));
    }

    //public void SetLayer13ToAllChildren()
    //{
    //    for (int i = 0; i < transform.childCount; ++i)
    //    {
    //        transform.GetChild(i).gameObject.layer = 13;
    //    }
    //}

    public void SetRightWeapon(int index)
    {
        if (pivotR.childCount>0) Destroy(pivotR.GetChild(0).gameObject);
        GameObject temp = cr.weapons[index];
        Instantiate(temp, pivotR);     
    }
    public void SetLeftWeapon(int index)
    {
        if (pivotL.childCount > 0) Destroy(pivotL.GetChild(0).gameObject);
        GameObject temp = cr.weapons[index];
        Instantiate(temp, pivotL);
    }

    public void SetChest(int index)
    {
        if (pivotChest.childCount > 0) Destroy(pivotChest.GetChild(0).gameObject);
        GameObject temp = cr.chests[index];
        Instantiate(temp, pivotChest);
    }
    public void SetElbow(int index)
    {
        if (pivotElbowL.childCount > 0) Destroy(pivotElbowL.GetChild(0).gameObject);
        if (pivotElbowR.childCount > 0) Destroy(pivotElbowR.GetChild(0).gameObject);
        GameObject temp = cr.elbows[index];
        Instantiate(temp, pivotElbowL);
        Instantiate(temp, pivotElbowR);
    }
    public void SetHeadParts(int index1, int index2, int index3)
    {
        for (int i = 0; i < pivotHead.childCount; i++)
        {
            Destroy(pivotHead.GetChild(i).gameObject);
        }
        GameObject temp = cr.accessories[index1];
        Instantiate(temp, pivotHead);
        temp = cr.hairs[index2];
        Instantiate(temp, pivotHead);
        temp = cr.heads[index3];
        Instantiate(temp, pivotHead);
    }

    public void SetHip(int index)
    {
        if (pivotHipL.childCount > 0) Destroy(pivotHipL.GetChild(0).gameObject);
        if (pivotHipR.childCount > 0) Destroy(pivotHipR.GetChild(0).gameObject);
        GameObject temp = cr.hips[index];
        Instantiate(temp, pivotHipL);
        Instantiate(temp, pivotHipR);
    }
    public void SetKnee(int index)
    {
        if (pivotKneeL.childCount > 0) Destroy(pivotKneeL.GetChild(0).gameObject);
        if (pivotKneeR.childCount > 0) Destroy(pivotKneeR.GetChild(0).gameObject);
        GameObject temp = cr.knees[index];
        Instantiate(temp, pivotKneeL);
        Instantiate(temp, pivotKneeR);
    }
    public void SetRoot(int index)
    {
        if (pivotRoot.childCount > 0) Destroy(pivotRoot.GetChild(0).gameObject);
        GameObject temp = cr.roots[index];
        Instantiate(temp, pivotRoot);
    }
    public void SetShoulder(int index)
    {
        if (pivotShoulderR.childCount > 0) Destroy(pivotShoulderR.GetChild(0).gameObject);
        if (pivotShoulderL.childCount > 0) Destroy(pivotShoulderL.GetChild(0).gameObject);
        GameObject temp = cr.shoulders[index];
        Instantiate(temp, pivotShoulderR);
        Instantiate(temp, pivotShoulderL);
    }
    public void SetSpines(int index)
    {
        if (pivotSpine.childCount > 0) Destroy(pivotSpine.GetChild(0).gameObject);
        GameObject temp = cr.spines[index];
        Instantiate(temp, pivotSpine);
    }
}
