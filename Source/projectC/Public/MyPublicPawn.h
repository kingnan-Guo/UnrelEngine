// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPublicObject.h"
#include "MyPublicGameInstance.h"
#include "GameFramework/SpringArmComponent.h"// �����ҡ�� ��ͷ�ļ�
#include "Camera/CameraComponent.h" // ����� ͷ�ļ�
#include "GameFramework/Pawn.h"
#include "MyPublicPawn.generated.h"


UENUM(BlueprintType)// ö��  BlueprintType ������ ��ͼ�� �� �ṹ�����ѡ�� �� myEnum
namespace myEnumType {
	enum myEnum {
		type1,
		type2
	};
}

UENUM(BlueprintType)// ö�������� ��һ�ַ�ʽ
enum class EMyTestEnum:uint8 {
	oneType UMETA(DisplayName = "oneType"),
	twoType UMETA(DisplayName = "twoType")
};


USTRUCT(BlueprintType)// BlueprintType ������ ��ͼ�� �� �ṹ�����ѡ�� �� MyStruct
struct FMyStruct
{
	GENERATED_BODY()// 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyStruct")//  category Ŀ¼
		int32  MyStructInt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyStruct")//  category Ŀ¼
		int32 Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyStruct")//  category Ŀ¼
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


	UPROPERTY(VisibleDefaultsOnly)// ͨ������ ������ ��¶�� ��ͼ ���� ϸ������У� ��û����ɷ������ݣ�UPROPERTY ����ͼ �ҵ����� ���߷���; VisibleDefaultsOnly ������Ĭ�����ÿɼ�
		int32 VisibleDefaultsOnlyInt;// ����һ������

	UPROPERTY(VisibleInstanceOnly)// VisibleInstanceOnly ���� ʵ���� ϸ�����ɼ�
		FString VisibleInstanceOnlyInt;

		 
	UPROPERTY(VisibleAnywhere)// VisibleAnywhere ������Ĭ�����ÿɼ� �� ʵ���� ϸ�����ɼ�
		FVector VisibleAnywhereVector;

	UPROPERTY(EditDefaultsOnly)// ���� �༭������ Ĭ������ ���Ա༭
		int32 EditDefaultsOnlyInt;

	UPROPERTY(EditInstanceOnly)// ���� ʵ����ϸ�����  ���Ա༭
		int32 EditInstanceOnlyInt;

	UPROPERTY(EditAnywhere)//  Ĭ������ ʵ����ϸ�����  ���Ա༭
		FVector EditAnywhereVector;

		
	UPROPERTY(EditAnywhere, BlueprintReadOnly)//  Ĭ������ ʵ����ϸ�����  ���Ա༭, ������ͼ�пɶ�
		int32 BlueprintReadOnlyInt;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)//  Ĭ������ ʵ����ϸ�����  ���Ա༭, ������ͼ�пɶ� ����д
		int32 BlueprintReadWriteInt;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "myIntValue")//  category Ŀ¼
		FVector myValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "myIntValue|mySubIntValue")//  category �� Ŀ¼
		FVector mySubIntValue;



	//mate Ԫ����˵����
	// displayName ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "metaValue"))// 
		int32 metaValueInt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Controller"))// EditorCondition �����༭
		bool isController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "isController"))//  isController Ϊ ��  value3 �ſ��Ա༭
		float value3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ToolTip = "isControllerTrue"))//  isController Ϊ ��  value3 �ſ��Ա༭
		bool isTrue;





	UFUNCTION(BlueprintCallable, Category = "myFunctionPrint")	// ������  �� ��ͼ���� ���õ�
		void myFunctionPrint();

	//// ��������
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "myFunctionPrint")	// ������  �� ��ͼ���� ���õ�
		bool myFunctionPrinttPure();


	// BlueprintImplementableEvent �� C++ ��  ���������ܶ��� ��ͼ������
	UFUNCTION(BlueprintImplementableEvent)
		void Test1();
	UFUNCTION(BlueprintImplementableEvent)
		int Test2();
	UFUNCTION(BlueprintImplementableEvent)
		void Test11(const FString& MyString);
	UFUNCTION(BlueprintImplementableEvent)
		void Test22(const FString& MyString);


	// BlueprintNativeEvent �� C++ ������ ��ʵ����ͼ�����ػ� �� ������
	UFUNCTION(BlueprintNativeEvent)
		void TestA();
	UFUNCTION(BlueprintNativeEvent)
		int TestB();
	UFUNCTION(BlueprintNativeEvent)
		void TestC(const FString& MyString);
	UFUNCTION(BlueprintNativeEvent)
		int TestD(const FString& MyString);

	// Ԫ����˵�� �� mate
	UFUNCTION(BlueprintCallable, Category = "myFunctionPrint", meta = (DisplayName = "myPrintTest"))
		void PrintTest();

		


	// �������� enum
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "myEnum")//  category �� Ŀ¼
		TEnumAsByte<myEnumType::myEnum> myEnum;


	// �������� enum
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EMyTestEnum")
		EMyTestEnum MyCustomTestEnum;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyStruct")
		FMyStruct MyCustomStruct;




	// ��ͼ����ʱ ��¶�� �� ���캯���� ������ʼֵ
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



	// �������ƶ� ������� ��ͷ����
	void Zoom(bool Direction, float ZoomSpeed);

};
