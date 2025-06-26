// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPublicDelegateActor.generated.h"


// 单播代理
DECLARE_DELEGATE(NoParamDelegate);//  声明一个代理 无参数 无返回值
DECLARE_DELEGATE_OneParam(OneParamDelegate, FString);// 声明一个代理 一个参数 无返回值; OneParamDelegate是 代理名称, FString 是参数类型
DECLARE_DELEGATE_TwoParams(TwoParamDelegate, FString, int32);// 声明一个代理 两个参数 无返回值; TwoParamDelegate是 代理名称, FString 是参数类型
DECLARE_DELEGATE_ThreeParams(ThreeParamDelegate, FString, int32, float);
// 带有 返回参数的
DECLARE_DELEGATE_RetVal(FString, RevalDelegate);// 声明一个代理 无参数 有返回值; RevalueDelegate是 代理名称, FString 是返回值类型



// 多播代理
DECLARE_MULTICAST_DELEGATE(NoParamMulticastDelegate);//  声明一个代理 无参数 无返回值
DECLARE_MULTICAST_DELEGATE_OneParam(OneParamMulticastDelegate, FString);// 声明一个代理 一个参数 无返回值; OneParamDelegate是 代理名称, FString 是参数类型
DECLARE_MULTICAST_DELEGATE_TwoParams(TwoParamMulticastDelegate, FString, int32);
DECLARE_MULTICAST_DELEGATE_ThreeParams(ThreeParamMulticastDelegate, FString, int32, float);
// 带有 返回参数的
// DECLARE_MULTICAST_DELEGATE_RetVal(FString, RevalMulticastDelegate);// 声明一个代理 无参数 有返回值; RevalueDelegate是 代理名称, FString 是返回值类型


UCLASS()
class PROJECTC_API AMyPublicDelegateActor : public AActor
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




	// 单播代理
	NoParamDelegate NoParamDelegate;
	OneParamDelegate OneParamDelegate;
	TwoParamDelegate TwoParamDelegate;
	ThreeParamDelegate ThreeParamDelegate;
	RevalDelegate RevalDelegate;

	void NoParamDelegateFunc();
	void OneParamDelegateFunc(FString str);
	void TwoParamDelegateFunc(FString str, int32 a);
	void ThreeParamDelegateFunc(FString str, int32 b, float c);
	FString RevalDelegateFunc();



	//  多播代理
	NoParamMulticastDelegate NoParamMulticastDelegate;
	OneParamMulticastDelegate OneParamMulticastDelegate;
	TwoParamMulticastDelegate TwoParamMulticastDelegate;
	ThreeParamMulticastDelegate ThreeParamMulticastDelegate;
	// RevalMulticastDelegate RevalMulticastDelegate;

	void NoParamMulticastDelegateFunc();
	void OneParamMulticastDelegateFunc(FString str);
	void OneParamMulticastDelegateFunc1(FString str);
	void OneParamMulticastDelegateFunc2(FString str);
	void TwoParamMulticastDelegateFunc(FString str, int32 a);
	void ThreeParamMulticastDelegateFunc(FString str, int32 b, float c);
	// FString RevalMulticastDelegateFunc();
};
