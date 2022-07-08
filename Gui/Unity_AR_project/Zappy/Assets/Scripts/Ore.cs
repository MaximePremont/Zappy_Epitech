using UnityEngine;

public class Ore : MonoBehaviour {
    public Vector3 basicPos;
    void Update() {
        if (this.transform.position.y < 3) {
            this.transform.position = new Vector3(basicPos.x, basicPos.y, basicPos.z);
            this.GetComponent<Rigidbody>().velocity = new Vector3(0, 0, 0);
        }
    }
}
