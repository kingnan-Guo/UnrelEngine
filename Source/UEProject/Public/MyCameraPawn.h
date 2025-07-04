// // Fill out your copyright notice in the Description page of Project Settings.

// #pragma once

// #include "CoreMinimal.h"
// #include "GameFramework/Pawn.h"
// #include "MyCameraPawn.generated.h"

// UCLASS()
// class UEPROJECT_API AMyCameraPawn : public APawn
// {
// 	GENERATED_BODY()

// public:
// 	// Sets default values for this pawn's properties
// 	AMyCameraPawn();

// protected:
// 	// Called when the game starts or when spawned
// 	virtual void BeginPlay() override;

// public:	
// 	// Called every frame
// 	virtual void Tick(float DeltaTime) override;

// 	// Called to bind functionality to input
// 	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// };


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "MyCameraPawn.generated.h"

UCLASS()
class UEPROJECT_API AMyCameraPawn : public APawn
{
    GENERATED_BODY()

public:
    AMyCameraPawn();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // 修改注视点位置
    UFUNCTION(BlueprintCallable, Category = "Camera")
    void ChangeLookAtPosition(const FVector& NewPosition, const FRotator& NewRotation, float Distance = 0.0f, float Duration = 1.0f);

    // 平滑移动相机
    void ChangeCameraPosition(const FVector& NewPosition, const FRotator& NewRotation, float Distance, float Duration = 1.0f);

protected:
    // Spring Arm 组件
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    // 相机组件
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UCameraComponent* CameraComponent;

    // 注视点位置（替代 LookAtCube）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    FVector LookAtPoint = FVector(0.0f, 0.0f, 0.0f);

    // 输入动作
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* IA_Zoom;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* IA_RotateHorizontal;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* IA_RotateVertical;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* IA_MoveForward;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* IA_MoveRight;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* IA_LookAtForward;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* IA_LookAtRight;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* IA_PanHorizontal;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* IA_PanVertical;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* IA_RightMouseButton;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* IA_MiddleMouseButton;

    // 输入映射上下文
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputMappingContext* IMC_CameraControls;

    // 旋转速度
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    float CameraRotateSpeed = 0.4f;

    // 移动速度
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    float CameraMoveSpeed = 2.0f;

    // 平移速度
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    float MoveCameraSidewaysSpeed = 100.0f;

    // 纵向平移速度
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
    float MoveCameraUpwardsSpeed = 30.0f;

private:
    bool bIsRotating = false;  // 是否正在旋转
    bool bIsPanning = false;   // 是否正在平移
    FVector TargetPosition;    // 目标位置（用于平滑过渡）
    FRotator TargetRotation;   // 目标旋转
    float TransitionDuration = 0.0f; // 过渡时间
    float ElapsedTime = 0.0f;  // 已过渡时间
    bool bIsTransitioning = false; // 是否在平滑过渡

    // 输入处理函数
    void Zoom(const FInputActionValue& Value);
    void RotateHorizontal(const FInputActionValue& Value);
    void RotateVertical(const FInputActionValue& Value);
    void MoveForward(const FInputActionValue& Value);
    void MoveRight(const FInputActionValue& Value);
    void MoveLookAtForward(const FInputActionValue& Value);
    void MoveLookAtRight(const FInputActionValue& Value);
    void PanHorizontal(const FInputActionValue& Value);
    void PanVertical(const FInputActionValue& Value);
    void StartRotate(const FInputActionValue& Value);
    void StopRotate(const FInputActionValue& Value);
    void StartPan(const FInputActionValue& Value);
    void StopPan(const FInputActionValue& Value);
};