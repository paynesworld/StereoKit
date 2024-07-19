#include "VarjoSupport.h"
#include "Utils.h"
#include "Varjo-SDK/include/Varjo.h"
#include <stdint.h>
#include <filesystem>
#include <winreg.h>

///////////////////////////////////////////

namespace sk {

    uint32_t _sessionPriority;

    // Hook the Varjo SDK (used by the OpenXR runtime) to keep the session as an overlay.
    void (*original_varjo_WaitSync)(struct varjo_Session* session, struct varjo_FrameInfo* frameInfo) = nullptr;
    void hooked_varjo_WaitSync(struct varjo_Session* session, struct varjo_FrameInfo* frameInfo) {
        
        varjo_SessionSetPriority(session, _sessionPriority);

        return original_varjo_WaitSync(session, frameInfo);
    }
    
    bool detectVarjoEnvironment() {
        return false;
    }

    bool varjoSupportInit(uint32_t sessionPriority) {

        bool isVarjo = detectVarjoEnvironment();
        if (isVarjo)
        {
            _sessionPriority = sessionPriority;

            // Hook the Varjo runtime to force overlay mode.
            const std::filesystem::path varjoLib =
                std::filesystem::path(Utils::RegGetString(HKEY_LOCAL_MACHINE, "SOFTWARE\\Varjo\\Runtime", "InstallDir")
                    .value_or(L"C:\\Program Files\\Varjo")) /
                L"varjo-openxr" / L"VarjoLib.dll";
            Utils::DetourDllAttach(varjoLib.c_str(), "varjo_WaitSync", hooked_varjo_WaitSync, original_varjo_WaitSync);
        }

        return isVarjo;
	}

} // namespace sk
