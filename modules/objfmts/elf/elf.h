/* $IdPath$
 * ELF object format helpers
 *
 *  Copyright (C) 2003  Michael Urman
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND OTHER CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR OTHER CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ELF_H_INCLUDED
#define ELF_H_INCLUDED

typedef struct elf_reloc_entry elf_reloc_entry;
typedef struct elf_reloc_head elf_reloc_head;
typedef struct elf_secthead elf_secthead;
typedef struct elf_strtab_entry elf_strtab_entry;
typedef struct elf_strtab_head elf_strtab_head;
typedef struct elf_symtab_entry elf_symtab_entry;
typedef struct elf_symtab_head elf_symtab_head;

typedef unsigned long	elf_address;
typedef unsigned long	elf_offset;
typedef unsigned long	elf_size;
typedef unsigned long	elf_section_info;

#define EHDR_SIZE 52

typedef enum {
    ET_NONE = 0,
    ET_REL = 1,					/* Relocatable */
    ET_EXEC = 2,				/* Executable */
    ET_DYN = 3,					/* Shared object */
    ET_CORE = 4,				/* Core */
    ET_LOPROC = 0xff00,				/* Processor specific */
    ET_HIPROC = 0xffff
} elf_file_type;

typedef enum {
    EM_NONE = 0,
    EM_M32 = 1,					/* AT&T WE 32100 */
    EM_SPARC = 2,				/* SPARC */
    EM_386 = 3,					/* Intel 80386 */
    EM_68K = 4,					/* Motorola 68000 */
    EM_88K = 5,					/* Motorola 88000 */
    EM_860 = 7,					/* Intel 80860 */
    EM_MIPS = 8					/* MIPS RS3000 */
} elf_machine;

typedef enum {
    ELFMAG0 = 0x7f,
    ELFMAG1 = 0x45,
    ELFMAG2 = 0x4c,
    ELFMAG3 = 0x46 
} elf_magic;

typedef enum {
    EV_NONE = 0,				/* invalid */
    EV_CURRENT = 1				/* current */
} elf_version;

typedef enum {
    EI_MAG0 = 0,				/* File id */
    EI_MAG1 = 1,
    EI_MAG2 = 2,
    EI_MAG3 = 3,
    EI_CLASS = 4,				/* File class */
    EI_DATA = 5,				/* Data encoding */
    EI_VERSION = 6,				/* File version */
    EI_PAD = 7,					/* Pad through end */
    EI_NIDENT = 16				/* Sizeof e_ident[] */
} elf_identification_index;

typedef enum {
    ELFCLASSNONE = 0,				/* invalid */
    ELFCLASS32 = 1,				/* 32-bit */
    ELFCLASS64 = 2				/* 64-bit */
} elf_class;

typedef enum {
    ELFDATANONE = 0,
    ELFDATA2LSB = 1,
    ELFDATA2MSB = 2
} elf_data_encoding;

/* elf section types - index of semantics */
typedef enum {
    SHT_NULL = 0,		/* inactive section - no associated data */
    SHT_PROGBITS = 1,		/* defined by program for its own meaning */
    SHT_SYMTAB = 2,		/* symbol table (primarily) for linking */
    SHT_STRTAB = 3,		/* string table - symbols need names */
    SHT_RELA = 4,		/* relocation entries w/ explicit addends */
    SHT_HASH = 5,		/* symbol hash table - for dynamic linking */
    SHT_DYNAMIC = 6,		/* information for dynamic linking */
    SHT_NOTE = 7,		/* extra data marking the file somehow */
    SHT_NOBITS = 8,		/* no stored data, but occupies runtime space */
    SHT_REL = 9,		/* relocations entries w/o explicit addends */
    SHT_SHLIB = 10,		/* reserved; unspecified semantics */
    SHT_DYNSYM = 11,		/* like symtab, but more for dynamic linking */

    SHT_LOPROC = 0x70000000,	/* reserved for processor specific semantics */
    SHT_HIPROC = 0x7fffffff/*,
    SHT_LOUSER = 0x80000000,*/	/* reserved for applications; safe */
    /*SHT_HIUSER = 0xffffffff*/
} elf_section_type;

/* elf section flags - bitfield of attributes */
typedef enum {
    SHF_WRITE = 0x1,		/* data should be writable at runtime */
    SHF_ALLOC = 0x2,		/* occupies memory at runtime */
    SHF_EXECINSTR = 0x4/*,*/	/* contains machine instructions */
    /*SHF_MASKPROC = 0xf0000000*/	/* bits reserved for processor specific needs */
} elf_section_flags;

