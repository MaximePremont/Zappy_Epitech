using System.Collections;
using UnityEngine;
using System;
using System.Text;
using System.Linq;

public class Broadcasts : MonoBehaviour {
    private ArrayList messages = new ArrayList();
    public UnityEngine.UI.Text text0;
    public UnityEngine.UI.Text text1;
    public UnityEngine.UI.Text text2;
    public UnityEngine.UI.Text text3;
    public UnityEngine.UI.Text text4;
    public UnityEngine.UI.Text but;
    private bool translated = false;
    private string xorIt(string key, string input) {
    StringBuilder sb = new StringBuilder();
    for(int i = 0; i < input.Length; i++)
        sb.Append((char)(input[i] ^ key[(i % key.Length)]));
    String result = sb.ToString ();
    return result;
    }
    public static string HextoString(string InputText) {
   
      byte[] bb = Enumerable.Range(0, InputText.Length)
                       .Where(x => x % 2 == 0)
                       .Select(x => Convert.ToByte(InputText.Substring(x, 2), 16))
                       .ToArray();
      return System.Text.Encoding.UTF8.GetString(bb);
  }
    private string getText(ArrayList vals) {
        string txt = (string) vals[2];
        string team = (string) vals[1];
        if (translated) {
            txt = HextoString(txt);
            txt = xorIt(team, txt);
        } else {
            int randLen = (new System.Random()).Next(12)+8;
            txt = "";
            for (int i = 0; i < randLen; i++)
                txt += ((char)(new System.Random()).Next('0', '}')+"");
        }
        return txt;
    }
    private void refresh() {
        if (messages.Count > 0) {
            ArrayList vals = (ArrayList) messages[0];
            text0.text = ((int)vals[0])+" ("+((string)vals[1])+") : "+getText(vals);
        }
        if (messages.Count > 1) {
            ArrayList vals = (ArrayList) messages[1];
            text1.text = ((int)vals[0])+" ("+((string)vals[1])+") : "+getText(vals);
        }
        if (messages.Count > 2) {
            ArrayList vals = (ArrayList) messages[2];
            text2.text = ((int)vals[0])+" ("+((string)vals[1])+") : "+getText(vals);
        }
        if (messages.Count > 3) {
            ArrayList vals = (ArrayList) messages[3];
            text3.text = ((int)vals[0])+" ("+((string)vals[1])+") : "+getText(vals);
        }
        if (messages.Count > 4) {
            ArrayList vals = (ArrayList) messages[4];
            text4.text = ((int)vals[0])+" ("+((string)vals[1])+") : "+getText(vals);
        }
    }
    public void sendText(string text, int n, string team) {
        ArrayList content = new ArrayList();
        content.Add(n);
        content.Add(team);
        content.Add(text);
        messages.Add(content);
        if (messages.Count > 5) {
            for (int i = 0; i < 6; i++)
                messages[i] = messages[i + 1];
        }
        refresh();
    }
    public void toggleView() {
        translated = !translated;
        if (!translated)
            but.text = "❍";
        else
            but.text = "⦿";
        refresh();
    }
}
