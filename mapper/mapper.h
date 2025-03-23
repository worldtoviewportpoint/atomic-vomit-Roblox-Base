#pragma once
#include "kdm/include/kdmapper.h"
#include "kdm/driver_bytes.hpp"

auto load_driver ( ) -> void {
    HANDLE iqvw64e_device_handle = intel_driver::Load();

    if (!iqvw64e_device_handle || iqvw64e_device_handle == INVALID_HANDLE_VALUE) {
        return;
    }

    if (!kdmapper::MapDriver(iqvw64e_device_handle, driver_bytes)) {
        intel_driver::Unload(iqvw64e_device_handle);
        return;
    }

    intel_driver::Unload(iqvw64e_device_handle);


}