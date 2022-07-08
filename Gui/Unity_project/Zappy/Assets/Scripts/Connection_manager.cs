using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.IO;
using System.Net.Sockets;
using System.Linq;
using System.Text;

public class Connection_manager : MonoBehaviour {
    private bool socketReady = false;
    private TcpClient socket;
    private NetworkStream netStream;
    private StreamWriter netWrite;
    private StreamReader netRead;
    public GameObject errorPanel;
    private Dictionary<long, ArrayList> cmds = new Dictionary<long, ArrayList>();
    void Awake() {
        StartCoroutine(useLoop());
    }

    public bool connect(string host, int port) {
        if (socketReady)
            return false;
        try {
            socket = new TcpClient(host, port);
            netStream = socket.GetStream();
            netWrite = new StreamWriter(netStream);
            netRead = new StreamReader(netStream);
            socketReady = true;
        } catch (Exception e) {
            e.ToString();
            return false;
        }
        if (!socketReady)
            return false;
        return true;
    }
    public void send(string line) {
        if (!socketReady)
            return;
        try {
            netWrite.Write(line+"\n");
            netWrite.Flush();
        } catch (Exception) {
            errorPanel.SetActive(true);
        }
    }
    private string[] read() {
        try {
            ArrayList lines = new ArrayList();
            if (!socketReady)
                return (string[]) lines.ToArray(typeof(string));
            string msg = "";
            if(netStream.CanRead){
                byte[] myReadBuffer = new byte[1];
                StringBuilder myCompleteMessage = new StringBuilder();
                int numberOfBytesRead = 0;

                while (netStream.DataAvailable) {
                    numberOfBytesRead = netStream.Read(myReadBuffer, 0, myReadBuffer.Length);
                    myCompleteMessage.AppendFormat("{0}", Encoding.ASCII.GetString(myReadBuffer, 0, numberOfBytesRead));
                }
                msg = myCompleteMessage.ToString();
            }
            if (msg == "")
                return (string[]) lines.ToArray(typeof(string));
            
            return msg.Split('\n');
        } catch(Exception) {
            errorPanel.SetActive(true);
        }
        string[] s = {};
        return s;
    }
    public void disconnect() {
        if (!socketReady)
            return;
        netWrite.Close();
        netRead.Close();
        socket.Close();
        socketReady = false;
    }
    private void manage_cmd_read() {
        string[] values = read();
        if (values.Length < 1)
            return;
        for (int i = 0; i < values.Length; i++) {
            string value = values[i];
            string[] args = value.Split(" ");
            if (args.Length < 2)
                continue;
            args = args.Skip(1).ToArray();
            select_command(args);
        }
    }
    private void select_command(string[] args) {
        switch (args[0]) {
            case "msz":
                this.GetComponent<Commands>().use_msz(args);;
                break;
            case "bct":
                this.GetComponent<Commands>().use_bct(args);
                break;
            case "tna":
                this.GetComponent<Commands>().use_tna(args);
                break;
            case "pnw":
                this.GetComponent<Commands>().use_pnw(args);
                break;
            case "pns":
                this.GetComponent<Commands>().use_pns(args);
                break;
            case "ppo":
                this.GetComponent<Commands>().use_ppo(args);
                break;
            case "plv":
                this.GetComponent<Commands>().use_plv(args);
                break;
            case "pin":
                this.GetComponent<Commands>().use_pin(args);
                break;
            case "pex":
                this.GetComponent<Commands>().use_pex(args);
                break;
            case "pbc":
                this.GetComponent<Commands>().use_pbc(args);
                break;
            case "pic":
                this.GetComponent<Commands>().use_pic(args);
                break;
            case "pie":
                this.GetComponent<Commands>().use_pie(args);
                break;
            case "pdr":
                this.GetComponent<Commands>().use_pdr(args);
                break;
            case "pgt":
                this.GetComponent<Commands>().use_pgt(args);
                break;
            case "pdi":
                this.GetComponent<Commands>().use_pdi(args);
                break;
            case "enw":
                this.GetComponent<Commands>().use_enw(args);
                break;
            case "eht":
                this.GetComponent<Commands>().use_eht(args);
                break;
            case "sgt":
                this.GetComponent<Commands>().use_sgt(args);
                break;
            case "seg":
                this.GetComponent<Commands>().use_seg(args);
                break;
            case "look":
                this.GetComponent<Commands>().use_look(args);
                break;
            case "pgte":
                this.GetComponent<Commands>().use_pgte(args);
                break;
            case "pexed":
                this.GetComponent<Commands>().use_pexed(args);
                break;
            default:
                break;
        }
    }
    IEnumerator useLoop() {
        while (true) {
            manage_cmd_read();
            yield return null;
        }
    }
}
