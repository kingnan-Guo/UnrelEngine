// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

// #include "Core/MyDelegateManager.h"
#include "Core/MyDelegateManagerOfInstance.h"

#include "MyPublicGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UEPROJECT_API UMyPublicGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:
    virtual void Init() override;
    virtual void Shutdown() override;

    UFUNCTION(BlueprintCallable, Category = "Delegate")
    UMyDelegateManagerOfInstance* GetDelegateManager(); // 更新为 UMyDelegateManagerOfInstance

private:
    UPROPERTY()
    UMyDelegateManagerOfInstance* DelegateManager; // 更新为 UMyDelegateManagerOfInstance

};
