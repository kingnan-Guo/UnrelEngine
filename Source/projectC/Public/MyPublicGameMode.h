// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MyPublicGameState.h"
#include "MyPublicHUD.h"
#include "MyPublicPawn.h"
#include "MyPublicPlayerController.h"
#include "MyPublicPlayerState.h"

#include "GameFramework/GameMode.h"
#include "MyPublicGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API AMyPublicGameMode : public AGameMode
{
	GENERATED_BODY()
	AMyPublicGameMode(); // Constructor 构造函数


	public:
		virtual void BeginPlay() override; // BeginPlay() 函数重写 BeginPlay 是在游戏开始时调用的函数
		// virtual void StartPlay() override; // StartPlay() 函数重写 StartPlay 是在游戏开始时调用的函数
		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override; // EndPlay() 函数重写 EndPlay 是在游戏结束时调用的函数
		virtual void Tick(float DeltaTime) override;// Tick() 函数重写 Tick 是在游戏进行时调用的函数


		bool bIsGameOver; // 是否游戏结束
		int32 Score;
		int64 Score_64;// 整形64位 变量

		BYTE Byte; // 字节型变量

		FString fstring; // 字符串型变量  唯一可以修改 的 字符串类型
		FName fname;// 名称型变量 不区分大小写 不可以更改
		FText ftext;// 文本型变量 显示 本地化文本
		FVector FVector;// 向量型变量 x,y,z 轴
		FRotator Rotator;// 旋转型变量
		FQuat Quat;// 四元数型变量
		FVector2D Vector2D;// 二维向量型变量
		FVector4 Vector4;// 四维向量型变量'
		FTransform Transform;// 变换型变量 旋转 缩放 平移
	




		TArray<int32> myTArray; // 数组型变量
		void PrintF();
		


		TMap<int32, int32> myTMap;


};
