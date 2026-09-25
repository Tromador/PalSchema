#pragma once

#include <string>
#include <unordered_map>

namespace Palworld::SignatureData {
    inline const std::unordered_map<std::string, std::string> Signatures {
        // Blueprint Loader apply logic
        { "UBlueprintGeneratedClass::PostLoadDefaultObject", "41 57 41 56 53 48 81 EC 90 01 00 00 49 89 F6 48 89 FB 49 89 E7 4C 89 FF 48 89 D6 E8 ?? ?? ?? ?? 4C 89 FF E8 ?? ?? ?? ?? 48 8B 0B 48 89 DF 4C 89 F6 48 89 C2 FF 91 B0 03 00 00" },
        // Raw Table apply logic
        { "FPakPlatformFile::GetPakFolders", "41 56 53 48 83 EC 28 49 89 F6 48 8D 7C 24 18 E8 ?? ?? ?? ?? 83 7C 24 20 00 BA ?? ?? ?? ?? 74 05 48 8B 54 24 18 48 8D 7C 24 08 BE ?? ?? ?? ?? 31 C0 E8 ?? ?? ?? ?? 49 63 5E 08 8D 43 01 41 89 46 08 41 3B 46 0C" },
        // Important so we can easily run things on the Game Thread
        { "AsyncTask", "48 8B C4 41 54 41 57 48 81 EC B8 00 00 00 48 89 58 08" },
        // Used to initialize any other loader logic like pals, items, etc
        { "AGameModeBase::InitGameState", "40 53 48 83 EC 20 48 8B 41 10 48 8B D9 48 8B 91 F0 02 00 00" },
        { "UClass::AssembleReferenceTokenStream", "48 8B C4 55 56 48 8D 68 A1 48 81 EC A8 00 00 00 48 89 58 10 48 8D B1 F8 01 00 00" },
        { "UClass::CreateDefaultObject", "41 57 41 56 41 54 53 48 81 EC 58 10 00 00 49 89 FC 48 83 BF 10 01 00 00 00 0F 85 ?? ?? ?? ?? 49 8B 5C 24 40 48 85 DB 74 ?? 48 89 DF BE 01 00 00 00 E8 ?? ?? ?? ?? 4C 8B B3 10 01 00 00 4D 85 F6 75 ?? 48 8B 03 48 89 DF FF 90 F8 03 00 00" },
        { "UStruct::StaticLink", "48 89 5C 24 08 57 48 81 EC C0 00 00 00 48 8B F9 0F B6 DA 48 8D 4C 24 20" },
        // UE4SS has StaticFindObject, but this lets us use it earlier.
		{ "UObjectGlobals::StaticFindObject", "55 41 57 41 56 41 55 41 54 53 48 83 EC 28 41 89 CF 48 89 F3 49 89 FE 31 C0 48 83 FE FF 48 0F 45 C6 48 89 44 24 20 48 8D 6C 24 08 48 89 EF 48 89 D6 74 ?? E8 ?? ?? ?? ?? 48 8D 7C 24 20 48 89 EE 31 D2 31 C9 45 31 C0 45 31 C9 E8 ?? ?? ?? ?? 84 C0" },
        // I had issues using the IsA provided by UE4SS due to early init, so I switched to using Unreal's own.
        { "FField::IsA", "48 8B 41 08 48 8B 4A 08 48 85 C9 74 08 48 85 48 10 0F 95 C0 C3" },
        // Important, we need this early.
        { "FName::Constructor", "48 89 5C 24 08 57 48 83 EC 30 48 8B D9 48 89 54 24 20" },
        // Points towards the MOV instruction in UPalItemContainer::ApplySaveData after the CALL to UPalItemSlot::UpdateItem_ServerInternal
        { "UPalItemContainer::ApplySaveData", "48 8B CB E8 ?? ?? ?? ?? 48 8B CB E8 ?? ?? ?? ?? 48 89 5C 24 48" },
        // Points towards the MOV instruction in UPalDynamicItemWorldSubsystem::ApplyWorldSaveData after the CALL to UPalDynamicItemWorldSubsystem::Create_ServerInternal
        { "UPalDynamicItemWorldSubsystem::ApplyWorldSaveData", "48 8B D8 48 8B 4C 24 50 48 85 C9 74 06 E8 ?? ?? ?? ?? 90 48 85 DB" },
        { "ValidateWorldSaveDynamicItemStaticIds", "48 89 5C 24 10 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 60 FF FF FF 48 81 EC A0 01 00 00 48 8B ?? ?? ?? ?? ?? 48 33 C4 48 89 85 90 00 00 00 4D 8B E9" },
        { "ValidateDynamicItemSaveData", "40 55 53 56 57 41 54 41 56 41 57 48 8D AC 24 80 FE FF FF 48 81 EC 80 02 00 00 48 8B ?? ?? ?? ?? ?? 48 33 C4 48 89 85 70 01 00 00" },
        { "CraftItemCount_ApplyDataMapReturn", "48 8B CE E8 ?? ?? ?? ?? 48 8B C8 48 89 44 24 60 4C 89 64 24 68" },
    };

