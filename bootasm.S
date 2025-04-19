.section .text.init
.global _start
_start:

//关掉mie与mip寄存器的中断
   csrw mie, zero
   csrw mip, zero
   csrr t0, mhartid
   bnez t0, secondary_hart

   la sp, stack_top
   la t0, bss_start
   la t1, bss_end

clear_bss:
   beq t0, t1, clear_bss_done
   sd zero, 0(t0)
   addi t0, t0, 8
   j clear_bss

clear_bss_done:
   call main
   j exit

exit:
   wfi
   j exit

secondary_hart:
   wfi
   j secondary_hart

.section .bss
.align 3
stack_bottom:
   .skip 4096
stack_top:
