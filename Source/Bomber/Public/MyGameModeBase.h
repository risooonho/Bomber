// Copyright 2020 Yevhenii Selivanov.

#pragma once

#include "GameFramework/GameModeBase.h"
//---
#include "MyGameModeBase.generated.h"

/**
 * The custom game mode class
 */
UCLASS()
class BOMBER_API AMyGameModeBase final : public AGameModeBase
{
	GENERATED_BODY()

public:
	/** Sets default values for this actor's properties */
	AMyGameModeBase();

protected:
	/** Store the pointer to the Pong Game State. */
	UPROPERTY(BlueprintReadWrite, Category = "C++")
	class AMyGameStateBase* MyGameState;

	/** Called when the game starts or when spawned */
	virtual void BeginPlay() override;

	/** Called after a successful login.  This is the first place it is safe to call replicated functions on the PlayerController. */
	virtual void PostLogin(APlayerController* NewPlayer) override;

	/** Called when all players were connected. */
	UFUNCTION(BlueprintCallable, Category = "C++", meta = (BlueprintProtected))
	void OnGameStarted();
};
