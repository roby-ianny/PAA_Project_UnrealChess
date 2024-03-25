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
	TileSize = 100;

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
}

void AChess_GameField::ResetField()
{
	for (AChess_Tile* Obj : TileArray) {
		Obj->setTileStatus(NOT_ASSIGNED, ETileStatus::EMPTY);
	}

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
			FVector Location = AChess_GameField::getRelativeLocationByXYPosition(x, y);
			AChess_Tile* Obj = GetWorld()->SpawnActor<AChess_Tile>(TileClass, Location, FRotator::ZeroRotator);
			const float TileScale = TileSize / 100;
			Obj->SetActorScale3D(FVector(TileScale, TileScale, 0.05));
			Obj->setGridPosition(x, y);
			TileArray.Add(Obj);
			TileMap.Add(FVector2D(x, y), Obj);
		}
	}
}

FVector2D AChess_GameField::getPosition(const FHitResult& Hit)
{
	return Cast<AChess_Tile>(Hit.GetActor())->getGridPosition();
}

TArray<AChess_Tile*>& AChess_GameField::getTileArray()
{
	return TileArray;
}

FVector AChess_GameField::getRelativeLocationByXYPosition(const int32 InX, const int32 InY) const
{
	return TileSize * FVector(InX,InY,0);
}

FVector2D AChess_GameField::getXYPositionByRelativeLocation(const FVector& Location) const
{
	const double x = Location[0] / TileSize;
	const double y = Location[1] / TileSize;
	return FVector2D(x,y);
}

/*
// Called every frame
void AChess_GameField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
*/

