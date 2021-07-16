INCLUDE(CMakeForceCompiler)

# CROSS COMPILER SETTING
SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

# THE VERSION NUMBER
SET (Tutorial_VERSION_MAJOR 1)
SET (Tutorial_VERSION_MINOR 0)

# ENABLE ASM
ENABLE_LANGUAGE(ASM)

SET(CMAKE_STATIC_LIBRARY_PREFIX)
SET(CMAKE_STATIC_LIBRARY_SUFFIX)

SET(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
SET(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)

 
# CURRENT DIRECTORY
SET(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})


SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -DDEBUG")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -D__STARTUP_CLEAR_BSS")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -g")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -march=rv32imcxpulpv2")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -Wall")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -fno-common")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -ffunction-sections")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -fdata-sections")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -ffreestanding")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -fno-builtin")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -std=gnu99")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -D__STARTUP_CLEAR_BSS")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -march=rv32imcxpulpv2")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -Wall")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -fno-common")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -ffunction-sections")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -fdata-sections")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -ffreestanding")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -fno-builtin")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -std=gnu99")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -include ${ProjDirPath}/../../../../../../../../boards/rv32m1_vega/wireless_examples/bluetooth/cycling_scs/freertos/ri5cy/app_preinclude.h")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DCPU_RV32M1_ri5cy")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DFSL_RTOS_FREE_RTOS")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DMULTICORE_APP=1")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -march=rv32imcxpulpv2")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -MMD")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -MP")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-common")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ffunction-sections")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fdata-sections")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ffreestanding")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-builtin")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -std=gnu99")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fshort-enums")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-inline-functions")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -include ${ProjDirPath}/../../../../../../../../boards/rv32m1_vega/wireless_examples/bluetooth/cycling_scs/freertos/ri5cy/app_preinclude.h")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DNDEBUG")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DCPU_RV32M1_ri5cy")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DFSL_RTOS_FREE_RTOS")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DMULTICORE_APP=1")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fno-store-merging")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -march=rv32imcxpulpv2")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -MMD")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -MP")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fno-common")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -ffunction-sections")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fdata-sections")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -ffreestanding")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fno-builtin")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -std=gnu99")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fshort-enums")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fno-inline-functions")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -include ${ProjDirPath}/../../../../../../../../boards/rv32m1_vega/wireless_examples/bluetooth/cycling_scs/freertos/ri5cy/app_preinclude.h")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -march=rv32imcxpulpv2")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -MMD")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -MP")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-common")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ffunction-sections")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fdata-sections")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ffreestanding")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-builtin")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-rtti")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-exceptions")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fshort-enums")

SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-inline-functions")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -include ${ProjDirPath}/../../../../../../../../boards/rv32m1_vega/wireless_examples/bluetooth/cycling_scs/freertos/ri5cy/app_preinclude.h")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-store-merging")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=rv32imcxpulpv2")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -MMD")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -MP")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-common")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -ffunction-sections")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fdata-sections")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -ffreestanding")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-builtin")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-rtti")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-exceptions")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fshort-enums")

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-inline-functions")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -g")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -march=rv32imcxpulpv2")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Wall")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fno-common")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -ffunction-sections")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fdata-sections")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -ffreestanding")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fno-builtin")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --gc-sections")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -static")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -z")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} muldefs")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -nostdlib")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -nostartfiles")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -march=rv32imcxpulpv2")

SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Wa,-march=rv32imcxpulpv2")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -march=rv32imcxpulpv2")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Wall")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -fno-common")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -ffunction-sections")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -fdata-sections")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -ffreestanding")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -fno-builtin")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} --gc-sections")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -static")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -z")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Xlinker")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} muldefs")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -nostdlib")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -nostartfiles")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -march=rv32imcxpulpv2")

SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -Wa,-march=rv32imcxpulpv2")

include_directories(${ProjDirPath}/..)

include_directories(${ProjDirPath}/../../..)

