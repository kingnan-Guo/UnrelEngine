// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProductObject.h"
#include "ProductB.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API UProductB : public UProductObject
{
	GENERATED_BODY()
public:
	virtual void ShowInfo() override{
		UE_LOG(LogTemp, Warning, TEXT("UProductB ShowInfo"));
	};
};
