// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Components/BoxComponent.h" // 碰撞体组件
#include "MyPublicCharacter.h"
#include "MyTimeLineActor.generated.h"

UCLASS()
class PROJECTC_API AMyTimeLineActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTimeLineActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "myCurve")//  
		UCurveFloat* myCurve;// UCurveFloat 是  浮点曲线类

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "mySenceComponent")//  
		UTimelineComponent* myTimeline;//UTimelineComponent 是  时间线组件类

	FOnTimelineFloat TimelineDelegate;//FOnTimelineFloat 是  时间线浮点事件类, 一开始进行的绑定
	FOnTimelineEvent TimelineEventFinishedDelegate;//FOnTimelineEvent 是  时间线事件类, 时间轴 执行完 执行的事件


	UFUNCTION()
		void TimelineStart(float Value); // 时间轴 开始
	UFUNCTION()
		void TimelineEnd(float Value); // 时间轴 结束




	// 
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "mySceneComponent")//  
		USceneComponent* myScene;// USceneComponent 是  场景组件类

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "mySceneComponent")//
		UStaticMeshComponent* myStaticMesh;// UStaticMeshComponent 是  静态网格组件类, 目的是 碰到就开启，离开就关闭
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "mySceneComponent")
		UBoxComponent* myBox;// UBoxComponent 是  盒子碰撞体组件类, 目的是 碰到就开启，离开就关闭
	



	UFUNCTION()// 这个宏 生成 函数的反射数据
		void BeginOverLapFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);// 
	UFUNCTION()// 这个宏 生成 函数的反射数据
		void EndOverLapFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);// 


};
