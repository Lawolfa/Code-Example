//Written by Justin Okanlawon 27-8-2022
#include "BaseEntity.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/TextRenderComponent.h"
#include "TimerManager.h"
#include "InventoryComponent.h"
#include "Items.h"
#include "Weapon.h"


//Dev Functions
ABaseEntity::ABaseEntity()
{
	PrimaryActorTick.bCanEverTick = true;

	//Variable initialization
	EquippedItem = nullptr;

	RunSpeed = 1000.f;
	WalkSpeed = 400.f;
	MouseSensetivity = 100.f;
	ZoomSpeed = 50.f;

	EquippedItemName = "Empty str";
	EquippedItemType = "Empty str";

	bHasReach = true;
	Reach = 200.f;
	ReachOffset = { 0.f, 0.f, 40.f };
	Spherical.SetSphere(30.f);

	//Component initialization
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("Inventory");

	DebugText1 = CreateDefaultSubobject<UTextRenderComponent>("DebugText1");
	DebugText2 = CreateDefaultSubobject<UTextRenderComponent>("DebugText2");
	DebugText3 = CreateDefaultSubobject<UTextRenderComponent>("DebugText3");

	DebugText1->SetupAttachment(RootComponent);
	DebugText2->SetupAttachment(RootComponent);
	DebugText3->SetupAttachment(RootComponent);
}

void ABaseEntity::BeginPlay()
{
	Super::BeginPlay();
}	

void ABaseEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DeltaC = GetWorld()->DeltaTimeSeconds;


	//Debug
	DrawDebugLine(GetWorld(), ReachStart, ReachEnd, FColor::Yellow, false, -1.f, 0U, 5.f);
	ReachStart = GetActorLocation() + ReachOffset + GetActorForwardVector() * 10.f;
	ReachEnd = ReachStart + GetController()->GetControlRotation().Vector() * Reach;
}

void ABaseEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	PlayerInputComponent->BindAction("ZoomIn", EInputEvent::IE_Pressed, this, &ABaseEntity::ZoomIn);
	PlayerInputComponent->BindAction("ZoomOut", EInputEvent::IE_Pressed, this, &ABaseEntity::ZoomOut);
	PlayerInputComponent->BindAction("InteractPickup", EInputEvent::IE_Pressed, this, &ABaseEntity::InteractPickup);

	PlayerInputComponent->BindAction("Equip1", EInputEvent::IE_Pressed, this, &ABaseEntity::Equip1);
	PlayerInputComponent->BindAction("Equip2", EInputEvent::IE_Pressed, this, &ABaseEntity::Equip2);
	PlayerInputComponent->BindAction("Equip3", EInputEvent::IE_Pressed, this, &ABaseEntity::Equip3);
	PlayerInputComponent->BindAction("Equip4", EInputEvent::IE_Pressed, this, &ABaseEntity::Equip4);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABaseEntity::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABaseEntity::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ABaseEntity::LookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &ABaseEntity::LookRight);

	PlayerInputComponent->BindAxis("UseEquippedItem1", this, &ABaseEntity::UseEquippedItem1);
	PlayerInputComponent->BindAxis("UseEquippedItem2", this, &ABaseEntity::UseEquippedItem2);
	PlayerInputComponent->BindAxis("UseEquippedItem3", this, &ABaseEntity::UseEquippedItem3);
	PlayerInputComponent->BindAxis("UseEquippedItem4", this, &ABaseEntity::UseEquippedItem4);
	PlayerInputComponent->BindAxis("UseEquippedItem5", this, &ABaseEntity::UseEquippedItem5);
	PlayerInputComponent->BindAxis("UseEquippedItem6", this, &ABaseEntity::UseEquippedItem6);

}

void ABaseEntity::Equip1()
{
	//have item in hands?
	if (EquippedItem != nullptr)
	{
		if (InventoryComponent->ItemsOnBody[0] == EquippedItem)
		{
			UnEquipItem();
			UpdateItemPositions();
			return;
		}

		if (InventoryComponent->ItemsOnBody[0] != nullptr && InventoryComponent->ItemsOnBody[0] != EquippedItem)
		{
			UnEquipItem();
			EquipAnItem(InventoryComponent->ItemsOnBody[0]);
			UpdateItemPositions();
			return;
		}

		if (InventoryComponent->ItemsOnBody[0] == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("No item to equip."));
			return;
		}
	}

	//No item equipped
	if (EquippedItem == nullptr)
	{
		if (EquipAnItem(InventoryComponent->ItemsOnBody[0]))
		{
			UpdateItemPositions();
			return;
		}
	}
}