/* elf section index - just the special ones */
typedef enum {
    SHN_UNDEF = 0,		/* undefined symbol; requires other global */
    SHN_LORESERVE = 0xff00,	/* reserved for various semantics */
    SHN_LOPROC = 0xff00,	/* reserved for processor specific semantics */
    SHN_HIPROC = 0xff1f,
    SHN_ABS = 0xfff1,		/* associated symbols don't change on reloc */
    SHN_COMMON = 0xfff2,	/* associated symbols refer to unallocated */
    SHN_HIRESERVE = 0xffff
} elf_section_index;

/* elf symbol binding - index of visibility/behavior */
typedef enum {
    STB_LOCAL = 0,		/* invisible outside defining file */
    STB_GLOBAL = 1,		/* visible to all combined object files */
    STB_WEAK = 2,		/* global but lower precedence */

    STB_LOPROC = 13,		/* reserved for processor specific semantics */
    STB_HIPROC = 15
} elf_symbol_binding;

/* elf symbol type - index of classifications */
typedef enum {
    STT_NOTYPE = 0,		/* type not specified */
    STT_OBJECT = 1,		/* data object such as a variable, array, etc */
    STT_FUNC = 2,		/* a function or executable code */
    STT_SECTION = 3,		/* a section: often for relocation, STB_LOCAL */
    STT_FILE = 4,		/* often source filename: STB_LOCAL, SHN_ABS */

    STT_LOPROC = 13,		/* reserved for processor specific semantics */
    STT_HIPROC = 15
} elf_symbol_type;

typedef enum {
    STN_UNDEF = 0
} elf_symbol_index;


/* internal only object definitions */
#ifdef YASM_OBJFMT_ELF_INTERNAL

#define ELF32_ST_INFO(bind, type)	(((bind) << 4) + ((type) & 0xf))
#define ELF32_R_INFO(s,t)		(((s)<<8)+(unsigned char)(t))

/* elf relocation type - index of semantics */
typedef enum {
    R_386_NONE = 0,		/* none */
    R_386_32 = 1,		/* word, S + A */
    R_386_PC32 = 2,		/* word, S + A - P */
    R_386_GOT32 = 3,		/* word, G + A - P */
    R_386_PLT32 = 4,		/* word, L + A - P */
    R_386_COPY = 5,		/* none */
    R_386_GLOB_DAT = 6,		/* word, S */
    R_386_JMP_SLOT = 7,		/* word, S */
    R_386_RELATIVE = 8,		/* word, B + A */
    R_386_GOTOFF = 9,		/* word, S + A - GOT */
    R_386_GOTPC = 10		/* word, GOT + A - P */
} elf_relocation_type;

struct elf_secthead {
    elf_section_type	 type;
    elf_section_flags	 flags;
    elf_address		 addr;
    elf_address		 offset;
    elf_size		 size;
    elf_section_index	 link;
    elf_section_info	 info;	    /* see note ESD1 */
    elf_address		 align;
    elf_size		 entsize;

    yasm_symrec		*sym;
    elf_strtab_entry	*name;
    elf_section_index	 index;

    elf_reloc_head	*relocs;
    elf_strtab_entry	*rel_name;
    elf_section_index	 rel_index;
    elf_address		 rel_offset;
    unsigned long	 nreloc;
};

/* Note ESD1:
 *   for section types SHT_REL, SHT_RELA:
 *     link -> index of associated symbol table
 *     info -> index of relocated section
 *   for section types SHT_SYMTAB, SHT_DYNSYM:
 *     link -> index of associated string table
 *     info -> 1+index of last "local symbol" (bind == STB_LOCAL)
 *  (for section type SHT_DNAMIC:
 *     link -> index of string table
 *     info -> 0 )
 *  (for section type SHT_HASH:
 *     link -> index of symbol table to which hash applies
 *     info -> 0 )
 *   for all others:
 *     link -> SHN_UNDEF
 *     info -> 0
 */

STAILQ_HEAD(elf_reloc_head, elf_reloc_entry);
struct elf_reloc_entry {
    STAILQ_ENTRY(elf_reloc_entry) qlink;
    elf_address		 addr;
    yasm_symrec		*sym;
    elf_relocation_type	 rtype;
};

STAILQ_HEAD(elf_strtab_head, elf_strtab_entry);
struct elf_strtab_entry {
    STAILQ_ENTRY(elf_strtab_entry) qlink;
    unsigned long	 index;
    char		*str;
};

