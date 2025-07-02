// Fill out your copyright notice in the Description page of Project Settings.


#include "MySmartPtrActor.h"

// Sets default values
AMySmartPtrActor::AMySmartPtrActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMySmartPtrActor::BeginPlay()
{
	Super::BeginPlay();

	TestSmartPtrFunc();
	TestSmartPtrFunc2();
	
}

// Called every frame
void AMySmartPtrActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMySmartPtrActor::TestSmartPtrFunc(){
	//  C++ 中创建指针
	TestA* ptr1 = new TestA(3,2.0f);

	// 共享指针 左值 初始化
	TSharedPtr<TestA> shaderPtr1(ptr1);// 不推荐这种方式，容易混淆 原生指针 和 共享指针
	ptr1 = nullptr;// 设置完共享指针后  原生指针 置空 才行



	// 共享指针 右值 初始化
	TSharedPtr<TestA> shaderPtr2(new TestA(4, 5.0f));

	// 使用共享指针 初始化 另一个共享指针； 拷贝构造函数
	TSharedPtr<TestA> shaderPtr3(shaderPtr2);


	//  UE 的方法 初始化共享指针
	TSharedPtr<TestA> shaderPtr4 = nullptr;// 初始化空指针
	shaderPtr4 = MakeShareable(new TestA(6, 7.0f));

	// 线程安全的共享指针
	TSharedPtr<TestA, ESPMode::ThreadSafe> shaderPrt5(new TestA(8, 9.0f));




	// 共享指针常用的接口

	if (shaderPrt5.IsValid()) {	// 判断 共享指针 是否指向一个有效的对象
	    UE_LOG(LogTemp, Warning, TEXT("shaderPrt5 is valid"));

		// 共享引用
		TSharedRef<TestA> shaderRef1(new TestA(10, 11.0f));// 危险！ 如果智能指针的构造函数抛出异常，分配的 TestA 对象不会被释放（因为此时引用计数尚未建立），导致内存泄漏
		// 这里直接用new的方法创建sharedref是不正确的，应当直接用 sharedptr 来初始化创建 sharedref 
		TSharedRef<TestA> shaderRef2 = MakeShared<TestA>(10, 11.0f);

		// 共享指针 转换成  共享引用
		shaderRef1 = shaderPrt5.ToSharedRef();

		// 共享引用 计数
		int32 Count1 = shaderRef1.GetSharedReferenceCount(); // 获得应用计数

		UE_LOG(LogTemp, Warning, TEXT("Count1 : =%d"), Count1);


		
		if(shaderPrt5.IsUnique()){// 判断是否为 唯一的 共享指针，是否指向 唯一的对象; 引用计数为1

		} else {
		    UE_LOG(LogTemp, Warning, TEXT("shaderPrt5 IsUnique false"));
		}

		shaderPrt5.Get()->a;// 解引用 就是引用对象的 原生指针 
		UE_LOG(LogTemp, Warning, TEXT("shaderPrt5.Get()->a : =%d"), shaderPrt5.Get()->a);


		shaderPrt5.Reset(); // 重置 共享指针， 把共享指针变为 null，引用计数减一，当引用计数为0 时，对象被释放

		int32 Count2 = shaderPrt5.GetSharedReferenceCount(); // 获得应用计数

		UE_LOG(LogTemp, Warning, TEXT("Count2 : =%d"), Count2);// 这时 应该为 0
			shaderPrt5.Reset(); 

		// int32 Count3 = shaderRef1.GetSharedReferenceCount(); // 获得应用计数

		// UE_LOG(LogTemp, Warning, TEXT("Count3 : =%d"), Count3);// 这时 应该为 0
	}
}




