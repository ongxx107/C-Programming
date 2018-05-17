# Ren Jeik Ong (ongxx107) 5343975 #
.text
.global  set_tod_from_secs

## ENTRY POINT FOR set_tod_from_secs FUNCTION ##
set_tod_from_secs:
### Data area associated with the next function
.myData:
      cmpl   $86400, %edi 	    # if (time_of_day_sec > 86400)
      ja     .ERROR		    # go to ERROR
      cmpl   $0, %edi		    # if (time_of_day_sec <0)
      jb     .ERROR		    # go to ERROR

      movl   %edi, %eax             # set a copy of time_of_day_sec(edi) to eax
      cqto                          # time_of_day_sec / 3600
      movl   $3600, %ecx            
      idivl  %ecx                   # (eax as quo, edx as remainder)

      movl   %edx, %ecx             # store remainder in ecx
      movl   %eax, %r8d             # set hour to r8
      movl   %ecx, %r9d		    # set minute to r9
      movl   %ecx, %r10d            # set second to r10
      
      movl   %r9d, %eax             # set a copy of r9 to eax
      cqto                          # remainder/60
      movl   $60, %ecx              
      idivl  %ecx                   # (eax as quo, edx as remainder)
 
      movl   %eax, %r9d             # set minute to r9
      movl   %edx, %r10d	    # set second to r10

      movl   $0,   %r11d            # set isPm = 0 to r11

      cmpl   $3600, %edi	    # if (time_of_day_sec < 60*60)
      jl     .CONDITION1	    # go to CONDITION1

      cmpl   $12,  %r8d		    # if (hour > 12)
      jg     .CONDITION2	    # go to CONDITION2

      cmpl   $43200, %edi	    # if (time_of_day_sec < 12*60*60)
      jge    .CONDITION3	    # go to CONDITION3

      movw   %r8w, (%rsi)           # set hour
      movw   %r9w, 2(%rsi)          # set minute
      movw   %r10w, 4(%rsi)         # set second
      movb   %r11b, 6(%rsi)         # set isPm
      movl   $0, %eax		    # success and return 0
      ret

.ERROR:
      movl   $1, %eax
      ret

.CONDITION1:
      movl   %edi, %eax            # set eax to edi
      cqto                         # extend sign of eax to edx
      movl   $60, %ecx             # set ecx to 12
      idivl  %ecx                  # divide combined register by 3600     //eax quo //edx remainder

      movl   $12, %r8d             # set hour to r8
      movl   %eax, %r9d            # set min to r9
      movl   %edx, %r10d           # set sec to r10
      movl   $0, %r11d
      jmp    .SUCCESS

.CONDITION2:
      movl   %r8d, %eax            # set eax to edi
      cqto                         # extend sign of eax to edx
      movl   $12, %ecx             # set ecx to 12
      idivl  %ecx                  # divide combined register by 3600     //eax quo //edx remainder

      movl   %edx, %r8d            # set hour to r8

      cmpl   $43200, %edi
      jge    .CONDITION3
      jmp    .SUCCESS

.CONDITION3:
      movl   $1, %r11d		# set ispm to 1
      jmp    .SUCCESS		# go to success

.SUCCESS:
      movw   %r8w, (%rsi)       # set hour
      movw   %r9w, 2(%rsi)      # set minute
      movw   %r10w, 4(%rsi)     # set second
      movb   %r11b, 6(%rsi)     # set isPm
      movl   $0, %eax		# success and return 0
      ret

.data
my_array:
      .int   0b0111111		# array[0]
      .int   0b0000110		# array[1]
      .int   0b1011011		# array[2]
      .int   0b1001111		# array[3]
      .int   0b1100110		# array[4]
      .int   0b1101101		# array[5]
      .int   0b1111101		# array[6]
      .int   0b0000111		# array[7]
      .int   0b1111111		# array[8]
      .int   0b1101111		# array[9]

.text
.global  set_display_bits_from_tod
## ENTRY POINT FOR set_display_bits_from_tod FUNCTION ##
set_display_bits_from_tod:

