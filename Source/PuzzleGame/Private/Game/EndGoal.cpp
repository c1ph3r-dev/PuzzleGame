// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/EndGoal.h"

#include "Blueprint/UserWidget.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PuzzlePlayer.h"

// Sets default values
AEndGoal::AEndGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent")));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
	Mesh->SetGenerateOverlapEvents(true);
	Mesh->SetCollisionResponseToAllChannels(ECR_Overlap);

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(Mesh);
	PointLight->LightColor = FColor::Yellow;
	PointLight->Intensity = 600.f;
	PointLight->AttenuationRadius = 1300.f;
	PointLight->SourceRadius = 80.f;
	PointLight->CastShadows = false;
}

// Called when the game starts or when spawned
void AEndGoal::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEndGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEndGoal::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	check(EndScreenWidget);

	if(const auto Player = Cast<APuzzlePlayer>(OtherActor))
	{
		if(Player->GetFollowers().Num() > 0 && Player->GetFollowers().Num() == Player->GetFollowersToCollect())
		{
			const auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			CreateWidget(PlayerController, EndScreenWidget)->AddToViewport();
			PlayerController->SetShowMouseCursor(true);
			const FInputModeUIOnly InputMode;
			PlayerController->SetInputMode(InputMode);
		}
	}
}

