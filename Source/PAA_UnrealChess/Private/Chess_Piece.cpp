// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_Piece.h"

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
}

void AChess_Piece::SetDarkMaterial()
{
	StaticMeshComponent->SetMaterial(0, DarkVariant);
	color = 1;
}

// Called when the game starts or when spawned
void AChess_Piece::BeginPlay()
{
	Super::BeginPlay();
	
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