.my_int:
      pushq  %r12		 # push callee register r12
      pushq  %r13		 # push callee register r13
      pushq  %r14		 # push callee register r14
      pushq  %r15		 # push callee register r15

      movq   %rdi, %r13          # set hour to r13 0 bit offset
      andq   $0xFFFF, %r13	 # set hour to r13 with AND operator

      movq   %rdi, %r12		 # make a copy of rdi to r12
      shrq   $16, %r12           # set minute to r12 16 bits offset
      andq   $0xFFFF, %r12	 # set minute to r12 with AND operator

      movq   %rdi, %r15		 # make a copy of rdi to r15
      shrq   $32, %r15           # set second to r15 32 bits off set
      andq   $0xFFFF, %r15	 # set seocnd to r15 with AND operator

      movq   %rdi, %rax		 # make a copy of rdi to rax
      shrq   $48, %rax   	 # set ispm to rax 48 bits offset
      andq   $0b111111111, %rax	 # set ispm to rax with AND operator

      cmpl   $12, %r13d		 # if tod.hours > 12 
      ja     .ERROR2		 # go to ERROR2
      cmpl   $60, %r12d		 # if tod.minutes >= 60
      jae     .ERROR2		 # go to ERROR2
      cmpl   $60, %r15d		 # if tod.seconds >= 60
      jae     .ERROR2		 # go to ERROR2

      cmpl   $0, %r13d		 # if tod.hours < 0 
      jl     .ERROR2		 # go to ERROR2
      cmpl   $0, %r12d		 # if tod.minutes < 0
      jl     .ERROR2		 # go to ERROR2
      cmpl   $0, %r15d		 # if tod.seconds < 0
      jl     .ERROR2		 # go to ERROR2

      leaq   my_array(%rip), %rcx
      movl   %eax, %r15d	      # temporary store ispm in r15
      movl   %r12d, %eax
      movl   (%rcx, %rax, 4), %r8d    # set min one to r8 given bits from array

      movl   $0, %eax
      movl   (%rcx, %rax, 4), %r9d    # set min ten to r9 with given bits from array

      movl   %r13d, %eax
      movl   (%rcx, %rax, 4), %r10d   # set hour one to r10 given bits from array

      movl   $0, %eax
      movl   (%rcx, %rax, 4), %r11d   # set hour ten to r11 given bits from array

      movl   %r15d, %eax	      # move back the ispm back to eax

      cmpl   $10, %r12d		      # if ( tod.minutes >=10)
      jge    .CONDITION11	      # go to CONDITION11

      jmp    .CONDITION22	      # else go to CONDITION22

.ERROR2:
      movl   $1, %eax                 # not success and return 1
      popq   %r15                     # pop callee save register 15
      popq   %r14                     # pop callee save register 14
      popq   %r13                     # pop callee save register 13
      popq   %r12                     # pop callee save register 12
      ret

.CONDITION11:
      movl   %eax, %r15d	      # temporary store ispm in r15

      movl   %r12d, %eax	      # (tod.minutes) /10
      cqto
      movl   $10, %ecx		      
      idivl  %ecx                     # (eax as quo, edx as remainder)

      leaq   my_array(%rip), %rcx
      movl   (%rcx, %rdx, 4), %r8d    # set min one = array[(tod.minutes) %10] // array[remainder]

      leaq   my_array(%rip), %rcx
      movl   (%rcx, %rax, 4), %r9d    # set min ten = array[(tod.minutes) /10] // array[quotient]

      movl   %r15d, %eax	      # move back the ispm back to eax

      jmp    .CONDITION22	      # go to necxt condition if the hour is more than or equal to 10

.CONDITION22:
      movl   %eax, %r15d	      # temporary store ispm in r15
      cmpl   $10, %r13d	              # if the hour is more than or equal to 10
      jge    .CONDITION33	      # set the hour ten and hour one
				      # else go to set hour ten as 0 and set hour one respectively
      leaq   my_array(%rip), %rcx     # set rcx as my_array address
      movl   %eax, %r15d	      # temporary store ispm in r15
      movl   %r13d, %eax	      # get element from my_array
      movl   (%rcx, %rax, 4), %r10d   # set hour one to r10
      movl   $0, %r11d                # set hour ten to r11
      movl   %r15d, %eax	      # move back the ispm back to eax

      cmpb   $0, %al	              # if the ispm is 0
      je     .SHIFTING0	              # set the bits element of ispm to 0b01
      jmp    .SHIFTING1		      # else set bits element of ispm to 0b10

