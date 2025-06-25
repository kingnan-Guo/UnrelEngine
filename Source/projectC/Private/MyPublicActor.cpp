// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPublicActor.h"

// Sets default values
AMyPublicActor::AMyPublicActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("MyPublicActor.cpp"));

	MyScene = CreateDefaultSubobject<USceneComponent>(TEXT("MyCustomSence"));
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyCustomMesh"));
	MyParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyCustomParticle"));
	MyBox = CreateDefaultSubobject<UBoxComponent>(TEXT("MyCustomBox"));
	MyAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("MyCustomAudio"));


	// ���ø��Ӽ�
	RootComponent = MyScene; // ��ΪĬ�ϸ����?

	// �� myMesh �ŵ� ���������?
	MyMesh->SetupAttachment(MyScene);
	MyParticle->SetupAttachment(MyScene);
	MyBox->SetupAttachment(MyScene);
	MyAudio->SetupAttachment(MyBox);


	// ���ؾ�̬��Դ
	static ConstructorHelpers::FObjectFinder<UStaticMesh>TempStaticMesh(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"));
	MyMesh->SetStaticMesh(TempStaticMesh.Object);

	static ConstructorHelpers::FObjectFinder<UParticleSystem>TempParticSystem(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	MyParticle->SetTemplate(TempParticSystem.Object);

	static ConstructorHelpers::FObjectFinder<USoundWave>TempSound(TEXT("/Script/Engine.SoundWave'/Game/StarterContent/Audio/Collapse01.Collapse01'"));
	MyAudio->SetSound(TempSound.Object);



	//���ؾ�̬��
	static ConstructorHelpers::FClassFinder<AActor>TempMyActor(TEXT("/Script/Engine.Blueprint'/Game/StarterContent/Blueprints/Blueprint_WallSconce.Blueprint_WallSconce_C'"));
	myActor = TempMyActor.Class;



	MyBox->OnComponentBeginOverlap.AddDynamic(this, &AMyPublicActor::BeginOverLapFunction);
	MyBox->OnComponentEndOverlap.AddDynamic(this, &AMyPublicActor::EndOverLapFunction);


	// ��ײ
	MyBox->OnComponentHit.AddDynamic(this, &AMyPublicActor::HitFunction);



	// ��ײ����
	MyBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);// ECollisionEnabled::NoCollision û����ײ
	MyBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);// ֻ�в�ѯ��ײ
	MyBox->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);// ֻ�� ������ײ
	MyBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);//  ��ѯ ���� ��ײ
	MyBox->SetCollisionEnabled(ECollisionEnabled::ProbeOnly);// ֻ�� probe ��ײ ������ ̽�� ��ײ
	MyBox->SetCollisionEnabled(ECollisionEnabled::QueryAndProbe);// ��ѯ�� ̽�� ��ײ


	// ��ײ��������
	MyBox->SetCollisionObjectType(ECC_WorldStatic);// ���� ��̬
	MyBox->SetCollisionObjectType(ECC_WorldDynamic);// ���� ��̬
	MyBox->SetCollisionObjectType(ECC_Pawn);// ��ɫ
	MyBox->SetCollisionObjectType();// zc

}

// Called when the game starts or when spawned
void AMyPublicActor::BeginPlay()
{
	Super::BeginPlay();
	int a = 10;
	UE_LOG(LogTemp, Warning, TEXT("AMyPublicActor BeginPlay %d"), a);

	if (myActor) {
		UE_LOG(LogTemp, Warning, TEXT("AMyPublicActor BeginPlay myActor %s"), *myActor->GetName());

	}



	// ��̬������Դ
	UStaticMesh* MyTempStaticMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (MyTempStaticMesh) {
		MyMesh->SetStaticMesh(MyTempStaticMesh);
	}


	// ��̬������
	UClass* myTempClass = LoadClass<AActor>(this, TEXT("/Script/Engine.Blueprint'/Game/StarterContent/Blueprints/Blueprint_CeilingLight.Blueprint_CeilingLight_C'"));
	if (myTempClass) {
		AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(myTempClass, FVector::ZeroVector, FRotator::ZeroRotator);
	}


}

// Called every frame
void AMyPublicActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// UE_LOG(LogTemp, Warning, TEXT("AMyPublicActor Tick"));


	//
	FVector myOffset = FVector(1, 0, 0);
	FHitResult myFHitResult;
	//AddActorLocalOffset(myOffset, false, &myFHitResult);// ƫ������ �Ƿ������ײ��? ��ײ�󷵻صĲ���
	AddActorWorldOffset(myOffset, false, &myFHitResult);

}

void AMyPublicActor::BeginOverLapFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BeginOverLapFunction"));// ����Ļ����ʾһ����Ϣ
}

void AMyPublicActor::EndOverLapFunction(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("EndOverLapFunction"));// ����Ļ����ʾһ����Ϣ
}

void AMyPublicActor::HitFunction(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("HitFunction"));// ����Ļ����ʾһ����Ϣ
}


