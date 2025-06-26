// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPublicPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API AMyPublicPlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	virtual void SetupInputComponent() override;//按键输入绑定的

	void WheelUpFunction();
	void WheelDownFunction();

	
};
