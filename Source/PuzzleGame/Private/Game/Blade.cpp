// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/Blade.h"

#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PuzzlePlayer.h"

ABlade::ABlade()
	: bMovingForward(true),
	StartPosition(FVector(0.f)),
	MoveTicks(5), CurrentMoveTicks(0)
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(SceneRoot);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->SetCollisionResponseToAllChannels(ECR_Overlap);

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(Mesh);
	PointLight->LightColor = FColor::Red;
	PointLight->Intensity = 2500.f;
	PointLight->AttenuationRadius = 100.f;
	PointLight->SourceRadius = 85.f;
	PointLight->CastShadows = true;

	Base = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base"));
	Base->SetupAttachment(GetRootComponent());
}

void ABlade::BeginPlay()
{
	Super::BeginPlay();

	StartPosition = Mesh->GetRelativeLocation();
}

void ABlade::CheckHit()
{
	TArray<AActor*> Actors;
	Mesh->GetOverlappingActors(Actors);

	if(Actors.Num() == 0) return;

	if(const auto Player = Cast<APuzzlePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		Player->GameOver();
	}
}

void ABlade::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	Mesh->AddWorldRotation(FRotator(0.f, DeltaSeconds * 180.f, 0.f));

	FVector NewPos = GetActorForwardVector();
	const int Multiplier = CurrentMoveTicks * 100.f;
	NewPos *= Multiplier;
	NewPos += StartPosition;
	
	Move(NewPos);
}

void ABlade::OnProgress()
{
	Super::OnProgress();

	if (bMovingForward)
	{
		if (MoveTicks == CurrentMoveTicks)
		{
			bMovingForward = false;
			CurrentMoveTicks--;
		}
		else
			CurrentMoveTicks++;
	}
	else
	{
		if (CurrentMoveTicks == 0)
		{
			bMovingForward = true;
			CurrentMoveTicks++;
		}
		else
			CurrentMoveTicks--;
	}

	GetWorld()->GetTimerManager().SetTimer(DelayHandle, this, &ABlade::CheckHit, 0.25f);
}
