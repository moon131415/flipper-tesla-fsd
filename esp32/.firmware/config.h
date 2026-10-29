#pragma once

// ── CAN IDs ───────────────────────────────────────────────────────────────────
#define CAN_ID_STW_ACTN_RQ    0x045u  // 69   - STW_ACTN_RQ:  steering stalk (Legacy follow distance)
#define CAN_ID_TRIP_PLANNING  0x082u  // 130  - UI_tripPlanning: precondition trigger
#define CAN_ID_ESP_STATUS     0x145u  // 325  - ESP_status: driver brake pedal state
#define CAN_ID_ESP_WHEELSPD   0x175u  // 373  - ESP_wheelSpeeds: 4 wheel speeds (Party CAN, read-only)
#define CAN_ID_VCSEC_TPMS     0x219u  // 537  - VCSEC_TPMSData: tyre pressures (Vehicle CAN, read-only)
#define CAN_ID_STEER_ANGLE    0x129u  // 297  - SCCM_steeringAngleSensor (Soft Engage gate, #108)
#define CAN_ID_BMS_HV_BUS     0x132u  // 306  - BMS_hvBusStatus: pack voltage / current
#define CAN_ID_BMS_SOC        0x292u  // 658  - BMS_socStatus:   state of charge
#define CAN_ID_UI_RANGE       0x33Au  // 826  - UI_range: SOC on the car's screen (#251)
#define CAN_ID_BMS_THERMAL    0x312u  // 786  - BMS_thermalStatus: battery temp
#define CAN_ID_GTW_CAR_STATE  0x318u  // 792  - GTW_carState:    OTA detection
#define CAN_ID_UI_MAP_DATA    0x238u  // 568  - UI_driverAssistMapData: map speed limit
// CAN_ID_DI_SPEED (0x257) — vehicle speed for the Autopark release gate (#180) —
// comes from the shared fsd_logic/fsd_handler.h (via fsd_events.h), so it is not
// redefined here (avoids adding to the config.h/shared CAN_ID_* redefinition set).
#define CAN_ID_SCCM_RSTALK    0x229u  // 553  - GearLever / right stalk
#define CAN_ID_DAS_CONTROL    0x2B9u  // 697  - DAS_control: cruise set speed / ACC state
#define CAN_ID_DAS_STATUS2    0x389u  // 905  - DAS_status2: ACC speed limit
#define CAN_ID_EPAS_STATUS    0x370u  // 880  - EPAS3P_sysStatus: nag killer target
#define CAN_ID_GTW_CAR_CONFIG 0x398u  // 920  - GTW_carConfig:   HW version detection
#define CAN_ID_VCFRONT_LIGHT  0x3F5u  // 1013 - VCFRONT_lighting: turn signal request state
#define CAN_ID_AP_LEGACY      0x3EEu  // 1006 - DAS_autopilot:   Legacy / HW1 / HW2
#define CAN_ID_FOLLOW_DIST    0x3F8u  // 1016 - DAS_followDistance: speed profile source
#define CAN_ID_DAS_AP_CONFIG  0x331u  // 817  - DAS autopilot config (tier restore target, ~1 Hz)
#define CAN_ID_AP_CONTROL     0x3FDu  // 1021 - DAS_autopilotControl: HW3 / HW4 core
#define CAN_ID_DAS_STATUS_HW3 0x399u  // 921  - DAS_status on Legacy/HW3 AP/DAS
#define CAN_ID_ISA_SPEED      0x399u  // 921  - ISA speed limit on HW4 only
#define CAN_ID_DAS_STATUS_HW4 0x39Bu  // 923  - DAS_status on HW4 AP/DAS
#define CAN_ID_TRACK_MODE_SET 0x313u  // 787  - UI_trackModeSettings: track mode request (checksummed)
#define CAN_ID_UI_POWERTRAIN  0x334u  // 820  - UI_powertrainControl: pedal map (Acceleration Mode override, #211)
#define CAN_ID_CP_STATUS      0x25Du  // 605  - CP_status: charge-port type / plug state (Vehicle CAN, #228)
// Same replacement list as fsd_logic/fsd_handler.h, so main.cpp seeing both is not a redefinition.
#define CAN_ID_DI_SYS_STATUS  0x118  // 280  - DI_systemStatus: DI_gear (Acceleration Mode standstill gate)
#define CAN_ID_VCLEFT_SWITCH  0x3C2  // 962  - VCLEFT_switchStatus: tap check bus hint (#218), RX only
// Vehicle/body bus reachability probes (#128) — RX presence only, never actuated.
#define CAN_ID_UI_VEHICLE_CTRL 0x273u // 627  - UI_vehicleControl: mirror fold/lock/wiper/horn/seat heat
#define CAN_ID_VCLEFT_DOOR     0x102u // 258  - VCLEFT_doorStatus: mirror state/tilt read-back
#define CAN_ID_VCSEC_WINDOW    0x119u // 281  - VCSEC_windowRequests: windows
#define CAN_ID_DAS_BODY        0x3E9u // 1001 - DAS_bodyControls: lights/hazards/turn/wipers

