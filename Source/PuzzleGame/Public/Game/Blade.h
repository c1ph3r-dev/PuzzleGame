// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Game/Progressor.h"
#include "Blade.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEGAME_API ABlade : public AProgressor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess="true"))
	USceneComponent* SceneRoot;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess="true"))
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess="true"))
	class UPointLightComponent* PointLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* Base;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess="true"))
	bool bMovingForward;

	FVector StartPosition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess="true"))
	int MoveTicks;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Movement, meta=(AllowPrivateAccess="true"))
	int CurrentMoveTicks;

	FTimerHandle DelayHandle;
public:
	ABlade();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void Move(FVector TargetPos);

	void CheckHit();

public:
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void OnProgress() override;
};
