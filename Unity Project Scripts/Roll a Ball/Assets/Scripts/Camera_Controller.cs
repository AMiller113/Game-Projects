using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Camera_Controller : MonoBehaviour {

    public GameObject player;
    private Vector3 offset;

	void Start () {
        offset = transform.position - player.transform.position; 
	}
	
	//Happens after update
	void LateUpdate () {
        transform.position = player.transform.position + offset;
	}
}
