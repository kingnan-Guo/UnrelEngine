// Fill out your copyright notice in the Description page of Project Settings.


#include "MySoftActor.h"
#include "Engine/AssetManager.h" // 资源管理

// Sets default values
AMySoftActor::AMySoftActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMySoftActor::BeginPlay()
{
	Super::BeginPlay();
	
	
	// 同步加载
	// FSoftObjectPath Path = FName(TEXT("/Script/Engine.Texture2D'/Game/StarterContent/Textures/T_Brick_Clay_Beveled_D.T_Brick_Clay_Beveled_D'"));
	FSoftObjectPath Path(TEXT("/Script/Engine.Texture2D'/Game/StarterContent/Textures/T_Brick_Clay_Beveled_D.T_Brick_Clay_Beveled_D'"));

	// 智能指针
	TSharedPtr<FStreamableHandle> ASyncStreamHandle = UAssetManager::GetStreamableManager().RequestAsyncLoad(Path); // 异步加载
	if(ASyncStreamHandle){
		UTexture2D* Image = Cast<UTexture2D>(ASyncStreamHandle->GetLoadedAsset());
		if(Image){
			// 加载成功
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("ASyncStreamHandle: %s"), *Image->GetName()));
		}
	}




	// 异步加载
	
	FSoftObjectPath Path2(TEXT("/Script/Engine.Texture2D'/Game/StarterContent/Textures/T_Brick_Clay_Beveled_M.T_Brick_Clay_Beveled_M'"));
	TSharedPtr<FStreamableHandle> SyncStreamHandle = UAssetManager::GetStreamableManager().RequestSyncLoad(Path2); 
	if(SyncStreamHandle){
		UTexture2D* Image = Cast<UTexture2D>(SyncStreamHandle->GetLoadedAsset());
		if(Image){
			// 加载成功
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("SyncStreamHandle: %s"), *Image->GetName()));
		}
	}


}

// Called every frame
void AMySoftActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

