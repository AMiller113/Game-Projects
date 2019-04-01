// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,Suspicious,Alerted
};

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:

	FRotator original_rotation;

	FTimerHandle timer_handler_reset_orientation;

	EAIState guard_state;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPawnSensingComponent* pawn_sensing_component;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void ResetOrientation();

	UFUNCTION()
		void OnPawnSeen(APawn* seen_pawn);

	UFUNCTION()
		void OnNoiseHeard(APawn* noise_instigator, const FVector& Location, float Volume);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnStateChanged(EAIState new_state);

	void SetGuardState(EAIState new_state);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
