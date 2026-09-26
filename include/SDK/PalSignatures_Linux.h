#pragma once

#include <string>
#include <unordered_map>

namespace Palworld::SignatureData {
    inline const std::unordered_map<std::string, std::string> Signatures {
        // Blueprint loader default-object post-load target.
        { "UBlueprintGeneratedClass::PostLoadDefaultObject", "41 57 41 56 53 48 81 EC 90 01 00 00 49 89 F6 48 89 FB 49 89 E7 4C 89 FF 48 89 D6 E8 ?? ?? ?? ?? 4C 89 FF E8 ?? ?? ?? ?? 48 8B 0B 48 89 DF 4C 89 F6 48 89 C2 FF 91 B0 03 00 00" },

        // Alternative pak-path hook used to add PalSchema's extra .pak read directory.
        { "FPakPlatformFile::GetPakFolders", "41 56 53 48 83 EC 28 49 89 F6 48 8D 7C 24 18 E8 ?? ?? ?? ?? 83 7C 24 20 00 BA ?? ?? ?? ?? 74 05 48 8B 54 24 18 48 8D 7C 24 08 BE ?? ?? ?? ?? 31 C0 E8 ?? ?? ?? ?? 49 63 5E 08 8D 43 01 41 89 46 08 41 3B 46 0C" },

        // Schedules work onto the game thread.
        { "AsyncTask", "48 8B C4 41 54 41 57 48 81 EC B8 00 00 00 48 89 58 08" },

        // Used to initialise later loader logic once GameMode/GameState is ready.
        { "AGameModeBase::InitGameState", "40 53 48 83 EC 20 48 8B 41 10 48 8B D9 48 8B 91 F0 02 00 00" },

        { "UClass::AssembleReferenceTokenStream", "48 8B C4 55 56 48 8D 68 A1 48 81 EC A8 00 00 00 48 89 58 10 48 8D B1 F8 01 00 00" },

        // Linux callable target used when UClassWrapper::GetDefaultObject(bool) must create a missing CDO.
        { "UClass::CreateDefaultObject", "41 57 41 56 41 54 53 48 81 EC 58 10 00 00 49 89 FC 48 83 BF 10 01 00 00 00 0F 85 ?? ?? ?? ?? 49 8B 5C 24 40 48 85 DB 74 ?? 48 89 DF BE 01 00 00 00 E8 ?? ?? ?? ?? 4C 8B B3 10 01 00 00 4D 85 F6 75 ?? 48 8B 03 48 89 DF FF 90 F8 03 00 00" },

		//// Linux UStruct::StaticLink(bool) wrapper; dispatches to UStruct::Link via vtable.
        { "UStruct::StaticLink", "55 41 56 53 48 81 EC A0 00 00 00 89 F5 48 89 FB 4C 8D 74 24 08 4C 89 F7 E8 ?? ?? ?? ?? 48 C7 44 24 08 ?? ?? ?? ?? 48 8B 03 48 89 DF 4C 89 F6 89 EA FF 90 D0 02 00 00 4C 89 F7 E8 ?? ?? ?? ?? 48 81 C4 A0 00 00 00 5B 41 5E 5D C3" },

        // Used during early initialisation before normal UE4SS object lookup is available.
        { "UObjectGlobals::StaticFindObject", "55 41 57 41 56 41 55 41 54 53 48 83 EC 28 41 89 CF 48 89 F3 49 89 FE 31 C0 48 83 FE FF 48 0F 45 C6 48 89 44 24 20 48 8D 6C 24 08 48 89 EF 48 89 D6 74 ?? E8 ?? ?? ?? ?? 48 8D 7C 24 20 48 89 EE 31 D2 31 C9 45 31 C0 45 31 C9 E8 ?? ?? ?? ?? 84 C0" },

        // Uses Unreal's own FField::IsA because the UE4SS helper is not available early enough.
        { "FField::IsA", "48 8B 41 08 48 8B 4A 08 48 85 C9 74 08 48 85 48 10 0F 95 C0 C3" },

        // Needed during early initialisation before normal UE4SS availability.
        { "FName::Constructor", "48 89 5C 24 08 57 48 83 EC 30 48 8B D9 48 89 54 24 20" },

        { "UPalItemContainer::ApplySaveData", "48 89 DF E8 3D 12 00 00 48 81 C4 C0 00 00 00 5B 41 5C 41 5D 41 5E 41 5F C3" },

        // Return site in ApplyWorldSaveData immediately after the call to Create_ServerInternal.
        { "UPalDynamicItemWorldSubsystem::ApplyWorldSaveData", "49 89 C5 48 8B 7C 24 28 48 85 FF 74 ?? E8 ?? ?? ?? ?? 4D 85 ED 74 ?? 41 F6 45 0B 60 74 ??" },

        { "ValidateWorldSaveDynamicItemStaticIds", "55 41 57 41 56 41 55 41 54 53 48 81 EC 58 01 00 00 41 B7 01 48 85 F6 74 ?? 49 89 CC 49 89 D6 48 89 F5 48 89 FB E8 ?? ?? ?? ?? 48 85 C0 74 ?? 49 89 C5 F6 40 0B 60 74 ?? 44 89 F8 48 81 C4 58 01 00 00 5B 41 5C 41 5D 41 5E 41 5F 5D C3 48 63 85 08 03 00 00" },

		// Item-loader inline-hook target for validating dynamic-item save data.
        { "ValidateDynamicItemSaveData", "55 41 57 41 56 41 55 41 54 53 48 81 EC F8 01 00 00 49 89 CE 48 89 D3 49 89 F5 48 89 FE 66 0F EF C0 66 0F 7F 84 24 00 01 00 00 66 0F 7F 84 24 F0 00 00 00 48 C7 44 24 18 00 00 00 00 48 8D AC 24 48 01 00 00 48 89 EF E8 ?? ?? ?? ?? 48 8D B4 24 F0 00 00 00 48 89 EF E8 ?? ?? ?? ?? 48 8B 84 24 48 01 00 00 48 8D 74 24 18 48 89 EF FF 90 18 01 00 00 48 89 EF E8 ?? ?? ?? ?? 4D 85 ED 74 ?? 41 F6 45 0B 60 0F 84 ?? ?? ?? ??" },

        // Exact return site after the craft-count ApplyDataMap call; compared directly with _ReturnAddress().
        { "CraftItemCount_ApplyDataMapReturn", "4C 89 EF E8 ?? ?? ?? ?? 8B 83 D0 08 00 00 41 87 85 48 31 00 00 8B 83 D4 08 00 00 41 87 85 4C 31 00 00 8B 83 D8 08 00 00 41 87 85 50 31 00 00 49 8D BD 58 31 00 00 48 8D B3 E0 08 00 00 E8 ?? ?? ?? ??" },
    };

