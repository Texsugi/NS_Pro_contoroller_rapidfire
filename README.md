# RENCON User Manual (Board ver2.1 / Firmware v8)

[日本語版はこちら / Japanese version](README.jp.md)

This is the user manual for **RENCON**, a rapid-fire mod board for the official Nintendo Switch Pro Controller (board ver2.1 / firmware v8).
The contents are based on the actual firmware v8 implementation.

Buy it here (BOOTH): https://xgames.booth.pm/items/6925334

---

## Files in this repository

| File | Contents |
|---|---|
| Rapidfire2.1_fw_v8.uf2 | **Current firmware (for board ver2.1)**. Use this one in normal cases |
| RENCON_Config_GUI.zip | PC configuration GUI (see "6. PC Configuration GUI") |
| GUI_MANUAL.md | Manual for the PC configuration GUI |
| Factory_Reset.uf2 | Factory-reset firmware. Flashing it restores all settings to their initial state (see "13. Troubleshooting") |
| Rapidfire_fw_v2.uf2 | Firmware for the old version (old board / previous generation) |
| MicroPython_fw.uf2 | Firmware for the old version (old board / previous generation) |

Note: For the current board ver2.1, use Rapidfire2.1_fw_v8.uf2. Do not use the old-version files on the current board.

---

## 1. Overview

RENCON is a multi-function input-control board that is installed inside an official Nintendo Switch Pro Controller.

- **All 16 buttons can be configured individually**, each with its own operating mode (Normal / Rapid Fire / Double-Click Rapid Fire / Toggle)
- Rapid-fire speed is set by two values — how long the button is held down (ON time) and how long it is released (OFF time) — each adjustable **in 5 ms steps**
- **Macro engine built in**: up to 4 presets, with up to 20 actions per preset
- Settings are saved in the board's flash memory and **are kept even when the power is off**
- Visual feedback from an RGB LED (rainbow animation in normal use)
- After 60 seconds without input, the board enters **deep sleep** to minimise standby power consumption
- It can also be configured from a browser-based GUI by connecting it to a PC with a USB cable

The microcontroller is an RP2354 (Raspberry Pi Pico family), and the firmware is developed with the Pico SDK (C/C++).

---

## 2. Configurable buttons

The following **16 buttons** can be configured.

| Group | Buttons |
|---|---|
| Main buttons | A / B / X / Y |
| Shoulder buttons | L / R / ZL / ZR |
| D-pad | Up / Down / Left / Right |
| System | HOME / Capture (SS) / + / - |

---

## 3. Operating modes

Each button can be set to one of the following four modes.

### 3.1 Normal (MODE_OFF)

- Complete pass-through: press = ON, release = OFF
- No special behaviour such as rapid fire
- **Buttons used by a macro (both the trigger buttons and the buttons pressed by the macro steps) must be set to this mode** (see "8. Macros")

### 3.2 Rapid Fire (MODE_RAPID)

- **Rapid fire while the button is held**. Release the button to stop
- **A quick double-press (double-click) latches the input ON for as long as you keep holding the button**. Release it to turn OFF
- A double-click is counted when the second press happens **within 250 ms** of the first press
- Examples: actions that need repeated tapping, or inputs you only want to auto-fire while held

### 3.3 Double-Click Rapid Fire (MODE_DOUBLE)

- **Single press: normal input** (ON only while held)
- **Double-click (two presses within 250 ms): rapid fire starts**. Release the button to stop the rapid fire
- Example: when you want to switch between normal input and rapid fire on the same button

### 3.4 Toggle (MODE_TOGGLE)

- **Each press switches rapid fire ON / OFF**
- While ON, rapid fire continues even after you let go of the button. Press it again to stop
- Example: inputs you want to keep auto-firing for a long time

### 3.5 About rapid-fire speed

Rapid-fire speed is determined by the combination of two times.

| Item | Meaning | Range | Step |
|---|---|---|---|
| ON time (on_ms) | How long the button is held down for one input | 20–500 ms | 5 ms |
| OFF time (off_ms) | How long the button is released between inputs | 50–500 ms | 5 ms |

The cycle is "ON time + OFF time", from a minimum of 70 ms to a maximum of 1,000 ms (roughly 1–14 shots per second).
Factory defaults: all buttons in Normal mode, ON time 35 ms / OFF time 250 ms.

---

## 4. Config mode (configuring with the controller buttons)

You can set each button's mode and rapid-fire speed, and enable/disable the rainbow LED, using only the buttons on the controller itself.

### 4.1 Entering config mode

1. **Hold L + R + ZL + ZR all at the same time for 5 seconds**
2. The LED lights up in the sequence "white → red → green → blue", and config mode starts

