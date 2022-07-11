using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class Player : MonoBehaviour {
    // Player information
    public GameObject instance;

    public int state; // 0 = eggs, 1 = passive, 2 = active
    public string team; // team name
    public int level; // incantation level
    public int number; // player number

    // Position of the player in the game
    public int width; // x position
    public int height; // y position
    public int orientation;
    public Dictionary<int, float> oris = new Dictionary<int, float>();  //1(N), 2(E), 3(S), 4(W)
    public Dictionary<string, int> inv = new Dictionary<string, int>();
    public int collecting = -1;
    void Awake() {
        oris.Add(1, 0);
        oris.Add(2, 90);
        oris.Add(3, 180);
        oris.Add(4, 270);
        instance = this.gameObject;
        inv.Add("Food", 0);
        inv.Add("Linemate", 0);
        inv.Add("Deraumere", 0);
        inv.Add("Sibur", 0);
        inv.Add("Mendiane", 0);
        inv.Add("Phiras", 0);
        inv.Add("Thystame", 0);
    }
    public void updateRotation() {
        instance.transform.rotation = Quaternion.Euler(instance.transform.rotation.x, oris[orientation], instance.transform.rotation.z);
    }
    public static Vector3 Parabola(Vector3 start, Vector3 end, float height, float t) {
        Func<float, float> f = x => -4 * height * x * x + 4 * height * x;

        var mid = Vector3.Lerp(start, end, t);

        return new Vector3(mid.x, f(t) + Mathf.Lerp(start.y, end.y, t), mid.z);
    }
    private bool mooving = false;
    private Vector3 useTarget;
    private bool useReset = false;
    private bool rotating = false;
    private Quaternion useRotateTarget;
    private void useEndMovement(GameObject obj) {
        if (mooving) {
            StopAllCoroutines();
            obj.transform.position = useTarget;
            mooving = false;
            if (useReset)
                obj.transform.GetChild(0).gameObject.GetComponent<Animator>().SetBool("Kicked", false);
            useReset = false;
        }
        if (rotating) {
            StopAllCoroutines();
            obj.transform.rotation = useRotateTarget;
            rotating = false;
        }
    }
    public void usePlayerMove(GameObject obj, Vector3 target, bool reset) {
        useEndMovement(obj);
        useTarget = target;
        mooving = true;
        useReset = reset;
        StartCoroutine(movePlayer(obj, target, reset));
    }
    private float moveDuration = 0.051f;
    IEnumerator movePlayer(GameObject obj, Vector3 target, bool reset) {
        float timeElapsed = 0;
        Vector3 start = obj.transform.position;
        while (timeElapsed < moveDuration) {
            obj.transform.position = Parabola(start, target, 0.5f, timeElapsed / moveDuration);
            timeElapsed += Time.deltaTime;
            yield return null;
        }
        obj.GetComponent<Rigidbody>().isKinematic = false;
        obj.transform.position = target;
        if (reset)
            obj.transform.GetChild(0).gameObject.GetComponent<Animator>().SetBool("Kicked", false);
    }
    public void usePlayerRotate(Quaternion target, GameObject obj) {
        useEndMovement(obj);
        useRotateTarget = target;
        rotating = true;
        StartCoroutine(rotatePlayer(target, obj));
    }
    private float rotateDuration = 0.051f;
    IEnumerator rotatePlayer(Quaternion target, GameObject obj) {
        float timeElapsed = 0;
        Quaternion start = obj.transform.rotation;
        while (timeElapsed < rotateDuration) {
            obj.transform.rotation = Quaternion.Lerp(start, target, timeElapsed / rotateDuration);
            timeElapsed += Time.deltaTime;
            yield return null;
        }
        obj.transform.rotation = target;
    }
}
