using System.Collections;
using UnityEngine;

public class Connect_menu : MonoBehaviour {
    public GameObject connection_controller;
    private string host;
    private int port;
    public GameObject main_menu;
    public GameObject disconnect_button;
    public GameObject menu_island;

    public GameObject connecting_text;
    public GameObject map_text;
    public GameObject teams_text;
    public GameObject time_text;
    public GameObject pls_text;
    private GameObject instance;
    public GameObject user;
    public GameObject maincam;
    public GameObject settings_buttons;
    private ArrayList validations = new ArrayList();
    public AudioSource sound;
    public AudioSource menuMusic;
    public AudioSource gameMusic;
    public GameObject broeadcast_panel;
    public GameObject game_menu;
    public void setInfos(string myhost, int myport) {
        host = myhost;
        port = myport;
    }

    void Start() {
        instance = this.gameObject;
        connection_controller.SetActive(true);
        main_menu.SetActive(false);
        StartCoroutine(connectCoroutine());
    }
    IEnumerator connectCoroutine() {
        yield return new WaitForSeconds(1f);
        if (!connection_controller.GetComponent<Connection_manager>().connect(host, port)) {
            StartCoroutine(connectCoroutine());
        } else {
            PlayerPrefs.SetString("Host", host);
            PlayerPrefs.SetString("Port", port+"");
            PlayerPrefs.Save();
            connecting_text.GetComponent<Loading_text>().validate();
            menu_island.SetActive(false);
            connection_controller.GetComponent<Connection_manager>().send("GUI");
            connection_controller.GetComponent<Connection_manager>().send("msz");
        }
    }
    public void validateMsz() {
        if (validations.Contains("msz"))
            return;
        map_text.GetComponent<Loading_text>().validate();
        validations.Add("msz");
        connection_controller.GetComponent<Connection_manager>().send("tna");
        finalValidation();
    }
    public void validateTna() {
        if (validations.Contains("tna"))
            return;
        validations.Add("tna");
        teams_text.GetComponent<Loading_text>().validate();
        connection_controller.GetComponent<Connection_manager>().send("sgt");
        finalValidation();
    }
    public void validateSgt() {
        if (validations.Contains("sgt"))
            return;
        validations.Add("sgt");
        time_text.GetComponent<Loading_text>().validate();
        connection_controller.GetComponent<Connection_manager>().send("pls");
        finalValidation();
    }
    public void validatePls() {
        if (validations.Contains("pls"))
            return;
        validations.Add("pls");
        pls_text.GetComponent<Loading_text>().validate();
        finalValidation();
    }
    private void finalValidation() {
        if (validations.Count < 4)
            return;
        connection_controller.GetComponent<Connection_manager>().send("mct");
        disconnect_button.SetActive(true);
        instance.SetActive(false);
        settings_buttons.SetActive(true);
        broeadcast_panel.SetActive(true);
        user.GetComponent<PlayerController>().enabled = true;
        maincam.GetComponent<MouseHandler>().enabled = true;
        sound.Play();
        menuMusic.Stop();
        gameMusic.Play();
        game_menu.SetActive(true);
    }
}
