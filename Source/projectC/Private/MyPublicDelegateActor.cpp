// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPublicDelegateActor.h"

// Sets default values
AMyPublicDelegateActor::AMyPublicDelegateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NoParamDelegate.BindUObject(this, &AMyPublicDelegateActor::NoParamDelegateFunc);
	OneParamDelegate.BindUObject(this, &AMyPublicDelegateActor::OneParamDelegateFunc);
	TwoParamDelegate.BindUObject(this, &AMyPublicDelegateActor::TwoParamDelegateFunc);
	ThreeParamDelegate.BindUObject(this, &AMyPublicDelegateActor::ThreeParamDelegateFunc);
	RevalDelegate.BindUObject(this, &AMyPublicDelegateActor::RevalDelegateFunc);



	// 多播代理
	NoParamMulticastDelegate.AddUObject(this, &AMyPublicDelegateActor::NoParamMulticastDelegateFunc);
	OneParamMulticastDelegate.AddUObject(this, &AMyPublicDelegateActor::OneParamMulticastDelegateFunc);
	OneParamMulticastDelegate.AddUObject(this, &AMyPublicDelegateActor::OneParamMulticastDelegateFunc1);
	OneParamMulticastDelegate.AddUObject(this, &AMyPublicDelegateActor::OneParamMulticastDelegateFunc2);
}

// Called when the game starts or when spawned
void AMyPublicDelegateActor::BeginPlay()
{
	Super::BeginPlay();


	// 执行单播代理
	NoParamDelegate.ExecuteIfBound();	// 调用无参代理
	OneParamDelegate.ExecuteIfBound(TEXT("Hello"));	// 调用带一个参数的代理
	TwoParamDelegate.ExecuteIfBound(TEXT("Hello"), 123);	// 调用带两个参数的代理
	ThreeParamDelegate.ExecuteIfBound(TEXT("Hello"), 123, 3.14f);	// 调用带三个参数的代理
	FString str = RevalDelegate.Execute();	// 调用带返回值的代理
	UE_LOG(LogTemp, Warning, TEXT("RevalDelegateFunc: %s"), *str);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("RevalDelegateFunc: %s"), *str));
	
	// 执行多播代理
	NoParamMulticastDelegate.Broadcast();	// 调用无参代理
	OneParamMulticastDelegate.Broadcast(TEXT("OneParamMulticastDelegate "));	// 调用带一个参数的代理


}

// Called every frame
void AMyPublicDelegateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyPublicDelegateActor::NoParamDelegateFunc(){
	// UE_LOG(LogTemp, Warning, TEXT("NoParamDelegateFunc"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("NoParamDelegateFunc"));
}

void AMyPublicDelegateActor::OneParamDelegateFunc(FString Param){
	// UE_LOG(LogTemp, Warning, TEXT("OneParamDelegateFunc: %s"), Param);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("OneParamDelegateFunc: %s"), *Param));
}

void AMyPublicDelegateActor::TwoParamDelegateFunc(FString Param1, int32 Param2){
	// UE_LOG(LogTemp, Warning, TEXT("TwoParamDelegateFunc: %s, %d"), Param1, Param2);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("TwoParamDelegateFunc: %s, %d"), *Param1, Param2));
}

void AMyPublicDelegateActor::ThreeParamDelegateFunc(FString Param1, int32 Param2, float Param3){
	// UE_LOG(LogTemp, Warning, TEXT("ThreeParamDelegateFunc: %s, %d, %f"), Param1, Param2, Param3);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("ThreeParamDelegateFunc: %s, %d, %f"), *Param1, Param2, Param3));
}

FString AMyPublicDelegateActor::RevalDelegateFunc(){

	FString str = FString::Printf(TEXT("RevalDelegateFunc"));
    return str;
}






// 多播代理
// NoParamMulticastDelegateFunc
void AMyPublicDelegateActor::NoParamMulticastDelegateFunc(){
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("NoParamMulticastDelegateFunc"));
}

// OneParamMulticastDelegateFunc
void AMyPublicDelegateActor::OneParamMulticastDelegateFunc(FString Param1){
	FString str = Param1.Append("0");
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("OneParamMulticastDelegateFunc: %s"), *str));
}

void AMyPublicDelegateActor::OneParamMulticastDelegateFunc1(FString Param1){
FString str = Param1.Append("1");
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("OneParamMulticastDelegateFunc: %s"), *str));
}
void AMyPublicDelegateActor::OneParamMulticastDelegateFunc2(FString Param1){
FString str = Param1.Append("2");
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("OneParamMulticastDelegateFunc: %s"), *str));
}


// TwoParamMulticastDelegateFunc
void AMyPublicDelegateActor::TwoParamMulticastDelegateFunc(FString Param1, int32 Param2){
    
}
// ThreeParamMulticastDelegateFunc
void AMyPublicDelegateActor::ThreeParamMulticastDelegateFunc(FString Param1, int32 Param2, float Param3){
    
}
