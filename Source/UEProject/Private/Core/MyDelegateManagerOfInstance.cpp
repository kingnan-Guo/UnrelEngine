// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MyDelegateManagerOfInstance.h"
#include "Kismet/GameplayStatics.h"

void UMyDelegateManagerOfInstance::RegisterMultiDelegate(UObject* Object, FName FunctionName)
{
    if (Object && !FunctionName.IsNone())
    {
        if (UFunction* Function = Object->GetClass()->FindFunctionByName(FunctionName))
        {
            OnMultiDataReceived.AddUFunction(Object, FunctionName); // 仅对静态委托使用 AddUFunction
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Registered %s on %s"), *FunctionName.ToString(), *Object->GetName()));
        }
        else
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Function %s not found on %s"), *FunctionName.ToString(), *Object->GetName()));
        }
    }
}

void UMyDelegateManagerOfInstance::TriggerMultiData(const FString& Data)
{
    if (OnMultiDataReceived.IsBound())
    {
        OnMultiDataReceived.Broadcast(Data);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Multi broadcast triggered: ") + Data);
    }
}

void UMyDelegateManagerOfInstance::TriggerDynamicMultiData(const FString& Data)
{
    if (OnDynamicMultiDataReceived.IsBound())
    {
        OnDynamicMultiDataReceived.Broadcast(Data);
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Dynamic Multi broadcast triggered: ") + Data);
    }
}

void UMyDelegateManagerOfInstance::OnMultiDataReceivedHandler(FString Data)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("DelegateManagerOfInstance received: %s"), *Data));
}

void UMyDelegateManagerOfInstance::AutoRegisterListeners(UWorld* World)
{
    // if (!World)
    // {
    //     GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AutoRegisterListeners: World is null"));
    //     return;
    // }

    // TArray<AActor*> FoundActors;
    // UGameplayStatics::GetAllActorsWithTag(World, FName("DataListener"), FoundActors);
    // for (AActor* Actor : FoundActors)
    // {
    //     RegisterMultiDelegate(Actor, FName("OnDataReceived"));
    // }
    // GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Auto-registered %d listeners"), FoundActors.Num()));
}