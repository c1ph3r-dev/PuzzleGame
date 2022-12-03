// Copyright Epic Games, Inc. All Rights Reserved.


#include "PuzzleGameGameModeBase.h"

#include "Game/Follower.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PuzzlePlayer.h"

void APuzzleGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	const auto World = GetWorld();

	TArray<AActor*> Followers;
	UGameplayStatics::GetAllActorsOfClass(World, AFollower::StaticClass(), Followers);

	Cast<APuzzlePlayer>(UGameplayStatics::GetPlayerPawn(World, 0))->SetFollowersToCollect(Followers.Num());
}
