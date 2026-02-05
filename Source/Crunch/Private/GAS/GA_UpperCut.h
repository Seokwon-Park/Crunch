// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/CGameplayAbility.h"
#include "CGameplayAbilityTypes.h"
#include "GA_UpperCut.generated.h"

/**
 * 
 */
UCLASS()
class UGA_UpperCut : public UCGameplayAbility
{
	GENERATED_BODY()
public:
	UGA_UpperCut();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Launch")
	TMap<FName, FGenericDamageEffectDef> ComboDamageMap;

	UPROPERTY(EditDefaultsOnly, Category = "Launch")
	TSubclassOf<UGameplayEffect> LaunchDamageEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Launch")
	float UpperCutLaunchSpeed= 1000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Launch")
	float UpperCutComboSpeed = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float TargetSweepSphereRadius = 80.0f;

	UPROPERTY(EditDefaultsOnly,Category = "Animation")
	UAnimMontage* UpperCutMontage;

	static FGameplayTag GetUpperCutLaunchTag();

	const FGenericDamageEffectDef* GetDamageEffectDefForCurrentCombo() const;

	UFUNCTION()
	void StartLaunching(FGameplayEventData TargetData);

	UFUNCTION()
	void HandleComboChangeEvent(FGameplayEventData EventData);

	UFUNCTION()
	void HandleComboCommitEvent(FGameplayEventData EventData);

	UFUNCTION()
	void HandleComboDamageEvent(FGameplayEventData EventData);

	FName NextComboName;
};