include_directories(${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/portable/GCC/RISCY)

include_directories(${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/include)

include_directories(${ProjDirPath}/../../../../../../../../RISCV)

include_directories(${ProjDirPath}/../../../../../../../../devices)

include_directories(${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source)

include_directories(${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include)

include_directories(${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/port/ksdk)

include_directories(${ProjDirPath}/../../../../../..)

include_directories(${ProjDirPath}/../../../../../../../../devices/RV32M1/drivers)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/RNG/Interface)

include_directories(${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Common/mbedtls)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/SecLib)

include_directories(${ProjDirPath}/../../../../../../../../middleware/multicore_2.3.1/rpmsg_lite/lib/include)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/hci_transport/interface)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/OSAbstraction/Interface)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Flash/Internal)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/GPIO)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Keyboard/Interface)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/LED/Interface)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Common)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/MemManager/Interface)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Messaging/Interface)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Panic/Interface)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/NVM/Interface)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/NVM/Source)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/SerialManager/Interface)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/SerialManager/Source)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Shell/Interface)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/TimersManager/Interface)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/TimersManager/Source)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/ModuleInfo)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/FunctionLib)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Lists)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/interface)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/config)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/controller/interface)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common/gatt_db)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common/gatt_db/macros)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/profiles/battery)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/profiles/device_info)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/profiles/cycling_speed_cadence)

include_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/MWSCoexistence/Interface)

include_directories(${ProjDirPath}/../../../../../../../../middleware/multicore_2.3.1/rpmsg_lite/lib/include/platform/rv32m1)

include_directories(${ProjDirPath}/../../../../../../../../devices/RV32M1/utilities)

include_directories(${ProjDirPath}/../../../../../../../../devices/RV32M1/utilities/io)

include_directories(${ProjDirPath}/../../../../../../../../devices/RV32M1/utilities/str)

include_directories(${ProjDirPath}/../../../../../../../../devices/RV32M1/utilities/log)

include_directories(${ProjDirPath}/../../../../../../../../middleware/multicore_2.3.1/mcmgr/src)

include_directories(${ProjDirPath}/../../../../../../../../platform/drivers/mu)

include_directories(${ProjDirPath}/../../../../../../../../devices/RV32M1)