    inline const std::unordered_map<std::string, std::string> SignaturesCallResolve {
        { "FFieldClass::GetNameToFieldClassMap", "E8 ?? ?? ?? ?? 49 89 C4 4C 8D 7C 24 08 BE ?? ?? ?? ?? 4C 89 FF BA 01 00 00 00 E8 ?? ?? ?? ?? 48 8B 7C 24 08 48 89 FB 48 C1 EB 20 E8 ?? ?? ?? ?? 01 D8 41 8B 4C 24 08 41 3B 4C 24 34" },
        // Important, we need this early.
        { "FName::ToString_Wchar", "E8 ?? ?? ?? ?? 4C 89 FF 31 F6 E8 ?? ?? ?? ?? 85 D2 74 ?? 48 89 C3 48 63 C2 48 8D 0C C0 4C 8D 2C 49 49 01 C5 4C 8D 64 24 08" },
        // More efficient object lookup for certain cases.
        { "GetObjectsOfClass", "E8 ?? ?? ?? ?? BE 30 00 00 00 31 FF 31 D2 E8 ?? ?? ?? ?? 48 89 C3 48 89 44 24 08 C7 44 24 10 03 00 00 00 48 C7 00 ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 89 43 10 48 C7 03 ?? ?? ?? ?? 4C 89 63 18 48 C7 43 20 ?? ?? ?? ?? 48 C7 43 28 00 00 00 00 49 8B 3C 24 48 8D 74 24 08 E8 ?? ?? ?? ?? 49 89 44 24 48" },
        // FMemory::Free for GMalloc
        { "FMemory::Free", "E8 ?? ?? ?? ?? 48 89 E3 48 89 DF E8 ?? ?? ?? ?? 4C 8D 7C 24 10" },
        // Raw Tables
        { "UDataTable::Serialize", "E8 ?? ?? ?? ?? 4C 89 F7 E8 ?? ?? ?? ?? 48 81 C4 98 01 00 00 5B 41 5E C3 41 57 41 56 53 48 83 EC 10 49 89 F6 48 89 FB 48 8B 06 4C 8B 78 08 E8 ?? ?? ?? ?? 48 8B 7B 28 48 85 FF 74 ?? F6 47 09 04 74 ?? E8 ?? ?? ?? ?? 48 85 C0 74 ?? 48 8B 73 28 48 89 C7 E8 ?? ?? ?? ?? 41 8B 47 28 A8 01 75 ?? A8 04 74 ?? 48 89 DF" },
        { "UPalDynamicItemWorldSubsystem::Create_ServerInternal", "E8 ?? ?? ?? ?? 48 8B D8 48 8B 4C 24 50 48 85 C9 74 06 E8 ?? ?? ?? ?? 90 48 85 DB" },
        { "UPalItemSlot::UpdateItem_ServerInternal", "E8 ?? ?? ?? ?? 48 8B CB E8 ?? ?? ?? ?? 48 8B CB E8 ?? ?? ?? ?? 48 89 5C 24 48" },
        { "UWorld::CleanupWorld", "E8 ?? ?? ?? ?? 8B 55 A7 FF C2 49 83 C5 08 89 55 A7" },
        { "FPalPlayerRecordDataRepInfoArrayThreadSafe_IntVal::ApplyDataMap", "E8 ?? ?? ?? ?? 41 80 BF E9 0C 00 00 00" },
    };
}
