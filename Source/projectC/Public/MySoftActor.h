// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MySoftActor.generated.h"

UCLASS()
class PROJECTC_API AMySoftActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMySoftActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoftActorPath")
		FSoftObjectPath AssetObjectPath;// 资源路径； 声音 贴图 等
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoftActorPath")
	 	FSoftClassPath AssetClassPath;// 类路径； 可以选择 Actor 资源
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoftActorPath")
		TSoftObjectPtr<AActor> AssetObjectPtr;// 资源指针
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoftActorPath")
		TSoftClassPtr<AActor> AssetClassPtr;// 类指针
};