void AMySmartPtrActor::TestSmartPtrFunc2(){
	// 共享引用 初始化的时候必须 要 有一个 有效的对象


	TSharedRef<TestA> shaderRef2(new TestA(22, 33.0f));// 危险！ 如果智能指针的构造函数抛出异常，分配的 TestA 对象不会被释放（因为此时引用计数尚未建立），导致内存泄漏
	if(shaderRef2.IsUnique()){// 判断是否为 唯一的 共享指针，是否指向 唯一的对象; 引用计数为1
		shaderRef2->a; // s虽然是共享引用但是 解 引用的方式 仍然是 -> 方式

		UE_LOG(LogTemp, Error, TEXT(" shaderRef2->a : =%d"), shaderRef2->a);
		
		
		
		// 共享引用转化成共享指针
		TSharedPtr<TestA> ShaderPtr6;
		ShaderPtr6 = shaderRef2;// 共享引用 赋值给 共享指针
		ShaderPtr6.Get()->b; // 解引用 就是引用对象的 原生指针
		UE_LOG(LogTemp, Error, TEXT(" ShaderPtr6.Get()->b : =%f"), ShaderPtr6.Get()->b);

		ShaderPtr6.Get()->a =  14;	

		UE_LOG(LogTemp, Error, TEXT(" ShaderPtr6.Get()->a : =%d"), ShaderPtr6.Get()->a);


		// 清除 shaderRef2
		// shaderRef2.Reset();
		ShaderPtr6.Reset(); // 重置 共享指针， 把共享指针变为 null，引用计数减一，当引用计数为0 时，对象被释放


		int32 Count4 = shaderRef2.GetSharedReferenceCount(); // 获得应用计数
		UE_LOG(LogTemp, Warning, TEXT("Count4 : =%d"), Count4);// 这时 应该为 0

		


		int32 Count5 = ShaderPtr6.GetSharedReferenceCount(); // 获得应用计数
		UE_LOG(LogTemp, Warning, TEXT("Count5 : =%d"), Count5);// 这时 应该为 0



	} else {
	    UE_LOG(LogTemp, Error, TEXT("shaderRef2 IsUnique false"));

	}
}

/**
 * 弱指针
 * 弱指针不能解引用，不能访问对象，只能访问共享指针
 * 弱指针可以用来检测对象是否被释放
 * 弱指针可以用来解决循环引用的问题
 * 
 * 为了解决循环引用 只对 引用对象保留引用权， 并不参与引用计数
 * 
 * 需要操作 引用对象的时候 需要转化成 智能指针；
 *  不能阻止对象被销毁， 如果 弱指针 指向 对象被销毁的话 ， 弱指针 会自动清空 ， 不需要手动清空
 * 
 */
void AMySmartPtrActor::TestSmartPtrFunc3(){
	// 声明 共享指针
	TSharedPtr<TestA> shaderPtr7 = MakeShareable(new TestA(44, 55.0f));

	// 声明共享引用
	TSharedRef<TestA> shaderRef8(new TestA(22, 33.0f));// 危险！ 如果智能指针的构造函数抛出异常，分配的 TestA 对象不会被释放（因为此时引用计数尚未建立），导致内存泄漏

	// 声明 弱指针 并初始化
	TWeakPtr<TestA> weakkPtr7(shaderPtr7);

	TWeakPtr<TestA> weakkPtr8(shaderRef8);


	if(weakkPtr7.IsValid()){ // 判断 弱指针 是否指向一个有效的对象
		UE_LOG(LogTemp, Warning, TEXT("weakkPtr7 is valid"));


		// 弱指针 转换成 共享指针
		TSharedPtr<TestA> shaderPtr9(weakkPtr7.Pin());// Pin 函数 返回一个 共享指针，如果弱指针 已经失效，则返回一个空指针
		if(shaderPtr9.IsValid()){
			shaderPtr9.Get()->a;
			UE_LOG(LogTemp, Warning, TEXT("shaderPtr9 is valid"));
			UE_LOG(LogTemp, Warning, TEXT("shaderPtr9.Get()->a : =%d"), shaderPtr9.Get()->a);// 这时 应该为 0
		}


	}
}


