// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PuzzlePlayer.generated.h"

UCLASS()
class PUZZLEGAME_API APuzzlePlayer : public APawn
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess="true"))
	USceneComponent* SceneRoot;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess="true"))
	class UStaticMeshComponent* Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess="true"))
	class UPointLightComponent* PointLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess="true"))
	class UBoxComponent* WallChecker;

	void SetupComponents();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Movement, meta=(AllowPrivateAccess="true"))
	bool bCanMove;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess="true"))
	FVector TargetPosition;

	void CallProgressors();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	TArray<class AFollower*> Followers;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	int FollowersToCollect;
public:
	// Sets default values for this pawn's properties
	APuzzlePlayer();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveUp();
	void MoveDown();
	void MoveRight();
	void MoveLeft();

	bool WallCheck(FVector PositionCheck) const;

	UFUNCTION(BlueprintImplementableEvent)
	void ResetCanMove();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GameOver();
	
	FORCEINLINE void SetFollowersToCollect(const int Value) { FollowersToCollect = Value; }

	FORCEINLINE TArray<AFollower*> GetFollowers() const { return Followers; }
	FORCEINLINE int GetFollowersToCollect() const { return FollowersToCollect; }
};
