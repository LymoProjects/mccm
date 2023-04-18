#pragma once

#include <co/fastring.h>

class osInfoType {
    fastring name;
    fastring arch;
    fastring version;

public:
    static
    auto ref() -> osInfoType & {
        static
        osInfoType info__;

        return info__;
    }

    auto isWindows() -> bool {

    }

    auto isOsx() const -> bool {

    }

    auto isLinux() const -> bool {

    }

    auto getName() const -> fastring {

    }

    auto getArch() const -> fastring {

    }

    auto getVersion() const -> fastring {

    }

    auto satisfy(fastring const & key, fastring const & value) -> bool {

    }
};