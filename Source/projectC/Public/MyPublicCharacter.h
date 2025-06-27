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
#include "MyPublicCharacter.generated.h"

UCLASS()
class PROJECTC_API AMyPublicCharacter : public ACharacter
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


	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
};
