// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSLaunchPad.h"
#include "FPSCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

// overlap -> Launch Character

// Sets default values
AFPSLaunchPad::AFPSLaunchPad()
{
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);

	OverlapComp->SetBoxExtent(FVector(100.0f, 100.0f, 20.0f));
	RootComponent = OverlapComp;

	OverlapComp->SetHiddenInGame(false);

	//OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchPad::HandleOverlap);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	ArrowComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowComp"));
	ArrowComp->SetupAttachment(MeshComp);

	LaunchStrength = 1500.f;
	LaunchPitchAngle = 35.0f;
}

void AFPSLaunchPad::BeginPlay()
{
	Super::BeginPlay();
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSLaunchPad::HandleOverlap);
}

void AFPSLaunchPad::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, ActivateLaunchPadEffect, GetActorLocation());
}

void AFPSLaunchPad::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FRotator LaunchDirection = GetActorRotation();
	LaunchDirection.Pitch += LaunchPitchAngle;
	UE_LOG(LogTemp, Log, TEXT("%f"), LaunchDirection.Pitch);
	FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrength;

	FVector Velocity = FVector(1000.f, 0.0f, 800.f);

	ACharacter* Object = Cast<ACharacter>(OtherActor);
	if (Object)
	{
		PlayEffects();
		Object->LaunchCharacter(LaunchVelocity, true, true);
	}
	else if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		PlayEffects();
		OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);
	}

	
}
