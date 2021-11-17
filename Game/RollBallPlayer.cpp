// Fill out your copyright notice in the Description page of Project Settings.

#include "RollBallPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ARollBallPlayer::ARollBallPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Create the components in our tree structure
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");

	// Set the root component
	RootComponent = Mesh;

	//SpringArm will follow Mesh
	SpringArm->SetupAttachment(Mesh);
	Camera->SetupAttachment(SpringArm);

	Mesh->SetSimulatePhysics(true);

	
}

// Called when the game starts or when spawned
void ARollBallPlayer::BeginPlay()
{
	Super::BeginPlay();

	//Calculate the MoveForce based on mass
	MoveForce *= Mesh->GetMass();
	JumpImpulse *= Mesh-> GetMass();

	//Manage collisions 
	Mesh->OnComponentHit.AddDynamic(this, &ARollBallPlayer::onHit);
}


// Called to bind functionality to input
void ARollBallPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Custom Axis Bindings
	InputComponent->BindAxis("MoveForward",this,&ARollBallPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ARollBallPlayer::MoveRight);

	//Custom Action Binding
	InputComponent->BindAction("Jump",IE_Pressed,this, &ARollBallPlayer::Jump);
}

void ARollBallPlayer::MoveRight(float Value)
{
	const FVector Right = Camera->GetRightVector() * MoveForce * Value;
	Mesh->AddForce(Right);
}

void ARollBallPlayer::MoveForward(float Value)
{
	const FVector Forward = Camera->GetForwardVector() * MoveForce * Value;
	Mesh->AddForce(Forward);
}

void ARollBallPlayer::Jump()
{
	//Cap the number of jumps
	if(JumpCount >= MaxJumpCount) return;
	//Apply an impulse to Z 
	Mesh->AddImpulse(FVector(0,0,JumpImpulse));
	//Track the jumps
	JumpCount++;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::Printf(TEXT("Jumps = %d"), JumpCount));
}

void ARollBallPlayer::onHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{

	const float HitDirection = Hit.Normal.Z;

	if (HitDirection > 0) JumpCount = 0;
	//Since is touching the floor will constantly be called
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("HIT"));
	
}

