using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Sensitivity_changer : MonoBehaviour {
    public GameObject keys_controller;
    public GameObject text_value;
    public MouseHandler mh;
    void Start() {
        this.GetComponent<UnityEngine.UI.Slider>().value = (float.Parse(keys_controller.GetComponent<Keys_controller>().getKey("Sensitivity")) - 10) / 490;
        text_value.GetComponent<UnityEngine.UI.Text>().text = keys_controller.GetComponent<Keys_controller>().getKey("Sensitivity");
    }
    public void sliding() {
        float value = this.GetComponent<UnityEngine.UI.Slider>().value;
        int sens = (int) (value * 490 + 10);
        text_value.GetComponent<UnityEngine.UI.Text>().text = sens+"";
        keys_controller.GetComponent<Keys_controller>().setKey("Sensitivity", sens+"");
        PlayerPrefs.SetString("Sensitivity", sens+"");
        PlayerPrefs.Save();
        mh.mouseSensitivity = sens;
    }
}
