// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "FPSGameState.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	// NetMulticast 프로퍼티는 모든 클라이언트에서 돌아가게 한다. 
	UFUNCTION(NetMulticast, Reliable)
	void MulticastMissionComplete(APawn* InstigaterPawn, bool bMissionSuccess);
};
