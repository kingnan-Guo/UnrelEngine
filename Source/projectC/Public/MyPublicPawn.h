// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPublicObject.h"
#include "MyPublicGameInstance.h"
#include "GameFramework/SpringArmComponent.h"// 摄像机摇臂 的头文件
#include "Camera/CameraComponent.h" // 摄像机 头文件
#include "GameFramework/Pawn.h"
#include "MyPublicPawn.generated.h"


UENUM(BlueprintType)// 枚举  BlueprintType 可以在 蓝图中 的 结构体可以选择 此 myEnum
namespace myEnumType {
	enum myEnum {
		type1,
		type2
	};
}

UENUM(BlueprintType)// 枚举声明的 另一种方式
enum class EMyTestEnum:uint8 {
	oneType UMETA(DisplayName = "oneType"),
	twoType UMETA(DisplayName = "twoType")
};


USTRUCT(BlueprintType)// BlueprintType 可以在 蓝图中 的 结构体可以选择 此 MyStruct
struct FMyStruct
{
	GENERATED_BODY()// 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyStruct")//  category 目录
		int32  MyStructInt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyStruct")//  category 目录
		int32 Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyStruct")//  category 目录
		FString MyStructFString;

};


UCLASS()
class PROJECTC_API AMyPublicPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPublicPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(VisibleDefaultsOnly)// 通过反射 把属性 暴露在 蓝图 或者 细节面板中； 虚幻会生成反射数据，UPROPERTY 让蓝图 找到变量 或者方法; VisibleDefaultsOnly 仅在类默认设置可见
		int32 VisibleDefaultsOnlyInt;// 定义一个变量

	UPROPERTY(VisibleInstanceOnly)// VisibleInstanceOnly 仅在 实例化 细节面板可见
		FString VisibleInstanceOnlyInt;

		 
	UPROPERTY(VisibleAnywhere)// VisibleAnywhere 仅在类默认设置可见 、 实例化 细节面板可见
		FVector VisibleAnywhereVector;

	UPROPERTY(EditDefaultsOnly)// 仅在 编辑器的类 默认设置 可以编辑
		int32 EditDefaultsOnlyInt;

	UPROPERTY(EditInstanceOnly)// 仅在 实例化细节面板  可以编辑
		int32 EditInstanceOnlyInt;

	UPROPERTY(EditAnywhere)//  默认设置 实例化细节面板  可以编辑
		FVector EditAnywhereVector;

		
	UPROPERTY(EditAnywhere, BlueprintReadOnly)//  默认设置 实例化细节面板  可以编辑, 仅在蓝图中可读
		int32 BlueprintReadOnlyInt;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)//  默认设置 实例化细节面板  可以编辑, 仅在蓝图中可读 可以写
		int32 BlueprintReadWriteInt;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "myIntValue")//  category 目录
		FVector myValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "myIntValue|mySubIntValue")//  category 子 目录
		FVector mySubIntValue;



	//mate 元数据说明符
	// displayName 别名

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "metaValue"))// 
		int32 metaValueInt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Controller"))// EditorCondition 条件编辑
		bool isController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "isController"))//  isController 为 真  value3 才可以编辑
		float value3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "isControllerTrue"))//  isController 为 真  value3 才可以编辑
		bool isTrue;





	UFUNCTION(BlueprintCallable, Category = "myFunctionPrint")	// 函数的  让 蓝图可以 调用到
		void myFunctionPrint();

	//// 纯净函数； 纯函数
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "myFunctionPrint")	// 函数的  让 蓝图可以 调用到
		bool myFunctionPrinttPure();


	// BlueprintImplementableEvent 在 C++ 中  声明，不能定义 蓝图可重写
	UFUNCTION(BlueprintImplementableEvent)
		void Test1();
	UFUNCTION(BlueprintImplementableEvent)
		int Test2();
	UFUNCTION(BlueprintImplementableEvent)
		void Test11(const FString& MyString);
	UFUNCTION(BlueprintImplementableEvent)
		void Test22(const FString& MyString);


	// BlueprintNativeEvent 在 C++ 中声明 和实现蓝图可重载或 者 不重载
	UFUNCTION(BlueprintNativeEvent)
		void TestA();
	UFUNCTION(BlueprintNativeEvent)
		int TestB();
	UFUNCTION(BlueprintNativeEvent)
		void TestC(const FString& MyString);
	UFUNCTION(BlueprintNativeEvent)
		int TestD(const FString& MyString);

	// 元数据说明 符 mate
	UFUNCTION(BlueprintCallable, Category = "myFunctionPrint", meta = (DisplayName = "myPrintTest"))
		void PrintTest();

		


	// 声明变量 enum
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "myEnum")//  category 子 目录
		TEnumAsByte<myEnumType::myEnum> myEnum;


	// 声明变量 enum
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EMyTestEnum")
		EMyTestEnum MyCustomTestEnum;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyStruct")
		FMyStruct MyCustomStruct;




	// 蓝图声明时 暴露， 在 构造函数中 创建初始值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyExposeOnSpawn", meta = (ExposeOnSpawn = "ExposeOnSpawnValue"))
		float MyHealth;

	UPROPERTY()
		UMyPublicObject* myTestObject;



	UPROPERTY()
		UMyPublicGameInstance* myPublicGameInstance;





	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MySceneComponent")
		USceneComponent* MyRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MySceneComponent")
		USpringArmComponent* MySpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MySceneComponent")
		UCameraComponent* MyCamera;



	// 鼠标滚轮移动 控制相机 镜头缩放
	void Zoom(bool Direction, float ZoomSpeed);

};
