// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PuzzlePlayer.h"

#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "Game/Follower.h"
#include "Game/Progressor.h"
#include "Kismet/GameplayStatics.h"

void APuzzlePlayer::SetupComponents()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(SceneRoot);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(Mesh);
	PointLight->LightColor = FColor::Emerald;
	PointLight->Intensity = 4500.f;
	PointLight->AttenuationRadius = 300.f;
	PointLight->SourceRadius = 20.f;
	PointLight->CastShadows = false;

	WallChecker = CreateDefaultSubobject<UBoxComponent>(TEXT("WallChecker"));
	WallChecker->SetupAttachment(GetRootComponent());
	WallChecker->SetGenerateOverlapEvents(true);

	FCollisionResponseContainer Responses;
	Responses.SetAllChannels(ECR_Ignore);
	Responses.SetResponse(ECC_Visibility, ECR_Overlap);
	Responses.SetResponse(ECC_Camera, ECR_Overlap);
	Responses.SetResponse(ECC_WorldStatic, ECR_Overlap);
	WallChecker->SetCollisionResponseToChannels(Responses);
}

void APuzzlePlayer::CallProgressors()
{
	TArray<AActor*> Progressors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AProgressor::StaticClass(), Progressors);

	for(const auto& Actor : Progressors)
	{
		const auto Progressor = Cast<AProgressor>(Actor);
		Progressor->OnProgress();
	}
}

// Sets default values
APuzzlePlayer::APuzzlePlayer()
	: bCanMove(true), TargetPosition(FVector(0.f)),
	FollowersToCollect(0)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetupComponents();
}

void APuzzlePlayer::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (const auto Follower = Cast<AFollower>(OtherActor))
	{
		if(Followers.Contains(Follower)) return;

		if(Followers.Num() > 0)
			Follower->SetTarget(Followers.Last());
		else
			Follower->SetTarget(this);
		
		Followers.Add(Follower);
	}
}

// Called when the game starts or when spawned
void APuzzlePlayer::BeginPlay()
{
	Super::BeginPlay();

	const auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	const FInputModeGameOnly InputMode;
	PlayerController->SetShowMouseCursor(false);
	PlayerController->SetInputMode(InputMode);
}

void APuzzlePlayer::MoveUp()
{
	if(!bCanMove || WallCheck(FVector(100.f, 0.f, 50.f))) return;

	TargetPosition = TargetPosition + FVector(100.f, 0.f, 0.f);

	ResetCanMove();
	CallProgressors();
}

void APuzzlePlayer::MoveDown()
{
	if(!bCanMove || WallCheck(FVector(-100.f, 0.f, 50.f))) return;

	TargetPosition = TargetPosition + FVector(-100.f, 0.f, 0.f);

	ResetCanMove();
	CallProgressors();
}

void APuzzlePlayer::MoveRight()
{
	if(!bCanMove || WallCheck(FVector(0.f, 100.f, 50.f))) return;

	TargetPosition = TargetPosition + FVector(0.f, 100.f, 0.f);

	ResetCanMove();
	CallProgressors();
}

void APuzzlePlayer::MoveLeft()
{
	if(!bCanMove || WallCheck(FVector(0.f, -100.f, 50.f))) return;

	TargetPosition = TargetPosition + FVector(0.f, -100.f, 0.f);

	ResetCanMove();
	CallProgressors();
}

bool APuzzlePlayer::WallCheck(const FVector PositionCheck) const
{
	WallChecker->SetRelativeLocation(PositionCheck);
	TArray<AActor*> OverlappingActors;
	WallChecker->GetOverlappingActors(OverlappingActors, AActor::StaticClass());

	return OverlappingActors.Num() > 0;
}

// Called every frame
void APuzzlePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APuzzlePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("MoveUp", IE_Pressed, this, &APuzzlePlayer::MoveUp);
	PlayerInputComponent->BindAction("MoveDown", IE_Pressed, this, &APuzzlePlayer::MoveDown);
	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &APuzzlePlayer::MoveRight);
	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &APuzzlePlayer::MoveLeft);
}

void APuzzlePlayer::GameOver()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(UGameplayStatics::GetCurrentLevelName(GetWorld())));
}

