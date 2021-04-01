using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class CustomizeButton : MonoBehaviour
{
    GameDataManager gdm;
    CustomizeResources cr;
    public GameObject avatar;
    public GameObject statHp;
    public GameObject statMoveSpeed;
    public GameObject statCool;
    public bool isRotate;
    public GameObject rotateButton;

    public GameObject IDLabel;

    void Start()
    {
        gdm = GameDataManager.gdm;
        cr = CustomizeResources.cr;
        isRotate = false;
        Reroll();
    }

    public void StartGame()
    {
        SceneManager.LoadScene(3);
    }

    public void Reroll()
    {
        gdm.playerHp = Random.Range(40, 60);
        statHp.GetComponent<UILabel>().text = "최대체력 : " + gdm.playerHp;

        int temp = Random.Range(15, 26);
        gdm.playerMoveSpeed = (float)temp/10f;
        statMoveSpeed.GetComponent<UILabel>().text = "이동속도 : " + gdm.playerMoveSpeed;

        temp = Random.Range(8, 13);
        gdm.playerDelay = (float)temp / 10f;
        statCool.GetComponent<UILabel>().text = "쿨타임 : " + gdm.playerDelay + "초";
    }

    public void IDupdate()
    {
        gdm.ID = IDLabel.GetComponent<UILabel>().text;
    }

    public void ToggleRotate()
    {
        if (isRotate)
        {
            //rotateButton.GetComponent<UISprite>().spriteName = "CasualUI_6_1";
            rotateButton.GetComponent<UIButton>().normalSprite = "CasualUI_6_1";
            // 버튼있는 스프라이트는 버튼의 디폴트 스프라이트를 바꿔야
            isRotate = false;
        }
        else
        {
            rotateButton.GetComponent<UIButton>().normalSprite = "CasualUI_6_2";
            isRotate = true;
        }
    }

    public void SuperRandomSkin()
    {
        gdm.playerWweaponIndex = Random.Range(0,10);
        avatar.GetComponent<Customize>().SetRightWeapon(gdm.playerWweaponIndex);
        gdm.playerLweaponIndex = Random.Range(0, 10);
        avatar.GetComponent<Customize>().SetLeftWeapon(gdm.playerLweaponIndex);
        gdm.playerChestsIndex = Random.Range(0, 10);
        avatar.GetComponent<Customize>().SetChest(gdm.playerChestsIndex);
        gdm.playerHipsIndex = Random.Range(0, 10);
        avatar.GetComponent<Customize>().SetHip(gdm.playerHipsIndex);
        gdm.playerKneesIndex = Random.Range(0, 10);
        avatar.GetComponent<Customize>().SetKnee(gdm.playerKneesIndex);
        gdm.playerRootsIndex = Random.Range(0, 10);
        avatar.GetComponent<Customize>().SetRoot(gdm.playerRootsIndex);
        gdm.playerSpinesIndex = Random.Range(0, 10);
        avatar.GetComponent<Customize>().SetSpines(gdm.playerSpinesIndex);
        gdm.playerAccessoriesIndex = Random.Range(0, 10);
        gdm.playerHairsIndex = Random.Range(0, 10);
        gdm.playerHeadsIndex = Random.Range(0, 10);
        avatar.GetComponent<Customize>().SetHeadParts(gdm.playerAccessoriesIndex, gdm.playerHairsIndex, gdm.playerHeadsIndex);
        gdm.playerElbowsIndex = Random.Range(0, 9);
        avatar.GetComponent<Customize>().SetElbow(gdm.playerElbowsIndex);
        gdm.playerShouldersIndex = Random.Range(0, 9);
        avatar.GetComponent<Customize>().SetShoulder(gdm.playerShouldersIndex);
    }




    // ############# 파츠 교체 관련 버튼들(스압) #########################


    public void PlusRightWeapon()
    {
        ++gdm.playerWweaponIndex;
        if (gdm.playerWweaponIndex >= cr.weapons.Length)
        {
            gdm.playerWweaponIndex = 0;
        }
        avatar.GetComponent<Customize>().SetRightWeapon(gdm.playerWweaponIndex);
    }
    public void MinusRightWeapon()
    {
        --gdm.playerWweaponIndex;
        if (gdm.playerWweaponIndex < 0)
        {
            gdm.playerWweaponIndex = cr.weapons.Length - 1;
        }
        avatar.GetComponent<Customize>().SetRightWeapon(gdm.playerWweaponIndex);
    }
    public void PlusLeftWeapon()
    {
        ++gdm.playerLweaponIndex;
        if (gdm.playerLweaponIndex >= cr.weapons.Length)
        {
            gdm.playerLweaponIndex = 0;
        }
        avatar.GetComponent<Customize>().SetLeftWeapon(gdm.playerLweaponIndex);
    }
    public void MinusLeftWeapon()
    {
        --gdm.playerLweaponIndex;
        if (gdm.playerLweaponIndex < 0)
        {
            gdm.playerLweaponIndex = cr.weapons.Length - 1;
        }
        avatar.GetComponent<Customize>().SetLeftWeapon(gdm.playerLweaponIndex);
    }

    public void PlusChest()
    {
        ++gdm.playerChestsIndex;
        if (gdm.playerChestsIndex >= cr.chests.Length)
        {
            gdm.playerChestsIndex = 0;
        }
        avatar.GetComponent<Customize>().SetChest(gdm.playerChestsIndex);
    }
    public void MinusChest()
    {
        --gdm.playerChestsIndex;
        if (gdm.playerChestsIndex < 0)
        {
            gdm.playerChestsIndex = cr.chests.Length - 1;
        }
        avatar.GetComponent<Customize>().SetChest(gdm.playerChestsIndex);
    }

    public void PlusElbow()
    {
        ++gdm.playerElbowsIndex;
        if (gdm.playerElbowsIndex >= cr.elbows.Length)
        {
            gdm.playerElbowsIndex = 0;
        }
        avatar.GetComponent<Customize>().SetElbow(gdm.playerElbowsIndex);
    }
    public void MinusElbow()
    {
        --gdm.playerElbowsIndex ;
        if (gdm.playerElbowsIndex < 0)
        {
            gdm.playerElbowsIndex = cr.elbows.Length - 1;
        }
        avatar.GetComponent<Customize>().SetElbow(gdm.playerElbowsIndex);
    }

    public void PlusHip()
    {
        ++gdm.playerHipsIndex;
        if (gdm.playerHipsIndex >= cr.hips.Length)
        {
            gdm.playerHipsIndex = 0;
        }
        avatar.GetComponent<Customize>().SetHip(gdm.playerHipsIndex);
    }
    public void MinusHip()
    {
        --gdm.playerHipsIndex;
        if (gdm.playerHipsIndex < 0)
        {
            gdm.playerHipsIndex = cr.hips.Length - 1;
        }
        avatar.GetComponent<Customize>().SetHip(gdm.playerHipsIndex);
    }
    public void PlusKnee()
    {
        ++gdm.playerKneesIndex;
        if (gdm.playerKneesIndex >= cr.knees.Length)
        {
            gdm.playerKneesIndex = 0;
        }
        avatar.GetComponent<Customize>().SetKnee(gdm.playerKneesIndex);
    }
    public void MinusKnee()
    {
        --gdm.playerKneesIndex;
        if (gdm.playerKneesIndex < 0)
        {
            gdm.playerKneesIndex = cr.knees.Length - 1;
        }
        avatar.GetComponent<Customize>().SetKnee(gdm.playerKneesIndex);
    }
    public void PlusRoot()
    {
        ++gdm.playerRootsIndex;
        if (gdm.playerRootsIndex >= cr.roots.Length)
        {
            gdm.playerRootsIndex = 0;
        }
        avatar.GetComponent<Customize>().SetRoot(gdm.playerRootsIndex);
    }
    public void MinusRoot()
    {
        --gdm.playerRootsIndex;
        if (gdm.playerRootsIndex < 0)
        {
            gdm.playerRootsIndex = cr.roots.Length - 1;
        }
        avatar.GetComponent<Customize>().SetRoot(gdm.playerRootsIndex);
    }
    public void PlusShoulder()
    {
        ++gdm.playerShouldersIndex;
        if (gdm.playerShouldersIndex >= cr.shoulders.Length)
        {
            gdm.playerShouldersIndex = 0;
        }
        avatar.GetComponent<Customize>().SetShoulder(gdm.playerShouldersIndex);
    }
    public void MinusShoulder()
    {
        --gdm.playerShouldersIndex;
        if (gdm.playerShouldersIndex < 0)
        {
            gdm.playerShouldersIndex = cr.shoulders.Length - 1;
        }
        avatar.GetComponent<Customize>().SetShoulder(gdm.playerShouldersIndex);
    }
    public void PlusSpine()
    {
        ++gdm.playerSpinesIndex;
        if (gdm.playerSpinesIndex >= cr.spines.Length)
        {
            gdm.playerSpinesIndex = 0;
        }
        avatar.GetComponent<Customize>().SetSpines(gdm.playerSpinesIndex);
    }
    public void MinusSpine()
    {
        --gdm.playerSpinesIndex;
        if (gdm.playerSpinesIndex < 0)
        {
            gdm.playerSpinesIndex = cr.spines.Length - 1;
        }
        avatar.GetComponent<Customize>().SetSpines(gdm.playerSpinesIndex);
    }


    public void PlusAcce()
    {
        ++gdm.playerAccessoriesIndex;
        if (gdm.playerAccessoriesIndex >= cr.accessories.Length)
        {
            gdm.playerAccessoriesIndex = 0;
        }
        avatar.GetComponent<Customize>().SetHeadParts(gdm.playerAccessoriesIndex, gdm.playerHairsIndex, gdm.playerHeadsIndex);
    }
    public void MinusAcce()
    {
        --gdm.playerAccessoriesIndex;
        if (gdm.playerAccessoriesIndex < 0)
        {
            gdm.playerAccessoriesIndex = cr.accessories.Length - 1;
        }
        avatar.GetComponent<Customize>().SetHeadParts(gdm.playerAccessoriesIndex, gdm.playerHairsIndex, gdm.playerHeadsIndex);
    }
    public void PlusHair()
    {
        ++gdm.playerHairsIndex;
        if (gdm.playerHairsIndex >= cr.hairs.Length)
        {
            gdm.playerHairsIndex = 0;
        }
        avatar.GetComponent<Customize>().SetHeadParts(gdm.playerAccessoriesIndex, gdm.playerHairsIndex, gdm.playerHeadsIndex);
    }
    public void MinusHair()
    {
        --gdm.playerHairsIndex;
        if (gdm.playerHairsIndex < 0)
        {
            gdm.playerHairsIndex = cr.hairs.Length - 1;
        }
        avatar.GetComponent<Customize>().SetHeadParts(gdm.playerAccessoriesIndex, gdm.playerHairsIndex, gdm.playerHeadsIndex);
    }
    public void PlusHead()
    {
        ++gdm.playerHeadsIndex;
        if (gdm.playerHeadsIndex >= cr.heads.Length)
        {
            gdm.playerHeadsIndex = 0;
        }
        avatar.GetComponent<Customize>().SetHeadParts(gdm.playerAccessoriesIndex, gdm.playerHairsIndex, gdm.playerHeadsIndex);
    }
    public void MinusHead()
    {
        --gdm.playerHeadsIndex;
        if (gdm.playerHeadsIndex < 0)
        {
            gdm.playerHeadsIndex = cr.heads.Length - 1;
        }
        avatar.GetComponent<Customize>().SetHeadParts(gdm.playerAccessoriesIndex, gdm.playerHairsIndex, gdm.playerHeadsIndex);
    }

}
