using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Island : MonoBehaviour {
    public int[] incants;
    public int x;
    public int y;
    public int foods = 0;
    public GameObject all_foods;
    public GameObject all_ores;
    public GameObject instance;
    public ArrayList foodObjects = new ArrayList();
    public Dictionary<string, ArrayList> ores = new Dictionary<string, ArrayList>();
    public void setFoodNumber(int nb) {
        int diff = foods - nb;
        if (diff == 0)
            return;
        if (diff < 0) {
            diff *= -1;
            for (int i = 0; i < diff; i++) {
                int randFood = (new System.Random()).Next(8);
                int randPos = (new System.Random()).Next(3);
                float randAngle = (new System.Random()).Next(36001) / 10;
                GameObject randFoodObj = GameObject.Instantiate(all_foods.transform.GetChild(randFood).gameObject);
                randFoodObj.transform.parent = instance.transform.GetChild(0).gameObject.transform;
                Vector3 randPosVec = instance.transform.GetChild(0).gameObject.transform.Find("Feed"+randPos).gameObject.transform.position;
                randFoodObj.GetComponent<Food>().basicPos = new Vector3(randPosVec.x, randPosVec.y, randPosVec.z);
                randFoodObj.transform.position = new Vector3(randPosVec.x, randPosVec.y, randPosVec.z);
                randFoodObj.transform.rotation = Quaternion.Euler(randFoodObj.transform.rotation.x, randAngle, randFoodObj.transform.rotation.z);
                foodObjects.Add(randFoodObj);
                randFoodObj.SetActive(true);
            }
            foods = nb;
            return;
        }
        for (int i = 0; i < diff && foodObjects.Count > 0; i++) {
            GameObject rmObj = (GameObject) foodObjects[0];
            foodObjects.Remove(rmObj);
            GameObject.Destroy(rmObj);
        }
    }
    public void setOreNumber(int nb, string ore) {
        ore = ore.ToLower();
        int nbOres = 0;
        if (ores.ContainsKey(ore))
            nbOres = ores[ore].Count;
        int diff = nbOres - nb;
        if (diff == 0)
            return;
        if (diff < 0) {
            diff *= -1;
            for (int i = 0; i < diff; i++) {
                int randPos = (new System.Random()).Next(3);
                float randAngle = (new System.Random()).Next(36001) / 10;
                GameObject randOreObj = GameObject.Instantiate(all_ores.transform.Find(ore).gameObject);
                randOreObj.transform.parent = instance.transform.GetChild(0).gameObject.transform;
                Vector3 randPosVec = instance.transform.GetChild(0).gameObject.transform.Find("Feed"+randPos).gameObject.transform.position;
                randOreObj.GetComponent<Ore>().basicPos = new Vector3(randPosVec.x, randPosVec.y, randPosVec.z);
                randOreObj.transform.position = new Vector3(randPosVec.x, randPosVec.y, randPosVec.z);
                randOreObj.transform.rotation = Quaternion.Euler(randOreObj.transform.rotation.x, randAngle, randOreObj.transform.rotation.z);
                if (!ores.ContainsKey(ore))
                    ores.Add(ore, new ArrayList());
                ores[ore].Add(randOreObj);
                randOreObj.SetActive(true);
            }
            return;
        }
        if (!ores.ContainsKey(ore))
            return;
        for (int i = 0; i < diff && ores[ore].Count > 0; i++) {
            GameObject rmObj = (GameObject) ores[ore][0];
            ores[ore].Remove(rmObj);
            GameObject.Destroy(rmObj);
        }
    }
}
