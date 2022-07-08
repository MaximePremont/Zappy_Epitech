from http import client
from re import I
import socket
from Ai.src.utils.utils import safe_cast
from Ai.src.ai.ai import IA
import logging
import selectors
import random
import subprocess
import ipdb

class Client():
    """This class implements a client which use asyncio for non-blocking communication
    We could connect, interact with data, and interact with the server

    Args:
        socket (socket.socket): the socket which allows to communicate with the server
    """

    def __init__(self, hostname: str, port: str, team_name: str, client_id: str):
        """Client constructor

        Args:
            hostname (str): ip address of the server
            port (str): port of the server
            team_name (str): name of the team to connect
        """
        self.team = team_name
        self.hostname = hostname
        self.port = port
        self.client_num = 0
        self.data_width = 0
        self.data_height = 0
        self.socket = None
        self.selectors = selectors.DefaultSelector()
        self.just_log = 0
        self.logged = 0
        self.ia = IA(self.team)
        self.ia.client_num = int(client_id)
        self.client_num = int(client_id)
        self.I = 0

    def connect_to_server(self):
        """Initialise a socket which connects to the server
        We initialize the selectors to and be sure to receive the Welcome message
        """
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.setblocking(False)
        self.socket.connect_ex((self.hostname, safe_cast(self.port, int)))
        events = selectors.EVENT_READ | selectors.EVENT_WRITE
        self.selectors.register(self.socket, events)

    def save_info(self, message, nb):
        """save start info
        """
        if nb == 1:
            self.ia.useless_slot = safe_cast(message, int)
            self.ia.data_to_write = ""
            self.just_log = 2
        else:
            message = message.split()
            self.data_width = safe_cast(message[0], int)
            self.data_height = safe_cast(message[1], int)
            self.ia.data_to_write = ""
            self.just_log = 3
            self.logged = 1
            self.ia.run = 1


    def launch_client(self):
        """Process the init data delivers by the server
        """
        message = ""
        while True:
            event = self.selectors.select(timeout=None)
            for _, mask in event:
                if mask & selectors.EVENT_READ:
                    data = self.socket.recv(1024).decode("utf-8")
                    if data:
                        message += data
                    else:
                        self.selectors.unregister(self.socket)
                        self.socket.close()
                    tmp = message.split("\n")
                    for elem in tmp[:-1]:
                        if "dead" in elem:
                            print("Je suis mort, id : " , self.client_num)
                            exit(0)
                        if "WELCOME" in elem and self.logged == 0:
                            self.ia.data_to_write = (self.team + '\n')
                        elif self.just_log < 3:
                            if "message" in elem:
                                continue
                            self.save_info(elem, self.just_log)
                        elif  "Elevation underway" in elem:
                            self.ia.step = 8
                        elif "Current level:" in elem:
                            self.ia.level = int(''.join(filter(str.isdigit, elem)))
                            if self.ia.level == 8:
                                exit(0)
                            print(elem)
                            self.ia.step = 9
                            self.ia.new_object = False
                            self.ia.to_search = ""
                            self.ia.incantation = 0
                            self.ia.master_incantation = 0
                            self.ia.nb_player_incantation = 1
                            self.ia.direction = 9
                            self.ia.ready_for_incantation = 0
                            self.ia.clear_read = 0
                            self.ia.clear_broadcast = 0
                            self.ia.data_to_write = 0
                        elif self.just_log >= 3 and "message" in elem:
                            if self.ia.clear_read == 1:
                                self.ia.clear_read = 0
                                message = message.split("\n")[-1]
                                continue
                            self.ia.broadcast = elem
                            self.ia.parse_broadcast(elem)
                            message = message.split("\n")[-1]
                            continue
                        elif "Take" in self.ia.data_to_write and "food" not in self.ia.data_to_write and elem == "ok":
                            self.ia.update_shared_inventory()
                            self.ia.new_object = True
                        elif self.ia.data_to_write == "Inventory\n":
                            try:
                                self.ia.parse_inventory(elem)
                            except ValueError:
                                print("Error ", elem)
                                pass
                        elif self.ia.data_to_write == "Look\n":
                            self.ia.look = elem
                        elif self.ia.data_to_write == "Connect_nbr\n":
                            self.ia.useless_slot = int(elem)
                            if self.ia.useless_slot != 0 and self.client_num < 6 and self.ia.fork == 1:
                                subprocess.Popen(["python3","zappy_ai","-p", self.port, "-n", self.team, "-i", str(self.client_num + 1)])
                                print("Je fork ", self.ia.client_num)
                                self.ia.fork = 0
                        message = message.split("\n")[-1]
                        self.ia.run = 1

                if mask & selectors.EVENT_WRITE:
                    if self.logged and self.ia.run == 1:
                        self.ia.algorithm()
                    if self.ia.data_to_write and self.ia.run != 0:
                        self.I += 1
                        if self.ia.data_to_write == (self.team + '\n') and self.logged == 0:
                            self.just_log = 1
                        self.socket.send(self.ia.data_to_write.encode())
                        self.ia.run = 0

    def close(self):
        """close the client
        """
        self.selectors.unregister(self.socket)
        self.socket.close()

    def check_available_slots(self):
        """Check if the server have a slot available, else shutdown the client
        """
        if self.client_num < 0:
            logging.INFO("The server does not have available slots")
