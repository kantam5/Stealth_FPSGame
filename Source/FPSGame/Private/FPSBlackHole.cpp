// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSBlackHole.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
AFPSBlackHole::AFPSBlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	InnerSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComponent"));
	InnerSphereComponent->SetupAttachment(MeshComp);
	InnerSphereComponent->SetSphereRadius(130);

	InnerSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPSBlackHole::OverlapInnerSphere);

	OuterSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphereComponent"));
	OuterSphereComponent->SetupAttachment(MeshComp);
	OuterSphereComponent->SetSphereRadius(4000);

}

void AFPSBlackHole::OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		OtherActor->Destroy();
	}
}

// Called every frame
void AFPSBlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> OverlappingComponents;
	OuterSphereComponent->GetOverlappingComponents(OverlappingComponents);

	for (UPrimitiveComponent* OverlappingComponent : OverlappingComponents)
	{
		const float Radius = InnerSphereComponent->GetScaledSphereRadius();
		const float Strength = -2000.f;
		if (OverlappingComponent && OverlappingComponent->IsSimulatingPhysics())
		{
			OverlappingComponent->AddRadialForce(GetActorLocation(), Radius, Strength, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}
}
