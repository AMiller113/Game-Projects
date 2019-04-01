using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Player_Controller : MonoBehaviour {

    //Public Variables

    public float speed;
    public Text count_text;
    public Text win_text;

    // Private Variables

    private Rigidbody rb;
    private int count;

    private void Start()
    {
        rb = GetComponent<Rigidbody>();
        count = 0;
        _set_Count_text();
        win_text.text = "";
    }

    private void FixedUpdate()
    {
        float move_horizontal = Input.GetAxis("Horizontal");
        float move_vertical = Input.GetAxis("Vertical");

        Vector3 movement = new Vector3(move_horizontal, 0.0f, move_vertical);
        rb.AddForce(movement * speed);
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.CompareTag("Pick Up"))
        {
            other.gameObject.SetActive(false);
            count++;
            _set_Count_text();
        }
    }

    private void _set_Count_text()
    {
        count_text.text = "Count: " + count.ToString();
        if (count >= 12)
        {
            win_text.text = "You win!";
        }
    }

}
