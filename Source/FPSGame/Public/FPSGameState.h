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
	// NetMulticast ������Ƽ�� ��� Ŭ���̾�Ʈ���� ���ư��� �Ѵ�. 
	UFUNCTION(NetMulticast, Reliable)
	void MulticastMissionComplete(APawn* InstigaterPawn, bool bMissionSuccess);
};
