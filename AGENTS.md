# AGENTS.md

Notes for anyone, human or AI agent, changing this code. The README is two lines; this file describes what is here.

## What this is

Two Arduino sketches that act as a USB mouse and nudge the pointer a couple of pixels every so often, so a
computer's screensaver or sleep timer doesn't kick in. They run on microcontroller boards, not on a computer:
build and upload them with the Arduino IDE or `arduino-cli`.

- `MouseJiggler.ino`: for Digispark-style ATtiny85 boards, using the `DigiMouse` library from the Digistump AVR
  board package. It moves the pointer in a small square (2 pixels each way), flashes pin 1 (the onboard LED on
  Digispark boards) with each move, then waits a random 10 to 20 seconds. It is based on James Franklin's
  Digispark Mouse Jiggler (credited in the file).
- `jiggler.ino`: for boards with native USB, such as the ATmega32U4 (Leonardo, Pro Micro), using the standard
  `Mouse` library. It moves the pointer 2 pixels right and back, then down and back, then waits a fixed 10 seconds.

## Commands

The two files share one folder, and the Arduino tools compile every `.ino` in a sketch folder as one program. As
they stand, both `setup()` and `loop()` would be defined twice. To build one, copy it into a folder of its own
with the same name, and compile that folder:

```bash
mkdir -p build/MouseJiggler build/jiggler
cp MouseJiggler.ino build/MouseJiggler/ && cp jiggler.ino build/jiggler/
arduino-cli compile --fqbn digistump:avr:digispark-tiny build/MouseJiggler   # needs the Digistump AVR core
arduino-cli compile --fqbn arduino:avr:leonardo build/jiggler
```

A Digispark is uploaded by plugging it in when the upload tool asks for it. There are no tests.

## Rules that keep it working

- **Keep USB alive on the Digispark.** The ATtiny85 has no USB hardware; `DigiMouse` handles USB in software. Wait
  with `DigiMouse.delay()`, never plain `delay()`, or the computer drops the device.
- **16-bit timings.** On AVR boards `unsigned int` holds at most 65535, so `LowerCycleTime` and `UpperCycleTime`
  must stay at or below 65535 ms.
- **Moves of 2 pixels.** The code moves 2 pixels on purpose: some macOS screensavers ignore 1-pixel moves.

## Making a change

- Compile for the right board, upload, and watch the pointer and the LED on a real computer.