// ── Board combination ───────────────────────────────────────────────────────
// A Waveshare ESP32-S3-RS485-CAN with a separate MCP2515 module wired to the
// pin header: the board's own (isolated) transceiver on the native TWAI
// controller is can0, the MCP2515 is can1 — the same two-bus layout as a
// LilyGO T-2CAN. Both flags come from platformio.ini.
#if defined(BOARD_WAVESHARE_S3) && defined(CAN_DRIVER_T2CAN_DUAL)
#define BOARD_WAVESHARE_S3_DUALCAN 1
#endif

// Boards that run the CAN-idle deep-sleep watchdog (sleep_tick() in main.cpp).
// Needs a CAN RX pin that is an RTC GPIO (so it can wake the chip) and a TX
// pin whose level can be latched while the digital domain is off.
//   BOARD_LILYGO  (T-CAN485):  classic ESP32, SN65HVD230 RXD on GPIO 26.
//   WAVESHARE_S3_DUALCAN:      ESP32-S3, TWAI RX on GPIO 16 (GPIO 0-21 are the
//                              RTC GPIOs on the S3), plus the MCP2515 INT pin
//                              as a second wake source.
#if defined(BOARD_LILYGO) || defined(BOARD_WAVESHARE_S3_DUALCAN)
#define CAN_DEEP_SLEEP_ENABLED 1
#endif

// ── Build identity ────────────────────────────────────────────────────────────
// Board name for the boot banner and the dashboard — same wording as the board
// table in esp32/README.md. One entry per BOARD_* flag in platformio.ini.
#if defined(BOARD_LILYGO_T2CAN_FD)
  #define BOARD_NAME "LilyGO T-2CAN FD"
#elif defined(BOARD_LILYGO_T2CAN)
  #define BOARD_NAME "LilyGO T-2CAN"
#elif defined(BOARD_LILYGO)
  #define BOARD_NAME "LilyGO T-CAN485"
#elif defined(BOARD_TTGO_DISPLAY)
  #define BOARD_NAME "TTGO T-Display + MCP2515"
#elif defined(BOARD_WAVESHARE_S3_DUALCAN)
  #define BOARD_NAME "Waveshare ESP32-S3-RS485-CAN + MCP2515 (dual CAN)"
#elif defined(BOARD_WAVESHARE_S3)
  #define BOARD_NAME "Waveshare ESP32-S3-RS485-CAN"
#elif defined(BOARD_M5STACK_ATOM_MATRIX)
  #define BOARD_NAME "M5Stack ATOM Matrix + ATOMIC CAN Base"
#elif defined(BOARD_M5STACK_ATOM)
  #define BOARD_NAME "M5Stack ATOM Lite + ATOMIC CAN Base"
#elif defined(BOARD_ESP32_GENERIC) && defined(CAN_DRIVER_MCP2515)
  #define BOARD_NAME "Generic ESP32 + MCP2515 module"
#elif defined(BOARD_ESP32_GENERIC)
  #define BOARD_NAME "Classic ESP32 DevKit + SN65HVD230"
#else
  #define BOARD_NAME "ESP32"
#endif

// Release version. gen_version.py (PlatformIO pre-script) passes the release
// tag or `git describe`; the fallback keeps host tests and other builds that
// bypass PlatformIO compiling.
#ifndef FW_VERSION
#define FW_VERSION "dev"
#endif

