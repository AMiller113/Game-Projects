// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSObjectiveActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "FPSCharacter.h"


// Sets default values
AFPSObjectiveActor::AFPSObjectiveActor()
{
	mesh_comp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Comp"));
	mesh_comp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = mesh_comp;

	sphere_comp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere_Comp"));
	sphere_comp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	sphere_comp->SetCollisionResponseToAllChannels(ECR_Ignore);
	sphere_comp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	sphere_comp->SetupAttachment(mesh_comp);

}

// Called when the game starts or when spawned
void AFPSObjectiveActor::BeginPlay()
{
	Super::BeginPlay();

	PlayEffects();
	
}

void AFPSObjectiveActor::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AFPSCharacter* My_Character = Cast<AFPSCharacter>(OtherActor);

	if (My_Character)
	{
		My_Character->bIs_carrying_Objective = true;

		PlayEffects();
	
		Destroy();
	}
}



//Plays an effect when the Objective is picked up
void AFPSObjectiveActor::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this,Pickup_FX,GetActorLocation());

}