.CONDITION33:
      movl   %eax, %r15d	      # temporary store ispm in r15
      movl   %r13d, %eax	      # (tod.hours) /10
      cqto
      movl   $10, %ecx                
      idivl  %ecx                     # (eax as quo, edx as remainder)

      leaq   my_array(%rip), %rcx
      movl   %edx, %eax
      movl   (%rcx, %rax, 4), %r10d   # set hour_one = array[(tod.hours) %10] // array[remainder] 

      leaq   my_array(%rip), %rcx
      movl   $1, %eax
      movl   (%rcx, %rax, 4), %r11d   # set hour_ten = hour_tens = array[1]
      movl   %r15d, %eax	      # move back the ispm back to eax

      cmpb   $0, %al		      # if the ispm is 0
      je     .SHIFTING0               # set the bits element of ispm to 0b01
      jmp    .SHIFTING1               # else set bits element of ispm to 0b10

.SHIFTING0:
      movl   $0, (%rsi)
      movq   $0,  %r14
      movq   $0b01, %rax

      orq    %r8, %r14             # shift min one and shifting is needed since min_one starts from beginning
      shlq   $7,  %r9              # shift left 7 bits off for min ten
      orq    %r9, %r14             # shift left 7 bits off for min ten
      shlq   $14,  %r10            # shift left 14 bits off for hour one
      orq    %r10, %r14            # shift left 14 bits off for hour one
      shlq   $21,  %r11            # shift left 21 bits off for hour ten
      orq    %r11, %r14            # shift left 21 bits off for hour ten
      shlq   $28,  %rax            # shift left 28 bits off for ispm
      orq    %rax, %r14            # shift left 28 bits for ispm

      movl   %r14d, (%rsi)	   # move 32bits of data from r14 register to rsi pointer
      movl   $0, %eax              # success and return 0
      popq   %r15                  # pop callee save register r15
      popq   %r14                  # pop callee save register r14
      popq   %r13                  # pop callee save register r13
      popq   %r12                  # pop callee save register r12
      ret

.SHIFTING1:
      movl   $0, (%rsi)
      movq   $0,  %r14
      movq   $0b10, %rax	   # bits for ispm = 1

      orq    %r8, %r14             # shift min one and shifting is needed since min_one starts from beginning
      shlq   $7,  %r9              # shift left 7 bits off for min ten
      orq    %r9, %r14             # shift left 7 bits off for min ten
      shlq   $14,  %r10            # shift left 14 bits off for hour one
      orq    %r10, %r14            # shift left 14 bits off for hour one
      shlq   $21,  %r11            # shift left 21 bits off for hour ten
      orq    %r11, %r14            # shift left 21 bits off for hour ten
      shlq   $28,  %rax            # shift left 28 bits off for ispm
      orq    %rax, %r14            # shift left 28 bits for ispm

      movl   %r14d, (%rsi)	   # move 32bits of data from r14 register to rsi pointer
      movl   $0, %eax		   # success and return 0
      popq   %r15		   # pop the callee save register r15
      popq   %r14		   # pop the callee save register r14
      popq   %r13		   # pop the callee save register r13
      popq   %r12		   # pop the callee save register r12
      ret

.text
.global lcd_update
## ENTRY POINT FOR lcd_update FUNCTION ##
lcd_update:
.STARTING:
      subq   $8, %rsp				# another way to push the pointer 8 bits down

      movq   %rsp, %rsi                         # set tod as arg2 for func call
      movl   TIME_OF_DAY_SEC(%rip), %edi        # set TIME_OF_DAY_SEC as arg1 16-byte aligned

      cmpl   $86400, %edi			# if TIME_OF_DAY_SEC > 86400
      ja     .ERROR3				# go to ERROR3
      cmpl   $0, %edi				# if TIME_OF_DAY_SEC < 0
      jl     .ERROR3				# go to ERROR3

      call set_tod_from_secs                    # go to set_tod_from_secs function

      movq   (%rsp), %rdi                       # set tod pointer as arg1 for func call
      leaq   LCD_DISPLAY_PORT(%rip), %rsi       # set &LCD_DISPLAY_PORT as arg2 for func call

      call   set_display_bits_from_tod          # go to set_tod_from_secs function

      movl   $0, %eax                           # success and return 0
      addq   $8, %rsp                           # remove rsp change
      ret

.ERROR3:
      movl   $1, %eax				# not success and return 1
      addq   $8, %rsp				# another way to pop the pointer back to normal
      ret
