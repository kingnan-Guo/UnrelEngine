// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h" // 输入映射 value 的值
#include "EnhancedInputComponent.h" // 增强映射组件的头文件
#include "EnhancedInputSubsystems.h" // 增强输入子系统 的头文件
#include "GameFramework/Controller.h" //控制器头文件
// 摄像机摇臂
#include "GameFramework/SpringArmComponent.h"
//相机
#include "Camera/CameraComponent.h"
// #include "GameFramework/Character.h" 
#include "GameFramework/CharacterMovementComponent.h" // 运动组件

#include "MyPublicInterface.h" // 自定义接口 头文件
#include "TimerManager.h" // 定时器头文件


#include "Components/WidgetComponent.h"

#include "MyHealthWidget.h"
#include "MyPublicCharacter.generated.h"

UCLASS()
class PROJECTC_API AMyPublicCharacter : public ACharacter, public IMyPublicInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPublicCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;




	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySceneComponent")
		USpringArmComponent* mySpringArmComponent; // 摄像机摇臂

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySceneComponent")
		UCameraComponent* myCameraComponent; // 摄像机

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "INPUT")
		class UInputMappingContext* DefaultInputMappingContext;// 输入映射上下文

	// 移动映射的输入
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "INPUT")
		class UInputAction* MoveAction;

	// 旋转映射的输入
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "INPUT")
		class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySceneComponent")
		class UWidgetComponent* myWidgetHealth;

	

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);


	// 重写接口函数
	virtual void Attack() override;
	virtual void CaclulateHealth() override;


	// 声明定时器变量
	FTimerHandle MyTimerHandle;
	void MyTimerFunction();


	// DamageAmount 是 ； EventInstigator指针，
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// myWidgetHealth




	//  射线检测
	FVector StartLocation;// 射线检测的 起始位置
	FVector ForwardVector;// 射线检测的 方向; 向前向量
	FVector EndLocation;// 射线检测的 结束位置
	// 结构体
	FHitResult HitResult; // 击中物体返回的 数据结构体


	// 射线检测 多通道
	TArray<FHitResult> HitResultArray;
};
