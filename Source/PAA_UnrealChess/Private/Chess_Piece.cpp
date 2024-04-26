// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_Piece.h"
#include "Chess_GameField.h"

// Sets default values
AChess_Piece::AChess_Piece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene")); //serve per vederlo nell'editor dei blueprint
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	// every actor has a RootComponent that defines the transform in the World
	SetRootComponent(Scene);
	StaticMeshComponent->SetupAttachment(Scene);

	color = 0;
	Type = EPieceType::NONE;
}

void AChess_Piece::SetDarkMaterial()
{
	StaticMeshComponent->SetMaterial(0, DarkVariant);
	color = 1;
}

int32 AChess_Piece::GetColor() const
{
	return color;
}

// Restituisce una array vuoto nel caso in cui non si usano i pezzi veri e propri

TArray<TSharedPtr<Chess_Move>> AChess_Piece::ComputeMoves(FVector2D frompos, AChess_GameField* GF)
{
	return TArray<TSharedPtr<Chess_Move>>();
}

bool AChess_Piece::CanCaptureOpponentKing(FVector2D frompos, AChess_GameField* GameField)
{
	for (TSharedPtr<Chess_Move> Move : ComputeMoves(frompos, GameField)) {
		FVector2D topos = Move->ToPosition;
		//checks if the tile is empty, it's more efficent to do this because it skips all the empty tiles (idk if it's a short circuit evaluation so i do it this way)
		if (GameField->TileMap[topos]->GetTileStatus() != ETileStatus::EMPTY){
			//checks if the piece on the tile is a king
			if(GameField->TileMap[topos]->GetOccupyingPiece()->GetType() == EPieceType::KING)
				return true;
		}
	}
	return false;
}


// Called when the game starts or when spawned
void AChess_Piece::BeginPlay()
{
	Super::BeginPlay();
	
}

TArray<FVector2D> AChess_Piece::MovePositionsInDir(FVector2D frompos, Chess_Direction direction, AChess_GameField* GF)
{
	TArray<FVector2D> ReachablePositions;
	ETileStatus OpponentStatus;
	if (color == 0)
		OpponentStatus = ETileStatus::OCCUPIEDBLACK;
	else
		OpponentStatus = ETileStatus::OCCUPIEDWHITE;

	for (FVector2D pos = frompos + direction.DirectionVector; GF->IsInside(pos); pos += direction.DirectionVector) {
		ETileStatus Status = GF->TileMap[pos]->GetTileStatus();

		if (Status == ETileStatus::EMPTY)
			ReachablePositions.Push(pos);
		else if (Status == OpponentStatus) {
			ReachablePositions.Push(pos);
			break;
		} else
			break;

	};
	return ReachablePositions;
}

// Useful for pieces that can move in multiple directions (Rook, Bishop, Queen)
TArray<FVector2D> AChess_Piece::MovePositionInDirs(FVector2D frompos, TArray<Chess_Direction> dirs, AChess_GameField* GF)
{
	TArray<FVector2D> ReachablePositions;
	for (Chess_Direction dir : dirs)
		ReachablePositions += MovePositionsInDir(frompos, dir, GF);
	return ReachablePositions;
}


// Called every frame
void AChess_Piece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChess_Piece::SelfDestroy()
{
	Destroy();
}

