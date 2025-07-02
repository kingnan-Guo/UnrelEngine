// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyFunctionLibraryActor.generated.h"

UCLASS()
class PROJECTC_API AMyFunctionLibraryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyFunctionLibraryActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "MyFunctionLibrary")
	void MyOpenLevel();

	UFUNCTION(BlueprintCallable, Category = "MyFunctionLibrary")
	void MyCurrentLevelName();

	UFUNCTION(BlueprintCallable, Category = "MyFunctionLibrary")
	void MyQuitGame();
};
