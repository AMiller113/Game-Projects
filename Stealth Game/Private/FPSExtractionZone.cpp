// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "FPSCharacter.h"
#include "FPSGameMode.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"




// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
	Overlap_Component = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap_Component"));
	Overlap_Component->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Overlap_Component->SetCollisionResponseToAllChannels(ECR_Ignore);
	Overlap_Component->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	Overlap_Component->SetBoxExtent(FVector(200.f));
	RootComponent = Overlap_Component;

	Overlap_Component->SetHiddenInGame(false);
	Overlap_Component->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap);

	Decal_Component = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal_Component"));
	Decal_Component->DecalSize = FVector(200.f);
	Decal_Component->SetupAttachment(RootComponent);
}

void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	

	AFPSCharacter* my_pawn = Cast<AFPSCharacter>(OtherActor);

	if (my_pawn == nullptr)
	{
		return;
	}

	

	if (my_pawn->bIs_carrying_Objective)
	{
		AFPSGameMode* game_mode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());

		if (game_mode)
		{
			game_mode->CompleteMission(my_pawn, true);
		}
	}
	else
	{
		UGameplayStatics::PlaySound2D(this, objective_missing_sound);
	}

	UE_LOG(LogTemp, Log, TEXT("Overlapped with extraction zone"));
}