// ── GPIO ──────────────────────────────────────────────────────────────────────
#if defined(BOARD_LILYGO_T2CAN)
  #define PIN_CAN_TX         7
  #define PIN_CAN_RX         6
  #define PIN_LED            -1
  #define PIN_BUTTON         0    // BOOT button, active-LOW, internal pull-up
  #define PIN_MCP_CS         10
  #define PIN_MCP_SCK        12
  #define PIN_MCP_MOSI       11
  #define PIN_MCP_MISO       13
  #define PIN_MCP_INT        8
  #if defined(BOARD_LILYGO_T2CAN_FD)
    // T-2CAN FD (H784-A): an MCP2518FD on the same SPI pins. It has no reset
    // pin; GPIO 9 goes to its INT0/GPIO0/XSTBY pin and GPIO 3 (through the DIP
    // switch) to INT1/GPIO1. The driver polls over SPI and drives neither.
    // Crystal: 40 MHz on LilyGO's T-2Can-Fd_V1.0 schematic. The driver
    // measures it before the controller may leave Listen-Only.
    #ifndef MCP2518FD_OSC_HZ
    #define MCP2518FD_OSC_HZ   40000000u
    #endif
  #else
    #define PIN_MCP_RST        9
    #ifndef MCP_CRYSTAL_MHZ
    #define MCP_CRYSTAL_MHZ    MCP_16MHZ
    #endif
  #endif
  #define PRECONDITION_TX_BUS_INDEX 0
#elif defined(BOARD_LILYGO)
  #define PIN_CAN_TX         27
  #define PIN_CAN_RX         26
  #define PIN_CAN_SPEED_MODE 23   // SN65HVD230 Rs — must be LOW for TX+RX
  #define PIN_LED            4    // SK6812 NeoPixel
  #define PIN_BUTTON         0    // Boot button, active-LOW, internal pull-up
  #define SD_MISO            2
  #define SD_MOSI            15
  #define SD_SCLK            14
  #define SD_CS              13
#elif defined(BOARD_TTGO_DISPLAY)
  #define PIN_LED            -1   // Blue LED is hardwired to charging IC (TP4054)
  #define PIN_LCD_BL         4    // ST7789 backlight
  #define PIN_LCD_POWER      22   // ST7789 power enable
  #define PIN_BUTTON         0    // Right button
  #define PIN_BUTTON2        35   // Left button (Display Sleep/Wake)
  // Remap MCP2515 to unused pins to avoid SPI conflict with Display
  #define PIN_MCP_MISO       32   // Use a 5v -> 3.3v voltage divider to prevent damage
  #define PIN_MCP_SCK        33
  #define PIN_MCP_MOSI       25
  #define PIN_MCP_CS         26
#elif defined(BOARD_WAVESHARE_S3_DUALCAN)
  // Waveshare ESP32-S3-RS485-CAN + a separate MCP2515 module = dual CAN, the
  // same bus layout as a LilyGO T-2CAN (can0 = native TWAI, can1 = MCP2515).
  // Every pin below can be overridden with a build flag.
  //
  // IMPORTANT — the two pairs are NOT interchangeable:
  //   * PIN_CAN_TX/RX is the board's own isolated CAN transceiver, hardwired to
  //     GPIO 15/16 by Waveshare. Nothing else may use those two pins.
  //   * The MCP2515 is wired by hand to the pin header, where IO3-IO14 are
  //     free. IO19/IO20 are the ESP32-S3's native USB D-/D+ pair and IO43/IO44
  //     the UART0 console — never route the MCP2515 there.
  //   * GPIO 35-37 are the in-package octal PSRAM (ESP32-S3R8) and GPIO 26-32
  //     the in-package flash: not available on any S3-WROOM module.
  #ifndef PIN_CAN_TX
  #define PIN_CAN_TX         15   // TWAI TX -> Waveshare CAN transceiver TXD
  #endif
  #ifndef PIN_CAN_RX
  #define PIN_CAN_RX         16   // TWAI RX <- Waveshare CAN transceiver RXD (RTC GPIO: deep-sleep wake)
  #endif
  #ifndef PIN_LED
  #define PIN_LED            46
  #endif
  #ifndef PIN_MCP_CS
  #define PIN_MCP_CS         10
  #endif
  #ifndef PIN_MCP_SCK
  #define PIN_MCP_SCK        12
  #endif
  #ifndef PIN_MCP_MOSI
  #define PIN_MCP_MOSI       11
  #endif
  #ifndef PIN_MCP_MISO
  #define PIN_MCP_MISO       13
  #endif
  // INT doubles as the deep-sleep wake source for can1, so it is wired (the
  // T-Display build leaves it unconnected and polls instead). RST lets the
  // driver hard-reset the chip after a deep-sleep wake, when the MCP2515 has
  // kept its configuration across the ESP32's reset.
  #ifndef PIN_MCP_INT
  #define PIN_MCP_INT        9
  #endif
  #ifndef PIN_MCP_RST
  #define PIN_MCP_RST        8
  #endif
  // Commodity MCP2515 breakout modules ship an 8 MHz crystal; the LilyGO
  // T-2CAN's onboard chip is the 16 MHz exception. Spelled out here so the
  // value never depends on which branch of the fallthrough below is taken.
  #ifndef MCP_CRYSTAL_MHZ
  #define MCP_CRYSTAL_MHZ    MCP_8MHZ
  #endif
  #define PRECONDITION_TX_BUS_INDEX 0
