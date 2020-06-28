// Copyright 2020 Yevhenii Selivanov.

#include "MyGameModeBase.h"
//---
#include "MyHUD.h"
#include "MyPlayerController.h"
#include "MyGameStateBase.h"
//---

// Sets default values for this actor's properties
AMyGameModeBase::AMyGameModeBase()
{
	// Custom defaults classes
	GameStateClass = AMyGameStateBase::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
	HUDClass = AMyHUD::StaticClass();
	DefaultPawnClass = nullptr;
}

// Called when the game starts or when spawned
void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called after a successful login
void AMyGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (!NewPlayer)
	{
		return;
	}

	const int32 PlayersNum = GetNumPlayers();
	if (PlayersNum /*&& PlayersNum == USingletonLibrary::GetCharactersNum()*/) // all players were connected
	{
		OnGameStarted();
	}
}

// Called when all players were connected.
void AMyGameModeBase::OnGameStarted()
{
	MyGameState = GetGameState<AMyGameStateBase>();
	if (MyGameState)
	{
		MyGameState->Server_SetGameState(EGameState::OnGameStarted);
	}
}
