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
	if (Piece != nullptr)
		OccupyingPiece = Piece;
}

void AChess_Tile::SetEmptyTile()
{
	OccupyingPiece = nullptr;
}

AChess_Piece* AChess_Tile::GetOccupyingPiece()
{
	return OccupyingPiece;
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
