// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "FPSGameMode.h"
#include "Engine/World.h"


// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	pawn_sensing_component = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn_Sensing_Component"));

	pawn_sensing_component->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	pawn_sensing_component->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnNoiseHeard);

	guard_state = EAIState::Idle;

}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();

	original_rotation = GetActorRotation();
}

void AFPSAIGuard::ResetOrientation()
{
	if (guard_state == EAIState::Alerted)
	{
		return;
	}

	SetActorRotation(original_rotation);

	SetGuardState(EAIState::Idle);
}

void AFPSAIGuard::OnPawnSeen(APawn * seen_pawn)
{
	if (seen_pawn == nullptr)
	{
		return;
	}
	DrawDebugSphere(GetWorld(),seen_pawn->GetActorLocation(),32.f,12,FColor::Red,false,10.f);

	AFPSGameMode* game_mode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());

	if (game_mode)
	{
		game_mode->CompleteMission(seen_pawn, false);
	}

	SetGuardState(EAIState::Alerted);
}

void AFPSAIGuard::OnNoiseHeard(APawn * noise_instigator, const FVector & Location, float Volume)
{
	if (guard_state == EAIState::Alerted)
	{
		return;
	}

	DrawDebugSphere(GetWorld(), Location, 32.f, 12, FColor::Blue,false, 10.f);

	FVector direction = Location - GetActorLocation();
	FRotator new_look_at = FRotationMatrix::MakeFromX(direction).Rotator();
	new_look_at.Pitch = 0.f;
	new_look_at.Roll = 0.f;

	SetActorRotation(new_look_at);
	GetWorldTimerManager().ClearTimer(timer_handler_reset_orientation);
	GetWorldTimerManager().SetTimer(timer_handler_reset_orientation, this, &AFPSAIGuard::ResetOrientation, 3.f);

	SetGuardState(EAIState::Suspicious);
}

void AFPSAIGuard::SetGuardState(EAIState new_state)
{
	if (guard_state == new_state)
	{
		return;
	}

	guard_state = new_state;

	OnStateChanged(guard_state);
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