void ABaseEntity::Equip2()
{
	//have item in hands?
	if (EquippedItem != nullptr)
	{
		if (InventoryComponent->ItemsOnBody[1] == EquippedItem)
		{
			UnEquipItem();
			UpdateItemPositions();
			return;
		}

		if (InventoryComponent->ItemsOnBody[1] != nullptr && InventoryComponent->ItemsOnBody[1] != EquippedItem)
		{
			UnEquipItem();
			EquipAnItem(InventoryComponent->ItemsOnBody[1]);
			UpdateItemPositions();
			return;
		}

		if (InventoryComponent->ItemsOnBody[1] == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("No item to equip."));
			return;
		}
	}

	//No item equipped
	if (EquippedItem == nullptr)
	{
		if (EquipAnItem(InventoryComponent->ItemsOnBody[1]))
		{
			UpdateItemPositions();
			return;
		}
	}

}

void ABaseEntity::Equip3()
{
	//Item Equipped?
	if (EquippedItem != nullptr)
	{
		if (InventoryComponent->SmallItemsOnBody[0] == EquippedItem)
		{
			UnEquipItem();
			UpdateItemPositions();
			return;
		}


		if (InventoryComponent->SmallItemsOnBody[0] != EquippedItem && InventoryComponent->SmallItemsOnBody[0] != nullptr)
		{
			UnEquipItem();
			EquipAnItem(InventoryComponent->SmallItemsOnBody[0]);
			UpdateItemPositions();
			return;
		}

		if (InventoryComponent->SmallItemsOnBody[0] == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("No item to equip."));
			return;
		}
	}

	//No item equipped
	if (EquippedItem == nullptr)
	{
		if (EquipAnItem(InventoryComponent->SmallItemsOnBody[0]))
		{
			UpdateItemPositions();
			return;
		}
	}
}

void ABaseEntity::Equip4()
{
	//Item Equipped?
	if (EquippedItem != nullptr)
	{
		if (InventoryComponent->SmallItemsOnBody[1] == EquippedItem)
		{
			UnEquipItem();
			UpdateItemPositions();
			return;
		}


		if (InventoryComponent->SmallItemsOnBody[1] != EquippedItem && InventoryComponent->SmallItemsOnBody[1] != nullptr)
		{
			UnEquipItem();
			EquipAnItem(InventoryComponent->SmallItemsOnBody[1]);
			UpdateItemPositions();
			return;
		}

		if (InventoryComponent->SmallItemsOnBody[1] == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("No item to equip."));
			return;
		}
	}

	//No item equipped
	if (EquippedItem == nullptr)
	{
		if (EquipAnItem(InventoryComponent->SmallItemsOnBody[1]))
		{
			UpdateItemPositions();
			return;
		}
	}
}

bool ABaseEntity::EquipAnItem(AItems* ItemToEquip)
{
	if (ItemToEquip == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemToEquip is nullptr"));
		return false;
	}

	EquippedItem = ItemToEquip;
	UpdateItemPositions();
	return true;
}

bool ABaseEntity::UnEquipItem()
{
	if (EquippedItem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Nothing to unequip."));
		return false;
	}
	
	EquippedItem = nullptr;
	UpdateItemPositions();
	return true;
}

void ABaseEntity::SetEquippedItemNull()
{
	EquippedItem = nullptr;
	UpdateItemPositions();
}


//Player Actions
void ABaseEntity::UseEquippedItem1(float Value)
{
	if (!UseCheck(Value))
	{
		return;
	}

	//Additional checks specific to this funtion
	if (bSwitchTo34 || bSwitchTo56)
	{
		return;
	}

	//Checks passed, now use
	EquippedItem->Use1();

	//Set to false to prevent using item every frame.
	bAllowActions = false;

	//bAllowActions will be set to true based on the equipped item fire rate
	GetWorldTimerManager().SetTimer(
		FireRateTimerHandle,
		this,
		&ABaseEntity::SetAllowActionsTrue,
		EquippedItem->FireRate);
}

