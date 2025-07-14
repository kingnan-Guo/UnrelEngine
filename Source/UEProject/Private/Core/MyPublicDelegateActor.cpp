// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MyPublicDelegateActor.h"

// Sets default values
AMyPublicDelegateActor::AMyPublicDelegateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// OneParamMulticastDelegate.AddUObject(this, &AMyPublicDelegateActor::OneParamMulticastDelegateFunction); //绑定函数

	
	// RegisterDelegate(TEXT("OneParamMulticastDelegateFunction")); // 绑定函数
}

// Called when the game starts or when spawned
void AMyPublicDelegateActor::BeginPlay()
{
	Super::BeginPlay();



	// OneParamMulticastDelegate.Broadcast(TEXT("OneParamMulticastDelegate"));

}

// Called every frame
void AMyPublicDelegateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	// OneParamMulticastDelegate.Broadcast(TEXT("OneParamMulticastDelegate "));	// 调用带一个参数的代理



}


// 定义一个带有参数的广播委托函数
void AMyPublicDelegateActor::OneParamMulticastDelegateFunction(FString Param1){
	// 将参数Param1与字符串"1"拼接
	FString str = Param1.Append("2");
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("OneParamMulticastDelegateFunc: %s"), *str));
}


void AMyPublicDelegateActor::RegisterDelegate(FName FunctionName){
	// Delegate.AddUObject(this, &AMyPublicDelegateActor::OneParamMulticastDelegateFunction);
	// OneParamMulticastDelegate.AddUObject(this, &AMyPublicDelegateActor::OneParamMulticastDelegateFunction); // 绑定函数


	OneParamMulticastDelegate.AddUFunction(this, FunctionName);
}

