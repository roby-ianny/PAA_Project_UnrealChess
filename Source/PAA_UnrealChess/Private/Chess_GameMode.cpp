// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_GameMode.h"

// Keep the default constructor just for now
AChess_GameMode::AChess_GameMode()
{
}


void AChess_GameMode::BeginPlay()
{
	Super::BeginPlay();

	IsGameOver = false;

	//spawns the gamefield
	if (GameFieldClass != nullptr) {
		GField = GetWorld()->SpawnActor<AChess_GameField>(GameFieldClass);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Game Field is null"));
	}

	//TODO
}
