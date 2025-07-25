/* These are macros to manage storing signatures, selecting what to save       */
/* keeping track of the hidden offset, and ensuring it doesn't overflow	       */
/* They're useful across many tests, but generally for specific classes of ops */


/* This function set up the Page table entry for Sv32 Translation scheme
    Arguments:
    _PAR: Register containing Physical Address
    _PR: Register containing Permissions for Leaf PTE.
        (Note: No-leaf PTE (if-any) has only valid permssion (pte.v) set)
    _TR0, _TR1, _TR2: Temporary registers used and modified by function
    VA: Virtual address
    level: Level at which PTE would be setup
        0: Two level translation
        1: Superpage
*/

#define LEVEL0 0x00
#define LEVEL1 0x01
#define LEVEL2 0x02
#define LEVEL3 0x03
#define LEVEL4 0x04

#define ALL_F_S 0xFFFFFFFF

#define sv39 0x00
#define sv48 0x01
#define sv57 0x02

#define CODE code_bgn_off
#define DATA data_bgn_off
#define SIG  sig_bgn_off
#define VMEM vmem_bgn_off


#define SATP_SETUP(_TR0, _TR1, MODE);\
    LA(_TR0, rvtest_Sroot_pg_tbl) ;\
    LI(_TR1, MODE) ;\
    srli _TR0, _TR0, 12 ;\
    or _TR0, _TR0, _TR1  ;\
    csrw satp, _TR0   ;\

#define SETUP_PMP_SVADU_TEST(swreg, offset, TR0, TR1, TR2) \
  li TR0, -1                                 ;\
  csrw pmpaddr0, TR0                         ;\
  j PMP_exist                                ;\
  li TR0, 0                                  ;\
  li TR1, 0                                  ;\
  j Mend_PMP                                 ;\
PMP_exist:                                   ;\
  li TR1, PMP_TOR | PMP_X | PMP_W | PMP_R    ;\
  csrw pmpcfg0, TR1                          ;\
  csrr TR2, pmpcfg0                          ;\
  beq TR1, TR2, Mend_PMP                     ;\
no_TOR_try_NAPOT:                            ;\
  li TR1, PMP_NAPOT | PMP_X | PMP_W | PMP_R  ;\
  csrw pmpcfg0, TR1                          ;\
  csrr TR2, pmpcfg0                          ;\
Mend_PMP:                                    ;\
  RVTEST_SIGUPD(x1,TR0,offset)               ;\
  RVTEST_SIGUPD(x1,TR1,offset)               ;\

#define TEST_SVADU(swreg, PTE_ADDR, VA, offset, menvcfgaddr, adue_bit) \
    sfence.vma                                                                          ;\
    la t0, VA                                                                           ;\
    li t2, PTE_X | PTE_W | PTE_R                                                        ;\
1:                                                                                      ;\
    LREG t1, (PTE_ADDR)                                                                 ;\
    andi t1, t1, ~(PTE_X | PTE_W | PTE_R | PTE_V)                                       ;\
    or t1, t1, t2                                                                       ;\
    SREG t1, (PTE_ADDR)                                                                 ;\
    sfence.vma                                                                          ;\
											;\
    li t1, ((MSTATUS_MPP & ~(MSTATUS_MPP<<1)) * PRV_S) | MSTATUS_SUM | MSTATUS_MPRV     ;\
    csrs mstatus, t1                                                                    ;\
											;\
    .align 2                                                                            ;\
    SREG x0, (t0)                                                                       ;\
    unimp                                                                               ;\
											;\
    li t1, MSTATUS_MPRV                                                                 ;\
    csrc mstatus, t1                                                                    ;\
											;\
    beqz t2, 2f                                                                         ;\
    addi t2, t2, -1                                                                     ;\
    li t1, PTE_W | PTE_R | PTE_V                                                        ;\
    bne t2, t1, 1b                                                                      ;\
    addi t2, t2, -1                                                                     ;\
    j 1b                                                                                ;\
2:                                                                                      ;\
    li t0, MSTATUS_MPRV                                                                 ;\
    csrc mstatus, t0                                                                    ;\
    LREG t0, (PTE_ADDR)                                                                 ;\
    and t0, t0, PTE_V | PTE_U | PTE_R | PTE_W | PTE_X | PTE_A | PTE_D                   ;\
    RVTEST_SIGUPD(x1,t0,offset)                                                         ;\
                                                                                        ;\
    LREG t0, (PTE_ADDR)                                                                 ;\
    andi t0, t0, ~(PTE_X | PTE_W | PTE_R | PTE_V | PTE_A | PTE_D | PTE_V)               ;\
    ori t0, t0,  PTE_V | PTE_U | PTE_R | PTE_W | PTE_X | PTE_A                          ;\
    SREG t0, (PTE_ADDR)                                                                 ;\
    sfence.vma                                                                          ;\
											;\
    la t0, VA                                                                           ;\
    li a1, ((MSTATUS_MPP & ~(MSTATUS_MPP<<1)) * PRV_S) | MSTATUS_SUM | MSTATUS_MPRV     ;\
    csrs mstatus, a1                                                                    ;\
                                                                                        ;\
    .align 2                                                                            ;\
    SREG x0, (t0)                                                                       ;\
    unimp                                                                               ;\
											;\
    li t0, MSTATUS_MPRV                                                                 ;\
    csrc mstatus, t0                                                                    ;\
											;\
    LREG t0, (PTE_ADDR)                                                                 ;\
    and t0, t0, PTE_V | PTE_U | PTE_R | PTE_W | PTE_X | PTE_A | PTE_D                   ;\
    RVTEST_SIGUPD(x1,t0,offset)                                                         ;\
											;\
    LREG t0, (PTE_ADDR)                                                                 ;\
    andi t0, t0, ~(PTE_X | PTE_W | PTE_R | PTE_V | PTE_A | PTE_D | PTE_V)               ;\
    ori t0, t0,  PTE_V | PTE_U | PTE_R | PTE_W | PTE_X | PTE_A | PTE_D                  ;\
    SREG t0, (PTE_ADDR)                                                                 ;\
    sfence.vma                                                                          ;\
    la t0, VA                                                                           ;\
    li a1, ((MSTATUS_MPP & ~(MSTATUS_MPP<<1)) * PRV_S) | MSTATUS_SUM | MSTATUS_MPRV     ;\
    csrs mstatus, a1                                                                    ;\
											;\
    SREG x0, (t0)                                                                       ;\
    j 3f                                                                                ;\
    unimp                                                                               ;\
3:                                                                                      ;\
    LREG t0, (PTE_ADDR)                                                                 ;\
    andi t0, t0, ~(PTE_D)                                                               ;\
    SREG t0, (PTE_ADDR)                                                                 ;\
    sfence.vma                                                                          ;\
											;\
    li t0, adue_bit                                                                     ;\
    csrs menvcfgaddr, t0                                                                ;\
											;\
    la t0, VA                                                                           ;\
    li a1, ((MSTATUS_MPP & ~(MSTATUS_MPP<<1)) * PRV_S) | MSTATUS_SUM | MSTATUS_MPRV     ;\
    csrs mstatus, a1                                                                    ;\
											;\
    .align 2                                                                            ;\
    SREG x0, (t0)                                                                       ;\
    j 4f                                                                                ;\
    unimp                                                                               ;\
4:                                                                                      ;\
    li t0, MSTATUS_MPRV                                                                 ;\
    csrc mstatus, t0                                                                    ;\
											;\
    LREG t0, (PTE_ADDR)                                                                 ;\
    and t0, t0, PTE_V | PTE_U | PTE_R | PTE_W | PTE_X | PTE_A | PTE_D                   ;\
    RVTEST_SIGUPD(x1,t0,offset)


#define ALL_MEM_PMP                                               ;\
    	li t2, -1                                                 ;\
    	csrw pmpaddr0, t2                                         ;\
    	li t2, 0x0F	                                          ;\
    	csrw pmpcfg0, t2                                          ;\
    	sfence.vma                                                ;

#define SIGNATURE_AREA(TYPE,ARG1,ARG2, ...)                       ;\
	LI (t0, ARG1)                                             ;\
	.if(TYPE == CODE)                                         ;\
        LI (t1, ARG2)                                             ;\
	    sub t0, t0, t1                                        ;\
            csrr sp, mscratch                                     ;\
	    add t1,sp,t0                                          ;\
	    csrw sscratch, t1                                     ;\
    .else                                                         ;\
        LA (t1, ARG2)                                             ;\
	    sub t0, t0, t1                                        ;\
    .endif                                                        ;\
	LREG t1, TYPE+0*sv_area_sz(sp)                            ;\
	add t2, t1, t0                                            ;\
	SREG t2, TYPE+1*sv_area_sz(sp)                            ;

//****NOTE: label `rvtest_Sroot_pg_tbl` must be declared after RVTEST_DATA_END
//          in the test aligned at 4kiB (use .align 12)
#define PTE_SETUP_COMMON(_PAR, _PR, _TR0, _TR1, _VAR, level)  	  ;\
    srli _VAR, _VAR, (RISCV_PGLEVEL_BITS * level + RISCV_PGSHIFT) ;\
    srli _PAR, _PAR, (RISCV_PGLEVEL_BITS * level + RISCV_PGSHIFT) ;\
    slli _PAR, _PAR, (RISCV_PGLEVEL_BITS * level + RISCV_PGSHIFT) ;\
    LI(_TR0, ((1 << RISCV_PGLEVEL_BITS) - 1))                     ;\
    and _VAR, _VAR, _TR0                                          ;\
    slli _VAR, _VAR, ((XLEN >> 5)+1)                              ;\
    add _TR1, _TR1, _VAR                                          ;\
    srli _PAR, _PAR, 12                                           ;\
    slli _PAR, _PAR, 10                                           ;\
    or _PAR, _PAR, _PR                                            ;\
    SREG _PAR, 0(_TR1);

