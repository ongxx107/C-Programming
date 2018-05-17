// Template for parsing an ELF file to print its symbol table
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <elf.h>

int DEBUG = 0;                  // controls whether to print debug messages

int main(int argc, char *argv[]){
  if(argc < 2){
    printf("usage: %s [-d] <file>\n",argv[0]);
    return 0;
  }

  char *objfile_name = argv[1];

  // check for debug mode
  if(argc >=3){
    if(strcmp("-d",argv[1])==0){
      DEBUG = 1;               // set debug flag if -d is passed on command line
      objfile_name = argv[2];
    }
    else{
      printf("incorrect usage\n");
      return 1;
    }
  }

  // Open file descriptor and set up memory map for objfile_name
  int fd  = open(objfile_name, O_RDONLY);
  struct stat stat_buf;
  fstat(fd, &stat_buf);
  int size = stat_buf.st_size;
  char* file_chars = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);

  // CREATE A POINTER to the intial bytes of the file which are an ELF64_Ehdr struct
  Elf64_Ehdr* ehdr = (Elf64_Ehdr*) file_chars;

  // CHECK e_ident field's bytes 0 to for for the sequence {0x75,'E','L','F'}.
  // Exit the program with code 1 if the bytes do not match
  int ident_matches =     // check the first bytes to ensure correct file format
    ehdr -> e_ident[0] == 0x7f &&
    ehdr -> e_ident[1] == 'E'  &&
    ehdr -> e_ident[2] == 'L'  &&
    ehdr -> e_ident[3] == 'F';

  if(!ident_matches){
    printf("Magic bytes wrong, this is not an ELF file\n");
    exit(1);
  }

  // PROVIDED: check for a 64-bit file
  if(ehdr->e_ident[EI_CLASS] != ELFCLASS64){
    printf("Not a 64-bit file ELF file\n");
    return 1;
  }

  // PROVIDED: check for x86-64 architecture
  if(ehdr->e_machine != EM_X86_64){
    printf("Not an x86-64 file\n");
    return 1;
  }

  // DETERMINE THE OFFSET of the Section Header Array (e_shoff), the
  // number of sections (e_shnum), and the index of the Section Header
  // String table (e_shstrndx). These fields are from the ELF File
  // Header.

  // Set up a pointer to the array of section headers. Use the section
  // header string table index to find its byte position in the file
  // and set up a pointer to it.
  Elf64_Shdr* shOffPtr = (Elf64_Shdr *) (file_chars + ehdr -> e_shoff);
  Elf64_Shdr* shOffStrPtr = &(shOffPtr[ehdr->e_shstrndx]);
  char* offSet = (char *) (file_chars + shOffStrPtr-> sh_offset);

  // Search the Section Header Array for the secion with name .symtab
  // (symbol table) and .strtab (string table).  Note their positions
  // in the file (sh_offset field).  Also note the size in bytes
  // (sh_size) and and the size of each entry (sh_entsize) for .symtab
  // so its number of entries can be computed.
  int strOff = 0;
  int symOff = 0;
  int shSize = 0;
  int shEntsize = 0;
  int numOfEntries = 0;

  for(int i=0; i< ehdr->e_shnum; i++){
    char* point = offSet + shOffPtr[i].sh_name;

    if ( strcmp(point, ".symtab") == 0 ) {
      symOff = shOffPtr[i].sh_offset;
      shSize = shOffPtr[i].sh_size;
      shEntsize = shOffPtr[i].sh_entsize;
    }

    if ( strcmp(point, ".strtab") == 0 ) {
      strOff = shOffPtr[i].sh_offset;
    }

  }

  if( symOff == 0 ){
    printf("Couldn't find symbol table\n");
    return 1;
  }

  if( strOff == 0 ){
    printf("Couldn't find string table\n");
    return 1;
  }
  numOfEntries = shSize / shEntsize;

  // PRINT byte information about where the symbol table was found and
  // its sizes. The number of entries in the symbol table can be
  // determined by dividing its total size in bytes by the size of
  // each entry.
  printf("Symbol Table\n");
  printf("- %lu bytes offset from start of file\n",(size_t) symOff);
  printf("- %lu bytes total size\n",(size_t) shSize);
  printf("- %lu bytes per entry\n",(size_t) shEntsize);
  printf("- %lu entries\n",(size_t) numOfEntries);


  // Set up pointers to the Symbol Table and associated String Table
  // using offsets found earlier.
  Elf64_Sym* symbolPtr = (Elf64_Sym *) (file_chars + symOff);

  char* strTabPtr = (file_chars + strOff);

  // Print column IDs for info on each symbol
  printf("[%3s]  %8s %4s %s\n",
         "idx","TYPE","SIZE","NAME");

  char* type;
  char* nm;
  int name;
  int sz;

  // Iterate over the symbol table entries
  for(int i=0; i<numOfEntries ; i++){

    name = symbolPtr[i].st_name;
    sz = (int) symbolPtr[i].st_size;

    // Determine size of symbol and name. Use <NONE> name has zero
    // length.
    if (name == 0){ // no name
        nm = "<NONE>";
    }
    else{
        nm = (char*) (strTabPtr + symbolPtr[i].st_name);
    }

    // Determine type of symbol. See assignment specification for
    // fields, macros, and definitions related to this.
    unsigned char typec = ELF64_ST_TYPE( (symbolPtr + i) -> st_info);
    if (typec == STT_NOTYPE) {
      type = "NOTYPE";
    }
    else if (typec == STT_OBJECT) {
      type = "OBJECT";
    }
    else if (typec == STT_FUNC) {
      type = "FUNC";
    }
    else if (typec == STT_SECTION) {
      type = "SECTION";
    }
    else if (typec == STT_FILE) {
      type = "FILE";
    }

    // Print symbol information
    printf("[%3d]: %8s %4lu %s\n",i, type, (size_t) sz, nm);
  }

  // Unmap file from memory and close associated file descriptor
  munmap(file_chars, size);
  close(fd);
  return 0;
}
