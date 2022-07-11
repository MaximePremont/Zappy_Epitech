using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Window_mode : MonoBehaviour {
    public void changeModeClick() {
        Screen.fullScreen = !Screen.fullScreen;
    }
}
