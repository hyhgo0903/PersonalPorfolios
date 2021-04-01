using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameSceneButtonManager : MonoBehaviour
{
    public GameObject[] labels;
    public GameObject enemyPrefab;
    public GameObject selectPanel;
    public GameObject[] GenSpots;
    public bool gameClear;
    public bool gamePause = false;
    public GameObject block;
    public int enemyNumbers;
    public GameObject enemyNumbersLabel;
    public GameObject uguiCanvas;
    GameDataManager gdm;
    private int leftIndex;
    private int centerIndex;
    private int rightIndex;
    public int calculatedDamage = 10;


    public UISlider volSlider;
    public UISlider dpiSlider;
    public GameObject optionBox;
    public showMode keyModeLabel;
    public GameObject joystickBack;
    public GameObject angleJoystickBack;

    public GameObject quizPanel;
    public Customize leftPanel;
    public Customize centerPanel;
    public Customize rightPanel;
    private int correctAnswer;

    public AudioClip bossBgm;

    public static GameSceneButtonManager gm = null;
    public static GameSceneButtonManager Instance
    {
        get
        {
            if (null == gm) { return null; }
            return gm;
        }
    }

    public void enemyDeleted()
    {
        --enemyNumbers;
        enemyNumbersLabel.GetComponent<UILabel>().text = "남은 적의 수 : " + enemyNumbers + "명";
        if (enemyNumbers == 1)
        {
            block.SetActive(false);
            enemyNumbersLabel.GetComponent<UILabel>().text = "위로 올라갈 수 있습니다.";
            Camera.main.GetComponent<AudioSource>().Stop();
            Camera.main.GetComponent<AudioSource>().clip = bossBgm;
            Camera.main.GetComponent<AudioSource>().Play();
        }
        if (enemyNumbers <= 0)
        {
            gameClear = true;
        }
    }

    public void blockRegen()
    {
        block.SetActive(true);
        enemyNumbersLabel.GetComponent<UILabel>().text = "끔찍한 시간을 보낼것 같다(내려갈 수 없음)";
    }

    private void Awake()
    {
        if (null == gm)
        {
            gm = this;
        }

        gdm = GameDataManager.gdm;
        enemyNumbers = 1;
        GameObject boss = Instantiate(enemyPrefab);
        boss.transform.position = GenSpots[0].transform.position;
        boss.transform.localScale *= 2f;
        
        for (int j = 1; j < 5; ++j)        
        {
            for (int i = 0; i < gdm.enemyNum; ++i)
            {
                GameObject enemies = Instantiate(enemyPrefab);
                enemies.transform.position = GenSpots[j].transform.position + new Vector3(Random.Range(-3f, 3f), 0, Random.Range(-3f, 3f));
                Vector3 tempVector = new Vector3(0, Random.Range(0, 360f), 0);
                enemies.transform.Rotate(tempVector);                
                ++enemyNumbers;
            }
        }
        enemyNumbersLabel.GetComponent<UILabel>().text = "남은 적의 수 : " + enemyNumbers + "명";
        gameClear = false;
        CloseOption();
    }

    private void Update()
    {
        if (gameClear && gdm.enemyNum != 0)
        {
            SelectSettingQuiz();
        }

    }

    private void SelectSettingQuiz()
    {
        gdm.enemyNum = 0;
        uguiCanvas.SetActive(false);
        quizPanel.SetActive(true);
        correctAnswer = Random.Range(0, 3); // 0,1,2중에
        switch (correctAnswer)
        {
            case 0:
                leftPanel.enemyInit();
                if (Random.Range(0,2) > 0)
                {
                    centerPanel.playerInit();
                    rightPanel.randomInit();
                }
                else
                {
                    centerPanel.randomInit();
                    rightPanel.playerInit();
                }
                break;
            case 1:
                centerPanel.enemyInit();
                if (Random.Range(0, 2) > 0)
                {
                    leftPanel.playerInit();
                    rightPanel.randomInit();
                }
                else
                {
                    leftPanel.randomInit();
                    rightPanel.playerInit();
                }
                break;
            case 2:
                rightPanel.enemyInit();
                if (Random.Range(0, 2) > 0)
                {
                    leftPanel.playerInit();
                    centerPanel.randomInit();
                }
                else
                {
                    leftPanel.randomInit();
                    centerPanel.playerInit();
                }
                break;
        }
    }


    public void QuizLeftButton()
    {
        if (correctAnswer == 0) SelectSettingSkill();
        else SceneManager.LoadScene(3);
    }

    public void QuizCenterButton()
    {
        if (correctAnswer == 1) SelectSettingSkill();
        else SceneManager.LoadScene(3);
    }

    public void QuizRightButton()
    {
        if (correctAnswer == 2) SelectSettingSkill();
        else SceneManager.LoadScene(3);
    }


    private void SelectSettingSkill()
    {
        quizPanel.SetActive(false);
        leftIndex = -1;  centerIndex = -1;  rightIndex = -1;
        selectPanel.SetActive(true);
        // 빈칸이 몇갠지
        List<int> emptyIndex = new List<int>();
        for (int i = 0; i < 8; ++i)
        {
            if (!gdm.itemBox[i])
            {
                emptyIndex.Add(i);
            }
        }
        if (emptyIndex.Count > 0)
        {
            int randIndex = Random.Range(0, emptyIndex.Count);
            leftIndex = emptyIndex[randIndex];
            gdm.itemBox[leftIndex] = true;
            labels[leftIndex].SetActive(true);
            labels[leftIndex].transform.localPosition = new Vector3(-350, 150, 0);
            emptyIndex.RemoveAt(randIndex);
        }
        if (emptyIndex.Count > 0)
        {
            int randIndex = Random.Range(0, emptyIndex.Count);
            centerIndex = emptyIndex[randIndex];
            gdm.itemBox[centerIndex] = true;
            labels[centerIndex].SetActive(true);
            labels[centerIndex].transform.localPosition = new Vector3(0, 150, 0);
            emptyIndex.RemoveAt(randIndex);
        }
        if (emptyIndex.Count > 0)
        {
            int randIndex = Random.Range(0, emptyIndex.Count);
            rightIndex = emptyIndex[randIndex];
            gdm.itemBox[rightIndex] = true;
            labels[rightIndex].SetActive(true);
            labels[rightIndex].transform.localPosition = new Vector3(350, 150, 0);
            emptyIndex.RemoveAt(randIndex);
        }
        emptyIndex.Clear();
        if (leftIndex == -1) SceneManager.LoadScene(3);
    }

    public void SelectLeft()
    {
        if (leftIndex == -1) return;
        if (centerIndex != -1) gdm.itemBox[centerIndex] = false;
        if (rightIndex != -1) gdm.itemBox[rightIndex] = false;
        SceneManager.LoadScene(3);
    }

    public void SelectCenter()
    {
        if (centerIndex == -1) return;
        if (leftIndex != -1) gdm.itemBox[leftIndex] = false;
        if (rightIndex != -1) gdm.itemBox[rightIndex] = false;
        SceneManager.LoadScene(3);
    }

    public void SelectRight()
    {
        if (rightIndex == -1) return;
        if (leftIndex != -1) gdm.itemBox[leftIndex] = false;
        if (centerIndex != -1) gdm.itemBox[centerIndex] = false;
        SceneManager.LoadScene(3);
    }



    public void SaveAndExit()
    {
        JsonManager.jm.Save();
#if UNITY_EDITOR
        UnityEditor.EditorApplication.isPlaying = false;
#elif UNITY_WEBPLAYER
            Application.OpenURL("http://google.com");
#else
            Application.Quit();
#endif
    }

    public void SetVolume()
    {
        AudioListener.volume = volSlider.value;
    }

    public void SetDpi()
    {
        OptionManager.om.dpi = 1f + 4f * dpiSlider.value;
    }

    public void ChangeKeyMode()
    {
        if (OptionManager.om.keyBoardMode) OptionManager.om.keyBoardMode = false;
        else OptionManager.om.keyBoardMode = true;
        keyModeLabel.modeShow();
    }

    public void OpenOption()
    {
        uguiCanvas.SetActive(false);
        gamePause = true;
        optionBox.SetActive(true);
    }

    public void CloseOption()
    {
        uguiCanvas.SetActive(true);
        gamePause = false;
        optionBox.SetActive(false);

        if (OptionManager.om.getKeyBoardMode())
        {
            joystickBack.SetActive(false);
            angleJoystickBack.SetActive(false);
        }
        else
        {
            joystickBack.SetActive(true);
            angleJoystickBack.SetActive(true);
        }
    }

}
