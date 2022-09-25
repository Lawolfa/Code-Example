//Written by Justin Okanlawon 27-8-2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEntity.generated.h"


//Forward Declarations
class USpringArmComponent;
class UCameraComponent;
class UTextRenderComponent;
class UInventoryComponent;
class AItems;

UCLASS()
class MG_TERROR_API ABaseEntity : public ACharacter
{
	GENERATED_BODY()

protected:
	//Gets executed when gameplay begins.
	virtual void BeginPlay() override;

public:
	//DEV FUNCTIONS
	ABaseEntity();

	//Gets called every frame.
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//ENTITY ACTIONS
	//Equips the item that is in body slot[0]
	void Equip1();

	//Equips the item that is in body slot[1]
	void Equip2();

	//Equips the item that is in small body slot[0]
	void Equip3();

	//Equips the item that is in small body slot[1]
	void Equip4();

	bool EquipAnItem(AItems* ItemToEquip);

	bool UnEquipItem();

	UFUNCTION(BlueprintCallable)
	void SetEquippedItemNull();
 
	void UseEquippedItem1(float Value);

	void UseEquippedItem2(float Value);

	void UseEquippedItem3(float Value);

	void UseEquippedItem4(float Value);

	void UseEquippedItem5(float Value);

	void UseEquippedItem6(float Value);

	//Switches the item use options to the 3rd and 4th option
	void SwitchTo3And4Use(float Value);

	//Switches the item use options to the 5th and 6th option
	void SwitchTo5And6Use(float Value);

	//Allowed to use item? mainly used for cooldowns and firerate of weapons
	bool UseCheck(float KeyPressValue);

	void InteractPickup();


	//PLAYER MOVEMENT
	void MoveForward(float Value);

	void MoveRight(float Value);

	bool MoveCheck();

	void LookUp(float Value);

	void LookRight(float Value);

	bool LookCheck();

	void ZoomIn();

	void ZoomOut();


	UFUNCTION(BlueprintCallable)
	void SetAllowActions(bool ShouldBeAllowed);

	UFUNCTION(BlueprintCallable)
	void SetAllowActionsTrue();

	UFUNCTION(BlueprintCallable)
	void SetAllowActionsFalse();


	UFUNCTION(BlueprintCallable)
	void SetAllowMovement(bool ShouldBeAllowed);

	UFUNCTION(BlueprintCallable)
	void SetAllowMovementTrue();

	UFUNCTION(BlueprintCallable)
	void SetAllowMovementFalse();


	UFUNCTION(BlueprintCallable)
	void SetAllowLook(bool ShouldBeAllowed);

	UFUNCTION(BlueprintCallable)
	void SetAllowLookTrue();

	UFUNCTION(BlueprintCallable)
	void SetAllowLookFalse();


	UFUNCTION(BlueprintCallable)
	void UpdateItemPositions();


	//INVENTORY
	//InventoryComponent has 3 arrays that can hold items, for more info check InventoryComponent.h
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UInventoryComponent* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AItems* EquippedItem;


	//VARIABLES
	UPROPERTY(EditAnywhere)
	float RunSpeed;

	UPROPERTY(EditAnywhere)
	float WalkSpeed;

	UPROPERTY(EditAnywhere)
	float MouseSensetivity;

	UPROPERTY(EditAnywhere)
	float ZoomSpeed;
	

	//FSTRING
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString EquippedItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString EquippedItemType;


	//ENTITY REACH
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasReach;

	UPROPERTY(EditAnywhere)
	float Reach;

	FHitResult Hit;
	FVector ReachStart;
	FVector ReachEnd;
	FVector ReachOffset;
	FCollisionShape Spherical;
	FTimerHandle FireRateTimerHandle;


	
	//COMPONENTS
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;
	

	//DEBUGGING TEXT
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextRenderComponent* DebugText1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextRenderComponent* DebugText2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextRenderComponent* DebugText3;


private:
	bool bAllowActions = true;

	bool bAllowMovement = true;

	bool bAllowLook = true;

	bool bSwitchTo34 = false;

	bool bSwitchTo56 = false;

	//Calculates time between frames, needed so frame rate does not impact gameplay
	float DeltaC = 0.f;


};