#else
  #ifndef PIN_CAN_TX
  #define PIN_CAN_TX   22   // TWAI TX → ATOMIC CAN Base TX
  #endif
  #ifndef PIN_CAN_RX
  #define PIN_CAN_RX   19   // TWAI RX ← ATOMIC CAN Base RX
  #endif
  #ifndef PIN_LED
  #define PIN_LED      27   // SK6812 NeoPixel (single LED)
  #endif
#endif
#ifndef PIN_BUTTON
#define PIN_BUTTON    0   // Built-in button (GPIO0), active-LOW, internal pull-up
#endif

// MCP2515 SPI — only used in CAN_DRIVER_MCP2515 build (generic ESP32)
// Standard VSPI pins: SCK=18, MISO=19, MOSI=23, CS=5
#ifndef PIN_MCP_CS
#define PIN_MCP_CS   5
#endif
#ifndef PIN_MCP_SCK
#define PIN_MCP_SCK  18
#endif
#ifndef PIN_MCP_MISO
#define PIN_MCP_MISO 19
#endif
#ifndef PIN_MCP_MOSI
#define PIN_MCP_MOSI 23
#endif
#ifndef PIN_MCP_RST
#define PIN_MCP_RST  -1
#endif
#ifndef PIN_MCP_INT
#define PIN_MCP_INT  -1
#endif
#ifndef PRECONDITION_TX_BUS_INDEX
#define PRECONDITION_TX_BUS_INDEX 0
#endif

// ── Generated TX routing ─────────────────────────────────────────────────────
// Bus index: 0=can0, 1=can1. Single-CAN builds only have can0.
// The Continuous AP 0x229 press only goes out on a bus where the car's own
// 0x229 is live (gear_tx_route.h); this picks the bus when both carry it.
#ifndef GEAR_LEVER_TX_BUS_INDEX
#if defined(BOARD_LILYGO_T2CAN) || defined(BOARD_WAVESHARE_S3_DUALCAN)
// Both dual-CAN builds wire the MCP2515 (can1) to the pair carrying the car's
// 0x229 in the documented setups, so the generated gear press starts there.
#define GEAR_LEVER_TX_BUS_INDEX 1
#else
#define GEAR_LEVER_TX_BUS_INDEX 0
#endif
#endif

// Builds with an MCP2515: can0 on the MCP2515 boards, can1 on the classic
// T-2CAN (the T-2CAN FD has an MCP2518FD there instead).
#if defined(CAN_DRIVER_MCP2515) || (defined(CAN_DRIVER_T2CAN_DUAL) && !defined(BOARD_LILYGO_T2CAN_FD))
#define CAN_HAS_MCP2515 1
#endif

// MCP2515 oscillator. Generic breakout modules often use 8 MHz; the LilyGO
// T-2CAN onboard MCP2515 follows the autowp library's 16 MHz default.
#ifndef MCP_CRYSTAL_MHZ
#define MCP_CRYSTAL_MHZ  MCP_8MHZ   // from autowp-mcp2515 CAN_CLOCK enum
#endif

