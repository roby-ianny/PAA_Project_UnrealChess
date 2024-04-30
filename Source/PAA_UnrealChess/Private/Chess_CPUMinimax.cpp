// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_CPUMinimax.h"

// Sets default values
AChess_CPUMinimax::AChess_CPUMinimax()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChess_CPUMinimax::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChess_CPUMinimax::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AChess_CPUMinimax::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

