using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Quit : MonoBehaviour {
    public GameObject connection_controller;
    public void quit() {
        connection_controller.GetComponent<Connection_manager>().disconnect();
        Application.Quit(0);
    }
}
