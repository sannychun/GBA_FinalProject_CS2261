PRODUCT_NAME       = ChunSanny_MetalGearSolidRedux
SOURCES            = main.c myLib.c instructions.c level1.c level2.c level1collision.c level2collision.c losescreen.c winscreen.c sprites.c startscreen.c pausescreen.c storyscreen1.c storyscreen2.c storyscreen3.c storyscreen4.c storyscreen5.c sound.c openingtheme.c crashsound.c callsound.c instructionstheme.c level1audio.c codecsound.c wintheme.c losetheme.c alertsound.c cheatsound.c
DKPATH             = C:\devkitARM\bin
CCPATH             = C:\cygwin\bin
VBASIM             = C:\vba\VisualBoyAdvance.exe
FIND               = find
COPY               = cp -r

# --- File Names
ELF_NAME           = $(PRODUCT_NAME).elf
ROM_NAME           = $(PRODUCT_NAME).gba
BIN_NAME           = $(PRODUCT_NAME)

#MODEL              = -mthumb-interwork -mthumb
MODEL              = -mthumb-interwork -marm -mlong-calls #This makes interrupts work
SPECS              = -specs=gba.specs

# --- Archiver
AS                 = $(DKPATH)/arm-eabi-as
ASFLAGS            = -mthumb-interwork

# --- Compiler
CC                 = $(DKPATH)/arm-eabi-gcc
CFLAGS             = $(MODEL) -O2 -Wall -pedantic -Wextra -std=c99 -save-temps -D_ROM=$(ROM_NAME) -D_VBA=$(VBASIM) 


# --- Linker
LD                 = $(DKPATH)/arm-eabi-gcc
LDFLAGS            = $(SPECS) $(MODEL) -lm

# --- Object/Executable Packager
OBJCOPY            = $(DKPATH)/arm-eabi-objcopy
OBJCOPYFLAGS       = -O binary

# --- ROM Fixer
GBAFIX             = $(DKPATH)/gbafix

# --- Delete
RM                 = rm -f

OBJECTS = $(SOURCES:.c=.o)


# --- Main build target

all : clean build 

run : $(ROM_NAME)
	$(VBASIM) $(ROM_NAME)


build : $(ROM_NAME)

# --- Build .elf file into .gba ROM file
$(ROM_NAME) : $(ELF_NAME)
	$(OBJCOPY) $(OBJCOPYFLAGS) $(ELF_NAME) $(ROM_NAME)
	$(GBAFIX) $(ROM_NAME)

# --- Build .o files into .elf file
$(ELF_NAME) : $(OBJECTS)
	$(LD) $(OBJECTS) $(LDFLAGS) -o $@

# -- Build .c files into .o files
$(OBJECTS) : %.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@



clean:
	$(RM) $(ROM_NAME)
	$(RM) $(ELF_NAME)
	$(RM) $(BIN_NAME)
	$(RM) *.o