// Copyright 2020 Yevhenii Selivanov

#include "MyGameStateBase.h"
//---
#include "UnrealNetwork.h"

// Default constructor
AMyGameStateBase::AMyGameStateBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

// Returns the AMyGameStateBase::CurrentGameState property.
void AMyGameStateBase::Server_SetGameState_Implementation(EGameState NewGameState)
{
	CurrentGameState = NewGameState;
	OnRep_CurrentGameState();
}

bool AMyGameStateBase::Server_SetGameState_Validate(EGameState NewGameState)
{
	return true;
}

// Called on the AMyGameStateBase::CurrentGameState property updating.
void AMyGameStateBase::OnRep_CurrentGameState()
{
	switch (CurrentGameState)
	{
		case EGameState::None: break;
		case EGameState::OnGameStarted: Server_DecrementInGameCountdown();
			break;
		default: ;
	}
}

// Decrement the countdown timer of the current game.
void AMyGameStateBase::Server_DecrementInGameCountdown_Implementation()
{
	UWorld* World = GetWorld();
	if (!World
	    || InGameCountdown <= 0)
	{
		return;
	}

	// Decrement timer
	TWeakObjectPtr<ThisClass> WeakThis(this);
	FTimerHandle InGameCountdownTimer;
	World->GetTimerManager().SetTimer(InGameCountdownTimer, [WeakThis]
	{
		if (AMyGameStateBase* MyGameStateBase = WeakThis.Get())
		{
			MyGameStateBase->InGameCountdown--;
		}
	}, 1.F, true);
}

bool AMyGameStateBase::Server_DecrementInGameCountdown_Validate()
{
	return true;
}

// Returns properties that are replicated for the lifetime of the actor channel.
void AMyGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, InGameCountdown);
	DOREPLIFETIME(ThisClass, CurrentGameState);
}