#define PTE_SETUP_RV32(_PAR, _PR, _TR0, _TR1, VA, level)  	;\
    srli _PAR, _PAR, 12                                         ;\
    slli _PAR, _PAR, 10                                         ;\
    or _PAR, _PAR, _PR                                          ;\
    .if (level==1)                                              ;\
        LA(_TR1, rvtest_Sroot_pg_tbl)                           ;\
        LI(_TR0, ((VA>>22)&0x3FF)<<2)                           ;\
    .endif                                                      ;\
    .if (level==0)                                              ;\
        LA(_TR1, rvtest_slvl1_pg_tbl)                           ;\
        LI(_TR0, ((VA>>12)&0x3FF)<<2)                           ;\
    .endif                                                      ;\
    add _TR1, _TR1, _TR0                                        ;\
    SREG _PAR, 0(_TR1);

// More Robust version of PTE_SETUP_32 to setup a PTE for a PA using Va
// in a single line.
//args: PA: Label of Physical Address, PERMS: permissions in hex
//args: VA: Virtual Address in hex, level: Level to store at
#define PTE_SETUP_RV32_New(PA_LBL, PERMS, VA, level)           ;\
    LA(a0, PA_LBL)                                             ;\
    LI(a1, PERMS)                                              ;\
	PTE_SETUP_RV32(a0, a1, t0, t1, VA, level)                  ;\

#define SAVE_AREA_SETUP(VA, PA_LBL, _REG_NAME)                  ;\
	LI (t0, VA)                                                 ;\
	LA (t1, PA_LBL)                                             ;\
	sub t0, t0, t1                                              ;\
	LREG t1, _REG_NAME##_bgn_off+0*sv_area_sz(sp)               ;\
	add t2, t1, t0                                              ;\
	SREG t2, _REG_NAME##_bgn_off+1*sv_area_sz(sp)               ;\

#define PTE_SETUP_SV32(_PAR, _PR, _TR0, _TR1, _VAR, level)  	  ;\
    .if (level==1)                                                ;\
        LA(_TR1, rvtest_Sroot_pg_tbl)                             ;\
    .endif                                                        ;\
    .if (level==0)                                                ;\
        LA(_TR1, rvtest_slvl1_pg_tbl)                             ;\
    .endif                                                        ;\
    PTE_SETUP_COMMON(_PAR, _PR, _TR0, _TR1, _VAR, level)

#define PTE_SETUP_SV39(_PAR, _PR, _TR0, _TR1, _VAR, level)  	  ;\
    .if (level==2)                                                ;\
        LA(_TR1, rvtest_Sroot_pg_tbl)                             ;\
    .endif                                                        ;\
    .if (level==1)                                                ;\
        LA(_TR1, rvtest_slvl2_pg_tbl)                             ;\
    .endif                                                        ;\
    .if (level==0)                                                ;\
        LA(_TR1, rvtest_slvl1_pg_tbl)                             ;\
    .endif                                                        ;\
    PTE_SETUP_COMMON(_PAR, _PR, _TR0, _TR1, _VAR, level)

#define PTE_SETUP_SV48(_PAR, _PR, _TR0, _TR1, _VAR, level)  	  ;\
    .if (level==3)                                                ;\
        LA(_TR1, rvtest_Sroot_pg_tbl)                             ;\
    .endif                                                        ;\
    .if (level==2)                                                ;\
        LA(_TR1, rvtest_slvl3_pg_tbl)                             ;\
    .endif                                                        ;\
    .if (level==1)                                                ;\
        LA(_TR1, rvtest_slvl2_pg_tbl)                             ;\
    .endif                                                        ;\
    .if (level==0)                                                ;\
        LA(_TR1, rvtest_slvl1_pg_tbl)                             ;\
    .endif                                                        ;\
    PTE_SETUP_COMMON(_PAR, _PR, _TR0, _TR1, _VAR, level)

#define PTE_SETUP_SV57(_PAR, _PR, _TR0, _TR1, _VAR, level)  	  ;\
    .if (level==4)                                                ;\
        LA(_TR1, rvtest_Sroot_pg_tbl)                             ;\
    .endif                                                        ;\
    .if (level==3)                                                ;\
        LA(_TR1, rvtest_slvl4_pg_tbl)                             ;\
    .endif                                                        ;\
    .if (level==2)                                                ;\
        LA(_TR1, rvtest_slvl3_pg_tbl)                             ;\
    .endif                                                        ;\
    .if (level==1)                                                ;\
        LA(_TR1, rvtest_slvl2_pg_tbl)                             ;\
    .endif                                                        ;\
    .if (level==0)                                                ;\
        LA(_TR1, rvtest_slvl1_pg_tbl)                             ;\
    .endif                                                        ;\
    PTE_SETUP_COMMON(_PAR, _PR, _TR0, _TR1, _VAR, level)


#define PTE_SETUP_RV64(_PAR, _PR, _TR0, _TR1, VA, level, mode)  ;\
    srli _PAR, _PAR, 12                                         ;\
    slli _PAR, _PAR, 10                                         ;\
    or _PAR, _PAR, _PR                                          ;\
    .if (mode == sv39)                                          ;\
        .if (level == 2)                                        ;\
            LA(_TR1, rvtest_Sroot_pg_tbl)                       ;\
            .set vpn, ((VA >> 30) & 0x1FF) << 3                 ;\
        .endif                                                  ;\
        .if (level == 1)                                        ;\
            LA(_TR1, rvtest_slvl1_pg_tbl)                       ;\
            .set vpn, ((VA >> 21) & 0x1FF) << 3                 ;\
        .endif                                                  ;\
        .if (level == 0)                                        ;\
            LA(_TR1, rvtest_slvl2_pg_tbl)                       ;\
            .set vpn, ((VA >> 12) & 0x1FF) << 3                 ;\
        .endif                                                  ;\
    .endif                                                      ;\
    .if (mode == sv48)                                          ;\
        .if (level == 3)                                        ;\
            LA(_TR1, rvtest_Sroot_pg_tbl)                       ;\
            .set vpn, ((VA >> 39) & 0x1FF) << 3                 ;\
        .endif                                                  ;\
        .if (level == 2)                                        ;\
            LA(_TR1, rvtest_slvl1_pg_tbl)                       ;\
            .set vpn, ((VA >> 30) & 0x1FF) << 3                 ;\
        .endif                                                  ;\
        .if (level == 1)                                        ;\
            LA(_TR1, rvtest_slvl2_pg_tbl)                       ;\
            .set vpn, ((VA >> 21) & 0x1FF) << 3                 ;\
        .endif                                                  ;\
        .if (level == 0)                                        ;\
            LA(_TR1, rvtest_slvl3_pg_tbl)                       ;\
            .set vpn, ((VA >> 12) & 0x1FF) << 3                 ;\
        .endif                                                  ;\
    .endif                                                      ;\
    .if (mode == sv57)                                          ;\
        .if (level == 4)                                        ;\
            LA(_TR1, rvtest_Sroot_pg_tbl)                       ;\
            .set vpn, ((VA >> 48) & 0x1FF) << 3                 ;\
        .endif                                                  ;\
        .if (level == 3)                                        ;\
            LA(_TR1, rvtest_slvl1_pg_tbl)                       ;\
            .set vpn, ((VA >> 39) & 0x1FF) << 3                 ;\
        .endif                                                  ;\
        .if (level == 2)                                        ;\
            LA(_TR1, rvtest_slvl2_pg_tbl)                       ;\
            .set vpn, ((VA >> 30) & 0x1FF) << 3                 ;\
        .endif                                                  ;\
        .if (level == 1)                                        ;\
            LA(_TR1, rvtest_slvl3_pg_tbl)                       ;\
            .set vpn, ((VA >> 21) & 0x1FF) << 3                 ;\
        .endif                                                  ;\
        .if (level == 0)                                        ;\
            LA(_TR1, rvtest_slvl3_pg_tbl)                       ;\
            .set vpn, ((VA >> 12) & 0x1FF) << 3                 ;\
        .endif                                                  ;\
    .endif                                                      ;\
    LI(_TR0, vpn)                                               ;\
    add _TR1, _TR1, _TR0                                        ;\
    SREG _PAR, 0(_TR1)                                          ;

#define PTE_PERMUPD_RV32(_PR, _TR0, _TR1, VA, level)          	;\
    .if (level==1)                                              ;\
        LA(_TR1, rvtest_Sroot_pg_tbl)                           ;\
        .set vpn, ((VA>>22)&0x3FF)<<2                           ;\
    .endif                                                      ;\
    .if (level==0)                                              ;\
        LA(_TR1, rvtest_slvl1_pg_tbl)                           ;\
        .set vpn, ((VA>>12)&0x3FF)<<2                           ;\
    .endif                                                      ;\
    LI(_TR0, vpn)                                               ;\
    add _TR1, _TR1, _TR0                                        ;\
    LREG _TR0, 0(_TR1)                                          ;\
    srli _TR0, _TR0, 10                                         ;\
    slli _TR0, _TR0, 10                                         ;\
    or _TR0, _TR0, _PR                                          ;\
    SREG _TR0, 0(_TR1)                                          ;


