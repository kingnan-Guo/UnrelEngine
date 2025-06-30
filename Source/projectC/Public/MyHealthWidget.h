// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyHealthWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API UMyHealthWidget : public UUserWidget
{
	GENERATED_BODY()
	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
			float CurrentHealth = 100.0f;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
			float MaxHealth = 100.0f;

};
