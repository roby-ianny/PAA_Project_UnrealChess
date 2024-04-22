// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_GameField.h"
#include "Kismet/GameplayStatics.h"
// Pieces
// GameMode

// Sets default values
AChess_GameField::AChess_GameField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// size of the field (8x8)
	Size = 8;
	// Tile dimension
	TileSize = 120;

}

void AChess_GameField::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

// Called when the game starts or when spawned
void AChess_GameField::BeginPlay()
{
	Super::BeginPlay();
	GenerateField();
	SpawnPieces();
}

void AChess_GameField::ResetField()
{
	//Sent a broadcast evento to registered objects, so them can also "reset"
	// OnResetEvent.Broadcast();

	/* gamemode part to set in the future
	ATTT_GameMode* GameMode = Cast<ATTT_GameMode>(GetWorld()->GetAuthGameMode());
	GameMode->IsGameOver = false;
	GameMode->MoveCounter = 0;
	GameMode->ChoosePlayerAndStartGame();
	*/

}

void AChess_GameField::GenerateField()
{
	for (int32 x = 0; x < Size; x++) {
		for (int32 y = 0; y < Size; y++) {
			FVector Location = AChess_GameField::GetRelativeLocationByXYPosition(x, y);
			AChess_Tile* Obj = GetWorld()->SpawnActor<AChess_Tile>(TileClass, Location, FRotator::ZeroRotator);
			const float TileScale = TileSize / 100;
			Obj->SetActorScale3D(FVector(TileScale, TileScale, 0.05));
			Obj->SetGridPosition(x, y);
			if ((x + y) % 2 == 0)
				Obj->SetDarkMaterial();
			TileArray.Add(Obj);
			TileMap.Add(FVector2D(x, y), Obj);
		}
	}
}

void AChess_GameField::SpawnPiece(TSubclassOf<AChess_Piece> PieceClass, int32 XPosition, int32 YPosition, bool black)
{
	const float TileScale = TileSize / 100;

	FVector PieceLocation = AChess_GameField::GetRelativeLocationByXYPosition(XPosition, YPosition);
	PieceLocation.Z += 1; // 1 because the tile is a Z = 0

	AChess_Piece* NewPiece = GetWorld()->SpawnActor<AChess_Piece>(PieceClass, PieceLocation, FRotator::ZeroRotator);
	NewPiece->SetActorScale3D(FVector(TileScale, TileScale, 0.05));

	if (black)
		NewPiece->SetDarkMaterial();

	AChess_Tile* Tile = TileMap[FVector2D(XPosition, YPosition)]; // prendo la tile dalla tilemap 
	Tile->SetOccupyingPiece(NewPiece);
}


void AChess_GameField::SpawnPieces()
{
	

	// Spawns pawns
	for (int32 x = 0; x < Size; x++) {
		SpawnPiece(PawnClass, x, 1, false);
		SpawnPiece(PawnClass, x, 6, true);
	}

	// Spawn other pieces
	for (int32 x = 0; x < Size; x++) {
		switch (x)
		{
		case 0:
		case 7:
			SpawnPiece(RookClass, x, 0, false);
			SpawnPiece(RookClass, x, 7, true);
			break;
		case 1:
		case 6:
			SpawnPiece(KnightClass, x, 0, false);
			SpawnPiece(KnightClass, x, 7, true);
			break;

		case 2:
		case 5:
			SpawnPiece(BishopClass, x, 0, false);
			SpawnPiece(BishopClass, x, 7, true);
			break;
		case 3: 
			SpawnPiece(QueenClass, x, 0, false);
			SpawnPiece(QueenClass, x, 7, true);
			break;
		case 4: 
			SpawnPiece(KingClass, x, 0, false);
			SpawnPiece(KingClass, x, 7, true);
			break;
		default:
			break;
		}
	}
}

FVector2D AChess_GameField::GetPosition(const FHitResult& Hit)
{
	return Cast<AChess_Tile>(Hit.GetActor())->GetGridPosition();
}

TArray<AChess_Tile*>& AChess_GameField::GetTileArray()
{
	return TileArray;
}

FVector AChess_GameField::GetRelativeLocationByXYPosition(const int32 InX, const int32 InY) const
{
	return TileSize * FVector(InX, -InY,0);
}

FVector2D AChess_GameField::GetXYPositionByRelativeLocation(const FVector& Location) const
{
	const double x = (Location[0] / TileSize);
	const double y = - (Location[1] / TileSize);
	return FVector2D(x,y);
}

AChess_Tile* AChess_GameField::GetTileByPositionAndDirection(const FVector2D Position, const Chess_Direction Direction) const
{
	return TileMap[FVector2D(Position + Direction.DirectionVector)];
}

bool AChess_GameField::IsInside(FVector2D position)
{
	return ((position.X >= 0 && position.X < Size) && (position.Y >= 0 && position.Y < Size));
}

bool AChess_GameField::IsEmpty(FVector2D position)
{
	return TileMap[position]->GetTileStatus() == ETileStatus::EMPTY;
}

// Highlights/DeHighlights all the tiles
void AChess_GameField::HighlightTiles(TArray<Chess_Move> Moves, bool ToHighlight)
{
	for (Chess_Move Move : Moves){
			TileMap[Move.ToPosition]->Highlight(ToHighlight);
		}
}

void AChess_GameField::DeHighlightAll()
{
	for (AChess_Tile* Tile : TileArray)
	{
		Tile->Highlight(false);
	}
}

/*
// Called every frame
void AChess_GameField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
*/

