using UnityEngine.UI;
using UnityEngine;

public class Island_information : MonoBehaviour
{
    // Start is called before the first frame update
    public string coordinates;
    public string foodNbr;
    public string linemateNbr;
    public string deraumereNbr;
    public string siburNbr;
    public string mendianeNbr;
    public string phirasNbr;
    public string thystameNbr;
    public Text textCoordinates;
    public Text textFoodNbr;
    public Text textLinemateNbr;
    public Text textDeraumereNbr;
    public Text textSiburNbr;
    public Text textMendianeNbr;
    public Text textPhirasNbr;
    public Text textThystameNbr;
    public MouseHandler mh;

    public void refresh() {
        mh.refreshIsland();
        textCoordinates.text = coordinates;
        textFoodNbr.text = foodNbr;
        textLinemateNbr.text = linemateNbr;
        textDeraumereNbr.text = deraumereNbr;
        textSiburNbr.text = siburNbr;
        textMendianeNbr.text = mendianeNbr;
        textPhirasNbr.text = phirasNbr;
        textThystameNbr.text = thystameNbr;
    }
}
