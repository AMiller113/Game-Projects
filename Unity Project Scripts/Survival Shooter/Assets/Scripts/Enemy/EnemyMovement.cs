using UnityEngine;
using System.Collections;

public class EnemyMovement : MonoBehaviour
{
    Transform player; //Player Transform
    PlayerHealth playerHealth; //Players Health Script Component
    EnemyHealth enemyHealth; //Enemy Health Script Component
    UnityEngine.AI.NavMeshAgent nav; //Enemy NavMesh Agent


    void Awake ()
    {
        player = GameObject.FindGameObjectWithTag ("Player").transform; //Finds the Player transform using the player tag
        playerHealth = player.GetComponent <PlayerHealth> (); //Finds the player health script attacthed to the player
        enemyHealth = GetComponent <EnemyHealth> (); //Finds the Enemy Health Script attached to the enemy component
        nav = GetComponent <UnityEngine.AI.NavMeshAgent> (); //Finds the nav mesh agent 
    }


    void Update ()
    {
        if(enemyHealth.currentHealth > 0 && playerHealth.currentHealth > 0) // Checks if the player is still alive
        {
            nav.SetDestination (player.position); //Sets the nav to move the enemy towards the player
        }
        else
        {
            nav.enabled = false; //Shuts off nav if player is dead
        }
    }
}
