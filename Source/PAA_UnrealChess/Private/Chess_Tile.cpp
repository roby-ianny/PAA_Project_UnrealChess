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

	Status = ETileStatus::EMPTY;
	PlayerOwner = -1;
	TileGridPosition = FVector2D(0, 0);

}

void AChess_Tile::setTileStatus(const int32 TileOwner, const ETileStatus TileStatus)
{
	PlayerOwner = TileOwner;
	Status = TileStatus;
}

ETileStatus AChess_Tile::getTileStatus()
{
	return Status;
}

int32 AChess_Tile::getTileOwner()
{
	return PlayerOwner;
}

void AChess_Tile::setGridPosition(const double InX, const double InY)
{
	TileGridPosition.Set(InX, InY);
}

FVector2D AChess_Tile::getGridPosition()
{
	return TileGridPosition;
}

void AChess_Tile::SetDarkMaterial()
{
	StaticMeshComponent->SetMaterial(0, DarkVariant);
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
