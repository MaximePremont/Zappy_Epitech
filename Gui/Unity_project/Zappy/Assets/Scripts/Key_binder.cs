using UnityEngine;

public class Key_binder : MonoBehaviour {
    public string action = "";
    public GameObject keys_controller;
    public GameObject key_change_text;
    private bool binding = false;
    public AudioSource sound;
    void Start() {
        this.transform.GetChild(0).gameObject.GetComponent<UnityEngine.UI.Text>().text = keys_controller.GetComponent<Keys_controller>().getKey(action);
    }
    public void click_change() {
        if (binding)
            return;
        binding = true;
        key_change_text.SetActive(true);
    }
    void Update() {
        if (!binding || !Input.anyKeyDown)
            return;
        string key = Input.inputString;
        if (key.Length < 1)
            return;
        key = key.ToUpper();
        this.transform.GetChild(0).gameObject.GetComponent<UnityEngine.UI.Text>().text = key;
        binding = false;
        key_change_text.SetActive(false);
        sound.Play();
        keys_controller.GetComponent<Keys_controller>().setKey(action, key);
    }
}
