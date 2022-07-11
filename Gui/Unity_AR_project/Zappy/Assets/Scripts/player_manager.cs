using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using TMPro;

public class player_manager : MonoBehaviour {
    public GameObject game_menu;
    public GameObject player_obj;
    public GameObject map_manager;
    private ArrayList players = new ArrayList();
    public AudioSource gameMusic;
    public AudioSource endMusic;
    public Broadcasts broadcasts;
    public GameObject spawnPlayer(int state, int number, int width, int height, int orientation, int level, string team) {
        GameObject p = GameObject.Instantiate(player_obj);
        game_menu.GetComponent<Game_information>().playerNbr = "Players --> " + (players.Count + 1);
        game_menu.GetComponent<Game_information>().refresh();
        p.GetComponent<Player>().state = state;
        p.GetComponent<Player>().number = number;
        p.GetComponent<Player>().width = width;
        p.GetComponent<Player>().height = height;
        p.GetComponent<Player>().orientation = orientation;
        p.GetComponent<Player>().level = level;
        p.GetComponent<Player>().team = team;
        p.SetActive(true);
        p.transform.Find("Human").transform.Find("Text").gameObject.GetComponent<TextMeshPro>().text = number+" "+team;
        players.Add(p);
        return p;
    }
    public GameObject selectPlayer(int n) {
        for (int i = 0; i < players.Count; i++) {
            GameObject current = (GameObject) players[i];
            if (current.GetComponent<Player>().number == n) {
                return current;
            }
        }
        return null;
    }
    public void setState(int n, int state) {
        GameObject p = selectPlayer(n);
    
        if (p == null)
            return;
        if (state == 1) {
            // Alive
            p.GetComponent<Player>().state = 2;
            p.transform.GetChild(0).gameObject.GetComponent<Animator>().SetBool("Animated", true);
        } else {
            // Not used
            p.GetComponent<Player>().state = 1;
            p.transform.GetChild(0).gameObject.GetComponent<Animator>().SetBool("Animated", false);
        }
    }
    public void setPosition(int n, int x, int y, int o) {
        GameObject p = selectPlayer(n);
    
        if (p == null)
            return;
        if (!p.GetComponent<Player>().oris.ContainsKey(o))
            return;
        if (p.GetComponent<Player>().orientation != o) {
            p.transform.GetChild(0).gameObject.GetComponent<Animator>().SetTrigger("Rotate");
            p.GetComponent<Player>().orientation = o;
            p.GetComponent<Player>().usePlayerRotate(Quaternion.Euler(0, p.GetComponent<Player>().oris[o], 0), p);
        } else if (p.GetComponent<Player>().width != x || p.GetComponent<Player>().height != y) {
            p.transform.GetChild(0).gameObject.GetComponent<Animator>().SetTrigger("Rotate");
            p.GetComponent<Rigidbody>().isKinematic = true;
            p.GetComponent<Player>().width = x;
            p.GetComponent<Player>().height = y;
            p.transform.parent = map_manager.GetComponent<Map_manager>().getIsland(x, y).transform.GetChild(0).gameObject.transform;
            Vector3 target = map_manager.GetComponent<Map_manager>().generatePoint(x, y);
            target.y += 0.1f;
            p.GetComponent<Player>().usePlayerMove(p, target, false);
        }
    }
    public void setPlayerLevel(int n, int l) {
        GameObject p = selectPlayer(n);
    
        if (p == null)
            return;
        if (l <= p.GetComponent<Player>().level)
            return;
        p.GetComponent<Player>().level = l;
        p.transform.GetChild(0).gameObject.GetComponent<Animator>().SetTrigger("Buff");
        Transform starter = p.transform.Find("Human").gameObject.transform.Find("Armors").gameObject.transform.Find("StarterClothes").gameObject.transform;
        Transform plate = p.transform.Find("Human").gameObject.transform.Find("Armors").gameObject.transform.Find("Plate1").gameObject.transform;
        p.transform.Find("LevelUp").gameObject.SetActive(true);
        StartCoroutine(stopLevelUpAnimation(p));
        switch (l) {
            case 2:
                starter.Find("Starter_Boots").gameObject.SetActive(true);
                starter.Find("Starter_Pants").gameObject.SetActive(true);
                break;
            case 3:
                starter.Find("Starter_Chest").gameObject.SetActive(true);
                break;
            case 4:
                plate.Find("PlateSet1_Boots").gameObject.SetActive(true);
                plate.Find("PlateSet1_Pants").gameObject.SetActive(true);
                break;
            case 5:
                plate.Find("PlateSet1_Chest").gameObject.SetActive(true);
                break;
            case 6:
                plate.Find("PlateSet1_Gloves").gameObject.SetActive(true);
                break;
            case 7:
                plate.Find("PlateSet1_Shoulders").gameObject.SetActive(true);
                break;
            case 8:
                plate.Find("PlateSet1_Helmet").gameObject.SetActive(true);
                break;
            default:
                break;
        }
        
    }
    IEnumerator stopLevelUpAnimation(GameObject p) {
        yield return new WaitForSeconds(1.3f);
        p.transform.Find("LevelUp").gameObject.SetActive(false);
    }
    public void setPlayerInventory(int n, int q0, int q1, int q2, int q3, int q4, int q5, int q6) {
        GameObject p = selectPlayer(n);
    
        if (p == null)
            return;
        p.GetComponent<Player>().inv["Food"] = q0;
        p.GetComponent<Player>().inv["Linemate"] = q1;
        p.GetComponent<Player>().inv["Deraumere"] = q2;
        p.GetComponent<Player>().inv["Sibur"] = q3;
        p.GetComponent<Player>().inv["Mendiane"] = q4;
        p.GetComponent<Player>().inv["Phiras"] = q5;
        p.GetComponent<Player>().inv["Thystame"] = q6;
    }
    public void playerLook(int n) {
        GameObject p = selectPlayer(n);
    
        if (p == null)
            return;
        p.transform.GetChild(0).gameObject.GetComponent<Animator>().SetTrigger("Look");
    }
    public void playerAttack(int n) {
        GameObject p = selectPlayer(n);
    
        if (p == null)
            return;
        p.transform.GetChild(0).gameObject.GetComponent<Animator>().SetTrigger("Attack");
    }
    public void playerKicked(int n, int x, int y) {
        GameObject p = selectPlayer(n);
    
        if (p == null)
            return;
        p.transform.GetChild(0).gameObject.GetComponent<Animator>().SetBool("Kicked", true);
        p.GetComponent<Rigidbody>().isKinematic = true;
        p.GetComponent<Player>().width = x;
        p.GetComponent<Player>().height = y;
        StopAllCoroutines();
        p.transform.parent = map_manager.GetComponent<Map_manager>().getIsland(x, y).transform.GetChild(0).gameObject.transform;
        Vector3 target = map_manager.GetComponent<Map_manager>().generatePoint(x, y);
        target.y += 0.1f;
        p.GetComponent<Player>().usePlayerMove(p, target, true);
    }
    public void playerPut(int n) {
        GameObject p = selectPlayer(n);
    
        if (p == null)
            return;
        p.transform.GetChild(0).gameObject.GetComponent<Animator>().SetTrigger("Put");
    }
    public void playerBroadcast(int n, string msg) {
        GameObject p = selectPlayer(n);
    
        if (p == null)
            return;
        p.transform.GetChild(0).gameObject.GetComponent<Animator>().SetTrigger("Scream");
        broadcasts.sendText(msg, p.GetComponent<Player>().number, p.GetComponent<Player>().team);
    }
    public void startPlayerCollect(int n, int i) {
        GameObject p = selectPlayer(n);
    
        if (p == null)
            return;
        p.GetComponent<Player>().collecting = i;
        p.transform.GetChild(0).gameObject.GetComponent<Animator>().SetBool("Mining", true);
    }
        public void endPlayerCollect(int n, int r) {
        GameObject p = selectPlayer(n);
    
        if (p == null)
            return;
        if (p.GetComponent<Player>().collecting < 0)
            return;
        p.transform.GetChild(0).gameObject.GetComponent<Animator>().SetBool("Mining", false);
        if (r == 0) {
            p.transform.GetChild(0).gameObject.GetComponent<Animator>().SetTrigger("Hit");
        } else {
            p.transform.GetChild(0).gameObject.GetComponent<Animator>().SetTrigger("Take");
        }
        p.GetComponent<Player>().collecting = -1;
    }
    public void playerDeath(int n) {
        GameObject p = selectPlayer(n);
    
        if (p == null)
            return;
        p.transform.GetChild(0).gameObject.GetComponent<Animator>().SetBool("Dead", true);
    }
    public void startIncantation(int n) {
        GameObject p = selectPlayer(n);
    
        if (p == null)
            return;
        p.transform.GetChild(0).gameObject.GetComponent<Animator>().SetBool("Incant", true);
    }
    public void endIncantation(int n) {
        GameObject p = selectPlayer(n);
    
        if (p == null)
            return;
        p.transform.GetChild(0).gameObject.GetComponent<Animator>().SetBool("Incant", false);
    }
    public void hatchEgg(int e) {
        GameObject p = selectPlayer(e);
    
        if (p == null)
            return;
        p.transform.Find("Egg").gameObject.SetActive(false);
        p.transform.Find("Human").gameObject.SetActive(true);
    }
    public void startDancing(string team) {
        for (int i = 0; i < players.Count; i++) {
            GameObject p = (GameObject) players[i];
            if (p.GetComponent<Player>().team == team)
                p.transform.Find("Human").gameObject.GetComponent<Animator>().SetBool("Dancing", true);
        }
        gameMusic.Stop();
        endMusic.Play();
    }
}