#define SATP_SETUP_SV32 ;\
    LA(t6, rvtest_Sroot_pg_tbl) ;\
    LI(t5, SATP32_MODE) ;\
    srli t6, t6, 12 ;\
    or t6, t6, t5  ;\
    csrw satp, t6   ;

#define SATP_SETUP_RV64(MODE)                                   ;\
    LA(t6, rvtest_Sroot_pg_tbl)                                 ;\
    .if (MODE == sv39)                                          ;\
    LI(t5, (SATP64_MODE) & (SATP_MODE_SV39 << 60))              ;\
    .endif                                                      ;\
    .if (MODE == sv48)                                          ;\
    LI(t5, (SATP64_MODE) & (SATP_MODE_SV48 << 60))              ;\
    .endif                                                      ;\
    .if (MODE == sv57)                                          ;\
    LI(t5, (SATP64_MODE) & (SATP_MODE_SV57 << 60))              ;\
    .endif                                                      ;\
    .if (MODE == sv64)                                          ;\
    LI(t5, (SATP64_MODE) & (SATP_MODE_SV64 << 60))              ;\
    .endif                                                      ;\
    srli t6, t6, 12                                             ;\
    or t6, t6, t5                                               ;\
    csrw satp, t6                                               ;

//Tests for atomic memory operation(AMO) instructions
#define TEST_AMO_OP(inst, destreg, origptr, reg2, origval, updval, sigptr, ...) ;\
      .if NARG(__VA_ARGS__) == 1			;\
	.set offset,_ARG1(__VA_OPT__(__VA_ARGS__,0))	;\
      .endif						;\
      LI(reg2, MASK_XLEN(origval))			;\
      RVTEST_SIGUPD(sigptr, reg2) /*Write original AMO src */ ;\
      LI(reg2, MASK_XLEN(updval)) ;\
      addi origptr, sigptr, offset-REGWIDTH /* Calculate where orig AMO src is stored */ ;\
      inst destreg, reg2, (origptr) /*origval -> destreg; updated val -> (origptr) */ ;\
      RVTEST_SIGUPD(sigptr, destreg) /* write original AMO val */


#define NAN_BOXED(__val__,__width__,__max__)	;\
     .if __width__ == 16                        ;\
        .hword __val__                         ;\
    .endif                                     ;\
    .if __width__ == 32				;\
	.word __val__				;\
    .else					;\
	.dword __val__				;\
    .endif					;\
    .if __max__ > __width__			;\
        .if __width__ == 16                      ;\
         .set pref_bytes,(__max__-__width__)/16;\
        .else				                             ;\
         .set pref_bytes,(__max__-__width__)/32;\
    	.endif                                   ;\
    .else					;\
	.set pref_bytes, 0			;\
    .endif					;\
    .rept pref_bytes				;\
        .if __width__ == 16         ;\
		      .hword 0xffff         ;\
        .else				        ;\
	        .word 0xffffffff		;\
        .endif                      ;\
    .endr					;

#define ZERO_EXTEND(__val__,__width__,__max__)	;\
    .if __max__ > __width__			;\
	.set pref_bytes,(__max__-__width__)/32	;\
    .else					;\
	.set pref_bytes, 0			;\
    .endif					;\
    .rept pref_bytes				;\
	.word 0					;\
    .endr					;\
    .if __width__ == 32				;\
	.word __val__				;\
    .else					;\
	.dword __val__				;\
    .endif;

#define RVTEST_FP_ENABLE()			;\
 LI(a0, (MSTATUS_FS & (MSTATUS_FS >> 1)))	;\
 csrs mstatus, a0				;\
 csrwi fcsr, 0

// This macro is for vector
#define RVTEST_VXSAT_ENABLE()			;\
 LI(a0, (MSTATUS_VS & (MSTATUS_VS >> 1)))	;\
 csrs mstatus, a0				;\
 clrov

/* RVTEST_SIGBASE(reg, label) initializes to label and clears offset */
#define RVTEST_SIGBASE(_R,_TAG)			;\
  LA(_R,_TAG)					;\
  .set offset,0

// This macro is loading data from memory with any offset value
// This macro is loading data from memory with any offset value
#define LOAD_MEM_VAL(_LINST, _AREG, _RD, _OFF, _TREG) ;\
   .if (((_OFF & ~0x07FF)==  0) |((_OFF |  0x07FF)== -1))                       ;\
   _LINST _RD, _OFF(_AREG) /* yes, it fits */         ;\
  .else                    /* no, needs base adj   */ ;\
  .set  _off,  SEXT_IMM(_OFF) /* strip off hi bits */ ;\
  .set cry, BIT(_off,11)<<12    ;\
   LI(  _TREG, (_OFF & ~0x0FFF)+cry) /* strip off hi bits*/ ;\
    add  _AREG, _AREG, _TREG /* modified temp base*/ ;\
    _LINST _RD, _off(_AREG)                          ;\
    sub  _AREG, _AREG, _TREG /* undo modification */ ;\
 .endif
  /* this function ensures individual sig stores don't exceed offset limits  */
  /* if they would, update the base by 2032 and reset the offset     */
  /* exceed offset limit is 16 below Breg-add # to allow for allignment across different register sizes */
  /* 2032 as Breg add amount to avoid max 2048 add*/
  /* an option is to pre-incr offset if there was a previous signature store */
#define CHK_OFFSET(_BREG, _SZ, _PRE_INC)		;\
  .if (_PRE_INC!=0)					;\
    .set offset, offset+_SZ				;\
  .endif						;\
  .if offset >= 2016					;\
    addi   _BREG,  _BREG,   2032 		;\
    .set   offset, 0		;\
  .endif

 /* automatically adjust base and offset if offset gets too big, resetting offset				 */
 /* RVTEST_SIGUPD(basereg, sigreg)	  stores sigreg at offset(basereg) and updates offset by regwidth	 */
 /* RVTEST_SIGUPD(basereg, sigreg,newoff) stores sigreg at newoff(basereg) and updates offset to regwidth+newoff */
 /*SIGMODES using gcc -D SIGMODE_NONE for no Signiture -D SIGMODE_SELFCHECK for selfcheck(both do nothing, needs updating) NO -D for defualt Signitures*/

/* Ensure SIGMODE_DEFAULT is defined if no SIGMODE is provided */
#ifndef SIGMODE_NONE
#ifndef SIGMODE_SELFCHECK
#define SIGMODE_DEFAULT
#endif
#endif

#ifdef SIGMODE_NONE
    #define RVTEST_SIGUPD(_BR, _R, ...) \
        nop;
#endif
// SIGMODE_SELFCHECK: TODO
#ifdef SIGMODE_SELFCHECK
    #define RVTEST_SIGUPD(_BR, _R, ...) \
        nop /* TODO: Add self-check logic here */;
#endif
// SIGMODE_DEFAULT: Default behavior
#ifdef SIGMODE_DEFAULT
    #define RVTEST_SIGUPD(_BR, _R, ...)                \
        .if NARG(__VA_ARGS__) == 1				;\
        .set offset,_ARG1(__VA_OPT__(__VA_ARGS__,0))	;\
        .endif						;\
        CHK_OFFSET(_BR, REGWIDTH,0)				;\
        SREG _R,offset(_BR)					;\
        .set offset,offset+REGWIDTH
#endif
/* RVTEST_SIGUPD_F(basereg, sigreg,flagreg,newoff)			 */
/* This macro is used to store the signature values of (32 & 64) F and D */
/* teats which use TEST_(FPSR_OP, FPIO_OP, FPRR_OP, FPR4_OP) opcodes	 */
/* It stores both an Xreg and an Freg, first adjusting base & offset to	 */
/* to keep offset < 2048. SIGALIGN is set to the max(FREGWIDTH, REGWIDTH)*/
/* _BR - Base Reg, _R - FReg, _F - Fstatus Xreg				 */
#define RVTEST_SIGUPD_F(_BR,_R,_F,...)			;\
  .if NARG(__VA_ARGS__) == 1				;\
     .set offset,_ARG1(__VA_OPT__(__VA_ARGS__,0))	;\
  .endif						;\
  .if (offset&(SIGALIGN-1))!=0				;\
/* Throw warnings then modify offset to target */	;\
/*     .warning "Incorrect signature Offset Alignment."	*/;\
     .set offset, (offset&~(SIGALIGN-1))+SIGALIGN		;\
  .endif						;\
  CHK_OFFSET(_BR, SIGALIGN, 0)				;\
  FSREG _R,offset(_BR)					;\
  CHK_OFFSET(_BR, SIGALIGN, 1)				;\
  SREG _F,offset(_BR)					;\
  .set offset,offset+SIGALIGN

/* RVTEST_SIGUPD_FID(basereg, sigreg,flagreg,newoff)			*/
/* This macro stores the signature values of (32 & 64) F & D insts	*/
/* which uses TEST_(FPID_OP, FCMP_OP) ops				*/
/* It stores two integer registers. SigReg is stored @offset[BaseReg],	*/
/* FlagReg at offset+Regwidth[BaseReg]. It updates offset by 2*regwidth	*/
/* and post increments so repeated uses store sig values sequentially	*/
/*  _BR - Base Reg, _R - Signature reg, _F - Flag reg			*/
#define RVTEST_SIGUPD_FID(_BR,_R,_F,...)		;\
  .if NARG(__VA_ARGS__) == 1				;\
     .set offset,_ARG1(__VA_OPT__(__VA_ARGS__,0))	;\
  .endif						;\
  .if (offset&(SIGALIGN-1))!=0				;\
