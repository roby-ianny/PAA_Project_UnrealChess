// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_GameMode.h"
#include "Chess_PlayerController.h"
#include "Chess_HumanPlayer.h"
#include "Chess_CPURandom.h"
#include "EngineUtils.h"


// Keep the default constructor just for now
AChess_GameMode::AChess_GameMode()
{
	PlayerControllerClass = AChess_PlayerController::StaticClass();
	DefaultPawnClass = AChess_HumanPlayer::StaticClass();
}


void AChess_GameMode::BeginPlay()
{
	Super::BeginPlay();

	IsGameOver = false;

	AChess_HumanPlayer* HumanPlayer = Cast<AChess_HumanPlayer>(*TActorIterator<AChess_HumanPlayer>(GetWorld()));
	//spawns the gamefield
	if (GameFieldClass != nullptr) {
		GField = GetWorld()->SpawnActor<AChess_GameField>(GameFieldClass);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Game Field is null"));
	}

	//camera things
	/*
	float CameraPosX = ((GField->TileSize * (FieldSize + ((FieldSize - 1) * GField->NormalizedCellPadding) - (FieldSize - 1))) / 2) - (GField->TileSize / 2);
	FVector CameraPos(CameraPosX, CameraPosX, 1000.0f);	// Prendo due volte cameraposx perché tanto il campo è quadrato
	HumanPlayer->SetActorLocationAndRotation(CameraPos, FRotationMatrix::MakeFromX(FVector(0, 0, -1)).Rotator());	//Setto come attore la telecamera e la associo allo humanplayer
	*/

	float CameraPosX = (GField->TileSize * (4));
	FVector CameraPos(CameraPosX, - CameraPosX, 1000.0f);	// Prendo due volte cameraposx
	HumanPlayer->SetActorLocationAndRotation(CameraPos, FRotationMatrix::MakeFromX(FVector(0, -0.02, -1)).Rotator());	//Setto come attore la telecamera e la associo allo humanplayer
	// Human player = 0
	Players.Add(HumanPlayer);
	//Random Player
	AChess_CPURandom* CPU = GetWorld()->SpawnActor<AChess_CPURandom>(FVector(), FRotator());

	// CPU player = 1
	Players.Add(CPU);

	this->ChoosePlayerAndStartGame();

	HumanPlayer->GameField = GField;
	CPU->GameField = GField;
}

void AChess_GameMode::ChoosePlayerAndStartGame()
{
	Players[0]->OnTurn(); //a differenza di quanto fatto per il TTT, qui inizia il bianco, che è l'umano
}

void AChess_GameMode::ExecuteMove(AChess_Piece* Piece, Chess_Move Move)
{
	GField->ExecuteMove(Piece, Move);
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("EndOfTurn"));
	TurnNextPlayer(); 
}

int32 AChess_GameMode::GetNextPlayer(int32 Player)
{
	Player++;
	if (!Players.IsValidIndex(Player))
	{
		Player = 0;
	}
	return Player;
}

void AChess_GameMode::TurnNextPlayer()
{
	// MoveCounter +=1;
	CurrentPlayer = GetNextPlayer(CurrentPlayer);
	Players[CurrentPlayer]->OnTurn();
}

TArray<Chess_Move> AChess_GameMode::FilterLegalMoves(TArray<Chess_Move> Moves)
{
	TArray<Chess_Move> LegalMoves;
	for (Chess_Move Move : Moves) {
		if (Move.IsLegal(GField))
			LegalMoves.Emplace(Move);
	}

	return LegalMoves;
}
