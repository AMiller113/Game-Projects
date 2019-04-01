using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Camera_Follow : MonoBehaviour {

    // Public Variables

    public Transform target; // Sets the target for the camera to follow
    public float smoothing = 5F; // Sets the rate of speed that the camera follows the the target 

    // Private Varibles

    Vector3 offset; // Difference between the camera position and the target position

    // Built-in Functions

    private void Start()
    {
        offset = transform.position - target.position; //Offset calculation
    }

    private void FixedUpdate()
    {
        Vector3 target_cam_pos = target.position + offset; //Set the new position for the target camera
        transform.position = Vector3.Lerp(transform.position, target_cam_pos, smoothing * Time.deltaTime); // Calculates the cameras new position and sets it.

    }
}
