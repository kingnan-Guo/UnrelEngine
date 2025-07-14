// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPublicGameInstance.h"

#include "Kismet/GameplayStatics.h"

void UMyPublicGameInstance::Init()
{
    Super::Init();
    DelegateManager = NewObject<UMyDelegateManagerOfInstance>(this);
    DelegateManager->AddToRoot(); // 防止垃圾回收
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("MyPublicGameInstance Initialized"));

    // 自动注册监听者
    // if (UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull))
    // {
    //     DelegateManager->AutoRegisterListeners(World);
    // }
}

void UMyPublicGameInstance::Shutdown()
{
    Super::Shutdown();
    if (DelegateManager)
    {
        DelegateManager->RemoveFromRoot(); // 清理
    }
}

UMyDelegateManagerOfInstance* UMyPublicGameInstance::GetDelegateManager()
{
    return DelegateManager;
}



// void UMyPublicGameInstance::Init()
// {
//     Super::Init();
//     DelegateManager = NewObject<UMyDelegateManager>(this);
//     DelegateManager->AddToRoot();
//     GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("MyPublicGameInstance Initialized"));
// }

// void UMyPublicGameInstance::Shutdown()
// {
//     Super::Shutdown();
//     if (DelegateManager)
//     {
//         DelegateManager->RemoveFromRoot();
//     }
// }

// UMyDelegateManager* UMyPublicGameInstance::GetDelegateManager()
// {
//     return DelegateManager;
// }



// 使用方式  // OtherModuleActor.cpp
// void AOtherModuleActor::BeginPlay()
// {
//     Super::BeginPlay();
//     if (UMyPublicGameInstance* GameInstance = Cast<UMyPublicGameInstance>(GetWorld()->GetGameInstance()))
//     {
//         UMyDelegateManager* DelegateManager = GameInstance->GetDelegateManager();
//         if (DelegateManager)
//         {
//             DelegateManager->RegisterMultiDelegate(this, FName("OnDataReceived"));
//             GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("RegisterMultiDelegate Success"));
//         }
//     }
// }




// void AOtherModuleActor::TriggerDataFromModule(const FString& Data)
// {
//     if (UMyPublicGameInstance* GameInstance = Cast<UMyPublicGameInstance>(GetWorld()->GetGameInstance()))
//     {
//         UMyDelegateManagerOfInstance* DelegateManager = GameInstance->GetDelegateManager();
//         if (DelegateManager)
//         {
//             DelegateManager->TriggerMultiData(Data);
//         }
//     }
// }