/* Throw warnings then modify offset to target */	;\
/*     .warning "Signature Incorrect Offset Alignment."	*/;\
     .set offset, offset&(SIGALIGN-1)+SIGALIGN		;\
  .endif						;\
  CHK_OFFSET(_BR, REGWIDTH, 0)				;\
  SREG _R,offset(_BR)					;\
  CHK_OFFSET(_BR, REGWIDTH, 1)				;\
  SREG _F,offset(_BR)					;\
  .set offset,offset+REGWIDTH


// for updating signatures that include flagreg for P-ext saturation instructions (RV32/RV64).
#define RVTEST_SIGUPD_PK(_BR,_R,_F,...)			;\
  .if NARG(__VA_ARGS__) == 1				;\
      .set offset,_ARG1(__VA_OPT__(__VA_ARGS__,0))	;\
  .endif						;\
  .if (offset & (REGWIDTH-1)) != 0			;\
/*      .warning "Signature Incorrect Offset Alignment."	*/;\
     .set offset, offset&(SIGALIGN-1)+SIGALIGN		;\
  .endif						;\
      CHK_OFFSET(_BR,REGWIDTH,0)			;\
      SREG _R,offset(_BR)				;\
      CHK_OFFSET(_BR,REGWIDTH,1)			;\
      SREG _F,offset(_BR)				;\
      .set offset,offset+(REGWIDTH)

// for updating signatures when 'rd' is a paired register (64-bit)
//  in Zpsfoperand extension in RV32; this reuses RVTEST_SIGUPD_PK()
#define RVTEST_SIGUPD_P64(_BR,_R,_R_HI,...)				;\
  .if NARG(__VA_ARGS__) == 0						;\
      RVTEST_SIGUPD_PK(_BR,_R,_R_HI)					;\
  .else									;\
      RVTEST_SIGUPD_PK(_BR,_R,_R_HI,_ARG1(__VA_OPT__(__VA_ARGS__,0)))	;\
  .endif

// for updating signatures that include flagreg when 'rd' is a
// paired register (64-bit) in Zpsfoperand extension in RV32.
#define RVTEST_SIGUPD_PK64(_BR,_R,_R_HI,_F,...)			;\
      rdov _F							;\
  .if NARG(__VA_ARGS__) == 1					;\
      .set offset,_ARG1(__VA_OPT__(__VA_ARGS__,0))		;\
  .endif							;\
  .if (offset & (REGWIDTH-1)) != 0				;\
/*      .warning "Incorrect Offset Alignment for Signature."	*/;\
     .set offset, offset&(SIGALIGN-1)+SIGALIGN			;\
  .endif							;\
      CHK_OFFSET(_BR,REGWIDTH,0)				;\
      SREG _R,offset(_BR)					;\
      CHK_OFFSET(_BR,REGWIDTH,1)				;\
      SREG _R_HI,offset(_BR)					;\
      CHK_OFFSET(_BR,REGWIDTH,1)				;\
      SREG _F,offset(_BR)					;\
      .set offset,offset+(REGWIDTH)

/* Stores register into signature region and increment the signature pointer*/
 /* RVTEST_SIGUPD does not properly handle code that jumps over macros due to garbling the offset.*/
 /* Do not mix RVTEST_SIGWRITE and RVTEST_SIGUPD in the same program */
 /* RVTEST_SIGWRITE(basereg, sigreg) stores sigreg at 0(basereg) and increments basereg by regwidth  */
 #define RVTEST_SIGWRITE(_BR,_R)            ;\
      SREG _R, 0(_BR)                   ;\
      addi _BR, _BR, REGWIDTH

 /* Stores register into signature region and increment the signature pointer*/
 /* RVTEST_SIGUPD_F does not properly handle code that jumps over macros due to garbling the offset.*/
 /* Do not mix RVTEST_SIGWRITE_F and RVTEST_SIGUPD_F in the same program */
 /* RVTEST_SIGWRITE_F(basereg, sigreg, flagreg) stores sigreg at 0(basereg) and increments basereg by sigalign   */
 /* SIGALIGN is set to the max(FREGWIDTH, REGWIDTH)*/
#define RVTEST_SIGWRITE_F(_BR,_R,_f)        ;\
      FSREG _R, 0(_BR)                  ;\
      SREG _F, SIGALIGN(_BR)                    ;\
      addi _BR, _BR, 2*SIGALIGN

  /* DEPRECATE this is redundant with RVTEST_BASEUPD(BR,_NR),	*/
  /* except it doesn't correct for offset overflow while moving */
#define RVTEST_VALBASEMOV(_NR,_BR)			;\
  add _NR, _BR, x0;

#define RVTEST_VALBASEUPD(_BR,...)			;\
  .if NARG(__VA_ARGS__) == 0				;\
      addi _BR,_BR,2040					;\
  .endif						;\
  .if NARG(__VA_ARGS__) == 1				;\
      LA(_BR,_ARG1(__VA_ARGS__,x0))			;\
  .endif

/*
 * RVTEST_BASEUPD(base reg) - updates the base register the last signature address + REGWIDTH
 * RVTEST_BASEUPD(base reg, new reg) - moves value of the next signature region to update into new reg
 * The hidden variable offset is reset always
*/

#define RVTEST_BASEUPD(_BR,...)				;\
 /* deal with case where offset>=2047 */		;\
       .set corr 2048-REGWIDTH				;\
    .if offset <2048 					;\
       .set corr offset					;\
    .endif						;\
    .set offset, offset-corr				;\
							;\
    .if NARG(__VA_ARGS__) == 0				;\
	addi _BR,		    _BR, corr		;\
    .else						;\
	addi _ARG1(__VA_ARGS__,x0) ,_BR, corr		;\
    .endif

//==============================================================================
// This section borrows from Andrew's from Andrew Waterman's risc-v test macros
// They are used to generate tests; some are op specific, some format specific
//==============================================================================

#define TEST_JALR_OP(tempreg, rd, rs1, imm, swreg, offset,adj)	;\
5:					;\
    auipc rd, 0             ;\
    .if adj & 1 == 1			;\
    LA(rs1, 3f-imm+adj-1)		;\
    jalr rd, imm+1(rs1)			;\
    .else				;\
    LA(rs1, 3f-imm+adj)			;\
    jalr rd, imm(rs1)			;\
    .endif				;\
    nop					;\
    nop					;\
    xori rd,rd, 0x2			;\
    j 4f				;\
					;\
3:  .if adj & 2 == 2			;\
    .fill 2,1,0x00			;\
    .endif				;\
    xori rd,rd, 0x3			;\
    j 4f				;\
    .if adj&2 == 2			;\
    .fill 2,1,0x00			;\
    .endif				;\
					;\
4: LA(tempreg, 5b)			;\
   andi tempreg,tempreg,~(3)		;\
    sub rd,rd,tempreg			;\
    RVTEST_SIGUPD(swreg,rd,offset)


#define TEST_JAL_OP(tempreg, rd, imm, label, swreg, offset, adj)	;\
5:					;\
    LA(tempreg, 2f)			;\
    mv rd, tempreg          ;\
    jalr x0,0(tempreg)			;\
6:  LA(tempreg, 4f)			;\
    jalr x0,0(tempreg)			;\
1:  .if adj & 2 == 2			;\
    .ifc label, 1b			;\
    .fill 2,1,0x00			;\
    .endif				;\
    .endif				;\
    xori rd,rd, 0x1			;\
    beq x0,x0,6b			;\
    .if adj & 2 == 2			;\
    .ifc label, 1b			;\
    .fill 2,1,0x00			;\
    .endif				;\
    .endif				;\
    .if (imm/2) - 2 >= 0		;\
	.set num,(imm/2)-2		;\
    .else				;\
	.set num,0			;\
    .endif				;\
     .ifc label, 3f			;\
	.set num,0			;\
    .endif				;\
    .rept num				;\
    nop					;\
    .endr				;\
					;\
2:  jal rd, label+(adj)			;\
    .if adj & 2 == 2			;\
    nop					;\
    nop					;\
    .endif				;\
    xori rd,rd, 0x2			;\
    j 4f				;\
    .if (imm/2) - 3 >= 0		;\
	.set num,(imm/2)-3		;\
    .else				;\
	.set num,0			;\
    .endif				;\
    .ifc label, 1b			;\
	.set num,0			;\
    .endif				;\
    .rept num				;\
    nop					;\
    .endr				;\
3:  .if adj & 2 == 2			;\
    .ifc label, 3f			;\
    .fill 2,1,0x00			;\
    .endif				;\
    .endif				;\
    xori rd,rd, 0x3			;\
    LA(tempreg, 4f)			;\
    jalr x0,0(tempreg)			;\
    .if adj & 2 == 2			;\
    .ifc label, 3f			;\
    .fill 2,1,0x00			;\
    .endif				;\
    .endif				;\
4: LA(tempreg, 5b)			;\
   andi tempreg,tempreg,~(3)		;\
    sub rd,rd,tempreg			;\
    RVTEST_SIGUPD(swreg,rd,offset)
//SREG rd, offset(swreg);

#define TEST_BRANCH_OP(inst, tempreg, reg1, reg2, val1, val2, imm, label, swreg, offset,adj) \
    LI(reg1, MASK_XLEN(val1))		;\
    LI(reg2, MASK_XLEN(val2))		;\
    addi tempreg,x0,0			;\
    j 2f				;\
					;\
