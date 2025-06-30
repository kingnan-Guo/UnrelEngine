// Fill out your copyright notice in the Description page of Project Settings.

#pragma once	// 预处理程序指令 #pragma once 用于防止头文件被重复包含

#include "CoreMinimal.h"				// 	包含引擎的头文件
#include "GameFramework/Actor.h"		// 	包含游戏框架的头文件； 基础Actor类
#include "Components/SceneComponent.h"	// 场景相关
#include "Components/StaticMeshComponent.h"	// 静态 网格 组件
#include "Components/BoxComponent.h"		// Box coller 盒体碰撞组件
#include "Particles/ParticleSystemComponent.h" 	// 粒子特效组件
#include "Components/AudioComponent.h" 	// 粒子特效组件

#include "Kismet/GameplayStatics.h"	// 	游戏框架中的游戏静态函数
#include "MyPublicCharacter.h" // MyPublicCharacter 头文件

#include "MyPublicActor.generated.h"	// 	包含生成的头文件, 把反射数据存储在 generated .h 文件中

UCLASS()
class PROJECTC_API AMyPublicActor : public AActor
{
	GENERATED_BODY()// 表示不直接使用父类的构造函数，如果我们要在我们定义的类中 做一些初始化 ，需要我们自己在 .h 的 头文件中生命构造函数，然后在 .cpp 文件中实现构造函数
	// GENERATED_UCLASS_BODY() 表示使用父类的构造函数, 如果我们要在我们定义的类中 做一些初始化 ，可以直接在 .cpp 文件中实现构造函数 ，不需要在 .h 的 头文件中生命构造函数
	// UCLASS 告诉虚幻引擎 生成雷额反射数据， 类必须派生自 UObject 类
	
	
public:	
	// Sets default values for this actor's properties
	AMyPublicActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "mySceneComponent")//  
		class USceneComponent* MyScene;
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "mySceneComponent")//  
	//	class StaticMeshComponent* MyStaticMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "mySceneComponent")//  
		class UStaticMeshComponent* MyMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "mySceneComponent")//  
		class UParticleSystemComponent* MyParticle;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "mySceneComponent")//  
		class UBoxComponent* MyBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "mySceneComponent")//  
		class UAudioComponent* MyAudio;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "myClass")//  
		TSubclassOf<AActor> myActor;

	UFUNCTION()// 这个宏 生成 函数的反射数据
		void BeginOverLapFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);// 
	UFUNCTION()// 这个宏 生成 函数的反射数据
		void EndOverLapFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);// 
	UFUNCTION()// 这个宏 生成 函数的反射数据
		void HitFunction(
			UPrimitiveComponent* HitComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			FVector NormalImpulse,
			const FHitResult& Hit
		);


};
