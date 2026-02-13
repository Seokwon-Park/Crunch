// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "TA_GroundPick.generated.h"

/**
 *
 */
UCLASS()
class ATA_GroundPick : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
public:
	ATA_GroundPick();
	void SetTargetAreaRadius(float NewRadius);
	FORCEINLINE void SetTargetTraceRange(float NewRange) { TargetTraceRange = NewRange; }
	virtual void ConfirmTargetingAndContinue() override;
	void SetTargetOptions(bool bTargetFriendly, bool bTargetEnemy);
	FORCEINLINE void SetShouldDrawDebug(bool bDrawDebug) { bShouldDrawDebug = bDrawDebug; }

private:
	UPROPERTY(EditDefaultsOnly, Category = "Targetting")
	class UDecalComponent* DecalComponent;
	
	bool bShouldTargetEnemy = true;
	bool bShouldTargetFriendly = false;

	virtual void Tick(float DeltaTime) override;

	FVector GetTargetPoint() const;

	UPROPERTY(EditDefaultsOnly, Category = "Targetting")
	float TargetAreaRadius = 300.f;


	UPROPERTY(EditDefaultsOnly, Category = "Targetting")
	float TargetTraceRange = 2000.f;

	bool bShouldDrawDebug = false;
};