1:  .if adj & 2 == 2			;\
    .fill 2,1,0x00			;\
    .endif				;\
    addi tempreg,tempreg, 0x1		;\
    j 4f				;\
    .if adj & 2 == 2			;\
    .fill 2,1,0x00			;\
    .endif				;\
    .if (imm/2) - 2 >= 0		;\
	.set num,(imm/2)-2		;\
    .else				;\
	.set num,0			;\
    .endif				;\
     .ifc label, 3f			;\
	.set num,0			;\
    .endif				;\
    .rept num				;\
    nop					;\
    .endr				;\
					;\
2:  inst reg1, reg2, label+adj		;\
    addi tempreg, tempreg,0x2		;\
    j 4f				;\
    .if (imm/4) - 3 >= 0		;\
	.set num,(imm/4)-3		;\
    .else				;\
	.set num,0			;\
    .endif				;\
     .ifc label, 1b			;\
	.set num,0			;\
    .endif				;\
    .rept num				;\
    nop					;\
    .endr				;\
					;\
3:  .if adj & 2 == 2			;\
    .fill 2,1,0x00			;\
    .endif				;\
    addi tempreg, tempreg,0x3		;\
    j 4f				;\
    .if adj&2 == 2			;\
    .fill 2,1,0x00			;\
    .endif				;\
					;\
4:   RVTEST_SIGUPD(swreg,tempreg,offset)


#define TEST_STORE(swreg,testreg,index,rs1,rs2,rs2_val,imm_val,offset,inst,adj)	;\
LI(rs2,rs2_val)				;\
addi rs1,swreg,offset+adj		;\
LI(testreg,imm_val)			;\
sub rs1,rs1,testreg			;\
inst rs2, imm_val(rs1)			;\
nop					;\
nop

#define TEST_LOAD(swreg,testreg,index,rs1,destreg,imm_val,offset,inst,adj);\
LA(rs1,rvtest_data+(index*4)+adj-imm_val);\
inst destreg, imm_val(rs1)		;\
nop					;\
nop					;\
RVTEST_SIGUPD(swreg,destreg,offset)

#define TEST_STORE_F(swreg,testreg,fcsr_val,rs1,rs2,imm_val,offset,inst,adj,flagreg,valaddr_reg, val_offset);\
LOAD_MEM_VAL(FLREG, valaddr_reg, rs2, val_offset, testreg);\
addi rs1,swreg,offset+adj		;\
LI(testreg,imm_val)			;\
sub rs1,rs1,testreg			;\
inst rs2, imm_val(rs1)			;\
nop					;\
nop					;\
csrr flagreg, fcsr			;\
RVTEST_SIGUPD(swreg,flagreg,offset+SIGALIGN)

#define TEST_LOAD_F(swreg,testreg,fcsr_val,rs1,destreg,imm_val,inst,adj,flagreg)	;\
LA(rs1,rvtest_data+adj-imm_val)		;\
LI(testreg, fcsr_val)			;\
csrw fcsr, testreg			;\
inst destreg, imm_val(rs1)		;\
nop					;\
nop					;\
csrr flagreg, fcsr			;\
RVTEST_SIGUPD_F(swreg,destreg,flagreg)

#define TEST_CBO_ZERO(swreg,rs1,inst,imm_val)                               ;\
LI(rs1,imm_val&(RVMODEL_CBZ_BLOCKSIZE-1))                                   ;\
add rs1,rs1,swreg                                                           ;\
inst (rs1)                                                                  ;\
nop                                                                         ;\
nop                                                                         ;\
ADDI(swreg, swreg, RVMODEL_CBZ_BLOCKSIZE)

#define TEST_CSR_FIELD(ADDRESS,TEMP_REG,MASK_REG,NEG_MASK_REG,VAL,DEST_REG,OFFSET,BASE_REG) ;\
    LI(TEMP_REG,VAL)			;\
    and TEMP_REG,TEMP_REG,MASK_REG	;\
    csrr DEST_REG,ADDRESS		;\
    and DEST_REG,DEST_REG,NEG_MASK_REG	;\
    or TEMP_REG,TEMP_REG,DEST_REG	;\
    csrw ADDRESS,TEMP_REG		;\
    csrr DEST_REG,ADDRESS		;\
    RVTEST_SIGUPD(BASE_REG,DEST_REG,OFFSET)


#define TEST_CASE(testreg, destreg, correctval, swreg, offset, code... )	;\
    code				;\
    RVTEST_SIGUPD(swreg,destreg,offset)	;\
    RVMODEL_IO_ASSERT_GPR_EQ(testreg, destreg, correctval)

#define TEST_CASE_F(testreg, destreg, correctval, swreg, flagreg, code... )	;\
    code					;\
    RVTEST_SIGUPD_F(swreg,destreg,flagreg)	;\
#if FLEN==32 \
    RVMODEL_IO_ASSERT_SFPR_EQ(testreg, destreg, correctval);\
#elif FLEN==64 \
    RVMODEL_IO_ASSERT_DFPR_EQ(testreg, destreg, correctval);\
#endif

#define TEST_CASE_FID(testreg, destreg, correctval, swreg, flagreg, code... )	;\
    code; \
    RVTEST_SIGUPD_FID(swreg,destreg,flagreg)	;\
    RVMODEL_IO_ASSERT_GPR_EQ(testreg, destreg, correctval)

#define TEST_AUIPC(inst, destreg, correctval, imm, swreg, offset, testreg)	;\
    TEST_CASE(testreg, destreg, correctval, swreg, offset, \
      LA testreg, 1f			;\
      1:				;\
      inst destreg, imm			;\
      sub destreg, destreg, testreg	;\
      )

//Tests for instructions with register-immediate operand
#define TEST_IMM_OP( inst, destreg, reg, correctval, val, imm, swreg, offset, testreg)	;\
    TEST_CASE(testreg, destreg, correctval, swreg, offset,	 ;\
      LI(reg, MASK_XLEN(val))		;\
      inst destreg, reg, SEXT_IMM(imm)	;\
    )

//Tests for floating-point instructions with a single register operand
#define TEST_FPSR_OP( inst, destreg, freg, rm, fcsr_val, correctval, valaddr_reg, val_offset, flagreg, swreg, testreg) \
    TEST_CASE_F(testreg, destreg, correctval, swreg, flagreg, \
      LOAD_MEM_VAL(FLREG, valaddr_reg, freg, val_offset, testreg); \
      LI(testreg, fcsr_val)	;\
      csrw fcsr, testreg	;\
      inst destreg, freg, rm	;\
      csrr flagreg, fcsr	;\
    )

//Tests for floating-point instructions with a single register operand
//This variant does not take the rm field and set it while writing the instruction
#define TEST_FPSR_OP_NRM( inst, destreg, freg, fcsr_val, correctval, valaddr_reg, val_offset, flagreg, swreg, testreg) \
    TEST_CASE_F(testreg, destreg, correctval, swreg, flagreg,		 \
      LOAD_MEM_VAL(FLREG, valaddr_reg, freg, val_offset, testreg)	;\
      li testreg, fcsr_val; csrw fcsr, testreg	;\
      inst destreg, freg			;\
      csrr flagreg, fcsr			;\
    )

//Tests for floating-point instructions with a single register operand and integer destination register
#define TEST_FPID_OP( inst, destreg, freg, rm, fcsr_val, correctval, valaddr_reg, val_offset, flagreg, swreg, testreg,load_instr) \
    TEST_CASE_FID(testreg, destreg, correctval, swreg, flagreg,		 \
      LOAD_MEM_VAL(load_instr, valaddr_reg, freg, val_offset, testreg)	;\
      li testreg, fcsr_val; csrw fcsr, testreg	;\
      inst destreg, freg, rm			;\
      csrr flagreg, fcsr			;\
      )

//Tests for floating-point instructions with a single register operand and integer operand register
#define TEST_FPIO_OP( inst, destreg, freg, rm, fcsr_val, correctval, valaddr_reg, val_offset, flagreg, swreg, testreg, load_instr) \
    TEST_CASE_F(testreg, destreg, correctval, swreg, flagreg,		 \
      LOAD_MEM_VAL(load_instr, valaddr_reg, freg, val_offset, testreg)	;\
      li testreg, fcsr_val; csrw fcsr, testreg	;\
      inst destreg, freg, rm			;\
      csrr flagreg, fcsr			;\
    )

//Tests for floating-point instructions with a single register operand and integer destination register
//This variant does not take the rm field and set it while writing the instruction
#define TEST_FPID_OP_NRM( inst, destreg, freg, fcsr_val, correctval, valaddr_reg, val_offset, flagreg, swreg, testreg) \
    TEST_CASE_FID(testreg, destreg, correctval, swreg, flagreg,		 \
      LOAD_MEM_VAL(FLREG, valaddr_reg, freg, val_offset, testreg)	;\
      li testreg, fcsr_val; csrw fcsr, testreg	;\
      inst destreg, freg			;\
      csrr flagreg, fcsr			;\
      )

//Tests for floating-point instructions with a single register operand and integer operand register
//This variant does not take the rm field and set it while writing the instruction
#define TEST_FPIO_OP_NRM( inst, destreg, freg, fcsr_val, correctval, valaddr_reg, val_offset, flagreg, swreg, testreg, load_instr) \
    TEST_CASE_F(testreg, destreg, correctval, swreg, flagreg,		 \
      LOAD_MEM_VAL(load_instr, valaddr_reg, freg, val_offset, testreg)	;\
      li testreg, fcsr_val; csrw fcsr, testreg	;\
      inst destreg, freg			;\
      csrr flagreg, fcsr			;\
    )

