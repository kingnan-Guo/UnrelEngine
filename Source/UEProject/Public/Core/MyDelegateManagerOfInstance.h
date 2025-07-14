// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyDelegateManagerOfInstance.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnMultiDataReceived, FString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDynamicMultiDataReceivedOfInstance, FString, Data); // 重命名
/**
 * 
 */
UCLASS()
class UEPROJECT_API UMyDelegateManagerOfInstance : public UObject
{
	GENERATED_BODY()
	

public:
    UFUNCTION(BlueprintCallable, Category = "Delegate")
    void RegisterMultiDelegate(UObject* Object, FName FunctionName);

    UFUNCTION(BlueprintCallable, Category = "Delegate")
    void TriggerMultiData(const FString& Data);

    UFUNCTION(BlueprintCallable, Category = "Delegate")
    void TriggerDynamicMultiData(const FString& Data);

    UFUNCTION(BlueprintCallable, Category = "Delegate")
    void AutoRegisterListeners(UWorld* World);

    FOnMultiDataReceived OnMultiDataReceived;
    UPROPERTY(BlueprintAssignable, Category = "Delegate")
    FOnDynamicMultiDataReceivedOfInstance OnDynamicMultiDataReceived; // 更新为新委托类型

private:
    void OnMultiDataReceivedHandler(FString Data);


};
