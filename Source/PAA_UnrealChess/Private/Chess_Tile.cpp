// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_Tile.h"

// Sets default values (costruttore)
AChess_Tile::AChess_Tile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// template function that creates a components
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene")); //serve per vederlo nell'editor dei blueprint
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	TileStatus = ETileStatus::EMPTY;
	// every actor has a RootComponent that defines the transform in the World
	SetRootComponent(Scene);
	StaticMeshComponent->SetupAttachment(Scene);

	TileGridPosition = FVector2D(0, 0);

}


void AChess_Tile::SetGridPosition(const double InX, const double InY)
{
	TileGridPosition.Set(InX, InY);
}

FVector2D AChess_Tile::GetGridPosition()
{
	return TileGridPosition;
}

void AChess_Tile::SetDarkMaterial()
{
	StaticMeshComponent->SetMaterial(0, DarkVariant);
}

void AChess_Tile::SetOccupyingPiece(AChess_Piece* Piece)
{
	if (Piece != nullptr) {
		OccupyingPiece = Piece;
		switch (Piece->GetColor())
		{
			case 0:
				TileStatus = ETileStatus::OCCUPIEDWHITE;
				break;
			case 1:
				TileStatus = ETileStatus::OCCUPIEDBLACK;
				break;
			default:
				TileStatus = ETileStatus::EMPTY;
				break;
		}
	} else {
		OccupyingPiece = nullptr;
		TileStatus = ETileStatus::EMPTY;
	}
}

ETileStatus AChess_Tile::GetTileStatus()
{
	return TileStatus;
}

void AChess_Tile::SetEmptyTile()
{
	TileStatus = ETileStatus::EMPTY;
	OccupyingPiece = nullptr;
}

AChess_Piece* AChess_Tile::GetOccupyingPiece()
{
	return OccupyingPiece;
}

void AChess_Tile::Highlight(bool highlight)
{
	if (highlight)
		StaticMeshComponent->SetOverlayMaterial(HighlightOverlay);
	else
		StaticMeshComponent->SetOverlayMaterial(nullptr);

}

// Called when the game starts or when spawned
void AChess_Tile::BeginPlay()
{
	Super::BeginPlay();
	
}

/*// Called every frame
void AChess_Tile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/
