using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using System.IO;

public class TitleButton : MonoBehaviour
{
    public GameObject InputBox;
    public GameObject ErrorBox;

    public UISlider volSlider;
    public UISlider dpiSlider;
    public GameObject optionBox;
    public showMode keyModeLabel;

    public GameObject[] buttonsToBeMuted;

    public void StartGame(){
        SceneManager.LoadScene(1); // 커마씬으로
    }

    public void LoadGame(){
        InputBox.SetActive(true);        
    }

    public void Submit()
    { //파일경로
        string strFile = Application.dataPath + "/Save/" + GameDataManager.gdm.ID + ".json";
        FileInfo fileInfo = new FileInfo(strFile);
        if (fileInfo.Exists)
        {
            JsonManager.jm.Load();
            SceneManager.LoadScene(2); // 바로 게임씬으로
        }
        else
        {
            InputBox.SetActive(false);
            StartCoroutine(ErrorBoxCoroutine());
        }

    }


    IEnumerator ErrorBoxCoroutine()
    {
        ErrorBox.SetActive(true);
        yield return new WaitForSeconds(3f);
        ErrorBox.SetActive(false);
    }


    public void Exit() {
    #if UNITY_EDITOR
        UnityEditor.EditorApplication.isPlaying = false;
    #elif UNITY_WEBPLAYER
        Application.OpenURL("http://google.com");
    #else
        Application.Quit();
    #endif
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
        optionBox.SetActive(true);
        for (int i = 0; i < buttonsToBeMuted.Length; ++i)
        {
            buttonsToBeMuted[i].GetComponents<UIPlaySound>()[0].volume = 0;
            buttonsToBeMuted[i].GetComponents<UIPlaySound>()[1].volume = 0;
        }
    }

    public void CloseOption()
    {
        optionBox.SetActive(false);
        for (int i = 0; i < buttonsToBeMuted.Length; ++i)
        {
            buttonsToBeMuted[i].GetComponents<UIPlaySound>()[0].volume = 1;
            buttonsToBeMuted[i].GetComponents<UIPlaySound>()[1].volume = 1;
        }
    }
}
