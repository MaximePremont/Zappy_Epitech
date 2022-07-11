using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Keys_controller : MonoBehaviour
{
    private Dictionary<string, string> keys = new Dictionary<string, string>();
    void Awake() {
        keys.Add("Up", PlayerPrefs.GetString("Up", "Z"));
        keys.Add("Down", PlayerPrefs.GetString("Down", "S"));
        keys.Add("Right", PlayerPrefs.GetString("Right", "D"));
        keys.Add("Left", PlayerPrefs.GetString("Left", "Q"));
        keys.Add("Sensitivity", PlayerPrefs.GetString("Sensitivity", "320"));
        keys.Add("Ascend", PlayerPrefs.GetString("Ascend", "A"));
        keys.Add("Descend", PlayerPrefs.GetString("Descend", "E"));
        keys.Add("Lock", PlayerPrefs.GetString("Lock", "X"));
    }
    public string getKey(string action) {
        if (!keys.ContainsKey(action))
            return "";
        return keys[action];
    }
    public void setKey(string action, string key) {
        keys[action] = key;
        PlayerPrefs.SetString(action, key);
        PlayerPrefs.Save();
    }
}
