///////////////////////////////////////////
//
// RISC-V Architectural Functional Coverage Covergroups
// 
// Copyright (C) 2024 Harvey Mudd College, 10x Engineers, UET Lahore, Habib University
//
// SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
//
// Licensed under the Solderpad Hardware License v 2.1 (the “License”); you may not use this file 
// except in compliance with the License, or, at your option, the Apache License version 2.0. You 
// may obtain a copy of the License at
//
// https://solderpad.org/licenses/SHL-2.1/
//
// Unless required by applicable law or agreed to in writing, any work distributed under the 
// License is distributed on an “AS IS” BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, 
// either express or implied. See the License for the specific language governing permissions 
// and limitations under the License.
////////////////////////////////////////////////////////////////////////////////////////////////

`define COVER_RV64ZBB
typedef RISCV_instruction #(ILEN, XLEN, FLEN, VLEN, NHART, RETIRE) ins_rv64zbb_t;


covergroup andn_cg with function sample(ins_rv64zbb_t ins);
    option.per_instance = 1; 
    option.comment = "andn";
    cp_asm_count : coverpoint ins.ins_str == "andn"  iff (ins.trap == 0 )  {
        option.comment = "Number of times instruction is executed";
        bins count[]  = {1};
    }
    cp_rd : coverpoint ins.get_gpr_reg(ins.current.rd)  iff (ins.trap == 0 )  {
        option.comment = "RD register assignment";
    }
    cp_rs1 : coverpoint ins.get_gpr_reg(ins.current.rs1)  iff (ins.trap == 0 )  {
        option.comment = "RS1 register assignment";
    }
    cp_rs2 : coverpoint ins.get_gpr_reg(ins.current.rs2)  iff (ins.trap == 0 )  {
        option.comment = "RS2 register assignment";
    }
    cr_rs1_rs2_corners : cross cp_rs1_corners,cp_rs2_corners  iff (ins.trap == 0 )  {
        option.comment = "Cross coverage of RS1 corners and RS2 corners";
    }
endgroup

covergroup clz_cg with function sample(ins_rv64zbb_t ins);
    option.per_instance = 1; 
    option.comment = "clz";
    cp_asm_count : coverpoint ins.ins_str == "clz"  iff (ins.trap == 0 )  {
        option.comment = "Number of times instruction is executed";
        bins count[]  = {1};
    }
    cp_rd : coverpoint ins.get_gpr_reg(ins.current.rd)  iff (ins.trap == 0 )  {
        option.comment = "RD register assignment";
    }
    cp_rs1 : coverpoint ins.get_gpr_reg(ins.current.rs1)  iff (ins.trap == 0 )  {
        option.comment = "RS1 register assignment";
    }
endgroup

covergroup clzw_cg with function sample(ins_rv64zbb_t ins);
    option.per_instance = 1; 
    option.comment = "clzw";
    cp_asm_count : coverpoint ins.ins_str == "clzw"  iff (ins.trap == 0 )  {
        option.comment = "Number of times instruction is executed";
        bins count[]  = {1};
    }
    cp_rd : coverpoint ins.get_gpr_reg(ins.current.rd)  iff (ins.trap == 0 )  {
        option.comment = "RD register assignment";
    }
    cp_rs1 : coverpoint ins.get_gpr_reg(ins.current.rs1)  iff (ins.trap == 0 )  {
        option.comment = "RS1 register assignment";
    }
endgroup

covergroup cpop_cg with function sample(ins_rv64zbb_t ins);
    option.per_instance = 1; 
    option.comment = "cpop";
    cp_asm_count : coverpoint ins.ins_str == "cpop"  iff (ins.trap == 0 )  {
        option.comment = "Number of times instruction is executed";
        bins count[]  = {1};
    }
    cp_rd : coverpoint ins.get_gpr_reg(ins.current.rd)  iff (ins.trap == 0 )  {
        option.comment = "RD register assignment";
    }
    cp_rs1 : coverpoint ins.get_gpr_reg(ins.current.rs1)  iff (ins.trap == 0 )  {
        option.comment = "RS1 register assignment";
    }
endgroup

covergroup cpopw_cg with function sample(ins_rv64zbb_t ins);
    option.per_instance = 1; 
    option.comment = "cpopw";
    cp_asm_count : coverpoint ins.ins_str == "cpopw"  iff (ins.trap == 0 )  {
        option.comment = "Number of times instruction is executed";
        bins count[]  = {1};
    }
    cp_rd : coverpoint ins.get_gpr_reg(ins.current.rd)  iff (ins.trap == 0 )  {
        option.comment = "RD register assignment";
    }
    cp_rs1 : coverpoint ins.get_gpr_reg(ins.current.rs1)  iff (ins.trap == 0 )  {
        option.comment = "RS1 register assignment";
    }
endgroup

covergroup ctz_cg with function sample(ins_rv64zbb_t ins);
    option.per_instance = 1; 
    option.comment = "ctz";
    cp_asm_count : coverpoint ins.ins_str == "ctz"  iff (ins.trap == 0 )  {
        option.comment = "Number of times instruction is executed";
        bins count[]  = {1};
    }
    cp_rd : coverpoint ins.get_gpr_reg(ins.current.rd)  iff (ins.trap == 0 )  {
        option.comment = "RD register assignment";
    }
    cp_rs1 : coverpoint ins.get_gpr_reg(ins.current.rs1)  iff (ins.trap == 0 )  {
        option.comment = "RS1 register assignment";
    }
endgroup

covergroup ctzw_cg with function sample(ins_rv64zbb_t ins);
    option.per_instance = 1; 
    option.comment = "ctzw";
    cp_asm_count : coverpoint ins.ins_str == "ctzw"  iff (ins.trap == 0 )  {
        option.comment = "Number of times instruction is executed";
        bins count[]  = {1};
    }
    cp_rd : coverpoint ins.get_gpr_reg(ins.current.rd)  iff (ins.trap == 0 )  {
        option.comment = "RD register assignment";
    }
    cp_rs1 : coverpoint ins.get_gpr_reg(ins.current.rs1)  iff (ins.trap == 0 )  {
        option.comment = "RS1 register assignment";
    }
endgroup

covergroup max_cg with function sample(ins_rv64zbb_t ins);
    option.per_instance = 1; 
    option.comment = "max";
    cp_asm_count : coverpoint ins.ins_str == "max"  iff (ins.trap == 0 )  {
        option.comment = "Number of times instruction is executed";
        bins count[]  = {1};
    }
    cp_rd : coverpoint ins.get_gpr_reg(ins.current.rd)  iff (ins.trap == 0 )  {
        option.comment = "RD register assignment";
    }
    cp_rs1 : coverpoint ins.get_gpr_reg(ins.current.rs1)  iff (ins.trap == 0 )  {
        option.comment = "RS1 register assignment";
    }
    cp_rs2 : coverpoint ins.get_gpr_reg(ins.current.rs2)  iff (ins.trap == 0 )  {
        option.comment = "RS2 register assignment";
    }
    cr_rs1_rs2_corners : cross cp_rs1_corners,cp_rs2_corners  iff (ins.trap == 0 )  {
        option.comment = "Cross coverage of RS1 corners and RS2 corners";
    }
endgroup

covergroup maxu_cg with function sample(ins_rv64zbb_t ins);
    option.per_instance = 1; 
    option.comment = "maxu";
    cp_asm_count : coverpoint ins.ins_str == "maxu"  iff (ins.trap == 0 )  {
        option.comment = "Number of times instruction is executed";
        bins count[]  = {1};
    }
    cp_rd : coverpoint ins.get_gpr_reg(ins.current.rd)  iff (ins.trap == 0 )  {
        option.comment = "RD register assignment";
    }
    cp_rs1 : coverpoint ins.get_gpr_reg(ins.current.rs1)  iff (ins.trap == 0 )  {
        option.comment = "RS1 register assignment";
    }
    cp_rs2 : coverpoint ins.get_gpr_reg(ins.current.rs2)  iff (ins.trap == 0 )  {
        option.comment = "RS2 register assignment";
    }
    cr_rs1_rs2_corners : cross cp_rs1_corners,cp_rs2_corners  iff (ins.trap == 0 )  {
        option.comment = "Cross coverage of RS1 corners and RS2 corners";
    }
endgroup

covergroup min_cg with function sample(ins_rv64zbb_t ins);
    option.per_instance = 1; 
    option.comment = "min";
    cp_asm_count : coverpoint ins.ins_str == "min"  iff (ins.trap == 0 )  {
        option.comment = "Number of times instruction is executed";
        bins count[]  = {1};
    }
    cp_rd : coverpoint ins.get_gpr_reg(ins.current.rd)  iff (ins.trap == 0 )  {
        option.comment = "RD register assignment";
    }
    cp_rs1 : coverpoint ins.get_gpr_reg(ins.current.rs1)  iff (ins.trap == 0 )  {
        option.comment = "RS1 register assignment";
    }
    cp_rs2 : coverpoint ins.get_gpr_reg(ins.current.rs2)  iff (ins.trap == 0 )  {
        option.comment = "RS2 register assignment";
    }
    cr_rs1_rs2_corners : cross cp_rs1_corners,cp_rs2_corners  iff (ins.trap == 0 )  {
        option.comment = "Cross coverage of RS1 corners and RS2 corners";
    }
endgroup

covergroup minu_cg with function sample(ins_rv64zbb_t ins);
    option.per_instance = 1; 
    option.comment = "minu";
    cp_asm_count : coverpoint ins.ins_str == "minu"  iff (ins.trap == 0 )  {
        option.comment = "Number of times instruction is executed";
        bins count[]  = {1};
    }
    cp_rd : coverpoint ins.get_gpr_reg(ins.current.rd)  iff (ins.trap == 0 )  {
        option.comment = "RD register assignment";
    }
    cp_rs1 : coverpoint ins.get_gpr_reg(ins.current.rs1)  iff (ins.trap == 0 )  {
        option.comment = "RS1 register assignment";
    }
    cp_rs2 : coverpoint ins.get_gpr_reg(ins.current.rs2)  iff (ins.trap == 0 )  {
        option.comment = "RS2 register assignment";
    }
    cr_rs1_rs2_corners : cross cp_rs1_corners,cp_rs2_corners  iff (ins.trap == 0 )  {
        option.comment = "Cross coverage of RS1 corners and RS2 corners";
    }
endgroup

covergroup orc_b_cg with function sample(ins_rv64zbb_t ins);
    option.per_instance = 1; 
    option.comment = "orc.b";
    cp_asm_count : coverpoint ins.ins_str == "orc.b"  iff (ins.trap == 0 )  {
        option.comment = "Number of times instruction is executed";
        bins count[]  = {1};
    }
    cp_rd : coverpoint ins.get_gpr_reg(ins.current.rd)  iff (ins.trap == 0 )  {
        option.comment = "RD register assignment";
    }
    cp_rs1 : coverpoint ins.get_gpr_reg(ins.current.rs1)  iff (ins.trap == 0 )  {
        option.comment = "RS1 register assignment";
    }
endgroup

covergroup orn_cg with function sample(ins_rv64zbb_t ins);
    option.per_instance = 1; 
    option.comment = "orn";
    cp_asm_count : coverpoint ins.ins_str == "orn"  iff (ins.trap == 0 )  {
        option.comment = "Number of times instruction is executed";
        bins count[]  = {1};
    }
    cp_rd : coverpoint ins.get_gpr_reg(ins.current.rd)  iff (ins.trap == 0 )  {
        option.comment = "RD register assignment";
    }
    cp_rs1 : coverpoint ins.get_gpr_reg(ins.current.rs1)  iff (ins.trap == 0 )  {
        option.comment = "RS1 register assignment";
    }
    cp_rs2 : coverpoint ins.get_gpr_reg(ins.current.rs2)  iff (ins.trap == 0 )  {
        option.comment = "RS2 register assignment";
    }
    cr_rs1_rs2_corners : cross cp_rs1_corners,cp_rs2_corners  iff (ins.trap == 0 )  {
        option.comment = "Cross coverage of RS1 corners and RS2 corners";
    }
endgroup

covergroup rev8_cg with function sample(ins_rv64zbb_t ins);
    option.per_instance = 1; 
    option.comment = "rev8";
    cp_asm_count : coverpoint ins.ins_str == "rev8"  iff (ins.trap == 0 )  {
        option.comment = "Number of times instruction is executed";
        bins count[]  = {1};
    }
    cp_rd : coverpoint ins.get_gpr_reg(ins.current.rd)  iff (ins.trap == 0 )  {
        option.comment = "RD register assignment";
    }
    cp_rs1 : coverpoint ins.get_gpr_reg(ins.current.rs1)  iff (ins.trap == 0 )  {
        option.comment = "RS1 register assignment";
    }
endgroup

covergroup rol_cg with function sample(ins_rv64zbb_t ins);
    option.per_instance = 1; 
    option.comment = "rol";
    cp_asm_count : coverpoint ins.ins_str == "rol"  iff (ins.trap == 0 )  {
        option.comment = "Number of times instruction is executed";
        bins count[]  = {1};
    }
    cp_rd : coverpoint ins.get_gpr_reg(ins.current.rd)  iff (ins.trap == 0 )  {
        option.comment = "RD register assignment";
    }
    cp_rs1 : coverpoint ins.get_gpr_reg(ins.current.rs1)  iff (ins.trap == 0 )  {
        option.comment = "RS1 register assignment";
    }
    cp_rs2 : coverpoint ins.get_gpr_reg(ins.current.rs2)  iff (ins.trap == 0 )  {
        option.comment = "RS2 register assignment";
    }
    cr_rs1_rs2_corners : cross cp_rs1_corners,cp_rs2_corners  iff (ins.trap == 0 )  {
        option.comment = "Cross coverage of RS1 corners and RS2 corners";
    }
endgroup

covergroup rolw_cg with function sample(ins_rv64zbb_t ins);
    option.per_instance = 1; 
    option.comment = "rolw";
    cp_asm_count : coverpoint ins.ins_str == "rolw"  iff (ins.trap == 0 )  {
        option.comment = "Number of times instruction is executed";
        bins count[]  = {1};
    }
    cp_rd : coverpoint ins.get_gpr_reg(ins.current.rd)  iff (ins.trap == 0 )  {
        option.comment = "RD register assignment";
    }
    cp_rs1 : coverpoint ins.get_gpr_reg(ins.current.rs1)  iff (ins.trap == 0 )  {
        option.comment = "RS1 register assignment";
    }
    cp_rs2 : coverpoint ins.get_gpr_reg(ins.current.rs2)  iff (ins.trap == 0 )  {
        option.comment = "RS2 register assignment";
    }
    cr_rs1_rs2_corners : cross cp_rs1_corners,cp_rs2_corners  iff (ins.trap == 0 )  {
        option.comment = "Cross coverage of RS1 corners and RS2 corners";
    }
endgroup

covergroup ror_cg with function sample(ins_rv64zbb_t ins);
    option.per_instance = 1; 
    option.comment = "ror";
    cp_asm_count : coverpoint ins.ins_str == "ror"  iff (ins.trap == 0 )  {
        option.comment = "Number of times instruction is executed";
        bins count[]  = {1};
    }
    cp_rd : coverpoint ins.get_gpr_reg(ins.current.rd)  iff (ins.trap == 0 )  {
        option.comment = "RD register assignment";
    }
    cp_rs1 : coverpoint ins.get_gpr_reg(ins.current.rs1)  iff (ins.trap == 0 )  {
        option.comment = "RS1 register assignment";
    }
    cp_rs2 : coverpoint ins.get_gpr_reg(ins.current.rs2)  iff (ins.trap == 0 )  {
        option.comment = "RS2 register assignment";
    }
    cr_rs1_rs2_corners : cross cp_rs1_corners,cp_rs2_corners  iff (ins.trap == 0 )  {
        option.comment = "Cross coverage of RS1 corners and RS2 corners";
    }
endgroup

covergroup rori_cg with function sample(ins_rv64zbb_t ins);
    option.per_instance = 1; 
    option.comment = "rori";
    cp_asm_count : coverpoint ins.ins_str == "rori"  iff (ins.trap == 0 )  {
        option.comment = "Number of times instruction is executed";
        bins count[]  = {1};
    }
    cp_rd : coverpoint ins.get_gpr_reg(ins.current.rd)  iff (ins.trap == 0 )  {
        option.comment = "RD register assignment";
    }
    cp_rs1 : coverpoint ins.get_gpr_reg(ins.current.rs1)  iff (ins.trap == 0 )  {
        option.comment = "RS1 register assignment";
    }
    cp_imm_sign : coverpoint int'(ins.current.imm)  iff (ins.trap == 0 )  {
        option.comment = "Immediate value sign";
        bins neg  = {[$:-1]};
        bins pos  = {[1:$]};
    }
    cp_imm_ones_zeros : coverpoint unsigned'(ins.current.imm)  iff (ins.trap == 0 )  {
        option.comment = "Immediate value ones and zeros";
        wildcard bins bit_0_0  = {64'b???????????????????????????????????????????????????????????????0};
        wildcard bins bit_1_0  = {64'b??????????????????????????????????????????????????????????????0?};
        wildcard bins bit_2_0  = {64'b?????????????????????????????????????????????????????????????0??};
        wildcard bins bit_3_0  = {64'b????????????????????????????????????????????????????????????0???};
        wildcard bins bit_4_0  = {64'b???????????????????????????????????????????????????????????0????};
        wildcard bins bit_5_0  = {64'b??????????????????????????????????????????????????????????0?????};
        wildcard bins bit_6_0  = {64'b?????????????????????????????????????????????????????????0??????};
        wildcard bins bit_7_0  = {64'b????????????????????????????????????????????????????????0???????};
        wildcard bins bit_8_0  = {64'b???????????????????????????????????????????????????????0????????};
        wildcard bins bit_9_0  = {64'b??????????????????????????????????????????????????????0?????????};
        wildcard bins bit_10_0  = {64'b?????????????????????????????????????????????????????0??????????};
        wildcard bins bit_11_0  = {64'b????????????????????????????????????????????????????0???????????};
        wildcard bins bit_12_0  = {64'b???????????????????????????????????????????????????0????????????};
        wildcard bins bit_0_1  = {64'b???????????????????????????????????????????????????????????????1};
        wildcard bins bit_1_1  = {64'b??????????????????????????????????????????????????????????????1?};
        wildcard bins bit_2_1  = {64'b?????????????????????????????????????????????????????????????1??};
        wildcard bins bit_3_1  = {64'b????????????????????????????????????????????????????????????1???};
        wildcard bins bit_4_1  = {64'b???????????????????????????????????????????????????????????1????};
        wildcard bins bit_5_1  = {64'b??????????????????????????????????????????????????????????1?????};
        wildcard bins bit_6_1  = {64'b?????????????????????????????????????????????????????????1??????};
        wildcard bins bit_7_1  = {64'b????????????????????????????????????????????????????????1???????};
        wildcard bins bit_8_1  = {64'b???????????????????????????????????????????????????????1????????};
        wildcard bins bit_9_1  = {64'b??????????????????????????????????????????????????????1?????????};
        wildcard bins bit_10_1  = {64'b?????????????????????????????????????????????????????1??????????};
        wildcard bins bit_11_1  = {64'b????????????????????????????????????????????????????1???????????};
        wildcard bins bit_12_1  = {64'b???????????????????????????????????????????????????1????????????};
    }
endgroup

covergroup roriw_cg with function sample(ins_rv64zbb_t ins);
    option.per_instance = 1; 
    option.comment = "roriw";
    cp_asm_count : coverpoint ins.ins_str == "roriw"  iff (ins.trap == 0 )  {
        option.comment = "Number of times instruction is executed";
        bins count[]  = {1};
    }
    cp_rd : coverpoint ins.get_gpr_reg(ins.current.rd)  iff (ins.trap == 0 )  {
        option.comment = "RD register assignment";
    }
    cp_rs1 : coverpoint ins.get_gpr_reg(ins.current.rs1)  iff (ins.trap == 0 )  {
        option.comment = "RS1 register assignment";
    }
    cp_imm_sign : coverpoint int'(ins.current.imm)  iff (ins.trap == 0 )  {
        option.comment = "Immediate value sign";
        bins neg  = {[$:-1]};
        bins pos  = {[1:$]};
    }
    cp_imm_ones_zeros : coverpoint unsigned'(ins.current.imm)  iff (ins.trap == 0 )  {
        option.comment = "Immediate value ones and zeros";
        wildcard bins bit_0_0  = {64'b???????????????????????????????????????????????????????????????0};
        wildcard bins bit_1_0  = {64'b??????????????????????????????????????????????????????????????0?};
        wildcard bins bit_2_0  = {64'b?????????????????????????????????????????????????????????????0??};
        wildcard bins bit_3_0  = {64'b????????????????????????????????????????????????????????????0???};
        wildcard bins bit_4_0  = {64'b???????????????????????????????????????????????????????????0????};
        wildcard bins bit_5_0  = {64'b??????????????????????????????????????????????????????????0?????};
        wildcard bins bit_6_0  = {64'b?????????????????????????????????????????????????????????0??????};
        wildcard bins bit_7_0  = {64'b????????????????????????????????????????????????????????0???????};
        wildcard bins bit_8_0  = {64'b???????????????????????????????????????????????????????0????????};
        wildcard bins bit_9_0  = {64'b??????????????????????????????????????????????????????0?????????};
        wildcard bins bit_10_0  = {64'b?????????????????????????????????????????????????????0??????????};
        wildcard bins bit_11_0  = {64'b????????????????????????????????????????????????????0???????????};
        wildcard bins bit_12_0  = {64'b???????????????????????????????????????????????????0????????????};
        wildcard bins bit_0_1  = {64'b???????????????????????????????????????????????????????????????1};
        wildcard bins bit_1_1  = {64'b??????????????????????????????????????????????????????????????1?};
        wildcard bins bit_2_1  = {64'b?????????????????????????????????????????????????????????????1??};
        wildcard bins bit_3_1  = {64'b????????????????????????????????????????????????????????????1???};
        wildcard bins bit_4_1  = {64'b???????????????????????????????????????????????????????????1????};
        wildcard bins bit_5_1  = {64'b??????????????????????????????????????????????????????????1?????};
        wildcard bins bit_6_1  = {64'b?????????????????????????????????????????????????????????1??????};
        wildcard bins bit_7_1  = {64'b????????????????????????????????????????????????????????1???????};
        wildcard bins bit_8_1  = {64'b???????????????????????????????????????????????????????1????????};
        wildcard bins bit_9_1  = {64'b??????????????????????????????????????????????????????1?????????};
        wildcard bins bit_10_1  = {64'b?????????????????????????????????????????????????????1??????????};
        wildcard bins bit_11_1  = {64'b????????????????????????????????????????????????????1???????????};
        wildcard bins bit_12_1  = {64'b???????????????????????????????????????????????????1????????????};
    }
endgroup

covergroup rorw_cg with function sample(ins_rv64zbb_t ins);
    option.per_instance = 1; 
    option.comment = "rorw";
    cp_asm_count : coverpoint ins.ins_str == "rorw"  iff (ins.trap == 0 )  {
        option.comment = "Number of times instruction is executed";
        bins count[]  = {1};
    }
    cp_rd : coverpoint ins.get_gpr_reg(ins.current.rd)  iff (ins.trap == 0 )  {
        option.comment = "RD register assignment";
    }
    cp_rs1 : coverpoint ins.get_gpr_reg(ins.current.rs1)  iff (ins.trap == 0 )  {
        option.comment = "RS1 register assignment";
    }
    cp_rs2 : coverpoint ins.get_gpr_reg(ins.current.rs2)  iff (ins.trap == 0 )  {
        option.comment = "RS2 register assignment";
    }
    cr_rs1_rs2_corners : cross cp_rs1_corners,cp_rs2_corners  iff (ins.trap == 0 )  {
        option.comment = "Cross coverage of RS1 corners and RS2 corners";
    }
endgroup

covergroup sext_b_cg with function sample(ins_rv64zbb_t ins);
    option.per_instance = 1; 
    option.comment = "sext.b";
    cp_asm_count : coverpoint ins.ins_str == "sext.b"  iff (ins.trap == 0 )  {
        option.comment = "Number of times instruction is executed";
        bins count[]  = {1};
    }
    cp_rd : coverpoint ins.get_gpr_reg(ins.current.rd)  iff (ins.trap == 0 )  {
        option.comment = "RD register assignment";
    }
    cp_rs1 : coverpoint ins.get_gpr_reg(ins.current.rs1)  iff (ins.trap == 0 )  {
        option.comment = "RS1 register assignment";
    }
endgroup

covergroup sext_h_cg with function sample(ins_rv64zbb_t ins);
    option.per_instance = 1; 
    option.comment = "sext.h";
    cp_asm_count : coverpoint ins.ins_str == "sext.h"  iff (ins.trap == 0 )  {
        option.comment = "Number of times instruction is executed";
        bins count[]  = {1};
    }
    cp_rd : coverpoint ins.get_gpr_reg(ins.current.rd)  iff (ins.trap == 0 )  {
        option.comment = "RD register assignment";
    }
    cp_rs1 : coverpoint ins.get_gpr_reg(ins.current.rs1)  iff (ins.trap == 0 )  {
        option.comment = "RS1 register assignment";
    }
endgroup

covergroup xnor_cg with function sample(ins_rv64zbb_t ins);
    option.per_instance = 1; 
    option.comment = "xnor";
    cp_asm_count : coverpoint ins.ins_str == "xnor"  iff (ins.trap == 0 )  {
        option.comment = "Number of times instruction is executed";
        bins count[]  = {1};
    }
    cp_rd : coverpoint ins.get_gpr_reg(ins.current.rd)  iff (ins.trap == 0 )  {
        option.comment = "RD register assignment";
    }
    cp_rs1 : coverpoint ins.get_gpr_reg(ins.current.rs1)  iff (ins.trap == 0 )  {
        option.comment = "RS1 register assignment";
    }
    cp_rs2 : coverpoint ins.get_gpr_reg(ins.current.rs2)  iff (ins.trap == 0 )  {
        option.comment = "RS2 register assignment";
    }
    cr_rs1_rs2_corners : cross cp_rs1_corners,cp_rs2_corners  iff (ins.trap == 0 )  {
        option.comment = "Cross coverage of RS1 corners and RS2 corners";
    }
endgroup

covergroup zext_h_cg with function sample(ins_rv64zbb_t ins);
    option.per_instance = 1; 
    option.comment = "zext.h";
    cp_asm_count : coverpoint ins.ins_str == "zext.h"  iff (ins.trap == 0 )  {
        option.comment = "Number of times instruction is executed";
        bins count[]  = {1};
    }
    cp_rd : coverpoint ins.get_gpr_reg(ins.current.rd)  iff (ins.trap == 0 )  {
        option.comment = "RD register assignment";
    }
    cp_rs1 : coverpoint ins.get_gpr_reg(ins.current.rs1)  iff (ins.trap == 0 )  {
        option.comment = "RS1 register assignment";
    }
endgroup

function void rv64zbb_sample(int hart, int issue);
    ins_rv64zbb_t ins;

    case (traceDataQ[hart][issue][0].inst_name)
        "andn"     : begin 
            ins = new(hart, issue, traceDataQ); 
            ins.add_rd(0);
            ins.add_rs1(1);
            ins.add_rs2(2);
            andn_cg.sample(ins); 
        end
        "clz"     : begin 
            ins = new(hart, issue, traceDataQ); 
            ins.add_rd(0);
            ins.add_rs1(1);
            ins.add_imm(2);
            clz_cg.sample(ins); 
        end
        "clzw"     : begin 
            ins = new(hart, issue, traceDataQ); 
            ins.add_rd(0);
            ins.add_rs1(1);
            ins.add_imm(2);
            clzw_cg.sample(ins); 
        end
        "cpop"     : begin 
            ins = new(hart, issue, traceDataQ); 
            ins.add_rd(0);
            ins.add_rs1(1);
            ins.add_imm(2);
            cpop_cg.sample(ins); 
        end
        "cpopw"     : begin 
            ins = new(hart, issue, traceDataQ); 
            ins.add_rd(0);
            ins.add_rs1(1);
            ins.add_imm(2);
            cpopw_cg.sample(ins); 
        end
        "ctz"     : begin 
            ins = new(hart, issue, traceDataQ); 
            ins.add_rd(0);
            ins.add_rs1(1);
            ins.add_imm(2);
            ctz_cg.sample(ins); 
        end
        "ctzw"     : begin 
            ins = new(hart, issue, traceDataQ); 
            ins.add_rd(0);
            ins.add_rs1(1);
            ins.add_imm(2);
            ctzw_cg.sample(ins); 
        end
        "max"     : begin 
            ins = new(hart, issue, traceDataQ); 
            ins.add_rd(0);
            ins.add_rs1(1);
            ins.add_rs2(2);
            max_cg.sample(ins); 
        end
        "maxu"     : begin 
            ins = new(hart, issue, traceDataQ); 
            ins.add_rd(0);
            ins.add_rs1(1);
            ins.add_rs2(2);
            maxu_cg.sample(ins); 
        end
        "min"     : begin 
            ins = new(hart, issue, traceDataQ); 
            ins.add_rd(0);
            ins.add_rs1(1);
            ins.add_rs2(2);
            min_cg.sample(ins); 
        end
        "minu"     : begin 
            ins = new(hart, issue, traceDataQ); 
            ins.add_rd(0);
            ins.add_rs1(1);
            ins.add_rs2(2);
            minu_cg.sample(ins); 
        end
        "orc.b"     : begin 
            ins = new(hart, issue, traceDataQ); 
            ins.add_rd(0);
            ins.add_rs1(1);
            ins.add_imm(2);
            orc_b_cg.sample(ins); 
        end
        "orn"     : begin 
            ins = new(hart, issue, traceDataQ); 
            ins.add_rd(0);
            ins.add_rs1(1);
            ins.add_rs2(2);
            orn_cg.sample(ins); 
        end
        "rev8"     : begin 
            ins = new(hart, issue, traceDataQ); 
            ins.add_rd(0);
            ins.add_rs1(1);
            ins.add_imm(2);
            rev8_cg.sample(ins); 
        end
        "rol"     : begin 
            ins = new(hart, issue, traceDataQ); 
            ins.add_rd(0);
            ins.add_rs1(1);
            ins.add_rs2(2);
            rol_cg.sample(ins); 
        end
        "rolw"     : begin 
            ins = new(hart, issue, traceDataQ); 
            ins.add_rd(0);
            ins.add_rs1(1);
            ins.add_rs2(2);
            rolw_cg.sample(ins); 
        end
        "ror"     : begin 
            ins = new(hart, issue, traceDataQ); 
            ins.add_rd(0);
            ins.add_rs1(1);
            ins.add_rs2(2);
            ror_cg.sample(ins); 
        end
        "rori"     : begin 
            ins = new(hart, issue, traceDataQ); 
            ins.add_rd(0);
            ins.add_rs1(1);
            ins.add_imm(2);
            rori_cg.sample(ins); 
        end
        "roriw"     : begin 
            ins = new(hart, issue, traceDataQ); 
            ins.add_rd(0);
            ins.add_rs1(1);
            ins.add_imm(2);
            roriw_cg.sample(ins); 
        end
        "rorw"     : begin 
            ins = new(hart, issue, traceDataQ); 
            ins.add_rd(0);
            ins.add_rs1(1);
            ins.add_rs2(2);
            rorw_cg.sample(ins); 
        end
        "sext.b"     : begin 
            ins = new(hart, issue, traceDataQ); 
            ins.add_rd(0);
            ins.add_rs1(1);
            ins.add_imm(2);
            sext_b_cg.sample(ins); 
        end
        "sext.h"     : begin 
            ins = new(hart, issue, traceDataQ); 
            ins.add_rd(0);
            ins.add_rs1(1);
            ins.add_imm(2);
            sext_h_cg.sample(ins); 
        end
        "xnor"     : begin 
            ins = new(hart, issue, traceDataQ); 
            ins.add_rd(0);
            ins.add_rs1(1);
            ins.add_rs2(2);
            xnor_cg.sample(ins); 
        end
        "zext.h"     : begin 
            ins = new(hart, issue, traceDataQ); 
            ins.add_rd(0);
            ins.add_rs1(1);
            ins.add_imm(2);
            zext_h_cg.sample(ins); 
        end
    endcase
endfunction