    inline const std::unordered_map<std::string, std::string> SignaturesCallResolve {
        // StaticClassStorage bootstrap: returns the global FName -> FFieldClass map.
        { "FFieldClass::GetNameToFieldClassMap", "E8 ?? ?? ?? ?? 49 89 C4 4C 8D 7C 24 08 BE ?? ?? ?? ?? 4C 89 FF BA 01 00 00 00 E8 ?? ?? ?? ?? 48 8B 7C 24 08 48 89 FB 48 C1 EB 20 E8 ?? ?? ?? ?? 01 D8 41 8B 4C 24 08 41 3B 4C 24 34" },

        // StaticClassStorage bootstrap: converts FFieldClass FNames to their string names.
        { "FName::ToString_Wchar", "E8 ?? ?? ?? ?? 4C 89 FF 31 F6 E8 ?? ?? ?? ?? 85 D2 74 ?? 48 89 C3 48 63 C2 48 8D 0C C0 4C 8D 2C 49 49 01 C5 4C 8D 64 24 08" },

        // Enum loader: enumerates UEnum objects after StaticFindObject obtains the UEnum class.
        { "GetObjectsOfClass", "E8 ?? ?? ?? ?? BE 30 00 00 00 31 FF 31 D2 E8 ?? ?? ?? ?? 48 89 C3 48 89 44 24 08 C7 44 24 10 03 00 00 00 48 C7 00 ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 89 43 10 48 C7 03 ?? ?? ?? ?? 4C 89 63 18 48 C7 43 20 ?? ?? ?? ?? 48 C7 43 28 00 00 00 00 49 8B 3C 24 48 8D 74 24 08 E8 ?? ?? ?? ?? 49 89 44 24 48" },

        // GMalloc bootstrap: PalSchema resolves FMemory::Free, then inspects its body for the GMalloc global.
        { "FMemory::Free", "E8 ?? ?? ?? ?? 48 89 E3 48 89 DF E8 ?? ?? ?? ?? 4C 8D 7C 24 10" },

        // Core-init trigger: the UDataTable::Serialize detour invokes PalSchema's InitCore callback.
        { "UDataTable::Serialize", "E8 ?? ?? ?? ?? 4C 89 F7 E8 ?? ?? ?? ?? 48 81 C4 98 01 00 00 5B 41 5E C3 41 57 41 56 53 48 83 EC 10 49 89 F6 48 89 FB 48 8B 06 4C 8B 78 08 E8 ?? ?? ?? ?? 48 8B 7B 28 48 85 FF 74 ?? F6 47 09 04 74 ?? E8 ?? ?? ?? ?? 48 85 C0 74 ?? 48 8B 73 28 48 89 C7 E8 ?? ?? ?? ?? 41 8B 47 28 A8 01 75 ?? A8 04 74 ?? 48 89 DF" },

        { "UPalDynamicItemWorldSubsystem::Create_ServerInternal", "E8 ?? ?? ?? ?? 49 89 C5 48 8B 7C 24 28 48 85 FF 74 ?? E8 ?? ?? ?? ?? 4D 85 ED 74 ?? 41 F6 45 0B 60 74 ??" },

        // Item-loader inline-hook target for server-side item-slot updates.
        { "UPalItemSlot::UpdateItem_ServerInternal", "E8 ?? ?? ?? ?? 66 0F EF D2 48 8B 44 24 10 4C 63 7C 24 18 4D 85 FF 74 ?? F3 0F 6F 03 4C 89 F9 48 C1 E1 04" },

        { "UWorld::CleanupWorld", "E8 ?? ?? ?? ?? 8B 55 A7 FF C2 49 83 C5 08 89 55 A7" },

        // Item-loader inline-hook target for applying the thread-safe player-record IntVal map.
        { "FPalPlayerRecordDataRepInfoArrayThreadSafe_IntVal::ApplyDataMap", "E8 ?? ?? ?? ?? 4C 89 EF E8 ?? ?? ?? ?? 8B 83 D0 08 00 00 41 87 85 48 31 00 00 8B 83 D4 08 00 00 41 87 85 4C 31 00 00" },
    };
}
