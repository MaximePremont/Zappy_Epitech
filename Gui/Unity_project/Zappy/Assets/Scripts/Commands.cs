using System.Collections;
using UnityEngine;
using System;

public class Commands : MonoBehaviour {
    public GameObject map_controller;
    public GameObject connect_menu;
    public GameObject game_menu;
    public GameObject winner_text;
    public GameObject player_controller;
    public GameObject player_selector;
    public GameObject island_selector;
    public void use_msz(string[] args) {
        try {
            int x = int.Parse(args[1]);
            int y = int.Parse(args[2]);

            map_controller.SetActive(true);
            map_controller.GetComponent<Map_manager>().setX(x);
            map_controller.GetComponent<Map_manager>().setY(y);
            game_menu.GetComponent<Game_information>().mapSz = "Map --> X:" + x + " | Y:" + y;
            game_menu.GetComponent<Game_information>().refresh();
            connect_menu.GetComponent<Connect_menu>().validateMsz();
        } catch (Exception) {
            Debug.Log("Error: Invalid map size");
        }
    }
    public void use_bct(string[] args) {
        map_controller.GetComponent<Map_manager>().setIslandData(int.Parse(args[1]), int.Parse(args[2]),
        int.Parse(args[3]), int.Parse(args[4]), int.Parse(args[5]), int.Parse(args[6]),
        int.Parse(args[7]), int.Parse(args[8]), int.Parse(args[9]));
        island_selector.GetComponent<Island_information>().refresh();
    }
    public void use_tna(string[] args) {
        try {
            int nb = int.Parse(args[1]);
            string[] teams = new string[nb];

            for (int i = 0; i < nb; i++) {
                teams[i] = args[i + 2];
            }
            if (teams.Length > 0) {
                game_menu.GetComponent<Game_information>().teamNbr = "Teams --> " + teams.Length.ToString();
                connect_menu.GetComponent<Connect_menu>().validateTna();
                game_menu.GetComponent<Game_information>().refresh();
            }
        } catch (Exception) {
            Debug.Log("Error: Invalid number of teams");
        }
    }
    public void use_pnw(string[] args) {
        try {
            map_controller.GetComponent<Map_manager>().spawnPlayerOnIsland(1, int.Parse(args[1]), int.Parse(args[2]), int.Parse(args[3]),
            int.Parse(args[4]), int.Parse(args[5]), args[6]);
            connect_menu.GetComponent<Connect_menu>().validatePls();
            player_selector.GetComponent<Player_information>().refresh();
        } catch (Exception) {
            Debug.Log("Error: Invalid player information");
        }
    }
    public void use_pns(string[] args) {
        try {
            player_controller.GetComponent<player_manager>().setState(int.Parse(args[1]), int.Parse(args[2]));
        } catch(Exception) {
            Debug.Log("Error: Invalid pns command");
        }
    }
    public void use_ppo(string[] args) {
        try {
            player_controller.GetComponent<player_manager>().setPosition(int.Parse(args[1]), int.Parse(args[2]), int.Parse(args[3]), int.Parse(args[4]));
            player_selector.GetComponent<Player_information>().refresh();
        } catch(Exception) {
            Debug.Log("Error: Invalid ppo command");
        }
    }
    public void use_plv(string[] args) {
        try {
            player_controller.GetComponent<player_manager>().setPlayerLevel(int.Parse(args[1]), int.Parse(args[2]));
            player_selector.GetComponent<Player_information>().refresh();
        } catch(Exception) {
            Debug.Log("Error: Invalid plv command");
        }
    }
    public void use_pin(string[] args) {
        try {
            player_controller.GetComponent<player_manager>().setPlayerInventory(int.Parse(args[1]), int.Parse(args[2]), int.Parse(args[3]),
            int.Parse(args[4]), int.Parse(args[5]), int.Parse(args[6]), int.Parse(args[7]), int.Parse(args[8]));
            player_selector.GetComponent<Player_information>().refresh();
        } catch(Exception) {
            Debug.Log("Error: Invalid pin command");
        }
    }
    public void use_pex(string[] args) {
        try {
            player_controller.GetComponent<player_manager>().playerAttack(int.Parse(args[1]));
        } catch(Exception) {
            Debug.Log("Error: Invalid pex command");
        }
    }
    public void use_pbc(string[] args) {
        try {
            player_controller.GetComponent<player_manager>().playerBroadcast(int.Parse(args[1]), args[2]);
        } catch(Exception) {
            Debug.Log("Error: Invalid pbc command");
        }
    }
    public void use_pic(string[] args) {
        try {
            ArrayList vals = new ArrayList();
            for (int i = 4; i < args.Length; i++)
                vals.Add(int.Parse(args[i]));
            int[]ns = (int[])vals.ToArray(typeof(int));
            map_controller.GetComponent<Map_manager>().startIncantation(int.Parse(args[1]), int.Parse(args[2]), ns);
        } catch(Exception) {
            Debug.Log("Error: Invalid pic command");
        }
    }
    public void use_pie(string[] args) {
        try {
            map_controller.GetComponent<Map_manager>().endIncantation(int.Parse(args[1]), int.Parse(args[2]));
        } catch(Exception) {
            Debug.Log("Error: Invalid pgt command");
        }
    }
    public void use_pdr(string[] args) {
        try {
            player_controller.GetComponent<player_manager>().playerPut(int.Parse(args[1]));
        } catch(Exception) {
            Debug.Log("Error: Invalid pdr command");
        }
    }
    public void use_pgt(string[] args) {
        try {
            player_controller.GetComponent<player_manager>().startPlayerCollect(int.Parse(args[1]), int.Parse(args[2]));
        } catch(Exception) {
            Debug.Log("Error: Invalid pgt command");
        }
    }
    public void use_pdi(string[] args) {
        try {
            player_controller.GetComponent<player_manager>().playerDeath(int.Parse(args[1]));
            game_menu.GetComponent<Game_information>().refresh();
        } catch(Exception) {
            Debug.Log("Error: Invalid pdi command");
        }
    }
    public void use_enw(string[] args) {
        try {
            map_controller.GetComponent<Map_manager>().spawnEgg(int.Parse(args[1]), int.Parse(args[2]), int.Parse(args[3]), int.Parse(args[4]));
            game_menu.GetComponent<Game_information>().refresh();
        } catch(Exception) {
            Debug.Log("Error: Invalid enw command");
        }
    }
    public void use_eht(string[] args) {
        try {
            player_controller.GetComponent<player_manager>().hatchEgg(int.Parse(args[1]));
        } catch(Exception) {
            Debug.Log("Error: Invalid eht command");
        }
    }
    public void use_sgt(string[] args) {
        try {
            map_controller.GetComponent<Map_manager>().setTiming((float) int.Parse(args[1]));
            connect_menu.GetComponent<Connect_menu>().validateSgt();
        } catch(Exception) {
            Debug.Log("Error: Invalid sgt command");
        }
    }
    public void use_seg(string[] args) {
        if (args.Length < 2)
            return;
        winner_text.GetComponent<UnityEngine.UI.Text>().text = "Team "+args[1]+" has won !";
        winner_text.SetActive(true);
        player_controller.GetComponent<player_manager>().startDancing(args[1]);
    }
    public void use_look(string[] args) {
        try {
            player_controller.GetComponent<player_manager>().playerLook(int.Parse(args[1]));
        } catch(Exception) {
            Debug.Log("Error: Invalid pns command");
        }
    }
    public void use_pgte(string[] args) {
        try {
            player_controller.GetComponent<player_manager>().endPlayerCollect(int.Parse(args[1]), int.Parse(args[2]));
        } catch(Exception) {
            Debug.Log("Error: Invalid pgte command");
        }
    }
    public void use_pexed(string[] args) {
        try {
            player_controller.GetComponent<player_manager>().playerKicked(int.Parse(args[1]), int.Parse(args[2]), int.Parse(args[3]));
        } catch(Exception) {
            Debug.Log("Error: Invalid pexed command");
        }
    }
}
