// Copyright 2020 Yevhenii Selivanov

#pragma once

#include "GameFramework/GameStateBase.h"
//---
#include "MyGameStateBase.generated.h"

/**
* The replicated states of the game.
*/
UENUM(BlueprintType)
enum class EGameState : uint8
{
	None,
	//OnGameLoading,
	//OnGameReady,
	OnGameStarted
	// On reset,
	// On host migration
	// ...
};

/**
 *
 */
UCLASS()
class BOMBER_API AMyGameStateBase final : public AGameStateBase
{
	GENERATED_BODY()

public:
	/** Default constructor. */
	AMyGameStateBase();

	/** Set the new game state for the current game. */
	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation, Category = "C++")
	void Server_SetGameState(EGameState NewGameState);

	/** Returns the AMyGameStateBase::CurrentGameState property. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "C++")
	FORCEINLINE EGameState GetGameState() const { return CurrentGameState; }

	/** Returns the AMyGameStateBase::InGameCountdown property. Used by BPW_InGameWidget. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "C++")
	FORCEINLINE float GetInGameCountdown() const { return InGameCountdown; };

protected:
	/** Seconds to end of the round. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Replicated, meta=(BlueprintProtected))
	float InGameCountdown = 120.F; //[B]

	/** Store the game state for the current game. */
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = "OnRep_CurrentGameState", meta=(BlueprintProtected))
	EGameState CurrentGameState;

	/** Called on the AMyGameStateBase::CurrentGameState property updating. */
	UFUNCTION()
	void OnRep_CurrentGameState();

	/** Decrement the countdown timer of the current game. */
	UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation, Category = "C++")
    void Server_DecrementInGameCountdown();

	/** Returns properties that are replicated for the lifetime of the actor channel. */
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
};
