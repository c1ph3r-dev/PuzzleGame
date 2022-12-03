// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Follower.h"

#include "Components/PointLightComponent.h"

AFollower::AFollower()
	: bCanMove(false)
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(SceneRoot);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->SetCollisionResponseToAllChannels(ECR_Overlap);

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(Mesh);
	PointLight->LightColor = FColor::Cyan;
	PointLight->Intensity = 3000.f;
	PointLight->AttenuationRadius = 200.f;
	PointLight->SourceRadius = 35.f;
	PointLight->CastShadows = true;
}

void AFollower::BeginPlay()
{
	Super::BeginPlay();

	TargetPosition = GetActorLocation();
}

void AFollower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(bCanMove)
		Move(TargetPosition);
}

void AFollower::OnProgress()
{
	Super::OnProgress();

	if(!bCanMove) return;;

	TargetPosition = Target->GetActorLocation();
}
