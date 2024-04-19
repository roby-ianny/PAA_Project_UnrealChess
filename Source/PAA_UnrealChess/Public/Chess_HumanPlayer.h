// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Chess_GameInstance.h"
#include "Chess_PlayerInterface.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Chess_HumanPlayer.generated.h"

UCLASS()
class PAA_UNREALCHESS_API AChess_HumanPlayer : public APawn, public IChess_PlayerInterface //Doppia ereditarietà
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AChess_HumanPlayer();

	// camera component 
	UCameraComponent* Camera;

	// game instance reference
	UChess_GameInstance* GameInstance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//turn tracking
	bool IsMyTurn = false;

	bool PieceSelected = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// overriding virtual functions
	virtual void OnTurn() override;
	virtual void OnWin() override;
	virtual void OnLose() override;

	// Called when player does a left mouse click
	UFUNCTION()
	void OnClick();

};
