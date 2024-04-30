// Fill out your copyright notice in the Description page of Project Settings.


#include "Chess_CPURandom.h"

// Sets default values
AChess_CPURandom::AChess_CPURandom()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// color = 1;
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
	
	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("CPU (Random) Turn"));
	GameInstance->SetTurnMessage(TEXT("CPU (Random) Turn"));
	
	FTimerHandle TimerHandle; //sets the timer handle
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]() {
		// gets the gamemode
		AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode->IsGameOver)
			return;
		TArray<TSharedPtr<Chess_Move>> PossibleMoves = GameMode->GetAllPlayerMoves(PlayerNumber);
		// picks a random index for chosing the move
		int32 RandomIndex = FMath::RandRange(0, PossibleMoves.Num() - 1);
		// execute the move
		GameMode->ExecuteMove(PossibleMoves[RandomIndex]);
		}, 1.5f, false); // waits 1,5 second before executing
}

void AChess_CPURandom::OnWin()
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("CPU (Random) Wins"));
	GameInstance->SetTurnMessage(TEXT("CPU (Random) Wins"));
	// GameInstance->IncrementScoreCPURandom();
}

void AChess_CPURandom::OnLose()
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("CPU (Random) Loses"));
	GameInstance->SetTurnMessage(TEXT("CPU (Random) Loses!"));
}

void AChess_CPURandom::OnDraw()
{
	GameInstance->SetTurnMessage(TEXT("Stalemate!"));
}



