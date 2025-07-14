// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MyDelegateManager.h"
#include "Engine/World.h"
#include "Engine/GameInstance.h"

UMyDelegateManager* UMyDelegateManager::SingletonInstance = nullptr;

UMyDelegateManager* UMyDelegateManager::GetInstance(UWorld* World)
{
    if (!SingletonInstance)
    {
        if (!World)
        {
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GetInstance: World is null"));
            }
            return nullptr;
        }

        UGameInstance* GameInstance = World->GetGameInstance();
        if (!GameInstance)
        {
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GetInstance: GameInstance is null"));
            }
            return nullptr;
        }

        SingletonInstance = NewObject<UMyDelegateManager>(GameInstance);
        SingletonInstance->AddToRoot();
        SingletonInstance->OnMultiDataReceived.AddUObject(SingletonInstance, &UMyDelegateManager::OnMultiDataReceivedHandler);
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("DelegateManager instance created"));
        }
    }
    return SingletonInstance;
}

void UMyDelegateManager::RegisterMultiDelegate(UObject* Object, FName FunctionName)
{
    if (Object && !FunctionName.IsNone())
    {
        if (UFunction* Function = Object->GetClass()->FindFunctionByName(FunctionName))
        {
            OnMultiDataReceived.AddUFunction(Object, FunctionName);
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Registered %s on %s"), *FunctionName.ToString(), *Object->GetName()));
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Function %s not found on %s"), *FunctionName.ToString(), *Object->GetName()));
        }
    }
}

void UMyDelegateManager::TriggerMultiData(const FString& Data)
{
    if (OnMultiDataReceived.IsBound())
    {
        OnMultiDataReceived.Broadcast(Data);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Multi broadcast triggered: ") + Data);
    }
}

void UMyDelegateManager::TriggerDynamicMultiData(const FString& Data)
{
    if (OnDynamicMultiDataReceived.IsBound())
    {
        OnDynamicMultiDataReceived.Broadcast(Data);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Dynamic Multi broadcast triggered: ") + Data);
    }
}

void UMyDelegateManager::OnMultiDataReceivedHandler(FString Data)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("DelegateManager received: %s"), *Data));
}


