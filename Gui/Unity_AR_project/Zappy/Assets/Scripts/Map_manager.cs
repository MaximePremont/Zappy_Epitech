using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class Map_manager : MonoBehaviour {
    private int x = -1;
    private int y = -1;
    private bool generated = false;
    private ArrayList floor;

    public GameObject island_object1;
    public GameObject island_object2;
    public GameObject island_object3;
    public GameObject island_object4;
    public GameObject island_object5;
    public GameObject island_object6;

    public GameObject decors;
    public GameObject player_controller;
    public Transform zero;
    public void setTiming(float time) {
        float multiplicator = time / 100;
        Time.timeScale = multiplicator;
    }

    public void setX(int nx) {
        x = nx;
        generateMap();
    }
    public void setY(int ny) {
        y = ny;
        generateMap();
    }
    private void generateMap() {
        if (x < 1 || y < 1 || generated)
            return;
        generated = true;
        floor = new ArrayList();
        Vector3 vec = new Vector3(0, 0, 0);
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                vec = new Vector3(zero.position.x + 1 * i + ((new System.Random()).Next(9) / 10 - 0.4f), zero.position.y -
                    0.5f + ((new System.Random()).Next(4) / 10), zero.position.z + 1 * j + ((new System.Random()).Next(9) / 10 - 0.4f));
                GameObject go = null;
                int rand = (new System.Random()).Next(6);
                float angle = (new System.Random()).Next(36001) / 10;
                switch (rand) {
                    case 0:
                        go = GameObject.Instantiate(island_object1); break;
                    case 1:
                        go = GameObject.Instantiate(island_object2); break;
                    case 2:
                        go = GameObject.Instantiate(island_object3); break;
                    case 3:
                        go = GameObject.Instantiate(island_object4); break;
                    case 4:
                        go = GameObject.Instantiate(island_object5); break;
                    default:
                        go = GameObject.Instantiate(island_object6); break;
                }
                go.GetComponent<Island>().x = i;
                go.GetComponent<Island>().y = j;
                int decorRand = (new System.Random()).Next(10) + 1;
                int max = decorRand >= 7 ? 2 : (decorRand >= 2 ? 1 : 0);
                ArrayList liPos = new ArrayList();
                for (int ci = 0; ci < max; ci++) {
                    int randObj = (new System.Random()).Next(19);
                    float decAngle = (new System.Random()).Next(36001) / 10;
                    GameObject decor = GameObject.Instantiate(decors.transform.GetChild(randObj).gameObject);
                    decor.transform.parent = go.transform.GetChild(0).gameObject.transform;
                    int randPos = (new System.Random()).Next(3);
                    while (liPos.Contains(randPos))
                        randPos = (new System.Random()).Next(3);
                    decor.transform.position = go.transform.GetChild(0).gameObject.transform.Find("Decor"+randPos).gameObject.transform.position;
                    if (randObj >= 10)
                        decor.transform.position = new Vector3(decor.transform.position.x, decor.transform.position.y - 0.42f, decor.transform.position.z);
                    else if (randObj >= 8)
                        decor.transform.position = new Vector3(decor.transform.position.x, decor.transform.position.y - 0.08f, decor.transform.position.z);
                    decor.transform.rotation = Quaternion.Euler(0, decAngle, 0);
                    decor.SetActive(true);
                }
                go.transform.position = vec;
                go.transform.rotation = Quaternion.Euler(0, angle, 0);
                floor.Add(go);
                go.SetActive(true);
                StartCoroutine(startAnimation(go));
            }
        }
    }

    IEnumerator startAnimation(GameObject go) {
        yield return new WaitForSeconds((new System.Random()).Next(1201)/1000);
        go.transform.GetChild(0).gameObject.GetComponent<Animator>().SetBool("Fly", true);
    }
    public void setIslandData(int X, int Y, int q0, int q1, int q2, int q3, int q4, int q5, int q6) {
        GameObject cois = null;
        for (int i = 0; i < floor.Count; i++) {
            GameObject fl = (GameObject) floor[i];
            if (fl.GetComponent<Island>().x == X && fl.GetComponent<Island>().y == Y) {
                cois = fl;
                break;
            }
        }
        if (cois == null)
            return;
        cois.GetComponent<Island>().setFoodNumber(q0);
        cois.GetComponent<Island>().setOreNumber(q1, "linemate");
        cois.GetComponent<Island>().setOreNumber(q2, "deraumere");
        cois.GetComponent<Island>().setOreNumber(q3, "sibur");
        cois.GetComponent<Island>().setOreNumber(q4, "mendiane");
        cois.GetComponent<Island>().setOreNumber(q5, "phiras");
        cois.GetComponent<Island>().setOreNumber(q6, "thystame");
    }
    public GameObject getIsland(int x, int y) {
        GameObject cois = null;
        for (int i = 0; i < this.floor.Count; i++) {
            GameObject fl = (GameObject) this.floor[i];
            if (fl.GetComponent<Island>().x == x && fl.GetComponent<Island>().y == y) {
                cois = fl;
                break;
            }
        }
        return cois;
    }
    public Vector3 generatePoint(int x, int y) {
        GameObject cois = null;
        for (int i = 0; i < this.floor.Count; i++) {
            GameObject fl = (GameObject) this.floor[i];
            if (fl.GetComponent<Island>().x == x && fl.GetComponent<Island>().y == y) {
                cois = fl;
                break;
            }
        }
        if (cois == null)
            return new Vector3(0, 0, 0);
        int randPos = (new System.Random()).Next(3);
        Vector3 randPosVec = cois.transform.GetChild(0).gameObject.transform.Find("Spawn"+randPos).gameObject.transform.position;
        return randPosVec;
    }
    public GameObject spawnPlayerOnIsland(int state, int number, int width, int height, int orientation, int level, string team) {
        GameObject cois = null;
        GameObject player = player_controller.GetComponent<player_manager>().spawnPlayer(state, number, width, height, orientation, level, team);
        for (int i = 0; i < this.floor.Count; i++) {
            GameObject fl = (GameObject) this.floor[i];
            if (fl.GetComponent<Island>().x == width && fl.GetComponent<Island>().y == height) {
                cois = fl;
                break;
            }
        }
        if (cois == null)
            return null;
        int randPos = (new System.Random()).Next(3);
        player.transform.parent = cois.transform.GetChild(0).gameObject.transform;
        Vector3 randPosVec = cois.transform.GetChild(0).gameObject.transform.Find("Spawn"+randPos).gameObject.transform.position;
        player.transform.position = new Vector3(randPosVec.x, randPosVec.y, randPosVec.z);
        player.GetComponent<Player>().updateRotation();
        return player;
    }
    public void spawnEgg(int n, int e, int x, int y) {
        int randOr = (new System.Random()).Next(4) + 1;
        GameObject player = player_controller.GetComponent<player_manager>().selectPlayer(n);

        if (player == null)
            return;
        player.transform.Find("Human").gameObject.GetComponent<Animator>().SetTrigger("Sit");
        GameObject egg = spawnPlayerOnIsland(0, e, x, y, randOr, 1, player.GetComponent<Player>().team);
        egg.transform.Find("Human").gameObject.SetActive(false);
        egg.transform.Find("Egg").gameObject.SetActive(true);
        egg.transform.position = new Vector3(player.transform.position.x, player.transform.position.y + 0.1f, player.transform.position.z);
    }
    public void startIncantation(int x, int y, int[] n) {
        GameObject obj = getIsland(x, y);
    
        if (obj == null)
            return;
        obj.transform.GetChild(0).gameObject.transform.Find("MagicAura").gameObject.SetActive(true);
        obj.GetComponent<Island>().incants = n;
        for (int i = 0; i < n.Length; i++)
            player_controller.GetComponent<player_manager>().startIncantation(n[i]);
    }
    public void endIncantation(int x, int y) {
        GameObject obj = getIsland(x, y);
    
        if (obj == null)
            return;
        obj.transform.GetChild(0).gameObject.transform.Find("MagicAura").gameObject.SetActive(false);
        int[] ns = obj.GetComponent<Island>().incants;
        for (int i = 0; i < ns.Length; i++)
            player_controller.GetComponent<player_manager>().endIncantation(ns[i]);
    }
}