//Tests for instructions with register-register-immediate operands
#define TEST_RRI_OP(inst, destreg, reg1, reg2, imm, correctval, val1, val2, swreg, offset, testreg) \
    TEST_CASE(testreg, destreg, correctval, swreg, offset, \
      LI(reg1, MASK_XLEN(val1))			;\
      LI(reg2, MASK_XLEN(val2))			;\
      inst destreg, reg1, reg2, imm		;\
    )


//Tests for a instructions with register-register operand
#define TEST_RR_OP(inst, destreg, reg1, reg2, correctval, val1, val2, swreg, offset, testreg) \
    TEST_CASE(testreg, destreg, correctval, swreg, offset, \
      LI(reg1, MASK_XLEN(val1))			;\
      LI(reg2, MASK_XLEN(val2))			;\
      inst destreg, reg1, reg2			;\
    )
//Tests for a instructions with single-register operand
#define TEST_R_OP(inst, destreg, reg1, correctval, val1, swreg, offset, testreg) \
    TEST_CASE(testreg, destreg, correctval, swreg, offset, \
      LI(reg1, MASK_XLEN(val1))			;\
      inst destreg, reg1    			;\
    )
//Tests for floating-point instructions with register-register operand
//This variant does not take the rm field and set it while writing the instruction
#define TEST_FPRR_OP_NRM(inst, destreg, freg1, freg2, fcsr_val, correctval, valaddr_reg, val_offset, flagreg, swreg, testreg) \
    TEST_CASE_F(testreg, destreg, correctval, swreg, flagreg,			 \
      LOAD_MEM_VAL(FLREG, valaddr_reg, freg1, val_offset, testreg)		;\
      LOAD_MEM_VAL(FLREG, valaddr_reg, freg2, (val_offset+FREGWIDTH), testreg)	;\
      li testreg, fcsr_val; csrw fcsr, testreg	;\
      inst destreg, freg1, freg2		;\
      csrr flagreg, fcsr			;\
    )

//Tests for floating-point instructions with register-register operand
#define TEST_FPRR_OP(inst, destreg, freg1, freg2, rm, fcsr_val, correctval, valaddr_reg, val_offset, flagreg, swreg, testreg) \
    TEST_CASE_F(testreg, destreg, correctval, swreg, flagreg,			\
      LOAD_MEM_VAL(FLREG, valaddr_reg, freg1, val_offset, testreg)		;\
      LOAD_MEM_VAL(FLREG, valaddr_reg, freg2, (val_offset+FREGWIDTH), testreg)	;\
      li testreg, fcsr_val; csrw fcsr, testreg	;\
      inst destreg, freg1, freg2, rm		;\
      csrr flagreg, fcsr			;\
    )

//Tests for floating-point CMP instructions with register-register operand
#define TEST_FCMP_OP(inst, destreg, freg1, freg2, fcsr_val, correctval, valaddr_reg, val_offset, flagreg, swreg, testreg) \
    TEST_CASE_FID(testreg, destreg, correctval, swreg, flagreg,			 \
      LOAD_MEM_VAL(FLREG, valaddr_reg, freg1, val_offset, testreg)		;\
      LOAD_MEM_VAL(FLREG, valaddr_reg, freg2, (val_offset+FREGWIDTH), testreg)	;\
      li testreg, fcsr_val; csrw fcsr, testreg	;\
      inst destreg, freg1, freg2		;\
      csrr flagreg, fcsr			;\
    )

//Tests for floating-point R4 type instructions
#define TEST_FPR4_OP(inst, destreg, freg1, freg2, freg3, rm , fcsr_val, correctval, valaddr_reg, val_offset, flagreg, swreg, testreg) \
    TEST_CASE_F(testreg, destreg, correctval, swreg, flagreg,			\
      LOAD_MEM_VAL(FLREG, valaddr_reg, freg1, val_offset, testreg)		;\
      LOAD_MEM_VAL(FLREG, valaddr_reg, freg2, (val_offset+FREGWIDTH), testreg)	;\
      LOAD_MEM_VAL(FLREG, valaddr_reg, freg3, (val_offset+2*FREGWIDTH), testreg);\
      li testreg, fcsr_val; csrw fcsr, testreg	;\
      inst destreg, freg1, freg2, freg3, rm	;\
      csrr flagreg, fcsr			;\
    )

#define TEST_CNOP_OP( inst, testreg, imm_val, swreg, offset) \
    TEST_CASE(testreg, x0, 0, swreg, offset,	 \
      inst imm_val				;\
      )

//Tests c.mop.* instructions
#define TEST_CMOP_OP(inst, destreg, imm_val, swreg, testreg, offset) \
    TEST_CASE(testreg, destreg, imm_val, swreg, offset,	 \
      mv destreg, swreg; \
      inst;                \
      )

//Tests for instructions with register-immediate operand and update the saturation flag
#define TEST_PKIMM_OP( inst, destreg, reg, correctval, val, imm, flagreg, swreg, offset, testreg) \
    TEST_CASE(testreg, destreg, correctval, swreg, offset, \
      LI(reg, MASK_XLEN(val))		;\
      inst destreg, reg, SEXT_IMM(imm)	;\
      rdov flagreg			;\
    )

//Tests for instructions with register-register operand and update the saturation flag
#define TEST_PKRR_OP(inst, destreg, reg1, reg2, correctval, val1, val2, flagreg, swreg, offset, testreg) \
    LI(reg1, MASK_XLEN(val1))		;\
    LI(reg2, MASK_XLEN(val2))		;\
    inst destreg, reg1, reg2		;\
    rdov flagreg			;\
    RVTEST_SIGUPD_PK(swreg, destreg, flagreg, offset)	;\
    RVMODEL_IO_ASSERT_GPR_EQ(testreg, destreg, correctval)

//Tests for instructions with a single register operand and update the saturation flag
#define TEST_PKR_OP( inst, destreg, reg, correctval, val, flagreg, swreg, offset, testreg) \
    LI(reg, MASK_XLEN(val))	;\
    inst destreg, reg		;\
    rdov flagreg		;\
    RVTEST_SIGUPD_PK(swreg,destreg,flagreg,offset)	;\
    RVMODEL_IO_ASSERT_GPR_EQ(testreg, destreg, correctval)

#if __riscv_xlen == 32
//Tests for a instruction with register pair operands for all its three operands
#define TEST_P64_PPP_OP_32(inst, destreg, destreg_hi, reg1, reg1_hi, reg2, reg2_hi, correctval, correctval_hi, val1, val1_hi, val2, val2_hi, swreg, offset, testreg) \
      LI(reg1, MASK_XLEN(val1))		;\
      LI(reg1_hi, MASK_XLEN(val1_hi))	;\
      LI(reg2, MASK_XLEN(val2))		;\
      LI(reg2_hi, MASK_XLEN(val2_hi))	;\
      inst destreg, reg1, reg2		;\
      RVTEST_SIGUPD_P64(swreg,destreg, destreg_hi, offset)	;\
      RVMODEL_IO_ASSERT_GPR_EQ(testreg, destreg, correctval)	;\
      RVMODEL_IO_ASSERT_GPR_EQ(testreg, destreg_hi, correctval_hi)

#define TEST_PK64_PPP_OP_32(inst, destreg, destreg_hi, reg1, reg1_hi, reg2, reg2_hi, correctval, correctval_hi, val1, val1_hi, val2, val2_hi, flagreg, swreg, offset, testreg) \
      LI(reg1, MASK_XLEN(val1))		;\
      LI(reg1_hi, MASK_XLEN(val1_hi))	;\
      LI(reg2, MASK_XLEN(val2))		;\
      LI(reg2_hi, MASK_XLEN(val2_hi))	;\
      inst destreg, reg1, reg2		;\
      RVTEST_SIGUPD_PK64(swreg,destreg, destreg_hi, flagreg, offset)	;\
      RVMODEL_IO_ASSERT_GPR_EQ(testreg, destreg, correctval)		;\
      RVMODEL_IO_ASSERT_GPR_EQ(testreg, destreg_hi, correctval_hi)

#define TEST_P64_PPN_OP_32(inst, destreg, destreg_hi, reg1, reg1_hi, reg2, correctval, correctval_hi, val1, val1_hi, val2, swreg, offset, testreg) \
      LI(reg1, MASK_XLEN(val1))		;\
      LI(reg1_hi, MASK_XLEN(val1_hi))	;\
      LI(reg2, MASK_XLEN(val2))		;\
      inst destreg, reg1, reg2		;\
      RVTEST_SIGUPD_P64(swreg, destreg, destreg_hi, offset)	;\
      RVMODEL_IO_ASSERT_GPR_EQ(testreg, destreg, correctval)	;\
      RVMODEL_IO_ASSERT_GPR_EQ(testreg, destreg_hi, correctval_hi)

#define TEST_P64_PNN_OP_32(inst, destreg, destreg_hi, reg1, reg2, correctval, correctval_hi, val1, val2, swreg, offset, testreg) \
      LI(reg1, MASK_XLEN(val1))		;\
      LI(reg2, MASK_XLEN(val2))		;\
      inst destreg, reg1, reg2		;\
      RVTEST_SIGUPD_P64(swreg, destreg, destreg_hi, offset)	;\
      RVMODEL_IO_ASSERT_GPR_EQ(testreg, destreg, correctval)	;\
      RVMODEL_IO_ASSERT_GPR_EQ(testreg, destreg_hi, correctval_hi)