add_executable(ble_cycling_speed_cadence_sensor_freertos.elf 
"${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/portable/GCC/RISCY/port.c"
"${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/portable/GCC/RISCY/portASM.S"
"${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/portable/GCC/RISCY/fsl_tickless_generic.h"
"${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/portable/GCC/RISCY/portmacro.h"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/gcc/startup_RV32M1_ri5cy.S"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/drivers/fsl_lpuart.h"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/drivers/fsl_lpuart.c"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/drivers/fsl_intmux.h"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/drivers/fsl_intmux.c"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/drivers/fsl_trng.c"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/drivers/fsl_trng.h"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/drivers/fsl_port.h"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/drivers/fsl_flash.c"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/drivers/fsl_flash.h"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/drivers/fsl_common.h"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/drivers/fsl_common.c"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/drivers/fsl_tpm.c"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/drivers/fsl_tpm.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/RNG/Interface/RNG_Interface.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/RNG/Source/RNG_mbedTLS.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/aes.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/aesni.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/arc4.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/asn1.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/asn1write.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/base64.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/bignum.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/blowfish.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/bn_mul.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/camellia.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/ccm.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/certs.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/check_config.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/cipher.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/cipher_internal.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/cmac.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/compat-1.3.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/config.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/ctr_drbg.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/debug.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/des.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/dhm.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/ecdh.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/ecdsa.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/ecjpake.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/ecp.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/entropy.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/entropy_poll.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/error.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/gcm.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/havege.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/hmac_drbg.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/md.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/md_internal.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/md2.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/md4.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/md5.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/memory_buffer_alloc.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/net.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/net_sockets.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/oid.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/padlock.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/pem.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/pk.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/pk_internal.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/pkcs5.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/pkcs11.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/pkcs12.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/platform.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/platform_time.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/ripemd160.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/rsa.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/sha1.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/sha256.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/sha512.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/ssl.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/ssl_cache.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/ssl_ciphersuites.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/ssl_cookie.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/ssl_internal.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/ssl_ticket.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/threading.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/timing.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/version.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/x509.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/x509_crl.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/x509_crt.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/x509_csr.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/include/mbedtls/xtea.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/aes.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/aesni.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/arc4.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/asn1parse.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/asn1write.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/base64.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/bignum.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/blowfish.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/camellia.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/ccm.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/certs.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/cipher.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/cipher_wrap.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/cmac.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/ctr_drbg.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/debug.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/des.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/dhm.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/ecdh.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/ecdsa.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/ecjpake.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/ecp.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/ecp_curves.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/entropy.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/entropy_poll.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/error.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/gcm.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/havege.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/hmac_drbg.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/md.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/md_wrap.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/md2.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/md4.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/md5.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/memory_buffer_alloc.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/net_sockets.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/oid.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/padlock.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/pem.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/pk.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/pk_wrap.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/pkcs5.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/pkcs11.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/pkcs12.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/pkparse.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/pkwrite.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/platform.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/ripemd160.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/rsa.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/sha1.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/sha256.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/sha512.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/ssl_cache.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/ssl_ciphersuites.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/ssl_cli.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/ssl_cookie.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/ssl_srv.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/ssl_ticket.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/ssl_tls.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/threading.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/timing.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/version.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/version_features.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/x509.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/x509_create.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/x509_crl.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/x509_crt.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/x509_csr.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/x509write_crt.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/x509write_csr.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/library/xtea.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Common/mbedtls/connectivity_mbedtls_config.h"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/drivers/fsl_cau3.c"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/drivers/fsl_cau3.h"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/drivers/fsl_sema42.h"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/drivers/fsl_sema42.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/SecLib/SecLib.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/SecLib/SecLib_mbedTLS.c"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/drivers/fsl_mu.h"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/drivers/fsl_mu.c"
"${ProjDirPath}/../../../../../../../../middleware/multicore_2.3.1/rpmsg_lite/lib/rpmsg_lite/porting/environment/rpmsg_env_freertos.c"
"${ProjDirPath}/../../../../../../../../middleware/multicore_2.3.1/rpmsg_lite/lib/include/rpmsg_env.h"
"${ProjDirPath}/../../../../../../../../middleware/multicore_2.3.1/rpmsg_lite/lib/include/rpmsg_queue.h"
"${ProjDirPath}/../../../../../../../../middleware/multicore_2.3.1/rpmsg_lite/lib/rpmsg_lite/rpmsg_queue.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/hci_transport/interface/hci_transport.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/hci_transport/source/hcit_rpmsg_lite_interface.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/OSAbstraction/Interface/fsl_os_abstraction.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/OSAbstraction/Interface/fsl_os_abstraction_config.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/OSAbstraction/Interface/fsl_os_abstraction_free_rtos.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/OSAbstraction/Source/fsl_os_abstraction_free_rtos.c"
"${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/portable/MemMang/heap_4.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Flash/Internal/Flash_Adapter.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Flash/Internal/Flash_Adapter.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/GPIO/GPIO_Adapter.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/GPIO/GPIO_Adapter.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Keyboard/Interface/Keyboard.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Keyboard/Source/Keyboard.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/LED/Interface/LED.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/LED/Source/LED.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Reset/Reset.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Common/EmbeddedTypes.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/MemManager/Interface/MemManager.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/MemManager/Source/MemManager.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Messaging/Interface/Messaging.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Messaging/Source/Messaging.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/OSAbstraction/Interface/fsl_os_abstraction.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/OSAbstraction/Interface/fsl_os_abstraction_config.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Panic/Interface/Panic.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Panic/Source/Panic.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/NVM/Interface/NVM_Interface.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/NVM/Source/NV_Flash.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/NVM/Source/NV_Flash.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/NVM/Source/NV_FsciCommands.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/NVM/Source/NV_FsciCommands.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/SerialManager/Interface/SerialManager.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/SerialManager/Source/SerialManager.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/SerialManager/Source/UART_Adapter.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/SerialManager/Source/UART_Adapter.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Shell/Interface/shell.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Shell/Interface/shell_config.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Shell/Source/shell.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Shell/Source/shell_autocomplete.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Shell/Source/shell_cmdhelp.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Shell/Source/shell_cmdhist.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/TimersManager/Interface/TimersManager.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/TimersManager/Source/TimersManager.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/TimersManager/Source/TimersManagerInternal.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/TimersManager/Source/TMR_Adapter.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/TimersManager/Source/TMR_Adapter.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/ModuleInfo/ModuleInfo.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/ModuleInfo/ModuleInfo.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/FunctionLib/FunctionLib.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/FunctionLib/FunctionLib.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Lists/GenericList.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/Lists/GenericList.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/interface/att_callbacks.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/interface/att_errors.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/interface/att_interface.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/interface/att_params.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/interface/att_types.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/interface/ble_constants.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/interface/ble_general.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/interface/ble_host_tasks.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/interface/ble_sig_defines.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/interface/ble_utils.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/interface/gap_interface.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/interface/gap_types.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/interface/gatt_client_interface.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/interface/gatt_database.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/interface/gatt_db_app_interface.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/interface/gatt_db_dynamic.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/interface/gatt_interface.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/interface/gatt_server_interface.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/interface/gatt_types.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/interface/hci_interface.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/interface/hci_types.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/interface/l2ca_cb_interface.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/interface/l2ca_interface.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/interface/l2ca_types.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/interface/vendor_debug_commands.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common/ble_host_tasks.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common/ble_host_task_config.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common/ble_conn_manager.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common/ble_conn_manager.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/config/ble_config.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/config/ble_globals.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common/ble_controller_task.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common/ble_controller_task_config.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/controller/interface/controller_interface.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common/ApplMain.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common/ApplMain.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common/ble_init.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common/ble_init.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common/gatt_db/macros/gatt_alloc_x.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common/gatt_db/macros/gatt_db_macros.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common/gatt_db/macros/gatt_db_x_macros.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common/gatt_db/macros/gatt_decl_x.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common/gatt_db/macros/gatt_enum_x.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common/gatt_db/macros/gatt_init_x.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common/gatt_db/macros/gatt_size_x.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common/gatt_db/macros/gatt_uuid_decl_x.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common/gatt_db/macros/gatt_uuid_def_x.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common/gatt_db/gatt_database.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common/gatt_db/gatt_db_handles.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common/ieee11073.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common/ble_service_discovery.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/application/common/ble_service_discovery.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/profiles/battery/battery_service.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/profiles/battery/battery_interface.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/profiles/device_info/device_info_service.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/profiles/device_info/device_info_interface.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/profiles/cycling_speed_cadence/cycling_speed_cadence_service.c"
"${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/profiles/cycling_speed_cadence/cycling_speed_cadence_interface.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/MWSCoexistence/Interface/MWS.h"
"${ProjDirPath}/../../../../../../../../middleware/wireless/framework_5.5.1/MWSCoexistence/Source/MWS.c"
"${ProjDirPath}/../app_preinclude.h"
"${ProjDirPath}/../cycling_speed_cadence_sensor.c"
"${ProjDirPath}/../cycling_speed_cadence_sensor.h"
"${ProjDirPath}/../../app_config.c"
"${ProjDirPath}/../gatt_db.h"
"${ProjDirPath}/../gatt_uuid128.h"
"${ProjDirPath}/../FreeRTOSConfig.h"
"${ProjDirPath}/../../../../../../../../middleware/multicore_2.3.1/rpmsg_lite/lib/include/rpmsg_lite.h"
"${ProjDirPath}/../../../../../../../../middleware/multicore_2.3.1/rpmsg_lite/lib/include/rpmsg_ns.h"
"${ProjDirPath}/../../../../../../../../middleware/multicore_2.3.1/rpmsg_lite/lib/include/llist.h"
"${ProjDirPath}/../../../../../../../../middleware/multicore_2.3.1/rpmsg_lite/lib/include/rpmsg_default_config.h"
"${ProjDirPath}/../../../../../../../../middleware/multicore_2.3.1/rpmsg_lite/lib/include/virtio_ring.h"
"${ProjDirPath}/../../../../../../../../middleware/multicore_2.3.1/rpmsg_lite/lib/include/virtqueue.h"
"${ProjDirPath}/../../../../../../../../middleware/multicore_2.3.1/rpmsg_lite/lib/include/rpmsg_compiler.h"
"${ProjDirPath}/../../../../../../../../middleware/multicore_2.3.1/rpmsg_lite/lib/common/llist.c"
"${ProjDirPath}/../../../../../../../../middleware/multicore_2.3.1/rpmsg_lite/lib/rpmsg_lite/rpmsg_lite.c"
"${ProjDirPath}/../../../../../../../../middleware/multicore_2.3.1/rpmsg_lite/lib/rpmsg_lite/rpmsg_ns.c"
"${ProjDirPath}/../../../../../../../../middleware/multicore_2.3.1/rpmsg_lite/lib/virtio/virtqueue.c"
"${ProjDirPath}/../../../../../../../../middleware/multicore_2.3.1/rpmsg_lite/lib/include/platform/rv32m1/rpmsg_platform.h"
"${ProjDirPath}/../../../../../../../../middleware/multicore_2.3.1/rpmsg_lite/lib/rpmsg_lite/porting/platform/rv32m1/rpmsg_platform.c"
"${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/include/croutine.h"
"${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/include/event_groups.h"
"${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/include/FreeRTOS.h"
"${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/include/list.h"
"${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/include/mpu_wrappers.h"
"${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/include/portable.h"
"${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/include/projdefs.h"
"${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/include/queue.h"
"${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/include/semphr.h"
"${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/include/StackMacros.h"
"${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/include/task.h"
"${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/include/timers.h"
"${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/include/deprecated_definitions.h"
"${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/include/freertos_tasks_c_additions.h"
"${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/croutine.c"
"${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/list.c"
"${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/queue.c"
"${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/tasks.c"
"${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/timers.c"
"${ProjDirPath}/../../../../../../../../rtos/freertos_9.0.0/Source/event_groups.c"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/system_RV32M1_ri5cy.c"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/system_RV32M1_ri5cy.h"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/utilities/fsl_debug_console.c"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/utilities/fsl_debug_console.h"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/utilities/fsl_debug_console_conf.h"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/utilities/fsl_io.c"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/utilities/fsl_io.h"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/utilities/fsl_log.c"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/utilities/fsl_log.h"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/utilities/fsl_str.c"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/utilities/fsl_str.h"
"${ProjDirPath}/../../../../../../../../middleware/multicore_2.3.1/mcmgr/src/mcmgr.h"
"${ProjDirPath}/../../../../../../../../middleware/multicore_2.3.1/mcmgr/src/mcmgr_internal_core_api.h"
"${ProjDirPath}/../../../../../../../../middleware/multicore_2.3.1/mcmgr/src/mcmgr.c"
"${ProjDirPath}/../../../../../../../../middleware/multicore_2.3.1/mcmgr/src/mcmgr_mu_internal.c"
"${ProjDirPath}/../../../../../../../../middleware/multicore_2.3.1/mcmgr/src/mcmgr_internal_core_api_rv32m1.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/port/ksdk/ksdk_mbedtls.c"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/port/ksdk/ksdk_mbedtls.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/port/ksdk/sha1_alt.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/port/ksdk/sha256_alt.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/port/ksdk/des_alt.h"
"${ProjDirPath}/../../../../../../../../middleware/mbedtls_2.4.2/port/ksdk/des_alt.c"
"${ProjDirPath}/../board.c"
"${ProjDirPath}/../board.h"
"${ProjDirPath}/../clock_config.c"
"${ProjDirPath}/../clock_config.h"
"${ProjDirPath}/../rpmsg_config.h"
"${ProjDirPath}/../hardware_init.c"
"${ProjDirPath}/../pin_mux.c"
"${ProjDirPath}/../pin_mux.h"
"${ProjDirPath}/../gpio_pins.c"
"${ProjDirPath}/../gpio_pins.h"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/drivers/fsl_gpio.h"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/drivers/fsl_gpio.c"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/drivers/fsl_msmc.h"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/drivers/fsl_msmc.c"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/drivers/fsl_clock.h"
"${ProjDirPath}/../../../../../../../../devices/RV32M1/drivers/fsl_clock.c"
)