Note: While in config mode, no button input is sent to the game.
Note: Entering config mode cancels any macro that is running.

### 4.2 Selecting the button to configure

Once in config mode, **press the button you want to configure once**. That button becomes "selected", and its current setting is shown on the LED (see "5. LED indications").

### 4.3 Configuration controls

While a button is selected, use the following controls to change its settings. The LED indication updates each time you press one.

| Button | Action |
|---|---|
| ZR | Switch mode (Normal → Rapid Fire → Double-Click Rapid Fire → Toggle → Normal …) |
| L | Shorten OFF time (−5 ms, minimum 50 ms) |
| R | Lengthen OFF time (+5 ms, maximum 500 ms) |
| + | Lengthen ON time (+5 ms, maximum 500 ms) |
| - | Shorten ON time (−5 ms, minimum 20 ms) |
| HOME | Enable the rainbow LED (LED lights green for 1.5 seconds) |
| Capture | Disable the rainbow LED (LED lights red for 1.5 seconds) |

To configure a different button, simply press that button.

### 4.4 Exiting config mode and saving

1. **Hold ZL for 5 seconds**
2. An LED animation is shown, and the board returns to normal operation

**Settings are saved to flash memory when you exit config mode.**
If you turn the power off while configuring, the settings will not be saved, so always exit using the procedure above.

---

## 5. LED indications

### 5.1 In normal use

- If the rainbow LED is enabled, the LED slowly cycles through rainbow colours in normal use
- If the rainbow LED is disabled, the LED stays off in normal use

### 5.2 In config mode

The setting of the selected button is shown as follows.

- **Normal mode**: lit white (steady, not blinking)
- **Rapid Fire / Double-Click Rapid Fire / Toggle**: blinks in the mode colour, **using exactly the ON time / OFF time set for that button**, so you can see the actual rapid-fire speed with your own eyes

| Mode | LED colour |
|---|---|
| Rapid Fire (MODE_RAPID) | Red |
| Double-Click Rapid Fire (MODE_DOUBLE) | Green |
| Toggle (MODE_TOGGLE) | Blue |

Exceptions to the blinking colour:

| Condition | Indication |
|---|---|
| When the ON time or OFF time is 100 / 200 / 300 / 400 ms | Blinks white |
| When the OFF time is at its minimum 50 ms / maximum 500 ms, or the ON time is at its minimum 20 ms / maximum 500 ms | Blinks purple |

Note: If both conditions apply, the white blinking takes priority.

---

## 6. PC configuration GUI (configuration over USB)

By connecting the board to a PC with a USB cable, you can also configure it from a browser-based GUI.

- Requirements: a web browser with Web Serial support, such as **Chrome / Edge** on a Windows PC
- The configuration GUI is distributed in this GitHub repository
- In the GUI you can set, for each of the 16 buttons, the mode, ON time and OFF time, as well as the rainbow LED on/off and the macros (see "8. Macros")
- Settings changed in the GUI are saved to flash memory automatically each time

Note: If you try to set a rapid-fire mode on a button that is used by an enabled macro, an error occurs and the setting is not changed. Either disable the macro first, or change the button assignment in the macro. (The reverse also applies: a macro setting that conflicts with a rapid-fire setting will result in an error.)

---

## 7. About saved settings

- Button settings, the rainbow LED setting and macro settings are all saved in the board's flash memory
- Settings are kept even when the power is off
- On first start-up (when no saved data exists), the board is initialised with: all buttons in Normal mode, ON time 35 ms / OFF time 250 ms, rainbow LED enabled

---

## 8. Macros

A macro plays back a pre-registered sequence of button actions when you press a designated pair of two buttons at the same time.

### 8.1 Macro specifications

| Item | Details |
|---|---|
| Number of presets | Up to 4 |
| Actions per preset | Up to 20 actions (steps) |
| Contents of one action | A combination of buttons to press (multiple buttons can be pressed at the same time) + hold time + wait time |
| Time unit | Frames (60 FPS basis, 1 frame ≈ 16.7 ms) |
| Hold time / wait time range | 1–600 frames each |
| Looping | Can be enabled/disabled per preset |

### 8.2 How to set up a macro

Macros are set up from the PC configuration GUI (see "6. PC Configuration GUI"). For each preset you set:

- Enabled / disabled
- The two trigger buttons
- Looping on/off
- Whether the trigger buttons' input is also passed through to the game (normally it is not)
- The sequence of actions (steps): the buttons to press, the hold time in frames, and the wait time in frames until the next action

Macro settings are saved to flash memory and are kept even when the power is off.

### 8.3 Starting and stopping a macro

