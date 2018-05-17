.data
my_array:
      .int 0b0111111
      .int 0b0000110
      .int 0b1011011
      .int 0b1001111
      .int 0b1100110
      .int 0b1101101
      .int 0b1111101
      .int 0b0000111
      .int 0b1111111
      .int 0b1101111

my_time:
      .int 0b01
      .int 0b10


.text
.global  set_display_bits_from_tod

## ENTRY POINT FOR REQUIRED FUNCTION
set_display_bits_from_tod:





.my_int:
      movq  %rdi, %r13     #hour
      andq  $0xFFFF, %r13
      movq  %rdi, %r12
      movq  %rdi, %rax
      movq  %rdi, %r15


      shrq  $16, %r12    #minute
      andq  $0xFFFF, %r12
      shrq  $32, %r15    #second
      andq  $0xFFFF, %r15
      shrq  $48, %rax    #ispm
      andq  $0b111111111, %rax

      cmpl	$12, %r13d
      ja   .ERROR2
      cmpl	$60, %r12d
      ja   .ERROR2
      cmpl	$60, %r15d
      ja   .ERROR2

      leaq  my_array(%rip), %rcx
      movl  %eax, %r15d
      movl  %r12d, %eax   ###############################
      #movl  0(%rdi), %r12d           # set min to r12
      movl  (%rcx, %rax, 4), %r8d     # min one

      #leaq  my_array(%rip), %rcx

      movl  $0, %eax
      movl  (%rcx, %rax, 4), %r9d   # min tens



      #leaq  my_array(%rip), %rcx
      movl  %r13d, %eax   #################################
      #movl  0(%rdi), %r13d         # set hour to r13
      movl  (%rcx, %rax, 4), %r10d  # hour one

      #leaq  my_array(%rip), %rcx
      movl  $0, %eax
      movl  (%rcx, %rax, 4), %r11d  # hour tens

      #movl  6(%rdi), %eax           #ispm to eax/rax #################################

      movl  %r15d, %eax

      cmpl	$10, %r12d
      jge   .CONDITION11

      jmp   .CONDITION22

.ERROR2:
      movl  $1, %eax
      ret


.CONDITION11:
      movl  %eax, %r15d

      movl  %r12d, %eax
      cqto
      movl  $10, %ecx
      idivl %ecx                  #    //eax quo //edx remainder



      leaq  my_array(%rip), %rcx
      #movl  %edx, %eax
      movl  (%rcx, %rdx, 4), %r8d  # min one

      leaq  my_array(%rip), %rcx
      #movl  $1, %eax
      movl  (%rcx, %rax, 4), %r9d  # min ten

      movl  %r15d, %eax

      jmp  .CONDITION22

.CONDITION22:
      #80000 42994 24000

      cmpl	$10, %r13d
      jge   .CONDITION33


      leaq  my_array(%rip), %rcx
      movl  %eax, %r15d
      movl  %r13d, %eax
      movl  (%rcx, %rax, 4), %r10d  # hour one

      movl  $0, %r11d               # hour tens

      movl  %r15d, %eax

      cmpl	$0, %eax
      je   .CONDITION4





      jmp   .SHIFTING1



.CONDITION33:
      movl  %eax, %r15d
      movl  %r13d, %eax
      cqto
      movl  $10, %ecx
      idivl %ecx                  #    //eax quo //edx remainder

      leaq  my_array(%rip), %rcx
      movl  %edx, %eax
      movl  (%rcx, %rax, 4), %r10d  # hour one

      leaq  my_array(%rip), %rcx
      movl  $1, %eax
      movl  (%rcx, %rax, 4), %r11d   # hour tens

      movl  %r15d, %eax

      cmpl	$0, %eax
      je   .CONDITION4

      jmp   .SHIFTING1

.CONDITION4:

      jmp   .SHIFTING0


.SHIFTING0:
      movq $0,  %r14
      movq $0b01, %rax

      orq  %r8, %r14
      shlq $7,  %r9
      orq  %r9, %r14
      shlq $14,  %r10
      orq  %r10, %r14
      shlq $21,  %r11
      orq  %r11, %r14
      shlq $28,  %rax
      orq  %rax, %r14

      movq %r14, (%rsi)

      movq $0, %rax
      ret

.SHIFTING1:
      movq $0,  %r14
      movq $0b10, %rax

      orq  %r8, %r14
      shlq $7,  %r9
      orq  %r9, %r14
      shlq $14,  %r10
      orq  %r10, %r14
      shlq $21,  %r11
      orq  %r11, %r14
      shlq $28,  %rax
      orq  %rax, %r14

      movq %r14, (%rsi)

      movq $0, %rax
      ret
