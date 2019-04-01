// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSObjectiveActor.generated.h"

class USphereComponent;

UCLASS()
class FPSGAME_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSObjectiveActor();

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	//Static mesh component of the actor
	UStaticMeshComponent * mesh_comp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	//Will hold collision information
	USphereComponent* sphere_comp; 

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* Pickup_FX;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Plays an effect when this objective is interacted with by the player
	void PlayEffects();

public:	

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
