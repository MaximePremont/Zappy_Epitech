from concurrent.futures import process
import re
import math
import random
from itertools import cycle
import json
from collections import Counter
import re

RESOURCES = ["linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]

LVLS = {1: {"linemate": 1},
        2: {"linemate": 1, "deraumere": 1, "sibur": 1},
        3: {"linemate": 2, "sibur": 1, "phiras": 2},
        4: {"linemate": 1, "deraumere": 1, "sibur": 2, "phiras": 1},
        5: {"linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3},
        6: {"linemate": 1, "deraumere": 2, "sibur": 3, "phiras": 1},
        7: {"linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1},
}

class IA:
    """The IA class encapsulates the intelligence of the player"""
    def __init__(self, name):
        """The IA class encapsulates the intelligence of the player
        Args:
            client (Client): the client which helps you to communicate with the server.
        """
        self.inventory = {"food": 0, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
        self.look = ""
        self.broadcast = []
        self.commands_list = []
        self.step = -2
        self.data_to_write = ""
        self.level = 1
        self.run = 1
        self.useless_slot = 0
        self.shared_inventory = {}
        self.client_num = 0
        self.team = name
        self.new_object = False
        self.to_search = ""
        self.incantation = 0
        self.master_incantation = 0
        self.nb_player_incantation = 1
        self.direction = 9
        self.ready_for_incantation = 0
        self.clear_read = 0
        self.clear_broadcast = 0
        self.fork = 1

    def check_incantation(self) -> bool:
        """Check if incantation is possible with the new object and the shared inventory

        Args:
            object (str): The name of the new objet we got

        Returns:
            bool: Incantation is possible or not
        """
        required_ressources = LVLS[self.level].copy()
        if "total" in self.shared_inventory:
            inventory = self.shared_inventory["total"].copy()
        if self.to_search in inventory:
            inventory[self.to_search] += 1
        else:
            inventory[self.to_search] = 1
        for k in required_ressources:
            if required_ressources[k] > inventory[k]:
                return False
        return True

    def search_good_ressources(self):
        required_ressources = LVLS[self.level].copy()
        liste = []
        if "total" in self.shared_inventory:
            inventory = self.shared_inventory["total"].copy()
        else:
            inventory = {"food": 0, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
        for k in required_ressources:
            if k not in inventory or required_ressources[k] > inventory[k]:
                liste.append(k)
        if liste == []:
            return "food"
        return random.choice(liste)


    def sxor(self, s1: str,s2: str):
        """Xor two strings"""    
        return ''.join(chr(ord(c)^ord(k)) for c,k in zip(s2, cycle(s1)))

    def parse_inventory(self, data):
        for char in "[]":
            data = data.replace(char, "")
        data = data.split(",")
        for i in range(len(data)):
            data[i] = data[i][1:]
        data[len(data) - 1] = data[len(data) - 1][:-1]
        for elem in data:
            if elem:
                self.inventory[elem.split()[0]] = int(elem.split()[1])

    def parse_shared_inventory(self, data):
        """Update shared inventory with broadcast
                        elif "Take" in self.ia.data_to_write and "food" not in self.ia.data_to_write:
                            print("Failed to take ", self.ia.to_search)
        Args:
            data (str): broadcast from other player
        """
        client, _, inventory = data.split(";")
        self.shared_inventory[self.client_num] = self.inventory
        self.shared_inventory[client] = json.loads(inventory)
        c = Counter()
        for d in self.shared_inventory:
            if d == 'total':
                continue
            c.update(self.shared_inventory[d])
        self.shared_inventory['total'] = dict(c)
            
    def update_shared_inventory(self):
        """Update shared inventory when we took new object
        """
        self.shared_inventory[self.client_num] = self.inventory
        c = Counter()
        for d in self.shared_inventory:
            if d == 'total':
                continue
            c.update(self.shared_inventory[d])
        self.shared_inventory['total'] = dict(c)

        
    def size_look(self, array: list) -> int:
        """Get the size of the array
        Args:
            array (list): the array
        Returns:
            int: the size of the array
        """
        nb = 0
        for elem in array:
            if elem == []:
                return nb
            nb += 1
        return nb

    def find_object(self, map: list, object: str) -> list:
        """Find the object in the map
        Args:
            map (list): the map
            object (str): the object
        Returns:
            list: coord x y of the object
        """

        v = 8
        h = 0
        while h < self.size_look(map[v]):
            if map[v][h] != [] and object in map[v][h][0]:
                return [v, h]
            else:
                h += 1
            tv = v
            while tv >= v-h:
                if map[v][h] != [] and object in map[tv][h][0]:
                    return [tv, h]
                tv -= 1
            tv = v
            while tv <= v+h:
                if map[v][h] != [] and object in map[tv][h][0]:
                    return [tv, h]
                tv += 1
            h+=1
        return None

    def get_nb_of_lines(self, data: list) -> int:
        """Get the number of line in the array
        Args:
            data (list): the array
        Returns:
            int: the number of line
        """
        data_len = len(data)
        return int(math.sqrt(data_len))

    def fill_map(self, map: list, data: list) -> list:
        """Fill the map with the object position
        Args:
            map (list): the map
            data (list): the array of object position
        return :
            array: the map
        """
        nb = 1
        v = 8
        h = 0
        i = 0
        x = 0

        line = self.get_nb_of_lines(data)
        for j in range(line):
            tv = v - h
            for a in range(nb):
                map[tv][h].append(data[i])
                tv += 1
                i += 1
            nb = (nb + 2)
            h += 1
        return map

    def generate_empty_map(self) -> list:
        """Generate an empty map
        Returns:
            array: the empty map
        """
        return [[[] for i in range(9)] for j in range(17)]

    def split_data(self, data: str) -> list:
        """Split the look command
        Args:
            data (str): the look command
        Returns:
            list: the object split"""
        for char in "[]":
            data = data.replace(char, "")
        data = data.split(",")
        for i in range(len(data)):
            data[i] = data[i][1:]
        data[len(data) - 1] = data[len(data) - 1][:-2]
        return data

    def parse_look(self, data: str, object : str) -> list:
        """Parse the look command
        Args:
            data (str): the look command
        Returns:
            array: the list of object position
        """
        data1 = data.split(",")
        liste = []
        for i in range(len(data1)):
            liste.append(' '.join(re.split('\W+', data1[i])[1:]))
        data = liste
        map = self.generate_empty_map()
        map = self.fill_map(map, data)
        coord = self.find_object(map, object)
        res = []
        if (coord == None):
            res.append(random.choice(["Forward\n", "Right\n", "Left\n"]))
            res.append(random.choice(["Forward\n", "Right\n", "Left\n"]))
            res.append(random.choice(["Forward\n", "Right\n", "Left\n"]))
            return res
        elif (coord[0] == 8 and coord[1] == 0):
            return ["Take " + object + "\n"]
        else:
            for i in range(int(coord[0]) - 8):
                res.append("Forward\n")
            if (coord[0] == 8):
                for i in range(int(coord[1])):
                    res.append("Forward\n")
                res.append("Take " + object + "\n")
                res.append("Inventory\n")
            if (coord[1] == 0):
                res.append("Take " + object + "\n")
            if (int(coord[0]) < 8):
                res.append("Left\n")
                for i in range(8 - int(coord[0])):
                    res.append("Forward\n")
                res.append("Take " + object + "\n")
                res.append("Inventory\n")
            if (int(coord[0]) > 8):
                res.append("Right\n")
                for i in range(int(coord[0]) - 8):
                    res.append("Forward\n")
                res.append("Take " + object + "\n")
                res.append("Inventory\n")
        return res

    def parse_broadcast(self, message):
        direction = int(message[8])
        message = self.sxor(self.team, bytes.fromhex(message[11:]).decode("utf-8"))
        if "inventory" in message:
            self.parse_shared_inventory(message[9:])
        if "incantation" in message:
            if self.clear_broadcast == 1:
                self.clear_broadcast = 0
                return
            if self.master_incantation >= 1 and int(message.split(";")[0]) > self.client_num:
                self.master_incantation = 0
                self.incantation = 0
                self.step = 0
                return
            if self.step > -1 and self.step < 4 and self.inventory["food"] > 35:
                self.step = 4
                self.commands_list = []
            if self.incantation == 1:
                self.commands_list = self.go_to_broadcast(direction)
        if "on my way" in message and self.master_incantation >= 1:
            self.nb_player_incantation += 1
        if "ready" in message and self.master_incantation >= 1:
            self.master_incantation += 1
    
    def go_to_broadcast(self, direction: int) -> list:
        if self.ready_for_incantation == 1 or self.commands_list:
            return
        res = []
        if (direction == 0):
            message = bytes(self.sxor(self.team, ("ready")), "utf-8").hex()
            self.data_to_write = "Broadcast " + message + "\n"
            self.direction = 0
            self.ready_for_incantation = 1
            return []
        if (direction in (2, 1, 8)):
            res.append("Forward\n")
        elif (direction in (5, 6, 7)):
            res.append("Right\n")  
        else:
            res.append("Left\n")
        return res

    def drop_object_incantation(self):
        if self.commands_list:
            return
        data = self.look.split(",")[0]
        while True:
            if len(data) == 0 or data[0].isalpha():
                break
            data = data[1:]
        data = data.split(" ")
        required_ressources = LVLS[self.level].copy()
        for k in required_ressources:
            for j in data:
                if j == k:
                    required_ressources[k] -= 1
        for k in required_ressources:
            if required_ressources[k] < 1:
                continue
            if k in self.inventory and self.inventory[k] != 0:
                self.commands_list = ["Set " + k + "\n"]
                self.commands_list.append("Look\n")
                self.inventory[k] -= 1
                return
        self.step = 7
        self.data_to_write = ""
        return

    def start_incantation(self):
        data = self.look.split(",")[0]
        while True:
            if len(data) == 0 or data[0].isalpha():
                break
            data = data[1:]
        data = data.split(" ")
        required_ressources = LVLS[self.level].copy()
        for k in required_ressources:
            for j in data:
                if j == k:
                    required_ressources[k] -= 1
        for k in required_ressources:
            if required_ressources[k] > 0:
                return
        self.data_to_write = "Incantation\n"
        self.commands_list = ["Incantation\n"]
        self.step += 1
        
    def algorithm(self):
        if self.step == -2:
            self.data_to_write = "Connect_nbr\n"
            self.step += 1
        elif self.step == -1:
            if self.client_num < 6 and self.useless_slot == 0:
                self.data_to_write = "Fork\n"
                self.fork = 1
            else:
                self.data_to_write = "Look\n"
            self.step += 1
        elif self.step == 0:
            if self.commands_list:
                self.data_to_write = self.commands_list[0]
                self.commands_list = self.commands_list[1:]
            else:
                self.data_to_write = "Inventory\n"
                self.step += 1
        elif self.step == 1:
            if self.new_object:
                if not self.check_incantation(): 
                    message = bytes(self.sxor(self.team, ("inventory" + str(self.client_num) + ";" + str(self.level) + ";" + str(json.dumps(self.inventory)))), "utf-8").hex()
                    self.data_to_write = "Broadcast " + message + "\n"
                else:
                    message = bytes(self.sxor(self.team, (str(self.client_num) + ";incantation;" + str(self.level))), "utf-8").hex()
                    self.data_to_write = "Broadcast " + message + "\n"
                    self.master_incantation = 1
                    self.step = 4
                    self.incantation = 1
                    self.new_object = False
                    return
                self.new_object = False
            else:
                self.step += 1
                self.algorithm()
                return
            self.step += 1
        elif self.step == 2:
            self.data_to_write = "Look\n"
            self.step += 1
        elif self.step == 3:
            if "food" in self.inventory and self.inventory["food"] < 45:
                self.commands_list = self.parse_look(self.look, "food")
                self.step = 0
            else:
                self.to_search = self.search_good_ressources()
                self.commands_list = self.parse_look(self.look, self.to_search)
                self.step = 0
        elif self.step == 4:
            if self.incantation == 0:
                data = bytes(self.sxor(self.team, str(self.client_num) + " on my way"), "utf-8").hex()
                self.data_to_write = "Broadcast " + data + "\n"
                self.incantation = 1
                return
            if self.master_incantation >= 6:
                self.step += 1
                return
            if self.master_incantation >= 1:
                pass
            elif self.commands_list and not self.ready_for_incantation:
                self.data_to_write = self.commands_list[0]
                self.commands_list = self.commands_list[1:]
                self.clear_broadcast = 1
                if not self.commands_list:
                    self.clear_read = 1
            elif self.ready_for_incantation and "Broadcast" in self.data_to_write:
                self.step += 1
            else:
                self.data_to_write = ""
        elif self.step == 5:
            self.clear_broadcast = 0
            self.data_to_write = "Look\n"
            self.step += 1
        elif self.step == 6:
            self.clear_broadcast = 0
            if self.master_incantation >= 6:
                self.start_incantation()
            if self.step != 7:
                self.drop_object_incantation()
                if self.commands_list:
                    self.data_to_write = self.commands_list[0]
                    self.commands_list = self.commands_list[1:]
                else:
                    self.data_to_write = "Inventory\n"
        elif self.step == 7:
            if self.master_incantation < 6:
                self.data_to_write = "Connect_nbr\n"
                return
            if self.commands_list:
                    self.data_to_write = self.commands_list[0]
                    self.commands_list = self.commands_list[1:]
            else:
                self.commands_list = ["Inventory\n"]
                self.commands_list = ["Look\n"]
        elif self.step == 8:
            self.data_to_write = ""
        elif self.step == 9:
            self.data_to_write = "Inventory\n"
            self.step += 1
        elif self.step == 10:
            message = bytes(self.sxor(self.team, ("inventory" + str(self.client_num) + ";" + str(self.level) + ";" + str(json.dumps(self.inventory)))), "utf-8").hex()
            self.data_to_write = "Broadcast " + message + "\n"
            self.step = 0