// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SingletonObject.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API USingletonObject : public UObject
{
	GENERATED_BODY()
	


	public:
		UFUNCTION(BlueprintCallable)
		static USingletonObject* GetSingletonObjectInstance();
		UFUNCTION(BlueprintCallable)
			void SetValue(int32 value);
		UFUNCTION(BlueprintCallable)
			int32 GetValue();



	private:
		static USingletonObject* SingletonObjectInstance;
		int32 Value;
};