set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -T${ProjDirPath}/RV32M1_ri5cy_flash.ld -static")

set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -T${ProjDirPath}/RV32M1_ri5cy_flash.ld -static")

TARGET_LINK_LIBRARIES(ble_cycling_speed_cadence_sensor_freertos.elf -Wl,--start-group)
target_link_libraries(ble_cycling_speed_cadence_sensor_freertos.elf debug m)

target_link_libraries(ble_cycling_speed_cadence_sensor_freertos.elf debug c)

target_link_libraries(ble_cycling_speed_cadence_sensor_freertos.elf debug gcc)

target_link_libraries(ble_cycling_speed_cadence_sensor_freertos.elf debug nosys)

target_link_libraries(ble_cycling_speed_cadence_sensor_freertos.elf optimized m)

target_link_libraries(ble_cycling_speed_cadence_sensor_freertos.elf optimized c)

target_link_libraries(ble_cycling_speed_cadence_sensor_freertos.elf optimized gcc)

target_link_libraries(ble_cycling_speed_cadence_sensor_freertos.elf optimized nosys)

link_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/lib)

target_link_libraries(ble_cycling_speed_cadence_sensor_freertos.elf debug ${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/lib/lib_ble_5-0_host_ri5cy.a)

link_directories(${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/lib)

target_link_libraries(ble_cycling_speed_cadence_sensor_freertos.elf optimized ${ProjDirPath}/../../../../../../../../middleware/wireless/bluetooth_1.4.0/host/lib/lib_ble_5-0_host_ri5cy.a)

TARGET_LINK_LIBRARIES(ble_cycling_speed_cadence_sensor_freertos.elf -Wl,--end-group)

