// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

#include "MyPublicGameState.h"
#include "MyPublicHUD.h"
#include "MyPublicPawn.h"
#include "MyPublicPlayerController.h"
#include "MyPublicPlayerState.h"
#include "MyCameraPawn.h"

#include "MyPublicGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UEPROJECT_API AMyPublicGameMode : public AGameMode
{
	GENERATED_BODY()
	AMyPublicGameMode();// 
	public:
		virtual void BeginPlay() override; // BeginPlay() 函数重写 BeginPlay 是在游戏开始时调用的函数
		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override; // EndPlay() 函数重写 EndPlay 是在游戏结束时调用的函数
		virtual void Tick(float DeltaTime) override;// Tick() 函数重写 Tick 是在游戏进行时调用的函数

};
