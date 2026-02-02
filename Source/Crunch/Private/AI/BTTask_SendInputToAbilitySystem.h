// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GAS/CGameplayAbilityTypes.h"
#include "BTTask_SendInputToAbilitySystem.generated.h"

/**
 * 
 */
UCLASS()
class UBTTask_SendInputToAbilitySystem : public UBTTaskNode
{
	GENERATED_BODY()

public:
	/** starts this task, should return Succeeded, Failed or InProgress
 *  (use FinishLatentTask() when returning InProgress)
 * this function should be considered as const (don't modify state of object) if node is not instanced! */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere)
	ECAbilityInputID InputID;
	
};
