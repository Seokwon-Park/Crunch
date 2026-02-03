// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Minion.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void AMinion::SetGenericTeamId(const FGenericTeamId& NewTeamId)
{
	Super::SetGenericTeamId(NewTeamId);
	PickSkinBasedOnTeamID();
}

bool AMinion::IsActive() const
{
	return !IsDead();
}

void AMinion::Activate()
{
	RespawnImmediately();
}

void AMinion::SetGoal(AActor* Goal)
{
	if (AAIController* AIController = GetController<AAIController>())
	{
		UE_LOG(LogTemp, Warning, TEXT("AIControllerIsNotNull"))

		if (UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent())
		{
			UE_LOG(LogTemp, Warning, TEXT("BB Is Not Null"))
			BlackboardComponent->SetValueAsObject(GoalBlackboardKeyName, Goal);
		}
	}
}

void AMinion::PickSkinBasedOnTeamID()
{
	USkeletalMesh** Skin = SkinMap.Find(GetGenericTeamId());
	if (Skin)
	{
		GetMesh()->SetSkeletalMesh(*Skin);
	}
}

void AMinion::OnRep_TeamID()
{
	PickSkinBasedOnTeamID();
}