- **Start**: press the two designated buttons at the same time (the order does not matter, but **press the second button within 100 ms of the first**)
- While a macro is running, the two trigger buttons are not sent to the game (unless "pass through to the game" is enabled)
- Once started, a macro will not restart until both trigger buttons have been released
- **Stop**: while a macro is running, **pressing any button other than the trigger buttons** stops the macro (to prevent accidental stops, stop input is ignored for the first 300 ms after start)
- A preset with looping enabled repeats until you perform the stop action

### 8.4 Notes on using macros

- **All buttons used by a macro (the two trigger buttons and every button included in the steps) must be set to Normal mode (MODE_OFF).** If a button used by a macro has a rapid-fire or other mode set, the firmware treats it as a conflict and the macro setting will result in an error
- In the factory default state, all macro presets are disabled

---

## 9. Power saving (sleep)

- If **no button is operated for 60 seconds**, the board automatically enters deep sleep (a true low-power state using Powman, with all power domains off)
- When entering sleep, the LED turns off, and button output and macros stop
- **To wake up, press HOME, A, ZL or ZR**
- The board does not enter sleep in the following cases:
  - While in config mode
  - While connected to a PC over USB and the host keeps the connection alive

---

## 10. Firmware update

The firmware can be updated by drag-and-drop of a UF2 file.

1. Keep holding the BOOT button on the board
2. While holding the button, connect the board to a PC with a USB cable
3. The board appears on the PC as a USB storage drive (drive name: "RP2350")
4. Drag and drop the UF2 file (firmware) onto that drive
5. The board reboots automatically and the update is complete (the USB storage disconnects automatically after writing)

Note: Do not unplug the USB cable during the update.
Note: If the write fails, start again from the BOOT procedure.
Note: The distributed firmware and manuals are published on GitHub (see the links at the end of this document).

---

## 11. Assembly

- All you need is one precision screwdriver. Tweezers make assembly easier
- No modification of the controller body is required
- Note: When replacing the board, the original vibration motor must be transplanted. If the motor is not used, the vibration function will not be available
- Assembly and setup videos are published on YouTube:
  https://www.youtube.com/playlist?list=PLq0JCu-0TrIZ6aA_hGS-kB6uELTtWY_ja
- Note: The videos cover the previous-generation board (RP2040 version). The functions differ from the current product (ver2.1 / RP2354), but the installation steps are the same for the current board. For the functions, please refer to this manual and the manual on GitHub

---

## 12. Notes

- There is no NFC antenna, so amiibo cannot be read
- This product is not a controller by itself (except for the complete units sold with a controller). Please prepare a controller separately
- Disassembling an official controller may make you ineligible for Nintendo's official support
- As a rule, individual support is not provided for this product
- The parts composition and other details may change in part
- This is an unofficial modification product. The seller accepts no responsibility for any damage or disadvantage arising from the use of this product. Use at your own risk
- No game input is performed while in config mode. Also, do not turn the power off while configuring (to prevent save failures)

---

## 13. Troubleshooting

| Symptom | What to check |
|---|---|
| Settings I made have reverted | Did you exit config mode by holding ZL for 5 seconds? Settings are saved when you exit. If you turn the power off while configuring, they are not saved |
| I cannot change the rapid-fire speed | After selecting a button in config mode, change the ON time with + / - and the OFF time with R / L. When you reach the limits (ON 20–500 ms / OFF 50–500 ms), the LED blinks purple |
| Rapid fire won't stop | Check whether the button is in Toggle mode. In Toggle mode, each press switches rapid fire ON/OFF. Also, in Rapid Fire mode, a double-click keeps the input ON while you hold the button |
| A macro won't start | Check that the preset is enabled, that you are pressing the second trigger button within 100 ms of the first, and that all buttons used by the trigger and the steps are in Normal mode |
| Setting a macro gives an error | If a rapid-fire or other mode is set on a button used by the trigger or the steps, a conflict error occurs. Set those buttons to Normal mode first |
| I cannot configure a button from the GUI | If the button is used by an enabled macro, an error occurs. Disable the macro first, or change the button assignment in the macro |
| The board won't wake from sleep | Only HOME / A / ZL / ZR can wake the board. Other buttons do not wake it |
| I want to restore the factory settings | Firmware v8 has no factory-reset operation in its button controls. To reset, flash Factory_Reset.uf2 from this repository using the same procedure as in "10. Firmware update". To change settings individually, use config mode button by button, or use the GUI |

---

## Links

- Product page (BOOTH): https://xgames.booth.pm/items/6925334
- Manual, firmware and configuration GUI (GitHub): https://github.com/Texsugi/NS_Pro_contoroller_rapidfire
- Firmware v8 source code (GitHub): https://github.com/Texsugi/pro16sw_v8
