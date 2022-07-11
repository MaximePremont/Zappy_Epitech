using System.Collections;
using System.Collections.Generic;
using UnityEngine.UI;
using UnityEngine;

public class Game_information : MonoBehaviour
{
    // Start is called before the first frame update
    public string teamNbr;
    public string playerNbr;
    public string mapSz;
    public Text textTeamNbr;
    public Text textPlayerNbr;
    public Text textMapSz;
    public void refresh() {
        textTeamNbr.text = teamNbr;
        textPlayerNbr.text = playerNbr;
        textMapSz.text = mapSz;
    }
}
