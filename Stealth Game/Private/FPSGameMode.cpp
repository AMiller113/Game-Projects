// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"


AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn * instigator_pawn, bool bMission_Success)
{
	if (instigator_pawn)
	{
		instigator_pawn->DisableInput(nullptr);

		if (spectating_view_point_class)
		{
			TArray<AActor*> returned_actors;

			UGameplayStatics::GetAllActorsOfClass(this, spectating_view_point_class, returned_actors);

			//Change view target if valid actor found
			if (returned_actors.Num() > 0)
			{
				AActor* new_view_target = returned_actors[0];

				APlayerController* player_controller = Cast<APlayerController>(instigator_pawn->GetController());

				if (player_controller)
				{
					player_controller->SetViewTargetWithBlend(new_view_target, .5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}

		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Spectating viewpoint class is cyrrently a null pointer. Please update gamemode with a valid class. Cant change view point."))
		}
	}

	OnMissionCompleted(instigator_pawn, bMission_Success);

}
