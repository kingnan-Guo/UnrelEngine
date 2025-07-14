// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyDelegateManager.generated.h"


// 定义多播委托
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMultiDataReceived, FString);

// 定义动态多播委托（支持蓝图）
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDynamicMultiDataReceived, FString, Data);

/**
 * 
 */
UCLASS()
class UEPROJECT_API UMyDelegateManager : public UObject
{
	GENERATED_BODY()
	

public:
    // 单例获取方法
	UFUNCTION(BlueprintCallable, Category = "Delegate")
    static UMyDelegateManager* GetInstance(UWorld* World);
    // 注册多播委托
    UFUNCTION(BlueprintCallable, Category = "Delegate")
    void RegisterMultiDelegate(UObject* Object, FName FunctionName);

    // 触发多播委托
    UFUNCTION(BlueprintCallable, Category = "Delegate")
    void TriggerMultiData(const FString& Data);

    // 触发动态多播委托（蓝图支持）
    UFUNCTION(BlueprintCallable, Category = "Delegate")
    void TriggerDynamicMultiData(const FString& Data);

    // 多播委托
    FOnMultiDataReceived OnMultiDataReceived;

    // 动态多播委托（蓝图可绑定）
    UPROPERTY(BlueprintAssignable, Category = "Delegate")
    FOnDynamicMultiDataReceived OnDynamicMultiDataReceived;

private:
    // 单例实例
    static UMyDelegateManager* SingletonInstance;

    // 自身处理多播数据
    void OnMultiDataReceivedHandler(FString Data);
};
