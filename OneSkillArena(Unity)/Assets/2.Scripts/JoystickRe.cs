using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class JoystickRe : MonoBehaviour, IPointerDownHandler, IPointerUpHandler, IDragHandler
{
    enum joystickType { Move, Angle }
    [SerializeField] private joystickType joyType;

    [SerializeField] private RectTransform rectBackground;
    [SerializeField] private RectTransform rectJoystick;
    public PlayerMove playerMove;

    private float radius;


    private bool isTouch = false;
    private Vector2 movePosition;

    public void OnDrag(PointerEventData eventData)
    {
        Vector2 value = eventData.position - (Vector2)rectBackground.position;

        value = Vector2.ClampMagnitude(value, radius);
        // value - radius ~ value + radius 범위로 가두기

        rectJoystick.localPosition = value;

        float distance = Vector2.Distance(rectBackground.position, rectJoystick.position)/radius;
        movePosition = value.normalized * distance;

    }

    public void OnPointerDown(PointerEventData eventData)
    {
        isTouch = true;
    }

    public void OnPointerUp(PointerEventData eventData)
    {
        if (joyType == joystickType.Move)
        {
            playerMove.JoyMove(Vector2.zero);
        }
        movePosition = Vector2.zero;
        isTouch = false;
        rectJoystick.localPosition = Vector3.zero;
    }


    // Start is called before the first frame update
    void Start()
    {
        radius = rectBackground.rect.width*0.5f;
    }

    // Update is called once per frame
    void Update()
    {
        if(isTouch)
        {
            switch (joyType)
            {
                case joystickType.Move:
                    if (playerMove)
                    {
                        playerMove.JoyMove(movePosition);
                    }
                    break;
                case joystickType.Angle:
                    if (playerMove)
                    {
                        playerMove.JoyAngle(movePosition);
                    }
                    break;
            }
        }

    }
}
