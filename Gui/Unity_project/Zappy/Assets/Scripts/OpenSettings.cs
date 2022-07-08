using UnityEngine;

public class OpenSettings : MonoBehaviour {
    private GameObject instance;
    public GameObject leave_button;
    public GameObject settings_menu;
    public PlayerController pc;
    public MouseHandler mh;
    void Start() {
        instance = this.gameObject;
    }
    public void click_settings() {
        instance.SetActive(false);
        leave_button.GetComponent<Leave_settings>().main = false;
        settings_menu.SetActive(true);
        pc.inMenu = true;
        mh.inMenu = true;
    }
}
