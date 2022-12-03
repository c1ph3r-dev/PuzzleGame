// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Progressor.h"
#include "Follower.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEGAME_API AFollower : public AProgressor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess="true"))
	USceneComponent* SceneRoot;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess="true"))
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess="true"))
	class UPointLightComponent* PointLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Movement, meta=(AllowPrivateAccess="true"))
	bool bCanMove;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess="true"))
	FVector TargetPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess="true"))
	AActor* Target;

public:
	AFollower();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void Move(FVector TargetPos);

public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void OnProgress() override;

	FORCEINLINE void SetTarget(AActor* TargetActor) { Target = TargetActor; bCanMove = true; }
};
