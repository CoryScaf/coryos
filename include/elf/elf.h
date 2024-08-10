#ifndef ELF_H_
#define ELF_H_

#include <stdint.h>

#define EI_NIDENT 16

typedef struct {
    uint8_t e_ident[16]; // EFL magic number
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint64_t e_entry; // entry point address
    uint64_t e_phoff; // program header file offset
    uint64_t e_shoff; // section header file offset
    uint32_t e_flags;
    uint32_t e_phentsize;
    uint32_t e_phnum;
    uint32_t e_shentsize;
    uint32_t e_shnum;
    uint32_t e_shstrndx;
} Elf64_Ehdr;

#define EI_MAG0 0 /* e_ident[] indexes */
#define EI_MAG1 1
#define EI_MAG2 2
#define EI_MAG3 3
#define EI_CLASS 4
#define EI_DATA 5
#define EI_VERSION 6
#define EI_OSABI 7
#define EI_PAD 8

#define ELFMAG0 0x7f /* EI_MAG */
#define ELFMAG1 'E'
#define ELFMAG2 'L'
#define ELFMAG3 'F'
#define ELFMAG "\177ELF"
#define SELFMAG 4

#endif
