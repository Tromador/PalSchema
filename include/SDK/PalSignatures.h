#pragma once

#include <filesystem>
#include <unordered_map>
#include <string>

namespace Palworld {
    class SignatureManager {
    public:
        static void Initialize();
        
        // Expected parameter format: [CLASS]::[FUNCTION] or [FUNCTION], for example AGameModeBase::InitGameState or AsyncTask
        static void* GetSignature(const std::string& ClassAndFunction);
    private:
        static inline std::unordered_map<std::string, void*> SignatureMap;
    };
}