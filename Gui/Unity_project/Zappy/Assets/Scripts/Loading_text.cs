using UnityEngine;

public class Loading_text : MonoBehaviour {
    public GameObject load;
    public GameObject check;
    public void validate() {
        load.SetActive(false);
        check.SetActive(true);
    }
}
