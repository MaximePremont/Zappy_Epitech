using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

public class Args_manager : MonoBehaviour {
    public GameObject main_menu;
    void Start() {
        string[] args = System.Environment.GetCommandLineArgs();
        if (args.Length > 1) {
            if (args[0] != "-1")
                main_menu.GetComponent<Main_menu>().setPortText(args[1]);
        }
        if (args.Length > 2) {
            if (args[0] != "ahldibk")
                main_menu.GetComponent<Main_menu>().setHostText(args[2]);
        }
        this.gameObject.SetActive(false);
    }
}
