using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MouseHandler : MonoBehaviour {
    public GameObject keys_controller;
    public GameObject island_selector;
    public GameObject player_selector;
    public Transform playerBody;
    float xRotation = 0f;
    public float mouseSensitivity = 320f;
    private bool canMoove = false;
    private GameObject ancientSelection = null;
    private int selectionType = -1;
    public AudioSource selectSound;
    public bool inMenu = false;
    public GameObject player_controller;
    private void Start() {
        Cursor.lockState = CursorLockMode.Locked;
        mouseSensitivity = float.Parse(keys_controller.GetComponent<Keys_controller>().getKey("Sensitivity"));
        canMoove = true;
    }

    private void unselect() {
        if (ancientSelection == null || selectionType < 0)
            return;
        if (selectionType == 0)
            deselectPlayer(ancientSelection);
        else
            deselectIsland(ancientSelection);
        ancientSelection = null;
        selectionType = -1;
    }
    void Update() {
        if (inMenu)
            return;
        if (Input.GetKeyDown(keys_controller.GetComponent<Keys_controller>().getKey("Lock").ToLower())) {
            if (canMoove)
                Cursor.lockState = CursorLockMode.Confined;
            else
                Cursor.lockState = CursorLockMode.Locked;
            canMoove = !canMoove;
        }
        if (Input.GetMouseButton(0) && !canMoove) {
            RaycastHit raycastHit;
            Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            if (Physics.Raycast(ray, out raycastHit, 100)) {
                GameObject clicked = raycastHit.transform.gameObject;
                while (clicked != null) {
                    if (clicked == ancientSelection)
                        break;
                    if (clicked.tag == "Player") {
                        unselect();
                        ancientSelection = clicked;
                        selectPlayer(clicked);
                        break;
                    } else if (clicked.tag == "island") {
                        unselect();
                        ancientSelection = clicked;
                        selectIsland(clicked);
                        break;
                    } else {
                        clicked = clicked.transform.parent.gameObject;
                    }
                }
            } else {
                unselect();
            }
        }
        if (!canMoove)
            return;
        float mouseX = Input.GetAxis("Mouse X") * mouseSensitivity * Time.unscaledDeltaTime;
        float mouseY = Input.GetAxis("Mouse Y") * mouseSensitivity * Time.unscaledDeltaTime;

        xRotation -= mouseY;
        xRotation = Mathf.Clamp(xRotation, -90f, 90f);

        transform.localRotation = Quaternion.Euler(xRotation, 0f, 0f);
        playerBody.Rotate(Vector3.up * mouseX);
    }
    private void definePlayerInfos(GameObject playerObj) {
        Dictionary<string, int> inventory = playerObj.GetComponent<Player>().inv;
        player_selector.GetComponent<Player_information>().team = "Team : " + playerObj.GetComponent<Player>().team; 
        player_selector.GetComponent<Player_information>().level = "Level : " + playerObj.GetComponent<Player>().level;
        player_selector.GetComponent<Player_information>().linemateNbr = "Linemate --> " + (inventory.ContainsKey("Linemate") ? inventory["Linemate"] : "0");
        player_selector.GetComponent<Player_information>().deraumereNbr = "Deraumere --> " + (inventory.ContainsKey("Deraumere") ? inventory["Deraumere"] : "0");
        player_selector.GetComponent<Player_information>().siburNbr = "Sibur --> " + (inventory.ContainsKey("Sibur") ? inventory["Sibur"] : "0");
        player_selector.GetComponent<Player_information>().mendianeNbr = "Mendiane --> " + (inventory.ContainsKey("Mendiane") ? inventory["Mendiane"] : "0");
        player_selector.GetComponent<Player_information>().phirasNbr = "Phiras --> " + (inventory.ContainsKey("Phiras") ? inventory["Phiras"] : "0");
        player_selector.GetComponent<Player_information>().thystameNbr = "Thystame --> " + (inventory.ContainsKey("Thystame") ? inventory["Thystame"] : "0");
        string[] values = player_controller.GetComponent<player_manager>().getTeamInfos(playerObj.GetComponent<Player>().team).Split(",");
        player_selector.GetComponent<Player_information>().aliveNbr = "Alive --> "+values[0];
        player_selector.GetComponent<Player_information>().deadNbr = "Dead --> "+values[1];
        player_selector.GetComponent<Player_information>().maxNbr = "Max level --> "+values[2];
    }
    private void selectPlayer(GameObject playerObj) {
        selectSound.Play();
        selectionType = 0;
        playerObj.transform.GetChild(0).gameObject.GetComponent<Outline>().enabled = true;

        player_selector.GetComponent<Player_information>().refresh();
        player_selector.SetActive(true);
    }
    private void deselectPlayer(GameObject playerObj) {
        selectSound.Play();
        playerObj.transform.GetChild(0).gameObject.GetComponent<Outline>().enabled = false;
        player_selector.SetActive(false);
    }
    private void defineIslandInfos(GameObject islandObj) {
        Dictionary<string, ArrayList> items = islandObj.GetComponent<Island>().ores;

        island_selector.GetComponent<Island_information>().coordinates = "X : " + islandObj.GetComponent<Island>().x + " | Y : " + islandObj.GetComponent<Island>().y;
        island_selector.GetComponent<Island_information>().foodNbr = "Food --> " + islandObj.GetComponent<Island>().foods;
        island_selector.GetComponent<Island_information>().linemateNbr = "Linemate --> " + (items.ContainsKey("linemate") ? items["linemate"].Count : "0");
        island_selector.GetComponent<Island_information>().deraumereNbr = "Deraumere --> " + (items.ContainsKey("deraumere") ? items["deraumere"].Count : "0");
        island_selector.GetComponent<Island_information>().siburNbr = "Sibur --> " + (items.ContainsKey("sibur") ? items["sibur"].Count : "0");
        island_selector.GetComponent<Island_information>().mendianeNbr = "Mendiane --> " + (items.ContainsKey("mendiane") ? items["mendiane"].Count : "0");
        island_selector.GetComponent<Island_information>().phirasNbr = "Phiras --> " + (items.ContainsKey("phiras") ? items["phiras"].Count : "0");
        island_selector.GetComponent<Island_information>().thystameNbr = "Thystame --> " + (items.ContainsKey("thystame") ? items["thystame"].Count : "0");
    }
    private void selectIsland(GameObject islandObj) {
        selectSound.Play();
        selectionType = 1;
        islandObj.transform.GetChild(0).gameObject.GetComponent<Outline>().enabled = true;

        defineIslandInfos(islandObj);
        island_selector.GetComponent<Island_information>().refresh();
        island_selector.SetActive(true);
    }
    private void deselectIsland(GameObject islandObj) {
        selectSound.Play();
        islandObj.transform.GetChild(0).gameObject.GetComponent<Outline>().enabled = false;
        island_selector.SetActive(false);
    }
    public void refreshIsland() {
        if (ancientSelection == null || selectionType < 0)
            return;
        if (selectionType != 1)
            return;
        defineIslandInfos(ancientSelection);
    }
    public void refreshPlayer() {
        if (ancientSelection == null || selectionType < 0)
            return;
        if (selectionType != 0)
            return;
        definePlayerInfos(ancientSelection);
    }
}
