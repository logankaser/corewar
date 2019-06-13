# Corewar

[Corewar](https://corewars.org) is a 1984 assembly game where progams fight for  
control of a virtual machine.  
Warriors are programmed in a 16 instruction assembler language that is  
compiled to bytecode and run on a VM with a cycilic memory space.  
Each Warrior must attempt to spead their code while defending from enemies  
that are attempting to do the same.

![visualizer screenshot](https://raw.githubusercontent.com/logankaser/corewar/master/resources/screenshot.png)

## Layout
The code is divided into three seperate and independent executables:
* The vm itself in `virtual_machine`
* The assembler in `assembler`
* The dissassembler in `disassembler`

To run a game, first build the vm and assembler following the instrucitons in [building](https://github.com/logankaser/corewar#building)
then assemble your champions from assembler language into bytecode with the asm exectuable.
Finally follow the virtual machines usage to setup your game, reproduced here:
```
usage: ./corewar [-dump nbr_cycles] [[-n number] <champ.cor>]
 -d <cycle>, --dump <cycle> | Specify cycle to dump memory
 -n <num> <player>, --number <num> <player> | Specify player number
 -q, --quiet  | Enable quiet mode (silence aff and live)
 -v, --visual | Enable visualization with ncurses, implies quiet mode
```

## Building
To build all, run `./build_all.sh`.  
Alternatively, cd in and of `virtual_machine`, `assembler`, or `disassembler`
and run `make` i.e `cd virtual_machine; make`

### Requires
* C compiler
* make
* ncurses

## Team
Jackson Beall  
Thomas Cherret  
Zeid Tisnes  
Logan Kaser  
