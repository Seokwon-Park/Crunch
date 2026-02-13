// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/CGameplayAbility.h"
#include "GAS/CGameplayAbilityTypes.h"
#include "GA_GroundBlast.generated.h"

/**
 *
 */
UCLASS()
class UGA_GroundBlast : public UCGameplayAbility
{
	GENERATED_BODY()
public:
	UGA_GroundBlast();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
private:
	UPROPERTY(EditDefaultsOnly, Category = "Cue")
	FGameplayTag BlastGameplayCueTag;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FGenericDamageEffectDef DamageEffectDef;

	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float TargetAreaRadius = 300.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float TargetTraceRange = 2000.0;

	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	TSubclassOf<class ATA_GroundPick> TargetActorClass;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* AimmingMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* CastMontage;

	UFUNCTION()
	void TargetConfirmed(const FGameplayAbilityTargetDataHandle& TargetDataHandle);
	UFUNCTION()
	void TargetCancelled(const FGameplayAbilityTargetDataHandle& TargetDataHandle);

};