STAILQ_HEAD(elf_symtab_head, elf_symtab_entry);
struct elf_symtab_entry {
    STAILQ_ENTRY(elf_symtab_entry) qlink;
    yasm_symrec		*sym;
    yasm_section	*sect;
    elf_strtab_entry	*name;
    elf_address		 value;
    yasm_expr		*xsize;
    elf_size		 size;
    elf_section_index	 index;
    elf_symbol_binding	 bind;
    elf_symbol_type	 type;
    elf_symbol_index	 symindex;
};

#endif /* defined(YASM_OBJFMT_ELF_INTERNAL) */



/* reloc functions */
elf_reloc_entry *elf_reloc_entry_new(yasm_symrec *sym,
				     elf_address addr,
				     int rel);
void elf_reloc_entry_delete(elf_reloc_entry *entry);
elf_reloc_head *elf_relocs_new(void);
void elf_reloc_delete(elf_reloc_head *head);

/* strtab functions */
elf_strtab_entry *elf_strtab_entry_new(const char *str);
elf_strtab_head *elf_strtab_new(void);
elf_strtab_entry *elf_strtab_append_str(elf_strtab_head *head, const char *str);
void elf_strtab_delete(elf_strtab_head *head);
unsigned long elf_strtab_output_to_file(FILE *f, elf_strtab_head *head);

/* symtab functions */
elf_symtab_entry *elf_symtab_entry_new(elf_strtab_entry *name,
				       struct yasm_symrec *sym);
void elf_symtab_entry_delete(elf_symtab_entry *entry);
void elf_symtab_entry_print(FILE *f, int indent_level, elf_symtab_entry *entry);
elf_symtab_head *elf_symtab_new(void);
elf_symtab_entry *elf_symtab_append_entry(elf_symtab_head *symtab,
					  elf_symtab_entry *entry);
elf_symtab_entry *elf_symtab_insert_local_sym(elf_symtab_head *symtab,
					      elf_strtab_head *strtab,
					      struct yasm_symrec *sym);
void elf_symtab_delete(elf_symtab_head *head);
unsigned long elf_symtab_assign_indices(elf_symtab_head *symtab);
unsigned long elf_symtab_write_to_file(FILE *f, elf_symtab_head *symtab);
void elf_symtab_set_nonzero(elf_symtab_entry	*entry,
			    struct yasm_section *sect,
			    elf_section_index	 sectidx,
			    elf_symbol_binding	 bind,
			    elf_symbol_type	 type,
			    struct yasm_expr	*size,
			    elf_address		 value);


/* section header functions */
elf_secthead *elf_secthead_new(elf_strtab_entry		*name,
			       elf_section_type		type,
			       elf_section_flags	flags,
			       elf_section_index	idx,
			       elf_address		offset,
			       elf_size			size);
void elf_secthead_delete(elf_secthead *esh);
unsigned long elf_secthead_write_to_file(FILE *f, elf_secthead *esd,
					 elf_section_index sindex);
void elf_secthead_print(FILE *f, int indent_level, elf_secthead *esh);
int elf_secthead_append_reloc(elf_secthead *shead, elf_reloc_entry *reloc);
elf_section_type elf_secthead_get_type(elf_secthead *shead);
elf_size elf_secthead_get_size(elf_secthead *shead);
struct yasm_symrec *elf_secthead_get_sym(elf_secthead *shead);
elf_address elf_secthead_set_addr(elf_secthead *shead, elf_address addr);
elf_address elf_secthead_set_align(elf_secthead *shead, elf_address align);
elf_section_info elf_secthead_set_info(elf_secthead *shead,
				       elf_section_info info);
elf_section_index elf_secthead_set_index(elf_secthead *shead,
					 elf_section_index sectidx);
elf_section_index elf_secthead_set_link(elf_secthead *shead,
					elf_section_index link);
elf_section_index elf_secthead_set_rel_index(elf_secthead *shead,
					     elf_section_index sectidx);
elf_strtab_entry *elf_secthead_set_rel_name(elf_secthead *shead,
					    elf_strtab_entry *entry);
struct yasm_symrec *elf_secthead_set_sym(elf_secthead *shead,
					 struct yasm_symrec *sym);
unsigned long elf_secthead_add_size(elf_secthead *shead, unsigned long size);
unsigned long elf_secthead_write_rel_to_file(FILE *f, elf_section_index symtab,
					     elf_secthead *esd,
					     elf_section_index sindex);
unsigned long elf_secthead_write_relocs_to_file(FILE *f, elf_secthead *shead);
long elf_secthead_set_file_offset(elf_secthead *shead, long pos);

/* program header function */
unsigned long
elf_proghead_write_to_file(FILE *f,
			   elf_offset secthead_addr,
			   unsigned long secthead_count,
			   elf_section_index shstrtab_index);

#endif /* ELF_H_INCLUDED */
