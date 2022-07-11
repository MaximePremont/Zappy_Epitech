using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Disconnect : MonoBehaviour {
    public GameObject connection_controller;
    public void disconnect() {
        connection_controller.GetComponent<Connection_manager>().disconnect();
        SceneManager.LoadScene("MainScene");
    }
}