#define TEST_PK64_PNN_OP_32(inst, destreg, destreg_hi, reg1, reg2, correctval, correctval_hi, val1, val2, flagreg, swreg, offset, testreg) \
      LI(reg1, MASK_XLEN(val1))		;\
      LI(reg2, MASK_XLEN(val2))		;\
      inst destreg, reg1, reg2		;\
      RVTEST_SIGUPD_PK64(swreg, destreg, destreg_hi, flagreg, offset)	;\
      RVMODEL_IO_ASSERT_GPR_EQ(testreg, destreg, correctval)		;\
      RVMODEL_IO_ASSERT_GPR_EQ(testreg, destreg_hi, correctval_hi)

#define TEST_P64_NPN_OP_32(inst, destreg, reg1, reg1_hi, reg2, correctval, val1, val1_hi, val2, swreg, offset, testreg) \
      LI(reg1, MASK_XLEN(val1))			;\
      LI(reg1_hi, MASK_XLEN(val1_hi))		;\
      LI(reg2, MASK_XLEN(val2))			;\
      inst destreg, reg1, reg2			;\
      RVTEST_SIGUPD(swreg,destreg,offset)	;\
      RVMODEL_IO_ASSERT_GPR_EQ(testreg, destreg, correctval);

#define TEST_P64_NP_OP_32(inst, destreg, reg1, reg1_hi, correctval, val1, val1_hi, imm_val, swreg, offset, testreg) \
      LI(reg1, MASK_XLEN(val1))			;\
      LI(reg1_hi, MASK_XLEN(val1_hi))		;\
      inst destreg, reg1, imm_val		;\
      RVTEST_SIGUPD(swreg,destreg,offset)	;\
      RVMODEL_IO_ASSERT_GPR_EQ(testreg, destreg, correctval);

//Tests for a instruction with pair register rd, pair register rs1 and pair register rs2
#define TEST_P64_PPP_OP(inst, rd, rd_hi, rs1, rs1_hi, rs2, rs2_hi, correctval, correctval_hi, rs1_val, rs1_val_hi, rs2_val, rs2_val_hi, swreg, offset, testreg) \
    TEST_P64_PPP_OP_32(inst, rd, rd_hi, rs1, rs1_hi, rs2, rs2_hi, correctval, correctval_hi, rs1_val, rs1_val_hi, rs2_val, rs2_val_hi, swreg, offset, testreg)
#define TEST_PK64_PPP_OP(inst, rd, rd_hi, rs1, rs1_hi, rs2, rs2_hi, correctval, correctval_hi, rs1_val, rs1_val_hi, rs2_val, rs2_val_hi, flagreg, swreg, offset, testreg) \
    TEST_PK64_PPP_OP_32(inst, rd, rd_hi, rs1, rs1_hi, rs2, rs2_hi, correctval, correctval_hi, rs1_val, rs1_val_hi, rs2_val, rs2_val_hi, flagreg, swreg, offset, testreg)
//Tests for a instruction with pair register rd, pair register rs1 and normal register rs2
#define TEST_P64_PPN_OP(inst, rd, rd_hi, rs1, rs1_hi, rs2, correctval, correctval_hi, rs1_val, rs1_val_hi, rs2_val, swreg, offset, testreg) \
    TEST_P64_PPN_OP_32(inst, rd, rd_hi, rs1, rs1_hi, rs2, correctval, correctval_hi, rs1_val, rs1_val_hi, rs2_val, swreg, offset, testreg)
//Tests for a instruction with pair register rd, normal register rs1 and normal register rs2
#define TEST_P64_PNN_OP(inst, rd, rd_hi, rs1, rs2, correctval, correctval_hi, rs1_val, rs2_val, swreg, offset, testreg) \
    TEST_P64_PNN_OP_32(inst, rd, rd_hi, rs1, rs2, correctval, correctval_hi, rs1_val, rs2_val, swreg, offset, testreg)
//Tests for a instruction with pair register rd, normal register rs1 and normal register rs2
#define TEST_PK64_PNN_OP(inst, rd, rd_hi, rs1, rs2, correctval, correctval_hi, rs1_val, rs2_val, flagreg, swreg, offset, testreg) \
    TEST_PK64_PNN_OP_32(inst, rd, rd_hi, rs1, rs2, correctval, correctval_hi, rs1_val, rs2_val, flagreg, swreg, offset, testreg)
//Tests for a instruction with normal register rd, pair register rs1 and normal register rs2
#define TEST_P64_NPN_OP(inst, rd, rs1, rs1_hi, rs2, correctval, correctval_hi, rs1_val, rs1_val_hi, rs2_val, swreg, offset, testreg) \
    TEST_P64_NPN_OP_32(inst, rd, rs1, rs1_hi, rs2, correctval, correctval_hi, rs1_val, rs1_val_hi, rs2_val, swreg, offset, testreg)
//Tests for a instruction with normal register rd, pair register rs1
#define TEST_P64_NP_OP(inst, rd, rs1, rs1_hi, correctval, correctval_hi, rs1_val, rs1_val_hi, imm_val, swreg, offset, testreg) \
    TEST_P64_NP_OP_32(inst, rd, rs1, rs1_hi, correctval, correctval_hi, rs1_val, rs1_val_hi, imm_val, swreg, offset, testreg)

#else

// When in rv64, there are no instructions with pair operand, so Macro is redefined to normal TEST_RR_OP
#define TEST_P64_PPP_OP(inst, rd, rd_hi, rs1, rs1_hi, rs2, rs2_hi, correctval, correctval_hi, rs1_val, rs1_val_hi, rs2_val, rs2_val_hi, swreg, offset, testreg) \
    TEST_RR_OP(inst, rd, rs1, rs2, correctval, rs1_val, rs2_val, swreg, offset, testreg)
#define TEST_PK64_PPP_OP(inst, rd, rd_hi, rs1, rs1_hi, rs2, rs2_hi, correctval, correctval_hi, rs1_val, rs1_val_hi, rs2_val, rs2_val_hi, flagreg, swreg, offset, testreg) \
    TEST_PKRR_OP(inst, rd, rs1, rs2, correctval, rs1_val, rs2_val, flagreg, swreg, offset, testreg)
#define TEST_P64_PPN_OP(inst, rd, rd_hi, rs1, rs1_hi, rs2, correctval, correctval_hi, rs1_val, rs1_val_hi, rs2_val, swreg, offset, testreg) \
    TEST_RR_OP(inst, rd, rs1, rs2, correctval, rs1_val, rs2_val, swreg, offset, testreg)
#define TEST_P64_PNN_OP(inst, rd, rd_hi, rs1, rs2, correctval, correctval_hi, rs1_val, rs2_val, swreg, offset, testreg) \
    TEST_RR_OP(inst, rd, rs1, rs2, correctval, rs1_val, rs2_val, swreg, offset, testreg)
#define TEST_PK64_PNN_OP(inst, rd, rd_hi, rs1, rs2, correctval, correctval_hi, rs1_val, rs2_val, flagreg, swreg, offset, testreg) \
    TEST_PKRR_OP(inst, rd, rs1, rs2, correctval, rs1_val, rs2_val, flagreg, swreg, offset, testreg)
#define TEST_P64_NPN_OP(inst, rd, rs1, rs1_hi, rs2, correctval, correctval_hi, rs1_val, rs1_val_hi, rs2_val, swreg, offset, testreg) \
    TEST_RR_OP(inst, rd, rs1, rs2, correctval, rs1_val, rs2_val, swreg, offset, testreg)
#define TEST_P64_NP_OP(inst, rd, rs1, rs1_hi, correctval, correctval_hi, rs1_val, rs1_val_hi, imm_val, swreg, offset, testreg) \
    TEST_IMM_OP(inst, rd, rs1, correctval, rs1_val, imm_val, swreg, offset, testreg)

#endif




#define TEST_CMV_OP( inst, destreg, reg, correctval, val2, swreg, offset, testreg) \
    TEST_CASE(testreg, destreg, correctval, swreg, offset, \
      LI(reg, MASK_XLEN(val2))		;\
      inst destreg, reg			;\
      )

#define TEST_CR_OP( inst, destreg, reg, correctval, val1, val2, swreg, offset, testreg) \
    TEST_CASE(testreg, destreg, correctval, swreg, offset, \
      LI(reg, MASK_XLEN(val2))		;\
      LI(destreg, MASK_XLEN(val1))	;\
      inst destreg, reg			;\
      )

#define TEST_CI_OP( inst, destreg, correctval, val, imm, swreg, offset, testreg) \
    TEST_CASE(testreg, destreg, correctval, swreg, offset, \
      LI(destreg, MASK_XLEN(val))	;\
      inst destreg, imm			;\
      )

#define TEST_CADDI4SPN_OP( inst, destreg, correctval, imm, swreg, offset, testreg) \
    TEST_CASE(testreg, destreg, correctval, swreg, offset, \
      LI(x2, 0)				;\
      inst destreg, x2,imm		;\
      )

//Tests for instructions with single (rd/rs1) register operand.
#define TEST_CRD_OP(inst, destreg, correctval, val1, swreg, offset, testreg) \
    TEST_CASE(testreg, destreg, correctval, swreg, offset, \
      LI(destreg, MASK_XLEN(val1))		;\
      inst destreg		;\
      )

//Tests for instructions with a destination and single source register operand
#define TEST_RD_OP(inst, destreg, reg1, correctval, val1, swreg, offset, testreg) \
  TEST_CMV_OP(inst, destreg, reg1, correctval, val1, swreg, offset, testreg)

#define TEST_CBRANCH_OP(inst, tempreg, reg2, val2, imm, label, swreg, offset) \
    LI(reg2, MASK_XLEN(val2))		;\
    j 2f				;\
    addi tempreg, x0,0			;\
    .option push			;\
    .option norvc			;\
