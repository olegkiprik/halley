## Halley's DAW

### Stage of development: real-time pitchshifter

Audio loopback, turn volume down!

Audio dropouts are possible on a weak PC.

Use at your own risk.

### Installation

Use Clang to compile.

x86-64 Linux portable.

```
cd src
make halley -j
./halley &
```

### How to use

Press <kbd>1-7</kbd> and <kbd>0</kbd> to change the mode.
<kbd>Shift-Q</kbd> to quit.
<kbd>W</kbd> to apply window function on input.

### Used sources

[Caesurus/foreign-dlopen](https://github.com/Caesurus/foreign-dlopen)
[pfalcon/foreign-dlopen](https://github.com/pfalcon/foreign-dlopen)
[RGFW](https://github.com/ColleagueRiley/RGFW)
[miniaudio](https://github.com/mackron/miniaudio)
