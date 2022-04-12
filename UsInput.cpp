#include "../Public/UsInput.h"

void UsInput::InitializeInput(const AActor* contextObject)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(contextObject, 0);
	if (PC) {

		mInputComponent = NewObject<UInputComponent>(UInputSettings::GetDefaultInputComponentClass());
		mInputComponent->Priority = 10;

		PC->PushInputComponent(mInputComponent);

		auto actionMappings = UInputSettings::GetInputSettings()->GetActionMappings();
		for (int i = 0; i < actionMappings.Num(); i++)
		{
			UInputSettings::GetInputSettings()->RemoveActionMapping(actionMappings[i]);
		}

		auto axisMappings = UInputSettings::GetInputSettings()->GetAxisMappings();
		for (int i = 0; i < axisMappings.Num(); i++)
		{
			UInputSettings::GetInputSettings()->RemoveAxisMapping(axisMappings[i]);
		}

		TArray<FKey> allKeys;
		EKeys::GetAllKeys(allKeys);

		for (int32 i = 0; i < allKeys.Num(); i++)
		{
			FKey currentKey = allKeys[i];

			if (currentKey.IsAxis1D()) {

				mAxisMap.Add(currentKey.GetFName(), 0.0);

				FInputAxisKeyMapping  AxisMap;
				AxisMap.AxisName = currentKey.GetFName();
				AxisMap.Key = currentKey;
				UInputSettings::GetInputSettings()->AddAxisMapping(AxisMap);

				FInputAxisBinding AxisBinding(currentKey.GetFName());
				AxisBinding.bConsumeInput = true;
				AxisBinding.bExecuteWhenPaused = false;

				AxisBinding.AxisDelegate.GetDelegateForManualSet().BindLambda([=](float Value)
					{
						mAxisMap[currentKey.GetFName()] = Value;
					});
				mInputComponent->AxisBindings.Add(MoveTemp(AxisBinding));
			}
			else
			{
				FInputActionKeyMapping ActionMap;
				ActionMap.ActionName = currentKey.GetFName();
				ActionMap.Key = currentKey;
				UInputSettings::GetInputSettings()->AddActionMapping(ActionMap);

				mIsPressMap.Add(currentKey.GetFName(), false);

				FInputActionBinding ABPressed(currentKey.GetFName(), IE_Pressed);
				ABPressed.bConsumeInput = true;

				ABPressed.ActionDelegate.GetDelegateWithKeyForManualSet().BindLambda([=](const FKey& Key)
					{
						mIsPressMap[Key.GetFName()] = true;
					});
				mInputComponent->AddActionBinding(MoveTemp(ABPressed));

				FInputActionBinding ABReleased(currentKey.GetFName(), IE_Released);
				ABReleased.bConsumeInput = true;
				ABReleased.ActionDelegate.GetDelegateWithKeyForManualSet().BindLambda([=](const FKey& Key)
					{
						mIsPressMap[Key.GetFName()] = false;
					});
				mInputComponent->AddActionBinding(MoveTemp(ABReleased));
			}
		}

		UInputSettings::GetInputSettings()->ForceRebuildKeymaps();
		UInputSettings::GetInputSettings()->SaveKeyMappings();
	}
}

void UsInput::ReleaseInput()
{
	mInputComponent = nullptr;
}

bool UsInput::IsPress(const int keyCode)
{
	FKey key = FInputKeyManager::Get().GetKeyFromCodes(keyCode, 0);

	return IsPress(key);
}

bool UsInput::IsPress(const FKey& key)
{
	if (!mIsPressMap.Contains(key.GetFName())) {
		return false;
	}

	return mIsPressMap[key.GetFName()];
}

float UsInput::AxisValue(const FKey& key)
{
	if (!mAxisMap.Contains(key.GetFName())) {
		return 0.0;
	}

	return mAxisMap[key.GetFName()];
}