1:  addi tempreg, tempreg,0x1		;\
    j 4f				;\
    .option pop				;\
    .if (imm/2) - 4 >= 0		;\
	.set num,(imm/2)-4		;\
    .else				;\
	.set num,0			;\
    .endif				;\
    .ifc label, 3f			;\
	.set num,0			;\
    .endif				;\
    .rept num				;\
    c.nop				;\
    .endr				;\
2:  inst reg2, label			;\
    .option push			;\
    .option norvc			;\
    addi tempreg, tempreg, 0x2		;\
    j 4f				;\
    .option pop				;\
    .if (imm/2) - 5 >= 0		;\
	.set num,(imm/2)-5		;\
    .else				;\
	.set num,0			;\
    .endif				;\
     .ifc label, 1b			;\
	.set num,0			;\
    .endif				;\
    .rept num				;\
    c.nop				;\
    .endr				;\
					;\
3:  addi tempreg, tempreg ,0x3		;\
					;\
4:  RVTEST_SIGUPD(swreg,tempreg,offset)

#define TEST_CJ_OP(inst, tempreg, imm, label, swreg, offset) \
    .option push			;\
    .option norvc			;\
    j 2f				;\
    addi tempreg,x0,0			;\
1:  addi tempreg, tempreg,0x1		;\
    j 4f				;\
    .option pop				;\
    .if (imm/2) - 4 >= 0		;\
	.set num,(imm/2)-4		;\
    .else				;\
	.set num,0			;\
    .endif				;\
    .ifc label, 3f			;\
	.set num,0			;\
    .endif				;\
    .rept num				;\
    c.nop				;\
    .endr				;\
2:  inst label				;\
    .option push			;\
    .option norvc			;\
    addi tempreg, tempreg, 0x2		;\
    j 4f				;\
    .option pop				;\
    .if (imm/2) - 5 >= 0		;\
	.set num,(imm/2)-5		;\
    .else				;\
	.set num,0			;\
    .endif				;\
     .ifc label, 1b			;\
	.set num,0			;\
    .endif				;\
    .rept num				;\
    c.nop				;\
    .endr				;\
					;\
3:  addi tempreg, tempreg, 0x3		;\
					;\
4:  RVTEST_SIGUPD(swreg,tempreg,offset)

#define TEST_CJAL_OP(inst, tempreg, imm, label, swreg, offset) \
5:					;\
    j 2f				;\
					;\
    .option push			;\
    .option norvc			;\
1:  xori x1,x1, 0x1			;\
    j 4f				;\
    .option pop				;\
    .if (imm/2) - 4 >= 0		;\
	.set num,(imm/2)-4		;\
    .else				;\
	.set num,0			;\
    .endif				;\
    .ifc label, 3f			;\
	.set num,0			;\
    .endif				;\
    .rept num				;\
    c.nop				;\
    .endr				;\
2:  inst label				;\
    .option push			;\
    .option norvc			;\
    xori x1,x1, 0x2			;\
    j 4f				;\
    .option pop				;\
    .if (imm/2) - 5 >= 0		;\
	.set num,(imm/2)-5		;\
    .else				;\
	.set num,0			;\
    .endif				;\
     .ifc label, 1b			;\
	.set num,0			;\
    .endif				;\
    .rept num				;\
    c.nop				;\
    .endr				;\
					;\
3:  xori x1,x1, 0x3			;\
					;\
4: LA(tempreg, 5b)			;\
   andi tempreg,tempreg,~(3)		;\
    sub x1,x1,tempreg			;\
  RVTEST_SIGUPD(swreg,x1,offset)

#define TEST_CJR_OP(tempreg, rs1, swreg, offset) \
5:					;\
    LA(rs1, 3f)				;\
					;\
2:  c.jr rs1				;\
    xori rs1,rs1, 0x2			;\
    j 4f				;\
					;\
3:  xori rs1,rs1, 0x3			;\
					;\
4: LA(tempreg, 5b)			;\
   andi tempreg,tempreg,~(3)		;\
    sub rs1,rs1,tempreg			;\
    RVTEST_SIGUPD(swreg,rs1,offset)

#define TEST_CJALR_OP(tempreg, rs1, swreg, offset) \
5:					;\
    LA(rs1, 3f)				;\
					;\
2:  c.jalr rs1				;\
    xori x1,x1, 0x2			;\
    j 4f				;\
					;\
3:  xori x1,x1, 0x3			;\
					;\
4: LA(tempreg, 5b)			;\
   andi tempreg,tempreg,~(3)		;\
    sub x1,x1,tempreg			;\
    RVTEST_SIGUPD(swreg,x1,offset)


// for updating signatures of Zacas paired destination register (RV32/RV64).
#define RVTEST_SIGUPD_PZACAS(_BR,_R1,_R2,...)		;\
  .if NARG(__VA_ARGS__) == 1				;\
      .set offset,_ARG1(__VA_OPT__(__VA_ARGS__,0))	;\
  .endif						;\
  .if (offset & (REGWIDTH-1)) != 0			;\
/*      .warning "Signature Incorrect Offset Alignment."	*/;\
     .set offset, offset&(SIGALIGN-1)+SIGALIGN		;\
  .endif						;\
      CHK_OFFSET(_BR,REGWIDTH,0)			;\
      SREG _R1,offset(_BR)				;\
      CHK_OFFSET(_BR,REGWIDTH,1)			;\
      SREG _R2,offset(_BR)				;\
      .set offset,offset+(REGWIDTH)

// Tests for a AMOCAS where operation width is <= xlen
// First store a value that will cause a mismatch on cas
// Test a failing amocas followed by a successful amocas
#define TEST_CAS_OP(inst, rd, rs1, rs2, swap_val, sigptr, offset) \
    LI(rd, swap_val);\
    neg rd, rd;\
    LA(rs1, rvtest_data);\
    SREG rd, (rs1);\
    LI(rd, swap_val);\
    LI(rs2, swap_val);\
    LA(rs1, rvtest_data);\
    inst rd, rs2, (rs1);\
    inst rd, rs2, (rs1);\
    RVTEST_SIGUPD(sigptr,rd,offset);

// Tests for a AMOCAS where operation width is <= xlen
// First store a value that will cause a mismatch on cas
// Test a failing amocas followed by a successful amocas
#define TEST_DCAS_OP(inst, rd, rd_hi, rs1, rs2, rs2_hi, swap_val, swap_val_hi, sigptr, offset) \
    LA(rs1, rvtest_data);\
    LI(rd, swap_val);\
    neg rd, rd;\
    SREG rd, (rs1);\
    LI(rd, swap_val_hi);\
    neg rd, rd;\
    SREG rd, (__riscv_xlen/8)(rs1);\
    LI(rd, swap_val);\
    LI(rd_hi, swap_val_hi);\
    LI(rs2, swap_val);\
    LI(rs2_hi, swap_val_hi);\
    LA(rs1, rvtest_data);\
    inst rd, rs2, (rs1);\
    LA(rs1, rvtest_data);\
    inst rd, rs2, (rs1);\
    RVTEST_SIGUPD_PZACAS(sigptr,rd,rd_hi,offset);

//--------------------------------- Migration aliases ------------------------------------------
#ifdef RV_COMPLIANCE_RV32M
  #warning "RV_COMPLIANCE_RV32M macro will be deprecated."
  #define RVMODEL_BOOT	 \
    RVTEST_IO_INIT	;\
    RV_COMPLIANCE_RV32M ;\
    RV_COMPLIANCE_CODE_BEGIN
#endif

#define SWSIG(a, b)

#ifdef RV_COMPLIANCE_DATA_BEGIN
  #warning "RV_COMPLIANCE_DATA_BEGIN macro deprecated in v0.2. Please use RVMODEL_DATA_BEGIN instead"
  #define RVMODEL_DATA_BEGIN \
    RV_COMPLIANCE_DATA_BEGIN
#endif

#ifdef RV_COMPLIANCE_DATA_END
  #warning "RV_COMPLIANCE_DATA_END macro deprecated in v0.2. Please use RVMODEL_DATA_END instead"
  #define RVMODEL_DATA_END \
    RV_COMPLIANCE_DATA_END
#endif

#ifdef RV_COMPLIANCE_HALT
  #warning "RV_COMPLIANCE_HALT macro deprecated in v0.2. Please use RVMODEL_HALT instead"
  #define RVMODEL_HALT \
    RV_COMPLIANCE_HALT
#endif

#ifdef RVTEST_IO_ASSERT_GPR_EQ
  #warning "RVTEST_IO_ASSERT_GPR_EQ macro deprecated in v0.2. Please use RVMODEL_IO_ASSERT_GPR_EQ instead"
  #define RVMODEL_IO_ASSERT_GPR_EQ(_SP, _R, _I) \
    RVTEST_IO_ASSERT_GPR_EQ(_SP,_R, _I)
#endif

#ifdef RVTEST_IO_WRITE_STR
  #warning "RVTEST_IO_WRITE_STR macro deprecated in v0.2. Please use RVMODEL_IO_WRITE_STR instead"
  #define RVMODEL_IO_WRITE_STR(_SP, _STR) \
    RVTEST_IO_WRITE_STR(_SP, _STR)
#endif

#ifdef RVTEST_IO_INIT
  #warning "RVTEST_IO_INIT is deprecated in v0.2. Please use RVMODEL_BOOT for initialization"
#endif

#ifdef RVTEST_IO_CHECK
  #warning "RVTEST_IO_CHECK is deprecated in v0.2.
#endif
