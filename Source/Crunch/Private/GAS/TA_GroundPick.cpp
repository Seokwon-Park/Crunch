// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/TA_GroundPick.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Crunch/Crunch.h"
#include "Engine/OverlapResult.h"
#include "GenericTeamAgentInterface.h"
#include "Components/DecalComponent.h"

ATA_GroundPick::ATA_GroundPick()
{
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Root Comp"));
	DecalComponent = CreateDefaultSubobject<UDecalComponent>("Decal Comp");
	DecalComponent->SetupAttachment(GetRootComponent());

}

void ATA_GroundPick::SetTargetAreaRadius(float NewRadius)
{
	TargetAreaRadius = NewRadius;
	DecalComponent->DecalSize = FVector(NewRadius);
}

void ATA_GroundPick::ConfirmTargetingAndContinue()
{
	TArray<FOverlapResult> OverlapResults;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);

	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(TargetAreaRadius);

	GetWorld()->OverlapMultiByObjectType(OverlapResults, GetActorLocation(), FQuat::Identity, ObjectQueryParams,
		CollisionShape
	);

	TSet<AActor*> TargetActors;

	IGenericTeamAgentInterface* OwnerTeamInterface = nullptr;
	if (OwningAbility)
	{
		OwnerTeamInterface = Cast<IGenericTeamAgentInterface>(OwningAbility->GetAvatarActorFromActorInfo());
	}


	for (const FOverlapResult& OverlapResult : OverlapResults)
	{
		if (OwnerTeamInterface && OwnerTeamInterface->GetTeamAttitudeTowards(*OverlapResult.GetActor()) == ETeamAttitude::Friendly && !bShouldTargetFriendly)continue;
		if (OwnerTeamInterface && OwnerTeamInterface->GetTeamAttitudeTowards(*OverlapResult.GetActor()) == ETeamAttitude::Hostile && !bShouldTargetEnemy)continue;

		TargetActors.Add(OverlapResult.GetActor());
	}

	FGameplayAbilityTargetDataHandle TargetData = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActorArray(TargetActors.Array(), false);

	FGameplayAbilityTargetData_SingleTargetHit* HitLoc = new FGameplayAbilityTargetData_SingleTargetHit;
	HitLoc->HitResult.ImpactPoint = GetActorLocation();

	TargetData.Add(HitLoc);

	TargetDataReadyDelegate.Broadcast(TargetData);
}

void ATA_GroundPick::SetTargetOptions(bool bTargetFriendly, bool bTargetEnemy)
{
	bShouldTargetFriendly = bTargetFriendly;
	bShouldTargetEnemy = bTargetEnemy;
}

void ATA_GroundPick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PrimaryPC && PrimaryPC->IsLocalPlayerController())
	{
		SetActorLocation(GetTargetPoint());
	}
}

FVector ATA_GroundPick::GetTargetPoint() const
{
	if (!PrimaryPC && !PrimaryPC->IsLocalPlayerController())
		return GetActorLocation();

	FHitResult TraceResult;

	FVector ViewLoc;
	FRotator ViewRot;

	PrimaryPC->GetPlayerViewPoint(ViewLoc, ViewRot);

	FVector TraceEnd = ViewLoc + ViewRot.Vector() * TargetTraceRange;
	GetWorld()->LineTraceSingleByChannel(TraceResult, ViewLoc, TraceEnd, ECC_Target);

	if (!TraceResult.bBlockingHit)
	{
		GetWorld()->LineTraceSingleByChannel(TraceResult, TraceEnd, TraceEnd + FVector::DownVector * TNumericLimits<float>::Max(), ECC_Target);
	}

	if (!TraceResult.bBlockingHit)
	{
		return GetActorLocation();
	}

	if (bShouldDrawDebug)
	{
		DrawDebugSphere(GetWorld(), TraceResult.ImpactPoint, TargetAreaRadius, 32, FColor::Red);
	}

	return TraceResult.ImpactPoint;
}


