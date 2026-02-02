// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GenericTeamAgentInterface.h"
#include "CGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ACGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	/**
 * Spawns the appropriate PlayerController for the given options; split out from Login() for easier overriding.
 * Override this to conditionally spawn specialized PlayerControllers, for instance.
 *
 * @param RemoteRole the role this controller will play remotely
 * @param Options the options string from the new player's URL
 *
 * @return PlayerController for the player, NULL if there is any reason this player shouldn't exist or due to some error
 */
	virtual APlayerController* SpawnPlayerController(ENetRole InRemoteRole, const FString& Options) override;
private:
	FGenericTeamId GetTeamIDForPlayer(const APlayerController* PlayerController) const;

	AActor* FindNextStartSpotForTeam(const FGenericTeamId& TeamID) const;

	UPROPERTY(EditDefaultsOnly, Category = "Team")
	TMap<FGenericTeamId, FName> TeamStartSpotTagMap;
	
};
