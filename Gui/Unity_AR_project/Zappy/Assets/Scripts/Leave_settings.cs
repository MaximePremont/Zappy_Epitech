using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Leave_settings : MonoBehaviour {
    public GameObject settings_menu;
    public GameObject main_menu;
    public GameObject button_sets;
    public bool main = true;
    public PlayerController pc;
    public MouseHandler mh;
    public void click_leave() {
        settings_menu.SetActive(false);
        pc.inMenu = false;
        mh.inMenu = false;
        if (main)
            main_menu.SetActive(true);
        else
            button_sets.SetActive(true);
    }
}
