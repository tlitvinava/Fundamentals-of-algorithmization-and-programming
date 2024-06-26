#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enums.h"
#include "StorageInterface.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStorageInventoryChange, FInventory, newInventory);

UINTERFACE(MinimalAPI)
class UStorageInterface : public UInterface
{
	GENERATED_BODY()
};

class RTSGAME_API IStorageInterface
{
	GENERATED_BODY()

public:
	virtual TArray<FItem>& GetItems();
	virtual void AddItem(FString name, int32 amount);
	virtual void RemoveItem(FString name, int32 amount);
	FInventory GetInventory() const { return inventory; }
	void SetInventory(FInventory val) { inventory = val; }

	FStorageInventoryChange inventoryChange;
protected:
		FInventory inventory;
};
