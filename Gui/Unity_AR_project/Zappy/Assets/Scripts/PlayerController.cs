using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour {
    public CharacterController controller;
    public Keys_controller k;
    public bool inMenu = false;
    void Update() {
        if (inMenu)
            return;
        float speed = 5;
        float x = 0;
        float z = 0;
        float y = 0;
        if (Input.GetKey(k.getKey("Up").ToLower()))
            z = 1;
        else if (Input.GetKey(k.getKey("Down").ToLower()))
            z = -1;
        if (Input.GetKey(k.getKey("Right").ToLower()))
            x = 1;
        else if (Input.GetKey(k.getKey("Left").ToLower()))
            x = -1;
        if (Input.GetKey(k.getKey("Ascend").ToLower()))
            y = 1;
        else if (Input.GetKey(k.getKey("Descend").ToLower()))
            y = -1;
        Vector3 move = transform.right * x + transform.forward * z + transform.up * y;
        controller.Move(move * speed * Time.unscaledDeltaTime);
    }
}
