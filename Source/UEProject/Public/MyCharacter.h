// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

// 添加相机摇臂
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
// 添加场景组件
#include "Components/SceneComponent.h"

// 增强输入系统
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"// 输入映射


#include "MyCharacter.generated.h"

UCLASS()
class UEPROJECT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySceneComponent")
		USceneComponent* MySceneComponent;// 创建一个新的USceneComponent实例 USceneComponent是所有具有3D变换（位置/旋转/缩放）组件的基类
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySceneComponent")
		USpringArmComponent* MySpringArmComponent;// 添加相机摇臂
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MySceneComponent")
		UCameraComponent* MyCameraComponent;// 添加相机


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyInput")// 增强输入系统
	UInputMappingContext* MyInputMappingContext;// 创建一个新的UInputMappingContext实例 UInputMappingContext是所有输入映射的基类
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyInput")
	UEnhancedInputComponent* MyEnhancedInputComponent;// 创建一个新的UEnhancedInputComponent实例 UEnhancedInputComponent是所有增强输入组件的基类
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyInput")
	UInputAction* MoveInputAction;// 创建一个新的UInputAction实例 UInputAction是所有输入动作的基类
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyInput")
	UInputAction* LookInputAction;//  


	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& Value);
	UFUNCTION(BlueprintCallable)
	void Look(const FInputActionValue& Value);


};
