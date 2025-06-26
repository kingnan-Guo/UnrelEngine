// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h" //	静态网格组件
#include "Components/CapsuleComponent.h" // 球形碰撞体
#include "Components/SphereComponent.h" // 添加USphereComponent
#include "GameFramework/ProjectileMovementComponent.h" // 子弹 运动 移动组件
#include "MyBulletActor.generated.h"

UCLASS()
class PROJECTC_API AMyBulletActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyBulletActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyBulletActor")
		UStaticMeshComponent* myBulletMesh; // 子弹的网格组件
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyBulletActor")
		USphereComponent* myBulletSphere; // 子弹的碰撞体组件
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyBulletActor")
		UProjectileMovementComponent* myBulletMove; // 子弹的移动组件

};
