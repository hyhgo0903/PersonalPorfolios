using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerMove : MonoBehaviour
{
    
    private Transform player;
    private Transform camPos;
    private Animator anim;
    public GameObject BulletPrefab;
    public GameObject imageEffect;
    public Slider hpSlider;
    float maxDelay;
    float delay;

    CharacterController cc;
    private float moveSpeed;
    private int hp;
    private int maxHp;
    float gravity = 6f;
    float yVelocity = 0;
    bool isJumping = false;

    GameDataManager gdm;

    private void Awake()
    {
        gdm = GameDataManager.gdm;
        // = Resources.Load<Sprite>("SkillIcons/Sword_Skill") as Sprite;
        moveSpeed = gdm.playerMoveSpeed;
        maxHp = gdm.playerHp;
        hp = maxHp;
        maxDelay = gdm.playerDelay;
        delay = 0f;
        player = GameObject.Find("Player").transform;
        anim = GameObject.Find("PlayerAni").GetComponent<Animator>();
        camPos = GameObject.Find("CamPosition").transform;
        cc = player.GetComponent<CharacterController>();
    }

    public void JoyMove(Vector2 v2) // 조이스틱 클래스에서 사용할 예정
    {
        if (hp <= 0 || GameSceneButtonManager.gm.gamePause || GameSceneButtonManager.gm.gameClear) return;
        Vector2 moveInput = v2;
        bool isMove = moveInput.magnitude != 0;
        if (!anim.GetCurrentAnimatorStateInfo(0).IsName("Base Layer.NormalAtk")) anim.SetBool("isMove", isMove);

        if (isMove && !anim.GetCurrentAnimatorStateInfo(0).IsName("Base Layer.NormalAtk"))
        {            
            Vector3 lookForward = new Vector3(camPos.forward.x, 0f, camPos.forward.z).normalized;
            Vector3 lookRight = new Vector3(camPos.right.x, 0f, camPos.right.z).normalized;
            Vector3 moveDir = lookForward * moveInput.y + lookRight * moveInput.x;
            player.forward = lookForward;
            cc.Move(transform.TransformDirection(moveDir.normalized) * Time.deltaTime * moveSpeed);
            camPos.position = player.position;
        }
    }

    public void JoyAngle(Vector2 v2) // 조이스틱 클래스에서 사용할 예정
    {
        if (hp <= 0 || GameSceneButtonManager.gm.gamePause || GameSceneButtonManager.gm.gameClear) return;
        Vector2 mouseDelta = OptionManager.om.getDpi() * v2;
        Vector3 camAngle = camPos.rotation.eulerAngles; 
        float tempAngle = camAngle.x - mouseDelta.y;
        if (tempAngle < 180f)  tempAngle = Mathf.Clamp(tempAngle, -1f, 40);
        else tempAngle = Mathf.Clamp(tempAngle, 335f, 361f);
        camPos.rotation = Quaternion.Euler(tempAngle,
            camAngle.y + mouseDelta.x, camAngle.z);
    }

    public void GetDmg(int damage)
    {
        if (hp <= 0) return;
        hp -= damage;
        if (hp <= 0)
        {
            anim.SetTrigger("GetDead");
            GameSceneButtonManager.gm.OpenRetry();
        }
        StartCoroutine(effectCoroutine());
    }

    IEnumerator effectCoroutine()
    {
        imageEffect.SetActive(true);
        yield return new WaitForSeconds(0.5f);
        imageEffect.SetActive(false);
    }


    public void GetHp(int heal)
    {
        if (hp <= 0) return;
        hp += heal;
        if (hp > maxHp)
        {
            hp = maxHp;
        }
    }

    public float GetDelRatio() { return delay / maxDelay; }

    public void fireButton()
    {
        if (delay > 0 || hp <= 0) return;
        delay = maxDelay;
        anim.SetTrigger("NormAtk");
        BulletManager.bm.PlayerFire();
    }

    void Update()
    {
        if (GameSceneButtonManager.gm.gamePause || GameSceneButtonManager.gm.gameClear) return;

        hpSlider.value = (float)hp / (float)maxHp;
        if (hp <= 0) return;
        if (delay > 0)
        {
            delay -= Time.deltaTime;
        }
        else delay = 0f;

        if (OptionManager.om.getKeyBoardMode())
        { // 키보드입력을 받기로 했을때만 키와 마우스인풋을 받습니다
            if(Input.GetMouseButton(0))
            {
                fireButton();
            }

            if(Input.GetMouseButton(1))
            { //마우스 얼마나 움직였는지
                Vector2 mouseDelta = new Vector2(OptionManager.om.getDpi() * Input.GetAxis("Mouse X"),
                OptionManager.om.getDpi() * Input.GetAxis("Mouse Y"));
                // 캠의 로테이션값을 오일러각으로 변환
                Vector3 camAngle = camPos.rotation.eulerAngles;
                // 새로운 회전값을 카메라 로테이션에 보정
                // 마우스 방향과 바라보는 방향을 일치시키려면 mouseDelta.y를 camAngle.x에서 빼주면 된다.

                float tempX = camAngle.x - mouseDelta.y; // 카메라 위치 제한을 걸기 위해
                                                         // 위쪽으로 회전하는 경우
                if (tempX < 180f) tempX = Mathf.Clamp(tempX, -1f, 40f); // -1인 이유는 수평면 아래로 마우스가 내려가게끔
                                                                        // 아랫쪽으로 회전하는 경우(180~360)
                else tempX = Mathf.Clamp(tempX, 335f, 361f);
                float tempY = camAngle.y + mouseDelta.x;
                // 마우스 좌우 움직임 델타x는 카메라 좌우를 제어해야하기 때문에
                // 마우스 수직 움직임 델타y는 카메라 상하를 제어해야하기 때문에
                camPos.rotation = Quaternion.Euler(tempX, tempY, camAngle.z);
            }       

            Vector2 moveInput = new Vector2(Input.GetAxis("Horizontal"), Input.GetAxis("Vertical"));

            bool isMove = moveInput.magnitude != 0;
            if (!anim.GetCurrentAnimatorStateInfo(0).IsName("Base Layer.NormalAtk")) anim.SetBool("isMove", isMove);

            if (isMove && !anim.GetCurrentAnimatorStateInfo(0).IsName("Base Layer.NormalAtk"))
            {
                Vector3 lookForward = new Vector3(camPos.forward.x, 0f, camPos.forward.z).normalized;
                Vector3 lookRight = new Vector3(camPos.right.x, 0f, camPos.right.z).normalized;
                Vector3 moveDir = lookForward * moveInput.y + lookRight * moveInput.x;
                player.forward = lookForward;
                cc.Move(transform.TransformDirection(moveDir.normalized) * Time.deltaTime * moveSpeed);
            }

        }

        camPos.position = player.position;

        if (cc.collisionFlags == CollisionFlags.Below)
        {
            isJumping = false;
            yVelocity = 0;
        }
        else
        {
            isJumping = true;
            yVelocity -= gravity * Time.deltaTime;
            cc.Move(new Vector3(0, yVelocity, 0) * Time.deltaTime);
        }

        //transform.position += dir * moveSpeed * Time.deltaTime;


    }
}
