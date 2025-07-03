// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPublicGameMode.h"

AMyPublicGameMode::AMyPublicGameMode(){
    DefaultPawnClass = AMyPublicPawn::StaticClass();
    PlayerControllerClass = AMyPublicPlayerController::StaticClass();
    HUDClass = AMyPublicHUD::StaticClass();
    GameStateClass = AMyPublicGameState::StaticClass();
    PlayerStateClass = AMyPublicPlayerState::StaticClass();
    // SpectatorClass = AMyPublicSpectator::StaticClass();

}


void AMyPublicGameMode::BeginPlay() {
    Super::BeginPlay();// 调用父类方法
    UE_LOG(LogTemp, Warning, TEXT("AMyPublicGameMode.cpp"));
}



void AMyPublicGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason) {
    Super::EndPlay(EndPlayReason);
}

void AMyPublicGameMode::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}