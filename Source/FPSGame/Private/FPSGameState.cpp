// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameState.h"
#include "FPSPlayerController.h"

// 각각의 클라이언트에게서 실행된다
void AFPSGameState::MulticastMissionComplete_Implementation(APawn* InstigaterPawn, bool bMissionSuccess)
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		AFPSPlayerController* PC = Cast<AFPSPlayerController>(It->Get());
		if (PC && PC->IsLocalController())
		{
			PC->OnMissionCompleted(InstigaterPawn, bMissionSuccess);

			// DisableInput
			APawn* MyPawn = PC->GetPawn();
			if (MyPawn)
			{
				MyPawn->DisableInput(PC);
			}
		}
	}
}
