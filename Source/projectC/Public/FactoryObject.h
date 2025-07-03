// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ProductObject.h"
#include "FactoryObject.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API UFactoryObject : public UObject
{
	GENERATED_BODY()

	public:
		static UProductObject* CreateNewProdcutObject(UObject* Outer, TSubclassOf<UProductObject> ProductClass){
			return NewObject<UProductObject>(Outer, ProductClass);
		};
	
};
