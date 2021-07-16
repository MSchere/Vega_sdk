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

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DCPU_RV32M1_ri5cy")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DSHELL_MAX_CMD=24")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DA_LITTLE_ENDIAN")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DFSL_RTOS_FREE_RTOS")

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

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DNDEBUG")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DCPU_RV32M1_ri5cy")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DSHELL_MAX_CMD=24")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DA_LITTLE_ENDIAN")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DFSL_RTOS_FREE_RTOS")

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

include_directories(${ProjDirPath}/../../../../..)

include_directories(${ProjDirPath}/..)

include_directories(${ProjDirPath}/../custom)

include_directories(${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/portable/GCC/RISCY)

include_directories(${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/include)

include_directories(${ProjDirPath}/../../../../../../../RISCV)

include_directories(${ProjDirPath}/../../../../../../../devices)

include_directories(${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source)

include_directories(${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/port/boards/rv32m1_vega/freertos/gt202)

include_directories(${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/port/boards/rv32m1_vega/freertos/silex2401)

include_directories(${ProjDirPath}/../../../../../../../devices/RV32M1/drivers)

include_directories(${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/port/drivers/lpspi_edma_freertos)

include_directories(${ProjDirPath}/../../../../../../../devices/RV32M1/utilities)

include_directories(${ProjDirPath}/../../../../../../../devices/RV32M1/utilities/io)

include_directories(${ProjDirPath}/../../../../../../../devices/RV32M1/utilities/str)

include_directories(${ProjDirPath}/../../../../../../../devices/RV32M1/utilities/log)

include_directories(${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/port/env/freertos)

include_directories(${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/port)

include_directories(${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/port/boards/rv32m1_vega/freertos)

include_directories(${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/custom_src/include)

include_directories(${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include)

include_directories(${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/include)

include_directories(${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0)

include_directories(${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/custom_src/stack_custom)

include_directories(${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include/AR6002)

include_directories(${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include/AR6002/hw2.0/hw)

include_directories(${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include/AR6002/hw4.0/hw)

include_directories(${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/stack_common)

include_directories(${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/hcd)

include_directories(${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/wmi)

include_directories(${ProjDirPath}/../../../../../../../devices/RV32M1)

add_executable(qca_throughput.elf 
"${ProjDirPath}/../../../../../../../devices/RV32M1/gcc/startup_RV32M1_ri5cy.S"
"${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/portable/GCC/RISCY/port.c"
"${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/portable/GCC/RISCY/portASM.S"
"${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/portable/GCC/RISCY/fsl_tickless_generic.h"
"${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/portable/GCC/RISCY/portmacro.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/port/boards/rv32m1_vega/freertos/gt202/wifi_shield_gt202.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/port/boards/rv32m1_vega/freertos/silex2401/wifi_shield_silex2401.h"
"${ProjDirPath}/../../../../../../../devices/RV32M1/drivers/fsl_lpspi.c"
"${ProjDirPath}/../../../../../../../devices/RV32M1/drivers/fsl_lpspi.h"
"${ProjDirPath}/../../../../../../../devices/RV32M1/drivers/fsl_edma.h"
"${ProjDirPath}/../../../../../../../devices/RV32M1/drivers/fsl_edma.c"
"${ProjDirPath}/../../../../../../../devices/RV32M1/drivers/fsl_intmux.h"
"${ProjDirPath}/../../../../../../../devices/RV32M1/drivers/fsl_intmux.c"
"${ProjDirPath}/../../../../../../../devices/RV32M1/drivers/fsl_dmamux.h"
"${ProjDirPath}/../../../../../../../devices/RV32M1/drivers/fsl_dmamux.c"
"${ProjDirPath}/../../../../../../../devices/RV32M1/drivers/fsl_lpspi_edma.h"
"${ProjDirPath}/../../../../../../../devices/RV32M1/drivers/fsl_lpspi_edma.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/port/drivers/lpspi_edma_freertos/wifi_spi.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/port/drivers/lpspi_edma_freertos/wifi_spi.h"
"${ProjDirPath}/../../../../../../../devices/RV32M1/drivers/fsl_lpuart.h"
"${ProjDirPath}/../../../../../../../devices/RV32M1/drivers/fsl_lpuart.c"
"${ProjDirPath}/../../../../../../../devices/RV32M1/drivers/fsl_gpio.h"
"${ProjDirPath}/../../../../../../../devices/RV32M1/drivers/fsl_gpio.c"
"${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/portable/MemMang/heap_4.c"
"${ProjDirPath}/../../../../../../../devices/RV32M1/drivers/fsl_port.h"
"${ProjDirPath}/../../../../../../../devices/RV32M1/drivers/fsl_common.h"
"${ProjDirPath}/../../../../../../../devices/RV32M1/drivers/fsl_common.c"
"${ProjDirPath}/../../../../../../../devices/RV32M1/utilities/fsl_debug_console.c"
"${ProjDirPath}/../../../../../../../devices/RV32M1/utilities/fsl_debug_console.h"
"${ProjDirPath}/../../../../../../../devices/RV32M1/utilities/fsl_debug_console_conf.h"
"${ProjDirPath}/../../../../../../../devices/RV32M1/utilities/fsl_io.c"
"${ProjDirPath}/../../../../../../../devices/RV32M1/utilities/fsl_io.h"
"${ProjDirPath}/../../../../../../../devices/RV32M1/utilities/fsl_log.c"
"${ProjDirPath}/../../../../../../../devices/RV32M1/utilities/fsl_log.h"
"${ProjDirPath}/../../../../../../../devices/RV32M1/utilities/fsl_str.c"
"${ProjDirPath}/../../../../../../../devices/RV32M1/utilities/fsl_str.h"
"${ProjDirPath}/../../../../../../../devices/RV32M1/system_RV32M1_ri5cy.c"
"${ProjDirPath}/../../../../../../../devices/RV32M1/system_RV32M1_ri5cy.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/port/env/freertos/wifi_port.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/port/env/freertos/wifi_env_port.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/port/env/freertos/wifi_env.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/port/env/freertos/wifi_env.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/port/wifi_common.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/port/boards/rv32m1_vega/freertos/wifi_shield.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/port/boards/rv32m1_vega/freertos/wifi_shield.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/atheros_stack_offload.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/atheros_wifi.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/atheros_wifi_api.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/atheros_wifi_internal.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/api_interface/api_init.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/api_interface/api_ioctl.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/api_interface/api_txrx.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/api_interface/api_wmi_rx.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/bmi/bmi.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/driver/driver_diag.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/driver/driver_init.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/driver/driver_main.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/driver/driver_netbuf.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/driver/driver_txrx.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/hcd/hcd_api.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/hcd/spi_hcd.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/htc/htc.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/hw_interface/hw_api.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/include/a_debug.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/include/a_drv.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/include/a_drv_api.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/include/aggr_recv_api.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/include/bmi.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/include/common_api.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/include/dbglog_api.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/include/driver_cxt.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/include/dset.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/include/dset_api.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/include/hif_internal.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/include/htc_api.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/include/ieee80211.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/include/netbuf.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/include/spi_hcd_if.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/include/wlan_api.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/include/wmi_api.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/qapi/qcom_api.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/qapi/qcom_legacy.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/reorder/rcv_aggr.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/stack_common/api_stack_offload.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/stack_common/common_stack_offload.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/storerecall/dset.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/storerecall/dset_api.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/storerecall/storerecall.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/util/util.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/wmi/wmi.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/common_src/wmi/wmi_host.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/custom_src/api_interface/cust_api_init.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/custom_src/api_interface/cust_api_ioctl.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/custom_src/api_interface/cust_api_txrx.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/custom_src/api_interface/cust_api_wmi_rx.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/custom_src/driver/cust_driver_main.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/custom_src/driver/cust_driver_netbuf.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/custom_src/hw_interface/cust_spi_hcd.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/custom_src/include/a_config.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/custom_src/include/a_osapi.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/custom_src/include/a_types.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/custom_src/include/cust_netbuf.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/custom_src/include/custom_wlan_api.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/custom_src/include/wlan_config.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/custom_src/qapi/custom_qcom_api.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/custom_src/stack_custom/cust_api_stack_offload.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/custom_src/stack_custom/cust_api_stack_txrx.c"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/custom_src/stack_custom/custom_stack_offload.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/custom_src/stack_custom/qca_structs.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include/AR6002/AR6K_version.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include/AR6002/hw2.0/hw/hw20_apb_map.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include/AR6002/hw2.0/hw/hw20_gpio_reg.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include/AR6002/hw2.0/hw/hw20_mbox_host_reg.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include/AR6002/hw2.0/hw/hw20_mbox_reg.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include/AR6002/hw2.0/hw/hw20_rtc_reg.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include/AR6002/hw2.0/hw/hw20_si_reg.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include/AR6002/hw2.0/hw/hw20_uart_reg.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include/AR6002/hw2.0/hw/hw20_vmc_reg.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include/AR6002/hw4.0/hw/hw40_rtc_reg.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include/AR6002/hw4.0/hw/hw40_rtc_wlan_reg.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include/athdefs.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include/bmi_msg.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include/dbglog.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include/dbglog_id.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include/htc.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include/htc_services.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include/p2p.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include/pkt_log.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include/pmu.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include/targaddrs.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include/wlan_defs.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/include/wmi.h"
"${ProjDirPath}/../../../../../../../middleware/wifi_qca_2.0.0/qcom_api.h"
"${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/include/croutine.h"
"${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/include/event_groups.h"
"${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/include/FreeRTOS.h"
"${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/include/list.h"
"${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/include/mpu_wrappers.h"
"${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/include/portable.h"
"${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/include/projdefs.h"
"${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/include/queue.h"
"${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/include/semphr.h"
"${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/include/StackMacros.h"
"${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/include/task.h"
"${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/include/timers.h"
"${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/include/deprecated_definitions.h"
"${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/include/freertos_tasks_c_additions.h"
"${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/croutine.c"
"${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/list.c"
"${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/queue.c"
"${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/tasks.c"
"${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/timers.c"
"${ProjDirPath}/../../../../../../../rtos/freertos_9.0.0/Source/event_groups.c"
"${ProjDirPath}/../../../../../../../devices/RV32M1/utilities/fsl_shell.c"
"${ProjDirPath}/../../../../../../../devices/RV32M1/utilities/fsl_shell.h"
"${ProjDirPath}/../board.c"
"${ProjDirPath}/../board.h"
"${ProjDirPath}/../clock_config.c"
"${ProjDirPath}/../clock_config.h"
"${ProjDirPath}/../../../../../../../devices/RV32M1/drivers/fsl_msmc.h"
"${ProjDirPath}/../../../../../../../devices/RV32M1/drivers/fsl_msmc.c"
"${ProjDirPath}/../../../../../../../devices/RV32M1/drivers/fsl_clock.h"
"${ProjDirPath}/../../../../../../../devices/RV32M1/drivers/fsl_clock.c"
"${ProjDirPath}/../main.c"
"${ProjDirPath}/../FreeRTOSConfig.h"
"${ProjDirPath}/../common/wmiconfig_qapi.c"
"${ProjDirPath}/../custom/calist-kingfisher-inc.h"
"${ProjDirPath}/../custom/cert-kingfisher-inc.h"
"${ProjDirPath}/../custom/Command_Lists.c"
"${ProjDirPath}/../custom/https.c"
"${ProjDirPath}/../custom/https.h"
"${ProjDirPath}/../custom/main.h"
"${ProjDirPath}/../custom/shell_config.h"
"${ProjDirPath}/../custom/task_manager.c"
"${ProjDirPath}/../custom/throughput.h"
"${ProjDirPath}/../custom/throughput_qapi.c"
"${ProjDirPath}/../custom/usb_classes.h"
"${ProjDirPath}/../custom/utils.c"
"${ProjDirPath}/../custom/wmiconfig_custom_qapi.c"
"${ProjDirPath}/../custom/worker_shell.h"
"${ProjDirPath}/../driver_plugin/atheros_wifi_mediactl_ext.c"
"${ProjDirPath}/../pin_mux.c"
"${ProjDirPath}/../pin_mux.h"
"${ProjDirPath}/../wlan_qca400x.c"
"${ProjDirPath}/../wlan_qcom.h"
)


set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -T${ProjDirPath}/RV32M1_ri5cy_flash.ld -static")

set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -T${ProjDirPath}/RV32M1_ri5cy_flash.ld -static")

TARGET_LINK_LIBRARIES(qca_throughput.elf -Wl,--start-group)
target_link_libraries(qca_throughput.elf debug m)

target_link_libraries(qca_throughput.elf debug c)

target_link_libraries(qca_throughput.elf debug gcc)

target_link_libraries(qca_throughput.elf debug nosys)

target_link_libraries(qca_throughput.elf optimized m)

target_link_libraries(qca_throughput.elf optimized c)

target_link_libraries(qca_throughput.elf optimized gcc)

target_link_libraries(qca_throughput.elf optimized nosys)

TARGET_LINK_LIBRARIES(qca_throughput.elf -Wl,--end-group)

