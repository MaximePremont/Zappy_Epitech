using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.XR.ARFoundation;

public class ARCursor : MonoBehaviour {
    public GameObject cursorChildObject;
    public GameObject objectToPlace;
    public ARRaycastManager raycastManager;
    public GameObject zero;
    public GameObject menu;
    public GameObject island;
    public ARPlaneManager pmanager;

    public bool useCursor = true;

    void Start() {
        cursorChildObject.SetActive(useCursor);
    }

    void Update() {
        if (useCursor) {
            UpdateCursor();
        }

        if (Input.touchCount > 0 && Input.GetTouch(0).phase == TouchPhase.Began) {
            if (useCursor) {
                zero.transform.position = transform.position;
                island.transform.position = zero.transform.position;
                island.SetActive(true);
                menu.SetActive(true);
                pmanager.enabled = false;
                this.gameObject.SetActive(false);
            } else {
                List<ARRaycastHit> hits = new List<ARRaycastHit>();
                raycastManager.Raycast(Input.GetTouch(0).position, hits, UnityEngine.XR.ARSubsystems.TrackableType.Planes);
                if (hits.Count > 0) {
                    GameObject.Instantiate(objectToPlace, hits[0].pose.position, hits[0].pose.rotation);
                }
            }
        }
    }

    void UpdateCursor() {
        Vector2 screenPosition = Camera.main.ViewportToScreenPoint(new Vector2(0.5f, 0.5f));
        List<ARRaycastHit> hits = new List<ARRaycastHit>();
        raycastManager.Raycast(screenPosition, hits, UnityEngine.XR.ARSubsystems.TrackableType.Planes);

        if (hits.Count > 0) {
            transform.position = hits[0].pose.position;
            transform.rotation = hits[0].pose.rotation;
        }
    }
}