// ── Timing ────────────────────────────────────────────────────────────────────
#define WIRING_WARN_MS        5000u   // Red LED / serial warning if no CAN after this
#define WIRING_WARN_REPEAT_MS 60000u  // ...then that bus's warning at most once a minute
#define OTA_SELF_VERIFY_MS   15000u   // Runtime before a new web-OTA image is confirmed
#define PRECOND_INTERVAL_MS    500u   // Re-inject 0x082 precondition every N ms
#define BMS_PRINT_MS          1000u   // BMS serial print interval
#define BUTTON_DEBOUNCE_MS        50u
#define LONG_PRESS_MS           3000u   // Long press → toggle NAG killer
#define DOUBLE_CLICK_MS          400u   // Max gap between two clicks for double-click
#define FACTORY_RESET_HOLD_MS   5000u   // Hold duration to arm factory reset
#define FACTORY_RESET_WINDOW_MS 20000u  // Clean-boot window during which reset is possible
#define STATUS_PRINT_MS       5000u   // Periodic status line when Active
#define WIFI_STA_CONNECT_TIMEOUT_MS 10000u  // Try saved infrastructure WiFi before AP fallback
#define WIFI_HOSTNAME_DEFAULT "tesla-fsd"  // Station hostname until the user sets one
#ifndef GEAR_LEVER_CACHED_COUNTER_MAX_AGE_MS
#define GEAR_LEVER_CACHED_COUNTER_MAX_AGE_MS 500u  // Immediate 0x229 TX only if latest live counter is fresh
#endif
#ifndef GEAR_SEQUENCE_STEP_MS
#define GEAR_SEQUENCE_STEP_MS 40u  // Gap between generated 0x229 press/release sequence frames
#endif
#ifndef GEAR_SEQUENCE_TIMEOUT_MS
#define GEAR_SEQUENCE_TIMEOUT_MS 1500u  // Give up if a generated 0x229 sequence cannot start/finish
#endif
#define CONT_AP_READY_WAIT_TIMEOUT_MS    6000u
#define CONT_AP_REENGAGE_DELAY_MS        1000u
#define CONT_AP_ATTEMPT_RESULT_MS         700u
#define CONT_AP_RETRY_DELAY_MS            300u
#ifndef CONT_AP_STEERING_TORQUE_ABORT_NM
#define CONT_AP_STEERING_TORQUE_ABORT_NM 2.5f
#endif
#define CONT_AP_STEERING_TORQUE_TIMEOUT_MS 5000u
#define CONT_AP_BRAKE_RECENT_MS          750u
#define CONT_AP_STALK_STOP_RECENT_MS     750u
#define CONT_AP_MAX_RETRIES                 3u

// Summon EU Unlock safety: auto-disable on clear vehicle motion (0x257, #193).
// Palladium S/X don't broadcast 0x229 on Party, so the gear-lever guard can't
// fire there. Above this speed the car is clearly driving (well past Summon's
// own crawl and the autopark creep window), so disarm the Summon override.
#define SUMMON_DISABLE_SPEED_KPH          3.0f

// OTA detection on GTW_carState (0x318): debounce thresholds are shared with the
// Flipper in fsd_logic/fsd_ota.h.

#if defined(BOARD_LILYGO)
  #define ME2107_EN 16
#endif

// ── Deep sleep (CAN_DEEP_SLEEP_ENABLED boards) ──────────────────────────────
// Two wake sources, both RTC GPIOs:
//
//   ext0 — the TWAI RX pin (BOARD_LILYGO: GPIO 26; Waveshare dual: GPIO 16).
//          The transceiver's RXD goes LOW when the bus goes dominant, so a
//          frame on can0 wakes the chip.
//   ext1 — the MCP2515 INT pin (Waveshare dual only, GPIO 9), active LOW, so a
//          frame on can1 wakes it too. The chip keeps its own power through the
//          sleep and is left in Listen-Only mode (it must stay on the bus to
//          see traffic; shutdown()'s CONFIG mode would leave the bus unwatched
//          and the device unable to wake from can1).
//
// The TX pad is latched recessive with gpio_hold_en() before sleeping: pads
// lose their driven level once the digital domain powers down, and a TX left
// floating could read as dominant and block the car's bus.
#define SLEEP_IDLE_MS   120000u   // CAN silence before entering deep sleep
#define SLEEP_WARN_MS    5000u   // serial/log warning this many ms before sleep
