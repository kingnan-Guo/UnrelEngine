// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyPublicGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API UMyPublicGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyPublicGameInstance();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "myInstance")
	FString myAppId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "myInstance")
	FString myUserId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "myInstance")
	FString myName;


};
