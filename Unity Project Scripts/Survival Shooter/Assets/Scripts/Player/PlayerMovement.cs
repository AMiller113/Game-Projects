using UnityEngine;

public class PlayerMovement : MonoBehaviour
{
    //Public Variables

    public float speed = 6f;

    // Private Variables

    Vector3 movement;
    Animator anim;
    Rigidbody player_rigidbody;
    int floor_mask;
    float cam_ray_length =  100f;

    // Built in Functions
    
    private void Awake()
    {
        floor_mask = LayerMask.GetMask("Floor");
        anim = GetComponent<Animator>();
        player_rigidbody = GetComponent<Rigidbody>();
    }

    private void FixedUpdate()
    {
        float h = Input.GetAxisRaw("Horizontal");
        float v = Input.GetAxisRaw("Vertical");

        _Move(h, v);
        _Turning();
        _Animating(h, v);
    }

    // User Generated Functions

    private void _Move(float h,float v)
    {
        movement.Set(h,0f,v);

        movement = movement.normalized * speed * Time.deltaTime;

        player_rigidbody.MovePosition(transform.position + movement);
    }

    private void _Turning()
    {
        Ray cam_ray = Camera.main.ScreenPointToRay(Input.mousePosition);

        RaycastHit floor_hit;

        if(Physics.Raycast(cam_ray, out floor_hit, cam_ray_length, floor_mask))
        {
            Vector3 player_to_mouse = floor_hit.point - transform.position;

            player_to_mouse.y = 0f;

            Quaternion new_rotation = Quaternion.LookRotation(player_to_mouse);

            player_rigidbody.MoveRotation(new_rotation);
        }
    }
    
    void _Animating(float h, float v)
    {
        bool walking = h != 0f || v != 0f;
        anim.SetBool("IsWalking", walking);
    }
}
