// Copyright Epic Games, Inc. All Rights Reserved.

#include "LocalMultiplayer.h"
#include "Editor.h"

#include "CoreMinimal.h"
#include "SlateBasics.h"
//#include "Slate/SlateBasics.h"
#include "Framework/Notifications/NotificationManager.h"
//#include "Notifications\SNotificationList.h"
#include "Widgets/Notifications/SNotificationList.h"
#include <Dialog/SMessageDialog.h>
#include "Misc/MessageDialog.h"
#include <Kismet/GameplayStatics.h>
#include <Subsystems/EditorActorSubsystem.h>


#define LOCTEXT_NAMESPACE "FLocalMultiplayerModule"

void FLocalMultiplayerModule::StartupModule()
{

	UE_LOG(LogTemp, Warning, TEXT("LocalMultiplayer: Log Started"));

	//FEditorDelegates::BeginPIE.AddUObject(this, &FLocalMultiplayerModule::OnBeginPIE);

	
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	//FEditorDelegates::BeginPIE.AddUObject(this, &FLocalMultiplayerModule::OnBeginPIE);
}

void FLocalMultiplayerModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FLocalMultiplayerModule::OnBeginPIE(bool bIsSimulating)
{
	UE_LOG(LogTemp, Warning, TEXT("LocalMultiplayer: OnBeginPIE"));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLocalMultiplayerModule, LocalMultiplayer)