// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
// #include "Core/MyPublicDelegateActor.h"
#include "Core/MyDelegateManager.h"

#include "MyPublicGameInstance.h"
#include "Core/MyDelegateManagerOfInstance.h"

#include "MyPublicPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UEPROJECT_API AMyPublicPlayerController : public APlayerController
{
	GENERATED_BODY()


	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	public:
		// Called every frame
		virtual void Tick(float DeltaTime) override;

		AMyPublicPlayerController();

		void PerformRaycast();



	UFUNCTION()
	void OnDataReceived(FString Data);

	// UFUNCTION(BlueprintCallable, Category = "Delegate")
	// void TriggerDataFromModule(const FString& Data);


};
