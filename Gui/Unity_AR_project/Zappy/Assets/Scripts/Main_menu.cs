using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Main_menu : MonoBehaviour {
    public GameObject host_text;
    public GameObject port_text;
    public GameObject connect_menu;
    public GameObject settings_menu;
    private GameObject instance;
    public GameObject leave_button;
    private string host = "";
    private string port = "";
    void Start() {
        instance = this.gameObject;
        if (host == "" && port == "") {
            setHostText(PlayerPrefs.GetString("Host", ""));
            setPortText(PlayerPrefs.GetString("Port", ""));
        }
    }
    public void setHostText(string value) {
        host_text.GetComponent<UnityEngine.UI.InputField>().text = value;
        host = value;
    }
    public void setPortText(string value) {
        port_text.GetComponent<UnityEngine.UI.InputField>().text = value;
        port = value;
    }
    public void click_connect() {
        string host = host_text.GetComponent<UnityEngine.UI.InputField>().text;
        string port = port_text.GetComponent<UnityEngine.UI.InputField>().text;

        connect_menu.GetComponent<Connect_menu>().setInfos(host, int.Parse(port));
        connect_menu.SetActive(true);
    }
    public void click_settings() {
        host = host_text.GetComponent<UnityEngine.UI.InputField>().text;
        port = port_text.GetComponent<UnityEngine.UI.InputField>().text;
        instance.SetActive(false);
        leave_button.GetComponent<Leave_settings>().main = true;
        settings_menu.SetActive(true);
    }
}
