using UnityEngine;

public class Menu_island : MonoBehaviour {
    void Start() {
        this.GetComponent<Animator>().SetBool("Fly", true);
    }
}
