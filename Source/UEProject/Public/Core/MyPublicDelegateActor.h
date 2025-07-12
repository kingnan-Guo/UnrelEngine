// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPublicDelegateActor.generated.h"



DECLARE_MULTICAST_DELEGATE_OneParam(OneParamMulticastDelegate, FString);


UCLASS()
class UEPROJECT_API AMyPublicDelegateActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyPublicDelegateActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	OneParamMulticastDelegate OneParamMulticastDelegate;
	void OneParamMulticastDelegateFunction(FString str);
};