void ABaseEntity::UseEquippedItem2(float Value)
{
	if (!UseCheck(Value))
	{
		return;
	}

	//Additional checks specific to this funtion
	if (bSwitchTo34 || bSwitchTo56)
	{
		return;
	}

	//Checks passed, now use
	EquippedItem->Use2();

	//Set to false to prevent using item every frame.
	bAllowActions = false;

	//bAllowActions will be set to true based on the equipped item fire rate
	GetWorldTimerManager().SetTimer(
		FireRateTimerHandle,
		this,
		&ABaseEntity::SetAllowActionsTrue,
		EquippedItem->FireRate);
}

void ABaseEntity::UseEquippedItem3(float Value)
{
	if (!UseCheck(Value))
	{
		return;
	}
	//Quit if we are not allowed to use
	if (!bSwitchTo34)
	{
		return;
	}
	//Quit if 56 is being activated
	if (bSwitchTo56)
	{
		return;
	}

	//Checks passed, now use
	EquippedItem->Use3();

	//Set to false to prevent using item every frame.
	bAllowActions = false;

	//bAllowActions will be set to true based on the equipped item fire rate
	GetWorldTimerManager().SetTimer(
		FireRateTimerHandle,
		this,
		&ABaseEntity::SetAllowActionsTrue,
		EquippedItem->FireRate);
}

void ABaseEntity::UseEquippedItem4(float Value)
{
	if (!UseCheck(Value))
	{
		return;
	}

	//Quit if we are not allowed to use
	if (!bSwitchTo34)
	{
		return;
	}
	//Quit if 56 is being activated
	if (bSwitchTo56)
	{
		return;
	}

	//Checks passed, now use
	EquippedItem->Use4();

	//Set to false to prevent using item every frame.
	bAllowActions = false;

	//bAllowActions will be set to true based on the equipped item fire rate
	GetWorldTimerManager().SetTimer(
		FireRateTimerHandle,
		this,
		&ABaseEntity::SetAllowActionsTrue,
		EquippedItem->FireRate);
}

void ABaseEntity::UseEquippedItem5(float Value)
{
	if (!UseCheck(Value))
	{
		return;
	}

	//Quit if we are not allowed to use
	if (!bSwitchTo56)
	{
		return;
	}
	//Quit if 34 is being activated
	if (bSwitchTo34)
	{
		return;
	}

	//Checks passed, now use
	EquippedItem->Use5();

	//Set to false to prevent using item every frame.
	bAllowActions = false;

	//bAllowActions will be set to true based on the equipped item fire rate
	GetWorldTimerManager().SetTimer(
		FireRateTimerHandle,
		this,
		&ABaseEntity::SetAllowActionsTrue,
		EquippedItem->FireRate);
}

void ABaseEntity::UseEquippedItem6(float Value)
{
	if (!UseCheck(Value))
	{
		return;
	}

	//Quit if we are not allowed to use
	if (!bSwitchTo56)
	{
		return;
	}
	//Quit if 34 is being activated
	if (bSwitchTo34)
	{
		return;
	}

	//Checks passed, now use
	EquippedItem->Use6();

	//Set to false to prevent using item every frame.
	bAllowActions = false;

	//bAllowActions will be set to true based on the equipped item fire rate
	GetWorldTimerManager().SetTimer(
		FireRateTimerHandle,
		this,
		&ABaseEntity::SetAllowActionsTrue,
		EquippedItem->FireRate);
}

void ABaseEntity::SwitchTo3And4Use(float Value)
{
	if (UseCheck(Value))
	{
		bSwitchTo34 = true;
	}
	else
	{
		bSwitchTo34 = false;
	}
}

void ABaseEntity::SwitchTo5And6Use(float Value)
{
	if (UseCheck(Value))
	{
		bSwitchTo56 = true;
	}
	else
	{
		bSwitchTo56 = false;
	}
}

bool ABaseEntity::UseCheck(float KeyPressValue)
{
	//Must allow actions
	if (!bAllowActions)
	{
		return false;
	}
	//Equipped Item cannot be empty
	if (EquippedItem == nullptr)
	{
		return false;
	}
	//Key must be pressed down
	if (KeyPressValue < 0.1f)
	{
		return false;
	}

	//Checks passed
	return true;
}

