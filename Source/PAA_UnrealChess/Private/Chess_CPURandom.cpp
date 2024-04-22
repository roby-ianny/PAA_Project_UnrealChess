// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_CPURandom.h"

// Sets default values
AChess_CPURandom::AChess_CPURandom()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GameInstance = Cast<UChess_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

// Called when the game starts or when spawned
void AChess_CPURandom::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChess_CPURandom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AChess_CPURandom::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AChess_CPURandom::OnTurn()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("CPU (Random) Turn"));
	GameInstance->SetTurnMessage(TEXT("CPU (Random) Turn"));

	FTimerHandle TimerHandle; //lambda function per il timer

	TArray<AChess_Tile*> CPUTiles = GameField->GetTilesWithPlayerPieces(1);

	AChess_Tile* ChosenTile;
	TArray<Chess_Move> PossibleMoves;
	AChess_Piece* PieceToMove;

	// select random tile
	if (CPUTiles.Num() > 0)
	{
		// picks a tile that has a piece that can move
		do{
			// picks a random tile
			int32 RandomIndex = FMath::RandRange(0, CPUTiles.Num() - 1);
			ChosenTile = CPUTiles[RandomIndex];
			// picks the piece and check the possible moves
			PieceToMove = ChosenTile->GetOccupyingPiece();
			PossibleMoves = PieceToMove->ComputeMoves(ChosenTile->GetGridPosition(), GameField);
		} while (PossibleMoves.Num() == 0); // exits if there are possible moves

		// picks a random index for chosing the move
		int32 RandomIndex = FMath::RandRange(0,PossibleMoves.Num() - 1);

		// executes the move
		AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
		GameMode->ExecuteMove(PieceToMove, PossibleMoves[RandomIndex]);
	} else
		OnLose();

}

void AChess_CPURandom::OnWin()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("CPU (Random) Wins"));
	GameInstance->SetTurnMessage(TEXT("CPU (Random) Wins"));
	// GameInstance->IncrementScoreCPURandom();
}

void AChess_CPURandom::OnLose()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("CPU (Random) Loses"));
	GameInstance->SetTurnMessage(TEXT("AI Loses!"));
}




