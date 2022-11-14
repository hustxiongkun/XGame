#include "TestPlayerController.h"

void ATestPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(PlayerInput)
	{
		// 添加Action映射 ->(按键映射)
		PlayerInput->AddActionMapping(FInputActionKeyMapping(FName("Sprint"), EKeys::LeftShift));
		PlayerInput->AddActionMapping(FInputActionKeyMapping(FName("Jump"), EKeys::SpaceBar));
		
/*
		// Windows绑定所有按键(枚举中只对应大部分),方便改键
		TArray<FKey> Keys;
		EKeys::GetAllKeys(Keys);
		for(int32 i = 0; i < Keys.Num(); ++i)
		{
			const auto& Key = Keys[i];
			PlayerInput->AddActionMapping(FInputActionKeyMapping(Key.GetFName(), Key));
		}
*/
	}
}