void ABaseEntity::InteractPickup()
{
	//Must have Reach enabled and actions
	if (!bHasReach || !bAllowActions)
	{
		return;
	}

	//Update vectors
	ReachStart = GetActorLocation() + ReachOffset + GetActorForwardVector();
	ReachEnd = ReachStart + GetController()->GetControlRotation().Vector() * Reach;
	

	//LineTrace returns true if something was hit
	if (GetWorld()->SweepSingleByChannel(Hit, ReachStart, ReachEnd, GetActorRotation().Quaternion(), ECollisionChannel::ECC_GameTraceChannel2, Spherical))
	{
		//Debug
		DrawDebugSphere(GetWorld(),
			Hit.ImpactPoint,
			30.f, 
			6, 
			FColor::Red, 
			true, 
			-1.f, 
			0, 
			2.f);
		DrawDebugLine(GetWorld(), ReachStart, ReachEnd, FColor::Purple, true, -1.f, 0, 5.f);
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Hit.GetActor()->GetName());
		//End debugg

		AItems* HitActor = Cast<AItems>(Hit.GetActor());
		if (HitActor == nullptr)
		{
			return;
		}

		if (InventoryComponent->AutoAddItem(HitActor))
		{
			UpdateItemPositions();
			return;
		}
	}
}


//Movement
void ABaseEntity::MoveForward(float Value)
{
	if (!MoveCheck())
	{
		return;
	}

	AddMovementInput(GetActorForwardVector() * WalkSpeed * Value * DeltaC);
}

void ABaseEntity::MoveRight(float Value)
{
	if (!MoveCheck())
	{
		return;
	}

	AddMovementInput(GetActorRightVector() * WalkSpeed * Value * DeltaC);
}

bool ABaseEntity::MoveCheck()
{
	if (!bAllowMovement)
	{
		return false;
	}
	return true;
}

void ABaseEntity::LookUp(float Value)
{
	if (!LookCheck())
	{
		return;
	}
	AddControllerPitchInput(MouseSensetivity * Value * DeltaC);
}

void ABaseEntity::LookRight(float Value)
{
	if (!LookCheck())
	{
		return;
	}
	AddControllerYawInput(MouseSensetivity * Value * DeltaC);
}

bool ABaseEntity::LookCheck()
{
	if (!bAllowLook)
	{
		return false;
	}
	return true;
}

void ABaseEntity::ZoomIn()
{
	SpringArm->TargetArmLength -= 50.f;
}

void ABaseEntity::ZoomOut()
{
	SpringArm->TargetArmLength += 50.f;
}


void ABaseEntity::SetAllowActions(bool ShouldBeAllowed)
{
	bAllowActions = ShouldBeAllowed;
}

void ABaseEntity::SetAllowActionsTrue()
{
	bAllowActions = true;
}

void ABaseEntity::SetAllowActionsFalse()
{
	bAllowActions = false;
}

void ABaseEntity::SetAllowMovement(bool ShouldBeAllowed)
{
}

void ABaseEntity::SetAllowMovementTrue()
{
	bAllowMovement = true;
}

void ABaseEntity::SetAllowMovementFalse()
{
	bAllowMovement = false;
}

void ABaseEntity::SetAllowLook(bool ShouldBeAllowed)
{
}

void ABaseEntity::SetAllowLookTrue()
{
	bAllowLook = true;
}

void ABaseEntity::SetAllowLookFalse()
{
	bAllowLook = false;
}

void ABaseEntity::UpdateItemPositions()
{
	//Display Items on the body
	if (!InventoryComponent->IsItemsOnBodySlotNull(0))
	{
		InventoryComponent->ItemsOnBody[0]->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, InventoryComponent->ItemsOnBody[0]->DesiredSocketForStorage1);
	}
	if (!InventoryComponent->IsItemsOnBodySlotNull(1))
	{
		InventoryComponent->ItemsOnBody[1]->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, InventoryComponent->ItemsOnBody[1]->DesiredSocketForStorage2);
	}
	if (!InventoryComponent->IsSmallItemsOnBodySlotNull(0))
	{
		InventoryComponent->SmallItemsOnBody[0]->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, InventoryComponent->SmallItemsOnBody[0]->DesiredSocketForStorage1);
	}
	if (!InventoryComponent->IsSmallItemsOnBodySlotNull(1))
	{
		InventoryComponent->SmallItemsOnBody[1]->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, InventoryComponent->SmallItemsOnBody[1]->DesiredSocketForStorage2);
	}
	if (EquippedItem != nullptr)
	{
		EquippedItem->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, EquippedItem->DesiredEquipSocket);
	}
}
