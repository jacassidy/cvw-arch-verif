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

`define COVER_RV32ZCBM
typedef RISCV_instruction #(ILEN, XLEN, FLEN, VLEN, NHART, RETIRE) ins_rv32zcbm_t;


covergroup c_mul_cg with function sample(ins_rv32zcbm_t ins);
    option.per_instance = 1; 
    option.comment = "c.mul";
    cp_asm_count : coverpoint ins.ins_str == "mul"  iff (ins.trap == 0 )  {
        option.comment = "Number of times instruction is executed";
        bins count[]  = {1};
    }
    cmp_rd_rs2_eqval : coverpoint ins.current.rd_val == ins.current.rs2_val  iff (ins.trap == 0 )  {
        option.comment = "Compare RD and RS2 register values";
        bins rd_eqval_rs2  = {1};
        bins rd_neval_rs2  = {0};
    }
    cmp_rd_rs2_c : coverpoint ins.current.rd == ins.current.rs2  iff (ins.trap == 0 )  {
        option.comment = "RD and RS1 register (assignment) WAR Hazard";
        bins x8  = {1} iff (ins.current.rd == "x8");
        bins x9  = {1} iff (ins.current.rd == "x9");
        bins x10  = {1} iff (ins.current.rd == "x10");
        bins x11  = {1} iff (ins.current.rd == "x11");
        bins x12  = {1} iff (ins.current.rd == "x12");
        bins x13  = {1} iff (ins.current.rd == "x13");
        bins x14  = {1} iff (ins.current.rd == "x14");
        bins x15  = {1} iff (ins.current.rd == "x15");
    }    cp_rd_sign : coverpoint int'(ins.current.rd_val)  iff (ins.trap == 0 )  {
        option.comment = "RD sign of value";
        bins neg  = {[$:-1]};
        bins pos  = {[1:$]};
    }
    cp_rs2_sign : coverpoint int'(ins.current.rs2_val)  iff (ins.trap == 0 )  {
        option.comment = "RS2 sign of value";
        bins neg  = {[$:-1]};
        bins pos  = {[1:$]};
    }
    cp_rdp : coverpoint ins.get_gpr_c_reg(ins.current.rd)  iff (ins.trap == 0 )  {
        option.comment = "RD register assignment";
    }
    cp_rs2p : coverpoint ins.get_gpr_c_reg(ins.current.rs2)  iff (ins.trap == 0 )  {
        option.comment = "RS2 register assignment";
    }
    cp_rd_corners : coverpoint unsigned'(ins.current.rd_val)  iff (ins.trap == 0 )  {
        option.comment = "RD Corners";
        wildcard bins zero  = {0};
        wildcard bins one  = {32'b00000000000000000000000000000001};
        wildcard bins two  = {32'b00000000000000000000000000000010};
        wildcard bins min  = {32'b10000000000000000000000000000000};
        wildcard bins minp1  = {32'b10000000000000000000000000000001};
        wildcard bins max  = {32'b01111111111111111111111111111111};
        wildcard bins maxm1  = {32'b01111111111111111111111111111110};
        wildcard bins ones  = {32'b11111111111111111111111111111111};
        wildcard bins onesm1  = {32'b11111111111111111111111111111110};
        wildcard bins walkeodd = {32'b10101010101010101010101010101010};
        wildcard bins walkeven = {32'b01010101010101010101010101010101};
        wildcard bins random   = {32'b01011011101111001000100001110111};
     }
    cp_rs2_corners : coverpoint unsigned'(ins.current.rs2_val)  iff (ins.trap == 0 )  {
        option.comment = "RS2 Corners";
        wildcard bins zero  = {0};
        wildcard bins one  = {32'b00000000000000000000000000000001};
        wildcard bins two  = {32'b00000000000000000000000000000010};
        wildcard bins min  = {32'b10000000000000000000000000000000};
        wildcard bins minp1  = {32'b10000000000000000000000000000001};
        wildcard bins max  = {32'b01111111111111111111111111111111};
        wildcard bins maxm1  = {32'b01111111111111111111111111111110};
        wildcard bins ones  = {32'b11111111111111111111111111111111};
        wildcard bins onesm1  = {32'b11111111111111111111111111111110};
        wildcard bins walkeodd = {32'b10101010101010101010101010101010};
        wildcard bins walkeven = {32'b01010101010101010101010101010101};
        wildcard bins random   = {32'b01011011101111001000100001110111};
     }
    cp_rd_toggle : coverpoint unsigned'(ins.current.rd_val)  iff (ins.trap == 0 )  {
        option.comment = "RD Toggle bits";
        wildcard bins bit_0_0  = {32'b???????????????????????????????0};
        wildcard bins bit_1_0  = {32'b??????????????????????????????0?};
        wildcard bins bit_2_0  = {32'b?????????????????????????????0??};
        wildcard bins bit_3_0  = {32'b????????????????????????????0???};
        wildcard bins bit_4_0  = {32'b???????????????????????????0????};
        wildcard bins bit_5_0  = {32'b??????????????????????????0?????};
        wildcard bins bit_6_0  = {32'b?????????????????????????0??????};
        wildcard bins bit_7_0  = {32'b????????????????????????0???????};
        wildcard bins bit_8_0  = {32'b???????????????????????0????????};
        wildcard bins bit_9_0  = {32'b??????????????????????0?????????};
        wildcard bins bit_10_0  = {32'b?????????????????????0??????????};
        wildcard bins bit_11_0  = {32'b????????????????????0???????????};
        wildcard bins bit_12_0  = {32'b???????????????????0????????????};
        wildcard bins bit_13_0  = {32'b??????????????????0?????????????};
        wildcard bins bit_14_0  = {32'b?????????????????0??????????????};
        wildcard bins bit_15_0  = {32'b????????????????0???????????????};
        wildcard bins bit_16_0  = {32'b???????????????0????????????????};
        wildcard bins bit_17_0  = {32'b??????????????0?????????????????};
        wildcard bins bit_18_0  = {32'b?????????????0??????????????????};
        wildcard bins bit_19_0  = {32'b????????????0???????????????????};
        wildcard bins bit_20_0  = {32'b???????????0????????????????????};
        wildcard bins bit_21_0  = {32'b??????????0?????????????????????};
        wildcard bins bit_22_0  = {32'b?????????0??????????????????????};
        wildcard bins bit_23_0  = {32'b????????0???????????????????????};
        wildcard bins bit_24_0  = {32'b???????0????????????????????????};
        wildcard bins bit_25_0  = {32'b??????0?????????????????????????};
        wildcard bins bit_26_0  = {32'b?????0??????????????????????????};
        wildcard bins bit_27_0  = {32'b????0???????????????????????????};
        wildcard bins bit_28_0  = {32'b???0????????????????????????????};
        wildcard bins bit_29_0  = {32'b??0?????????????????????????????};
        wildcard bins bit_30_0  = {32'b?0??????????????????????????????};
        wildcard bins bit_31_0  = {32'b0???????????????????????????????};
        wildcard bins bit_0_1  = {32'b???????????????????????????????1};
        wildcard bins bit_1_1  = {32'b??????????????????????????????1?};
        wildcard bins bit_2_1  = {32'b?????????????????????????????1??};
        wildcard bins bit_3_1  = {32'b????????????????????????????1???};
        wildcard bins bit_4_1  = {32'b???????????????????????????1????};
        wildcard bins bit_5_1  = {32'b??????????????????????????1?????};
        wildcard bins bit_6_1  = {32'b?????????????????????????1??????};
        wildcard bins bit_7_1  = {32'b????????????????????????1???????};
        wildcard bins bit_8_1  = {32'b???????????????????????1????????};
        wildcard bins bit_9_1  = {32'b??????????????????????1?????????};
        wildcard bins bit_10_1  = {32'b?????????????????????1??????????};
        wildcard bins bit_11_1  = {32'b????????????????????1???????????};
        wildcard bins bit_12_1  = {32'b???????????????????1????????????};
        wildcard bins bit_13_1  = {32'b??????????????????1?????????????};
        wildcard bins bit_14_1  = {32'b?????????????????1??????????????};
        wildcard bins bit_15_1  = {32'b????????????????1???????????????};
        wildcard bins bit_16_1  = {32'b???????????????1????????????????};
        wildcard bins bit_17_1  = {32'b??????????????1?????????????????};
        wildcard bins bit_18_1  = {32'b?????????????1??????????????????};
        wildcard bins bit_19_1  = {32'b????????????1???????????????????};
        wildcard bins bit_20_1  = {32'b???????????1????????????????????};
        wildcard bins bit_21_1  = {32'b??????????1?????????????????????};
        wildcard bins bit_22_1  = {32'b?????????1??????????????????????};
        wildcard bins bit_23_1  = {32'b????????1???????????????????????};
        wildcard bins bit_24_1  = {32'b???????1????????????????????????};
        wildcard bins bit_25_1  = {32'b??????1?????????????????????????};
        wildcard bins bit_26_1  = {32'b?????1??????????????????????????};
        wildcard bins bit_27_1  = {32'b????1???????????????????????????};
        wildcard bins bit_28_1  = {32'b???1????????????????????????????};
        wildcard bins bit_29_1  = {32'b??1?????????????????????????????};
        wildcard bins bit_30_1  = {32'b?1??????????????????????????????};
        wildcard bins bit_31_1  = {32'b1???????????????????????????????};
    }
    cp_rs2_toggle : coverpoint unsigned'(ins.current.rs2_val)  iff (ins.trap == 0 )  {
        option.comment = "RS2 Toggle bits";
        wildcard bins bit_0_0  = {32'b???????????????????????????????0};
        wildcard bins bit_1_0  = {32'b??????????????????????????????0?};
        wildcard bins bit_2_0  = {32'b?????????????????????????????0??};
        wildcard bins bit_3_0  = {32'b????????????????????????????0???};
        wildcard bins bit_4_0  = {32'b???????????????????????????0????};
        wildcard bins bit_5_0  = {32'b??????????????????????????0?????};
        wildcard bins bit_6_0  = {32'b?????????????????????????0??????};
        wildcard bins bit_7_0  = {32'b????????????????????????0???????};
        wildcard bins bit_8_0  = {32'b???????????????????????0????????};
        wildcard bins bit_9_0  = {32'b??????????????????????0?????????};
        wildcard bins bit_10_0  = {32'b?????????????????????0??????????};
        wildcard bins bit_11_0  = {32'b????????????????????0???????????};
        wildcard bins bit_12_0  = {32'b???????????????????0????????????};
        wildcard bins bit_13_0  = {32'b??????????????????0?????????????};
        wildcard bins bit_14_0  = {32'b?????????????????0??????????????};
        wildcard bins bit_15_0  = {32'b????????????????0???????????????};
        wildcard bins bit_16_0  = {32'b???????????????0????????????????};
        wildcard bins bit_17_0  = {32'b??????????????0?????????????????};
        wildcard bins bit_18_0  = {32'b?????????????0??????????????????};
        wildcard bins bit_19_0  = {32'b????????????0???????????????????};
        wildcard bins bit_20_0  = {32'b???????????0????????????????????};
        wildcard bins bit_21_0  = {32'b??????????0?????????????????????};
        wildcard bins bit_22_0  = {32'b?????????0??????????????????????};
        wildcard bins bit_23_0  = {32'b????????0???????????????????????};
        wildcard bins bit_24_0  = {32'b???????0????????????????????????};
        wildcard bins bit_25_0  = {32'b??????0?????????????????????????};
        wildcard bins bit_26_0  = {32'b?????0??????????????????????????};
        wildcard bins bit_27_0  = {32'b????0???????????????????????????};
        wildcard bins bit_28_0  = {32'b???0????????????????????????????};
        wildcard bins bit_29_0  = {32'b??0?????????????????????????????};
        wildcard bins bit_30_0  = {32'b?0??????????????????????????????};
        wildcard bins bit_31_0  = {32'b0???????????????????????????????};
        wildcard bins bit_0_1  = {32'b???????????????????????????????1};
        wildcard bins bit_1_1  = {32'b??????????????????????????????1?};
        wildcard bins bit_2_1  = {32'b?????????????????????????????1??};
        wildcard bins bit_3_1  = {32'b????????????????????????????1???};
        wildcard bins bit_4_1  = {32'b???????????????????????????1????};
        wildcard bins bit_5_1  = {32'b??????????????????????????1?????};
        wildcard bins bit_6_1  = {32'b?????????????????????????1??????};
        wildcard bins bit_7_1  = {32'b????????????????????????1???????};
        wildcard bins bit_8_1  = {32'b???????????????????????1????????};
        wildcard bins bit_9_1  = {32'b??????????????????????1?????????};
        wildcard bins bit_10_1  = {32'b?????????????????????1??????????};
        wildcard bins bit_11_1  = {32'b????????????????????1???????????};
        wildcard bins bit_12_1  = {32'b???????????????????1????????????};
        wildcard bins bit_13_1  = {32'b??????????????????1?????????????};
        wildcard bins bit_14_1  = {32'b?????????????????1??????????????};
        wildcard bins bit_15_1  = {32'b????????????????1???????????????};
        wildcard bins bit_16_1  = {32'b???????????????1????????????????};
        wildcard bins bit_17_1  = {32'b??????????????1?????????????????};
        wildcard bins bit_18_1  = {32'b?????????????1??????????????????};
        wildcard bins bit_19_1  = {32'b????????????1???????????????????};
        wildcard bins bit_20_1  = {32'b???????????1????????????????????};
        wildcard bins bit_21_1  = {32'b??????????1?????????????????????};
        wildcard bins bit_22_1  = {32'b?????????1??????????????????????};
        wildcard bins bit_23_1  = {32'b????????1???????????????????????};
        wildcard bins bit_24_1  = {32'b???????1????????????????????????};
        wildcard bins bit_25_1  = {32'b??????1?????????????????????????};
        wildcard bins bit_26_1  = {32'b?????1??????????????????????????};
        wildcard bins bit_27_1  = {32'b????1???????????????????????????};
        wildcard bins bit_28_1  = {32'b???1????????????????????????????};
        wildcard bins bit_29_1  = {32'b??1?????????????????????????????};
        wildcard bins bit_30_1  = {32'b?1??????????????????????????????};
        wildcard bins bit_31_1  = {32'b1???????????????????????????????};
    }
endgroup

function void rv32zcbm_sample(int hart, int issue);
    ins_rv32zcbm_t ins;
    if (traceDataQ[hart][issue][0].insn[1:0] != 3) begin // compressed instruction
        $display("Examining compressed instruction rv32zcbm_sample with inst_name = %s disass = %s", traceDataQ[hart][issue][0].inst_name, traceDataQ[hart][issue][0].disass);
        case (traceDataQ[hart][issue][0].inst_name)
            "mul" : begin
                if (traceDataQ[hart][issue][0].insn[1:0] == 2'b01 && traceDataQ[hart][issue][0].insn[15:10] == 6'b100111) begin // Specific bits for "mul" 
                    ins = new(hart, issue, traceDataQ); 
                    ins.add_rd(0);                 
                    ins.add_rs2(2);                
                    c_mul_cg.sample(ins);       
                end
            end
        endcase
    end
endfunction
