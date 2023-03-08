Require Import Coq.Strings.String Coq.Lists.List.
Import ListNotations.
Local Open Scope string_scope.
Local Open Scope list_scope.
Example example : list string := [
"SECTION .text";
"	GLOBAL fiat_25519_carry_square_optimised";
"";
"fiat_25519_carry_square_optimised:";
"	sub rsp, 0x38 ";
"	mov [rsp + 0x08 * 0 ], rbx; saving to stack";
"	mov [rsp + 0x08 * 1 ], rbp; saving to stack";
"	mov [rsp + 0x08 * 2 ], r12; saving to stack";
"	mov [rsp + 0x08 * 3 ], r13; saving to stack";
"	mov [rsp + 0x08 * 4 ], r14; saving to stack";
"	mov [rsp + 0x08 * 5 ], r15; saving to stack";
"	; rdi contains out1";
"	; rsi contains arg1";
"	;chose >>saved<< arg1[0] from:arg1[0], arg1[0][1] and candidates: arg1[0], arg1[0]";
"	mov rdx, [rsi + 0x08 * 0 ]; arg1[0] to rdx";
"	; fr:rax,r10,r11,rbx,rbp,r12,r13,r14,r15,rcx,r8,r9";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""arg1[0]:rdx""]";
"	;chose >>RANDOMLY<< r12 from candidates :rax, r10, r11, rbx, rbp, r12, r13, r14, r15, rcx, r8, r9[5].";
"	; fr:rax,r10,r11,rbx,rbp,r13,r14,r15,rcx,r8,r9";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""arg1[0]:rdx"",""x38:r12""]";
"	;chose >>RANDOMLY<< r13 from candidates :rax, r10, r11, rbx, rbp, r13, r14, r15, rcx, r8, r9[5].";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""arg1[0]:rdx"",""x38:r12"",""x37:r13""]";
"	mulx r12, r13, [rsi + 0x08 * 0 ]; x38, x37<- arg1[0] * arg1[0]";
"	; fr:rax,r10,r11,rbx,rbp,r14,r15,rcx,r8,r9";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""arg1[0]:rdx"",""x38:r12"",""x37:r13""]";
"	;chose >>RANDOMLY<< rax from candidates :rax, r10, r11, rbx, rbp, r14, r15, rcx, r8, r9[0].";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""arg1[0]:rdx"",""x38:r12"",""x37:r13"",""x4:rax""]";
"	imul rax, [rsi + 0x08 * 3 ], 0x13; x4 <- arg1[3] * 0x13";
"	;CF: KILLED,OF: KILLED";
"	; fr:r10,r11,rbx,rbp,r14,r15,rcx,r8,r9";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""arg1[0]:rdx"",""x38:r12"",""x37:r13"",""x4:rax""]";
"	;chose >>RANDOMLY<< rbp from candidates :r10, r11, rbx, rbp, r14, r15, rcx, r8, r9[3].";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""arg1[0]:rdx"",""x38:r12"",""x37:r13"",""x4:rax"",""x1:rbp""]";
"	imul rbp, [rsi + 0x08 * 4 ], 0x13; x1 <- arg1[4] * 0x13";
"	;CF: KILLED,OF: KILLED";
"	; fr:r10,r11,rbx,r14,r15,rcx,r8,r9";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""arg1[0]:rdx"",""x38:r12"",""x37:r13"",""x4:rax"",""x1:rbp""]";
"	;chose >>RANDOMLY<< r14 from candidates :r10, r11, rbx, r14, r15, rcx, r8, r9[3].";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""arg1[0]:rdx"",""x38:r12"",""x37:r13"",""x4:rax"",""x1:rbp"",""x2:r14""]";
"	imul r14, rbp, 0x2; x2 <- x1 * 0x2";
"	;CF: KILLED,OF: KILLED";
"	;chose >>saved<< arg1[1] from:arg1[1], x2[0] and candidates: arg1[1], x2";
"	mov rdx, [rsi + 0x08 * 1 ]; arg1[1] to rdx";
"	; fr:r10,r11,rbx,r15,rcx,r8,r9";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x38:r12"",""x37:r13"",""x4:rax"",""x1:rbp"",""x2:r14"",""arg1[1]:rdx""]";
"	;chose >>RANDOMLY<< rbx from candidates :r10, r11, rbx, r15, rcx, r8, r9[2].";
"	; fr:r10,r11,r15,rcx,r8,r9";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x38:r12"",""x37:r13"",""x4:rax"",""x1:rbp"",""x2:r14"",""arg1[1]:rdx"",""x22:rbx""]";
"	;chose >>RANDOMLY<< r10 from candidates :r10, r11, r15, rcx, r8, r9[0].";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x38:r12"",""x37:r13"",""x4:rax"",""x1:rbp"",""x2:r14"",""arg1[1]:rdx"",""x22:rbx"",""x21:r10""]";
"	mulx rbx, r10, r14; x22, x21<- arg1[1] * x2";
"	; fr:r11,r15,rcx,r8,r9";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x38:r12"",""x37:r13"",""x4:rax"",""x1:rbp"",""x2:r14"",""arg1[1]:rdx"",""x22:rbx"",""x21:r10""]";
"	;chose >>RANDOMLY<< r11 from candidates :r11, r15, rcx, r8, r9[0].";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x38:r12"",""x37:r13"",""x4:rax"",""x1:rbp"",""x2:r14"",""arg1[1]:rdx"",""x22:rbx"",""x21:r10"",""x5:r11""]";
"	imul r11, rax, 0x2; x5 <- x4 * 0x2";
"	;CF: KILLED,OF: KILLED";
"	;chose >>saved<< x5 from:arg1[2], x5[1] and candidates: arg1[2], x5";
"	mov rdx, r11; x5 to rdx";
"	; fr:r11,r15,rcx,r8,r9";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x38:r12"",""x37:r13"",""x4:rax"",""x1:rbp"",""x2:r14"",""x22:rbx"",""x21:r10"",""x18:rdx""]";
"	;chose >>RANDOMLY<< r9 from candidates :r11, r15, rcx, r8, r9[4].";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x38:r12"",""x37:r13"",""x4:rax"",""x1:rbp"",""x2:r14"",""x22:rbx"",""x21:r10"",""x18:rdx"",""x17:r9""]";
"	mulx rdx, r9, [rsi + 0x08 * 2 ]; x18, x17<- arg1[2] * x5";
"	";
"";
"	; add:";
"	; r:x39,f:x40<-add(0x0,x21,x17)";
"	; CF: KILLED,OF: KILLED";
"	;chose >>saved<< c_xor_adx from:c_add, c_xor_adx, c_test_adx[1] and candidates: c_add, c_xor_adx, c_test_adx";
"	; fr:r11,r15,rcx,r8";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x38:r12"",""x37:r13"",""x4:rax"",""x1:rbp"",""x2:r14"",""x22:rbx"",""x18:rdx"",""x17:r9"",""x39:r10""]";
"	;chose >>RANDOMLY<< r11 from candidates :r11, r15, rcx, r8[0].";
"	xor r11, r11";
"	;chose >>saved<< OF from:CF, OF[1] and candidates: CF, OF";
"	adox r10, r9";
"	";
"";
"	; add:";
"	; r:x43,f:x44<-add(0x0,x37,x39)";
"	; CF: ZERO,OF: ALIVE";
"	adcx r13, r10";
"	";
"";
"	; add:";
"	; r:x41,f:_<-add(x40,x22,x18)";
"	; CF: ALIVE,OF: ALIVE";
"	adox rbx, rdx";
"	";
"";
"	; add:";
"	; r:x45,f:_<-add(x44,x38,x41)";
"	; CF: ALIVE,OF: KILLED";
"	adcx r12, rbx";
"	; fr:r15,rcx,r8";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x4:rax"",""x1:rbp"",""x2:r14"",""x18:rdx"",""x17:r9"",""x39:r10"",""0x0:r11"",""x40:OF"",""x43:r13"",""x44:CF"",""x41:rbx"",""x45:r12""]";
"	;chose >>RANDOMLY<< r15 from candidates :r15, rcx, r8[0].";
"	mov r15,  r13; x47, copying x43 here, cause x43 is needed in a reg for other than x47, namely all: , x47, x48, size: 2";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x4:rax"",""x1:rbp"",""x2:r14"",""x18:rdx"",""x17:r9"",""x39:r10"",""0x0:r11"",""x40:OF"",""x43:r13"",""x44:CF"",""x41:rbx"",""x45:r12"",""x47:r15""]";
"	shrd r15, r12, 51; x47 <- x45||x43 >> 51";
"	; fr:rcx,r8";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x4:rax"",""x1:rbp"",""x2:r14"",""x18:rdx"",""x17:r9"",""x39:r10"",""0x0:r11"",""x40:OF"",""x43:r13"",""x44:CF"",""x41:rbx"",""x45:r12"",""x47:r15""]";
"	;chose >>RANDOMLY<< rcx from candidates :rcx, r8[0].";
"	mov rcx, 0x7ffffffffffff ; moving imm to reg";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x4:rax"",""x1:rbp"",""x2:r14"",""x18:rdx"",""x17:r9"",""x39:r10"",""0x0:r11"",""x40:OF"",""x44:CF"",""x41:rbx"",""x45:r12"",""x47:r15"",""0x7ffffffffffff:rcx"",""x48:r13""]";
"	and r13, rcx; x48 <- x43& 0x7ffffffffffff";
"	; fr:r8";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x4:rax"",""x1:rbp"",""x2:r14"",""x18:rdx"",""x17:r9"",""x39:r10"",""0x0:r11"",""x40:OF"",""x44:CF"",""x41:rbx"",""x45:r12"",""x47:r15"",""0x7ffffffffffff:rcx"",""x48:r13""]";
"	;chose >>RANDOMLY<< r8 from candidates :r8[0].";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x4:rax"",""x1:rbp"",""x2:r14"",""x18:rdx"",""x17:r9"",""x39:r10"",""0x0:r11"",""x40:OF"",""x44:CF"",""x41:rbx"",""x45:r12"",""x47:r15"",""0x7ffffffffffff:rcx"",""x48:r13"",""x8:r8""]";
"	imul r8, [rsi + 0x08 * 1 ], 0x2; x8 <- arg1[1] * 0x2";
"	;CF: KILLED,OF: KILLED";
"	;chose >>saved<< x8 from:arg1[0], x8[1] and candidates: arg1[0], x8";
"	mov rdx, r8; x8 to rdx";
"	; fr:r8";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x4:rax"",""x1:rbp"",""x2:r14"",""x17:r9"",""x39:r10"",""0x0:r11"",""x40:OF"",""x44:CF"",""x41:rbx"",""x45:r12"",""x47:r15"",""0x7ffffffffffff:rcx"",""x48:r13"",""x36:rdx""]";
"	;chose >>RANDOMLY<< r8 from candidates :r8[0].";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x4:rax"",""x1:rbp"",""x2:r14"",""x17:r9"",""x39:r10"",""0x0:r11"",""x40:OF"",""x44:CF"",""x41:rbx"",""x45:r12"",""x47:r15"",""0x7ffffffffffff:rcx"",""x48:r13"",""x36:rdx"",""x35:r8""]";
"	mulx rdx, r8, [rsi + 0x08 * 0 ]; x36, x35<- arg1[0] * x8";
"	;chose >>saved<< arg1[2] from:arg1[2], x2[0] and candidates: arg1[2], x2";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x4:rax"",""x1:rbp"",""x2:r14"",""x17:r9"",""x39:r10"",""0x0:r11"",""x40:OF"",""x44:CF"",""x41:rbx"",""x45:r12"",""x47:r15"",""0x7ffffffffffff:rcx"",""x48:r13"",""x36:rdx"",""x35:r8"",""arg1[2]:rdx""]";
"	; freeing x17 (r9) no dependants anymore";
"	mov r9, rdx; preserving value of x36 into a new reg";
"	mov rdx, [rsi + 0x08 * 2 ]; saving arg1[2] in rdx.";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x4:rax"",""x1:rbp"",""x2:r14"",""x39:r10"",""0x0:r11"",""x40:OF"",""x44:CF"",""x41:rbx"",""x45:r12"",""x47:r15"",""0x7ffffffffffff:rcx"",""x48:r13"",""x36:r9"",""x35:r8"",""arg1[2]:rdx""]";
"	; freeing x39 (r10) no dependants anymore";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x4:rax"",""x1:rbp"",""x2:r14"",""0x0:r11"",""x40:OF"",""x44:CF"",""x41:rbx"",""x45:r12"",""x47:r15"",""0x7ffffffffffff:rcx"",""x48:r13"",""x36:r9"",""x35:r8"",""arg1[2]:rdx"",""x16:r10""]";
"	; freeing x41 (rbx) no dependants anymore";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x4:rax"",""x1:rbp"",""x2:r14"",""0x0:r11"",""x40:OF"",""x44:CF"",""x45:r12"",""x47:r15"",""0x7ffffffffffff:rcx"",""x48:r13"",""x36:r9"",""x35:r8"",""arg1[2]:rdx"",""x16:r10"",""x15:rbx""]";
"	mulx r10, rbx, r14; x16, x15<- arg1[2] * x2";
"	;chose >>saved<< arg1[3] from:arg1[3], x4[0] and candidates: arg1[3], x4";
"	mov rdx, [rsi + 0x08 * 3 ]; arg1[3] to rdx";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x1:rbp"",""x2:r14"",""0x0:r11"",""x40:OF"",""x44:CF"",""x45:r12"",""x47:r15"",""0x7ffffffffffff:rcx"",""x48:r13"",""x36:r9"",""x35:r8"",""x16:r10"",""x15:rbx"",""arg1[3]:rdx"",""x14:rax""]";
"	; freeing x45 (r12) no dependants anymore";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x1:rbp"",""x2:r14"",""0x0:r11"",""x40:OF"",""x44:CF"",""x47:r15"",""0x7ffffffffffff:rcx"",""x48:r13"",""x36:r9"",""x35:r8"",""x16:r10"",""x15:rbx"",""arg1[3]:rdx"",""x14:rax"",""x13:r12""]";
"	mulx rax, r12, rax; x14, x13<- arg1[3] * x4";
"	";
"";
"	; add:";
"	; r:x73,f:x74<-add(0x0,x15,x13)";
"	; CF: KILLED,OF: KILLED";
"	;chose >>saved<< c_xor_adx from:c_add, c_xor_adx, c_test_adx[1] and candidates: c_add, c_xor_adx, c_test_adx";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x1:rbp"",""x2:r14"",""0x0:r11"",""x40:OF"",""x44:CF"",""x47:r15"",""0x7ffffffffffff:rcx"",""x48:r13"",""x36:r9"",""x35:r8"",""x16:r10"",""arg1[3]:rdx"",""x14:rax"",""x13:r12"",""x73:rbx""]";
"	;chose 0x7ffffffffffff to spill because list of spills:arg1[1]Larg1[1]Larg1[1]Larg1[1]Larg1[1]L0x7ffffffffffffL0x7ffffffffffffL0x7ffffffffffffL0x7ffffffffffffL0x7ffffffffffffLarg1[2]Larg1[2]Larg1[4] and candidates: 0x7ffffffffffff, arg1[3]";
"	; freeing, i.e. spilling 0x7ffffffffffff, because I am out of ideas";
"	; allocs: out1(rdi),arg1(rsi),x1(rbp),x2(r14),0x0(r11),x47(r15),0x7ffffffffffff(rcx),x48(r13),x36(r9),x35(r8),x16(r10),arg1[3](rdx),x14(rax),x13(r12),x73(rbx); clobs x73,x74,0x0,x15,x13,x15; will spare: 0x7ffffffffffff ";
"	xor rcx, rcx";
"	;chose >>saved<< OF from:CF, OF[1] and candidates: CF, OF";
"	adox rbx, r12";
"	";
"";
"	; add:";
"	; r:x75,f:_<-add(x74,x16,x14)";
"	; CF: ZERO,OF: ALIVE";
"	adox r10, rax";
"	";
"";
"	; add:";
"	; r:x77,f:x78<-add(0x0,x35,x73)";
"	; CF: ZERO,OF: KILLED";
"	adcx r8, rbx";
"	";
"";
"	; add:";
"	; r:x81,f:x82<-add(0x0,x47,x77)";
"	; CF: ALIVE,OF: KILLED";
"	dec rcx; OF<-0x0, preserve CF 3";
"	adox r15, r8";
"	";
"";
"	; add:";
"	; r:x79,f:_<-add(x78,x36,x75)";
"	; CF: ALIVE,OF: ALIVE";
"	adcx r9, r10";
"	";
"";
"	; add:";
"	; r:x83,f:_<-add(x82,x79)";
"	; CF: KILLED,OF: ALIVE";
"	; fr:r11";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x1:rbp"",""x2:r14"",""x48:r13"",""arg1[3]:rdx"",""x14:rax"",""x13:r12"",""x73:rbx"",""x75:r10"",""x77:r8"",""x78:CF"",""x81:r15"",""-0x1:rcx"",""x82:OF"",""x83:r9""]";
"	;chose >>RANDOMLY<< r11 from candidates :r11[0].";
"	mov r11, 0x0 ; moving imm to reg";
"	adox r9, r11";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x1:rbp"",""x2:r14"",""x48:r13"",""arg1[3]:rdx"",""x14:rax"",""x13:r12"",""x73:rbx"",""x75:r10"",""x77:r8"",""x78:CF"",""x81:r15"",""-0x1:rcx"",""x82:OF"",""x83:r9"",""0x0:r11""]";
"	; freeing x14 (rax) no dependants anymore";
"	mov rax,  r15; x84, copying x81 here, cause x81 is needed in a reg for other than x84, namely all: , x84, x85, size: 2";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x1:rbp"",""x2:r14"",""x48:r13"",""arg1[3]:rdx"",""x13:r12"",""x73:rbx"",""x75:r10"",""x77:r8"",""x78:CF"",""x81:r15"",""-0x1:rcx"",""x82:OF"",""x83:r9"",""0x0:r11"",""x84:rax""]";
"	shrd rax, r9, 51; x84 <- x83||x81 >> 51";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x1:rbp"",""x2:r14"",""x48:r13"",""arg1[3]:rdx"",""x13:r12"",""x73:rbx"",""x75:r10"",""x77:r8"",""x78:CF"",""x81:r15"",""-0x1:rcx"",""x82:OF"",""x83:r9"",""0x0:r11"",""x84:rax""]";
"	; freeing x13 (r12) no dependants anymore";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x1:rbp"",""x2:r14"",""x48:r13"",""arg1[3]:rdx"",""x73:rbx"",""x75:r10"",""x77:r8"",""x78:CF"",""x81:r15"",""-0x1:rcx"",""x82:OF"",""x83:r9"",""0x0:r11"",""x84:rax"",""x7:r12""]";
"	imul r12, [rsi + 0x08 * 2 ], 0x2; x7 <- arg1[2] * 0x2";
"	;CF: KILLED,OF: KILLED";
"	;chose >>saved<< x7 from:arg1[0], x7[1] and candidates: arg1[0], x7";
"	mov rdx, r12; x7 to rdx";
"	; fr:r12";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x1:rbp"",""x2:r14"",""x48:r13"",""x73:rbx"",""x75:r10"",""x77:r8"",""x78:CF"",""x81:r15"",""-0x1:rcx"",""x82:OF"",""x83:r9"",""0x0:r11"",""x84:rax"",""x7:rdx""]";
"	;chose >>RANDOMLY<< r12 from candidates :r12[0].";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x1:rbp"",""x2:r14"",""x48:r13"",""x73:rbx"",""x75:r10"",""x77:r8"",""x78:CF"",""x81:r15"",""-0x1:rcx"",""x82:OF"",""x83:r9"",""0x0:r11"",""x84:rax"",""x7:rdx"",""x34:r12""]";
"	; freeing x73 (rbx) no dependants anymore";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x1:rbp"",""x2:r14"",""x48:r13"",""x75:r10"",""x77:r8"",""x78:CF"",""x81:r15"",""-0x1:rcx"",""x82:OF"",""x83:r9"",""0x0:r11"",""x84:rax"",""x7:rdx"",""x34:r12"",""x33:rbx""]";
"	mulx r12, rbx, [rsi + 0x08 * 0 ]; x34, x33<- arg1[0] * x7";
"	;chose >>saved<< arg1[1] from:arg1[1], arg1[1][0] and candidates: arg1[1], arg1[1]";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x1:rbp"",""x2:r14"",""x48:r13"",""x75:r10"",""x77:r8"",""x78:CF"",""x81:r15"",""-0x1:rcx"",""x82:OF"",""x83:r9"",""0x0:r11"",""x84:rax"",""x7:rdx"",""x34:r12"",""x33:rbx"",""arg1[1]:rdx""]";
"	; freeing x75 (r10) no dependants anymore";
"	mov r10, rdx; preserving value of x7 into a new reg";
"	mov rdx, [rsi + 0x08 * 1 ]; saving arg1[1] in rdx.";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x1:rbp"",""x2:r14"",""x48:r13"",""x77:r8"",""x78:CF"",""x81:r15"",""-0x1:rcx"",""x82:OF"",""x83:r9"",""0x0:r11"",""x84:rax"",""x7:r10"",""x34:r12"",""x33:rbx"",""arg1[1]:rdx""]";
"	; freeing x77 (r8) no dependants anymore";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x1:rbp"",""x2:r14"",""x48:r13"",""x78:CF"",""x81:r15"",""-0x1:rcx"",""x82:OF"",""x83:r9"",""0x0:r11"",""x84:rax"",""x7:r10"",""x34:r12"",""x33:rbx"",""arg1[1]:rdx"",""x28:r8""]";
"	; freeing x83 (r9) no dependants anymore";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x1:rbp"",""x2:r14"",""x48:r13"",""x78:CF"",""x81:r15"",""-0x1:rcx"",""x82:OF"",""0x0:r11"",""x84:rax"",""x7:r10"",""x34:r12"",""x33:rbx"",""arg1[1]:rdx"",""x28:r8"",""x27:r9""]";
"	mulx r8, r9, [rsi + 0x08 * 1 ]; x28, x27<- arg1[1] * arg1[1]";
"	;chose >>saved<< x2 from:arg1[3], x2[1] and candidates: arg1[3], x2";
"	mov rdx, r14; x2 to rdx";
"	; fr:r14";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x1:rbp"",""x48:r13"",""x78:CF"",""x81:r15"",""-0x1:rcx"",""x82:OF"",""0x0:r11"",""x84:rax"",""x7:r10"",""x34:r12"",""x33:rbx"",""x28:r8"",""x27:r9"",""x12:rdx""]";
"	;chose >>RANDOMLY<< r14 from candidates :r14[0].";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x1:rbp"",""x48:r13"",""x78:CF"",""x81:r15"",""-0x1:rcx"",""x82:OF"",""0x0:r11"",""x84:rax"",""x7:r10"",""x34:r12"",""x33:rbx"",""x28:r8"",""x27:r9"",""x12:rdx"",""x11:r14""]";
"	mulx rdx, r14, [rsi + 0x08 * 3 ]; x12, x11<- arg1[3] * x2";
"	";
"";
"	; add:";
"	; r:x65,f:x66<-add(0x0,x27,x11)";
"	; CF: KILLED,OF: KILLED";
"	;chose >>saved<< c_add from:c_add, c_xor_adx, c_test_adx[0] and candidates: c_add, c_xor_adx, c_test_adx";
"	add r9, r14; could be done better, if r0 has been u8 as well";
"	";
"";
"	; add:";
"	; r:x69,f:x70<-add(0x0,x33,x65)";
"	; CF: ALIVE,OF: KILLED";
"	inc rcx; OF<-0x0, preserve CF 1";
"	adox rbx, r9";
"	";
"";
"	; add:";
"	; r:x67,f:_<-add(x66,x28,x12)";
"	; CF: ALIVE,OF: ALIVE";
"	adcx r8, rdx";
"	";
"";
"	; add:";
"	; r:x71,f:_<-add(x70,x34,x67)";
"	; CF: KILLED,OF: ALIVE";
"	adox r12, r8";
"	";
"";
"	; add:";
"	; r:x86,f:x87<-add(0x0,x84,x69)";
"	; CF: KILLED,OF: KILLED";
"	;chose >>saved<< c_test_adx from:c_add, c_xor_adx, c_test_adx[2] and candidates: c_add, c_xor_adx, c_test_adx";
"	test al, al";
"	;chose >>saved<< CF from:CF, OF[0] and candidates: CF, OF";
"	adox rax, rbx";
"	";
"";
"	; add:";
"	; r:x88,f:_<-add(x87,x71)";
"	; CF: ZERO,OF: ALIVE";
"	adox r12, rcx";
"	; fr:r11";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x1:rbp"",""x48:r13"",""x81:r15"",""0x0:rcx"",""x7:r10"",""x12:rdx"",""x11:r14"",""x65:r9"",""x66:CF"",""x69:rbx"",""x67:r8"",""x86:rax"",""x87:OF"",""x88:r12""]";
"	;chose >>RANDOMLY<< r11 from candidates :r11[0].";
"	mov r11,  rax; x89, copying x86 here, cause x86 is needed in a reg for other than x89, namely all: , x90, x89, size: 2";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x1:rbp"",""x48:r13"",""x81:r15"",""0x0:rcx"",""x7:r10"",""x12:rdx"",""x11:r14"",""x65:r9"",""x66:CF"",""x69:rbx"",""x67:r8"",""x86:rax"",""x87:OF"",""x88:r12"",""x89:r11""]";
"	shrd r11, r12, 51; x89 <- x88||x86 >> 51";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x1:rbp"",""x48:r13"",""x81:r15"",""0x0:rcx"",""x7:r10"",""x12:rdx"",""x11:r14"",""x65:r9"",""x66:CF"",""x69:rbx"",""x67:r8"",""x86:rax"",""x87:OF"",""x88:r12"",""x89:r11""]";
"	; freeing x12 (rdx) no dependants anymore";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x1:rbp"",""x48:r13"",""x81:r15"",""0x0:rcx"",""x7:r10"",""x11:r14"",""x65:r9"",""x66:CF"",""x69:rbx"",""x67:r8"",""x86:rax"",""x87:OF"",""x88:r12"",""x89:r11"",""x6:rdx""]";
"	imul rdx, [rsi + 0x08 * 3 ], 0x2; x6 <- arg1[3] * 0x2";
"	;CF: KILLED,OF: KILLED";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x1:rbp"",""x48:r13"",""x81:r15"",""0x0:rcx"",""x7:r10"",""x11:r14"",""x65:r9"",""x66:CF"",""x69:rbx"",""x67:r8"",""x86:rax"",""x87:OF"",""x88:r12"",""x89:r11"",""x6:rdx""]";
"	; freeing x11 (r14) no dependants anymore";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x1:rbp"",""x48:r13"",""x81:r15"",""0x0:rcx"",""x7:r10"",""x65:r9"",""x66:CF"",""x69:rbx"",""x67:r8"",""x86:rax"",""x87:OF"",""x88:r12"",""x89:r11"",""x6:rdx"",""x32:r14""]";
"	; freeing x65 (r9) no dependants anymore";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x1:rbp"",""x48:r13"",""x81:r15"",""0x0:rcx"",""x7:r10"",""x66:CF"",""x69:rbx"",""x67:r8"",""x86:rax"",""x87:OF"",""x88:r12"",""x89:r11"",""x6:rdx"",""x32:r14"",""x31:r9""]";
"	mulx r14, r9, [rsi + 0x08 * 0 ]; x32, x31<- arg1[0] * x6";
"	;chose >>saved<< arg1[4] from:arg1[4], x1[0] and candidates: arg1[4], x1";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x1:rbp"",""x48:r13"",""x81:r15"",""0x0:rcx"",""x7:r10"",""x66:CF"",""x69:rbx"",""x67:r8"",""x86:rax"",""x87:OF"",""x88:r12"",""x89:r11"",""x6:rdx"",""x32:r14"",""x31:r9"",""arg1[4]:rdx""]";
"	; freeing x69 (rbx) no dependants anymore";
"	mov rbx, rdx; preserving value of x6 into a new reg";
"	mov rdx, [rsi + 0x08 * 4 ]; saving arg1[4] in rdx.";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x48:r13"",""x81:r15"",""0x0:rcx"",""x7:r10"",""x66:CF"",""x67:r8"",""x86:rax"",""x87:OF"",""x88:r12"",""x89:r11"",""x6:rbx"",""x32:r14"",""x31:r9"",""arg1[4]:rdx"",""x10:rbp""]";
"	; freeing x67 (r8) no dependants anymore";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x48:r13"",""x81:r15"",""0x0:rcx"",""x7:r10"",""x66:CF"",""x86:rax"",""x87:OF"",""x88:r12"",""x89:r11"",""x6:rbx"",""x32:r14"",""x31:r9"",""arg1[4]:rdx"",""x10:rbp"",""x9:r8""]";
"	mulx rbp, r8, rbp; x10, x9<- arg1[4] * x1";
"	;chose >>saved<< x7 from:arg1[1], x7[1] and candidates: arg1[1], x7";
"	mov rdx, r10; x7 to rdx";
"	; fr:r10";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x48:r13"",""x81:r15"",""0x0:rcx"",""x66:CF"",""x86:rax"",""x87:OF"",""x88:r12"",""x89:r11"",""x6:rbx"",""x32:r14"",""x31:r9"",""x10:rbp"",""x9:r8"",""x26:rdx""]";
"	;chose >>RANDOMLY<< r10 from candidates :r10[0].";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x48:r13"",""x81:r15"",""0x0:rcx"",""x66:CF"",""x86:rax"",""x87:OF"",""x88:r12"",""x89:r11"",""x6:rbx"",""x32:r14"",""x31:r9"",""x10:rbp"",""x9:r8"",""x26:rdx"",""x25:r10""]";
"	mulx rdx, r10, [rsi + 0x08 * 1 ]; x26, x25<- arg1[1] * x7";
"	";
"";
"	; add:";
"	; r:x57,f:x58<-add(0x0,x25,x9)";
"	; CF: KILLED,OF: KILLED";
"	;chose >>saved<< c_xor_adx from:c_add, c_xor_adx, c_test_adx[1] and candidates: c_add, c_xor_adx, c_test_adx";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x48:r13"",""x81:r15"",""0x0:rcx"",""x66:CF"",""x86:rax"",""x87:OF"",""x88:r12"",""x89:r11"",""x6:rbx"",""x32:r14"",""x31:r9"",""x10:rbp"",""x9:r8"",""x26:rdx"",""x57:r10""]";
"	; freeing x88 (r12) no dependants anymore";
"	xor r12, r12";
"	;chose >>saved<< CF from:CF, OF[0] and candidates: CF, OF";
"	adox r10, r8";
"	";
"";
"	; add:";
"	; r:x61,f:x62<-add(0x0,x31,x57)";
"	; CF: ZERO,OF: ALIVE";
"	adcx r9, r10";
"	";
"";
"	; add:";
"	; r:x59,f:_<-add(x58,x26,x10)";
"	; CF: ALIVE,OF: ALIVE";
"	adox rdx, rbp";
"	";
"";
"	; add:";
"	; r:x91,f:x92<-add(0x0,x89,x61)";
"	; CF: ALIVE,OF: KILLED";
"	dec r12; OF<-0x0, preserve CF 3";
"	adox r11, r9";
"	";
"";
"	; add:";
"	; r:x63,f:_<-add(x62,x32,x59)";
"	; CF: ALIVE,OF: ALIVE";
"	adcx r14, rdx";
"	";
"";
"	; add:";
"	; r:x93,f:_<-add(x92,x63)";
"	; CF: KILLED,OF: ALIVE";
"	; fr:rcx";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x48:r13"",""x81:r15"",""x86:rax"",""x6:rbx"",""x10:rbp"",""x9:r8"",""x57:r10"",""x61:r9"",""x62:CF"",""x59:rdx"",""x91:r11"",""-0x1:r12"",""x92:OF"",""x93:r14""]";
"	;chose >>RANDOMLY<< rcx from candidates :rcx[0].";
"	mov rcx, 0x0 ; moving imm to reg";
"	adox r14, rcx";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x48:r13"",""x81:r15"",""x86:rax"",""x6:rbx"",""x10:rbp"",""x9:r8"",""x57:r10"",""x61:r9"",""x62:CF"",""x59:rdx"",""x91:r11"",""-0x1:r12"",""x92:OF"",""x93:r14"",""0x0:rcx""]";
"	; freeing x10 (rbp) no dependants anymore";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x48:r13"",""x81:r15"",""x86:rax"",""x6:rbx"",""x9:r8"",""x57:r10"",""x61:r9"",""x62:CF"",""x59:rdx"",""x91:r11"",""-0x1:r12"",""x92:OF"",""x93:r14"",""0x0:rcx"",""x3:rbp""]";
"	imul rbp, [rsi + 0x08 * 4 ], 0x2; x3 <- arg1[4] * 0x2";
"	;CF: KILLED,OF: KILLED";
"	;chose >>saved<< x3 from:arg1[0], x3[1] and candidates: arg1[0], x3";
"	mov rdx, rbp; x3 to rdx";
"	; fr:rbp";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x48:r13"",""x81:r15"",""x86:rax"",""x6:rbx"",""x9:r8"",""x57:r10"",""x61:r9"",""x62:CF"",""x91:r11"",""-0x1:r12"",""x92:OF"",""x93:r14"",""0x0:rcx"",""x30:rdx""]";
"	;chose >>RANDOMLY<< rbp from candidates :rbp[0].";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x48:r13"",""x81:r15"",""x86:rax"",""x6:rbx"",""x9:r8"",""x57:r10"",""x61:r9"",""x62:CF"",""x91:r11"",""-0x1:r12"",""x92:OF"",""x93:r14"",""0x0:rcx"",""x30:rdx"",""x29:rbp""]";
"	mulx rdx, rbp, [rsi + 0x08 * 0 ]; x30, x29<- arg1[0] * x3";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x48:r13"",""x81:r15"",""x86:rax"",""x6:rbx"",""x9:r8"",""x57:r10"",""x61:r9"",""x62:CF"",""x91:r11"",""-0x1:r12"",""x92:OF"",""x93:r14"",""0x0:rcx"",""x30:rdx"",""x29:rbp""]";
"	; freeing x9 (r8) no dependants anymore";
"	mov r8,  r11; x94, copying x91 here, cause x91 is needed in a reg for other than x94, namely all: , x95, x94, size: 2";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x48:r13"",""x81:r15"",""x86:rax"",""x6:rbx"",""x57:r10"",""x61:r9"",""x62:CF"",""x91:r11"",""-0x1:r12"",""x92:OF"",""x93:r14"",""0x0:rcx"",""x30:rdx"",""x29:rbp"",""x94:r8""]";
"	shrd r8, r14, 51; x94 <- x93||x91 >> 51";
"	;chose >>saved<< arg1[1] from:arg1[1], x6[0] and candidates: arg1[1], x6";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x48:r13"",""x81:r15"",""x86:rax"",""x6:rbx"",""x57:r10"",""x61:r9"",""x62:CF"",""x91:r11"",""-0x1:r12"",""x92:OF"",""x93:r14"",""0x0:rcx"",""x30:rdx"",""x29:rbp"",""x94:r8"",""arg1[1]:rdx""]";
"	; freeing x57 (r10) no dependants anymore";
"	mov r10, rdx; preserving value of x30 into a new reg";
"	mov rdx, [rsi + 0x08 * 1 ]; saving arg1[1] in rdx.";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x48:r13"",""x81:r15"",""x86:rax"",""x61:r9"",""x62:CF"",""x91:r11"",""-0x1:r12"",""x92:OF"",""x93:r14"",""0x0:rcx"",""x30:r10"",""x29:rbp"",""x94:r8"",""arg1[1]:rdx"",""x24:rbx""]";
"	; freeing x61 (r9) no dependants anymore";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x48:r13"",""x81:r15"",""x86:rax"",""x62:CF"",""x91:r11"",""-0x1:r12"",""x92:OF"",""x93:r14"",""0x0:rcx"",""x30:r10"",""x29:rbp"",""x94:r8"",""arg1[1]:rdx"",""x24:rbx"",""x23:r9""]";
"	mulx rbx, r9, rbx; x24, x23<- arg1[1] * x6";
"	;chose >>saved<< arg1[2] from:arg1[2], arg1[2][1] and candidates: arg1[2], arg1[2]";
"	mov rdx, [rsi + 0x08 * 2 ]; arg1[2] to rdx";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x48:r13"",""x81:r15"",""x86:rax"",""x62:CF"",""x91:r11"",""-0x1:r12"",""x92:OF"",""x93:r14"",""0x0:rcx"",""x30:r10"",""x29:rbp"",""x94:r8"",""x24:rbx"",""x23:r9"",""arg1[2]:rdx""]";
"	; freeing x93 (r14) no dependants anymore";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x48:r13"",""x81:r15"",""x86:rax"",""x62:CF"",""x91:r11"",""-0x1:r12"",""x92:OF"",""0x0:rcx"",""x30:r10"",""x29:rbp"",""x94:r8"",""x24:rbx"",""x23:r9"",""arg1[2]:rdx"",""x20:r14""]";
"	; freeing 0x0 (rcx, since all are neeed, but this one is just an immediate value.";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x48:r13"",""x81:r15"",""x86:rax"",""x62:CF"",""x91:r11"",""-0x1:r12"",""x92:OF"",""x30:r10"",""x29:rbp"",""x94:r8"",""x24:rbx"",""x23:r9"",""arg1[2]:rdx"",""x20:r14"",""x19:rcx""]";
"	mulx r14, rcx, [rsi + 0x08 * 2 ]; x20, x19<- arg1[2] * arg1[2]";
"	";
"";
"	; add:";
"	; r:x49,f:x50<-add(0x0,x23,x19)";
"	; CF: KILLED,OF: KILLED";
"	;chose >>saved<< c_xor_adx from:c_add, c_xor_adx, c_test_adx[1] and candidates: c_add, c_xor_adx, c_test_adx";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x48:r13"",""x81:r15"",""x86:rax"",""x62:CF"",""x91:r11"",""-0x1:r12"",""x92:OF"",""x30:r10"",""x29:rbp"",""x94:r8"",""x24:rbx"",""arg1[2]:rdx"",""x20:r14"",""x19:rcx"",""x49:r9""]";
"	;chose arg1[2] to spill because list of spills:arg1[1]Larg1[1]Larg1[1]Larg1[1]Larg1[1]L0x7ffffffffffffL0x7ffffffffffffL0x7ffffffffffffL0x7ffffffffffffL0x7ffffffffffffLarg1[2]Larg1[2]Larg1[4] and candidates: -0x1, arg1[2]";
"	; freeing, i.e. spilling arg1[2], because I am out of ideas";
"	; allocs: out1(rdi),arg1(rsi),x48(r13),x81(r15),x86(rax),x91(r11),-0x1(r12),x30(r10),x29(rbp),x94(r8),x24(rbx),arg1[2](rdx),x20(r14),x19(rcx),x49(r9); clobs x49,x50,0x0,x23,x19,x23; will spare: arg1[2] ";
"	xor rdx, rdx";
"	;chose >>saved<< CF from:CF, OF[0] and candidates: CF, OF";
"	adox r9, rcx";
"	";
"";
"	; add:";
"	; r:x53,f:x54<-add(0x0,x29,x49)";
"	; CF: ZERO,OF: ALIVE";
"	adcx rbp, r9";
"	";
"";
"	; add:";
"	; r:x51,f:_<-add(x50,x24,x20)";
"	; CF: ALIVE,OF: ALIVE";
"	adox rbx, r14";
"	";
"";
"	; add:";
"	; r:x96,f:x97<-add(0x0,x94,x53)";
"	; CF: ALIVE,OF: KILLED";
"	inc r12; OF<-0x0, preserve CF 1";
"	adox r8, rbp";
"	";
"";
"	; add:";
"	; r:x55,f:_<-add(x54,x30,x51)";
"	; CF: ALIVE,OF: ALIVE";
"	adcx r10, rbx";
"	";
"";
"	; add:";
"	; r:x98,f:_<-add(x97,x55)";
"	; CF: KILLED,OF: ALIVE";
"	adox r10, r12";
"	; fr:rdx";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x48:r13"",""x81:r15"",""x86:rax"",""x91:r11"",""x20:r14"",""x19:rcx"",""x49:r9"",""0x0:r12"",""x53:rbp"",""x54:CF"",""x51:rbx"",""x96:r8"",""x97:OF"",""x98:r10""]";
"	;chose >>RANDOMLY<< rdx from candidates :rdx[0].";
"	mov rdx,  r8; x99, copying x96 here, cause x96 is needed in a reg for other than x99, namely all: , x99, x100, size: 2";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x48:r13"",""x81:r15"",""x86:rax"",""x91:r11"",""x20:r14"",""x19:rcx"",""x49:r9"",""0x0:r12"",""x53:rbp"",""x54:CF"",""x51:rbx"",""x96:r8"",""x97:OF"",""x98:r10"",""x99:rdx""]";
"	shrd rdx, r10, 51; x99 <- x98||x96 >> 51";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x48:r13"",""x81:r15"",""x86:rax"",""x91:r11"",""x20:r14"",""x19:rcx"",""x49:r9"",""0x0:r12"",""x53:rbp"",""x54:CF"",""x51:rbx"",""x96:r8"",""x97:OF"",""x98:r10"",""x101:rdx""]";
"	imul rdx, rdx, 0x13; x101 <- x99 * 0x13";
"	;CF: KILLED,OF: KILLED";
"	";
"";
"	; add:";
"	; r:x102,f:_<-add(x48,x101)";
"	; CF: KILLED,OF: KILLED";
"	lea r13, [r13+rdx]";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x81:r15"",""x86:rax"",""x91:r11"",""x20:r14"",""x19:rcx"",""x49:r9"",""0x0:r12"",""x53:rbp"",""x54:CF"",""x51:rbx"",""x96:r8"",""x97:OF"",""x98:r10"",""x101:rdx"",""x102:r13""]";
"	; freeing x20 (r14) no dependants anymore";
"	mov r14,  r13; x103, copying x102 here, cause x102 is needed in a reg for other than x103, namely all: , x103, x104, size: 2";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x81:r15"",""x86:rax"",""x91:r11"",""x19:rcx"",""x49:r9"",""0x0:r12"",""x53:rbp"",""x54:CF"",""x51:rbx"",""x96:r8"",""x97:OF"",""x98:r10"",""x101:rdx"",""x102:r13"",""x103:r14""]";
"	shr r14, 51; x103 <- x102>> 51";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x81:r15"",""x86:rax"",""x91:r11"",""x19:rcx"",""x49:r9"",""0x0:r12"",""x53:rbp"",""x54:CF"",""x51:rbx"",""x96:r8"",""x97:OF"",""x98:r10"",""x101:rdx"",""x102:r13"",""x103:r14""]";
"	; freeing x19 (rcx) no dependants anymore";
"	mov rcx, 0x7ffffffffffff ; moving imm to reg";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x86:rax"",""x91:r11"",""x49:r9"",""0x0:r12"",""x53:rbp"",""x54:CF"",""x51:rbx"",""x96:r8"",""x97:OF"",""x98:r10"",""x101:rdx"",""x102:r13"",""x103:r14"",""0x7ffffffffffff:rcx"",""x85:r15""]";
"	and r15, rcx; x85 <- x81& 0x7ffffffffffff";
"	";
"";
"	; add:";
"	; r:x105,f:_<-add(x103,x85)";
"	; CF: KILLED,OF: KILLED";
"	lea r14, [r14+r15]";
"	; fr:";
"	; allocatedR: ;-- allocation: [""out1:rdi"",""arg1:rsi"",""x86:rax"",""x91:r11"",""x49:r9"",""0x0:r12"",""x53:rbp"",""x54:CF"",""x51:rbx"",""x96:r8"",""x97:OF"",""x98:r10"",""x101:rdx"",""x102:r13"",""0x7ffffffffffff:rcx"",""x85:r15"",""x105:r14""]";
"	; freeing x49 (r9) no dependants anymore";
"	mov r9,  r14; x107, copying x105 here, cause x105 is needed in a reg for other than x107, namely all: , x107, x106, size: 2";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x86:rax"",""x91:r11"",""0x0:r12"",""x53:rbp"",""x54:CF"",""x51:rbx"",""x96:r8"",""x97:OF"",""x98:r10"",""x101:rdx"",""x102:r13"",""0x7ffffffffffff:rcx"",""x85:r15"",""x105:r14"",""x107:r9""]";
"	and r9, rcx; x107 <- x105& 0x7ffffffffffff";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x86:rax"",""0x0:r12"",""x53:rbp"",""x54:CF"",""x51:rbx"",""x96:r8"",""x97:OF"",""x98:r10"",""x101:rdx"",""x102:r13"",""0x7ffffffffffff:rcx"",""x85:r15"",""x105:r14"",""x107:r9"",""x95:r11""]";
"	and r11, rcx; x95 <- x91& 0x7ffffffffffff";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x86:rax"",""0x0:r12"",""x53:rbp"",""x54:CF"",""x51:rbx"",""x96:r8"",""x97:OF"",""x98:r10"",""x101:rdx"",""x102:r13"",""0x7ffffffffffff:rcx"",""x85:r15"",""x105:r14"",""x107:r9"",""x95:r11""]";
"	mov [rdi + 0x08 * 3 ], r11; out1[3] = x95";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""x86:rax"",""0x0:r12"",""x53:rbp"",""x54:CF"",""x51:rbx"",""x96:r8"",""x97:OF"",""x98:r10"",""x101:rdx"",""x102:r13"",""0x7ffffffffffff:rcx"",""x85:r15"",""x107:r9"",""x95:r11"",""x106:r14""]";
"	shr r14, 51; x106 <- x105>> 51";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""0x0:r12"",""x53:rbp"",""x54:CF"",""x51:rbx"",""x96:r8"",""x97:OF"",""x98:r10"",""x101:rdx"",""x102:r13"",""0x7ffffffffffff:rcx"",""x85:r15"",""x107:r9"",""x95:r11"",""x106:r14"",""x90:rax""]";
"	and rax, rcx; x90 <- x86& 0x7ffffffffffff";
"	";
"";
"	; add:";
"	; r:x108,f:_<-add(x106,x90)";
"	; CF: KILLED,OF: KILLED";
"	lea r14, [r14+rax]";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""0x0:r12"",""x53:rbp"",""x54:CF"",""x51:rbx"",""x96:r8"",""x97:OF"",""x98:r10"",""x101:rdx"",""x102:r13"",""0x7ffffffffffff:rcx"",""x85:r15"",""x107:r9"",""x95:r11"",""x90:rax"",""x108:r14""]";
"	mov [rdi + 0x08 * 2 ], r14; out1[2] = x108";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""0x0:r12"",""x53:rbp"",""x54:CF"",""x51:rbx"",""x96:r8"",""x97:OF"",""x98:r10"",""x101:rdx"",""x102:r13"",""0x7ffffffffffff:rcx"",""x85:r15"",""x95:r11"",""x90:rax"",""x108:r14"",""x107:r9""]";
"	mov [rdi + 0x08 * 1 ], r9; out1[1] = x107";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""0x0:r12"",""x53:rbp"",""x54:CF"",""x51:rbx"",""x97:OF"",""x98:r10"",""x101:rdx"",""x102:r13"",""0x7ffffffffffff:rcx"",""x85:r15"",""x95:r11"",""x90:rax"",""x108:r14"",""x107:r9"",""x100:r8""]";
"	and r8, rcx; x100 <- x96& 0x7ffffffffffff";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""0x0:r12"",""x53:rbp"",""x54:CF"",""x51:rbx"",""x97:OF"",""x98:r10"",""x101:rdx"",""x102:r13"",""0x7ffffffffffff:rcx"",""x85:r15"",""x95:r11"",""x90:rax"",""x108:r14"",""x107:r9"",""x100:r8""]";
"	mov [rdi + 0x08 * 4 ], r8; out1[4] = x100";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""0x0:r12"",""x53:rbp"",""x54:CF"",""x51:rbx"",""x97:OF"",""x98:r10"",""x101:rdx"",""0x7ffffffffffff:rcx"",""x85:r15"",""x95:r11"",""x90:rax"",""x108:r14"",""x107:r9"",""x100:r8"",""x104:r13""]";
"	and r13, rcx; x104 <- x102& 0x7ffffffffffff";
"	;-- allocation: [""out1:rdi"",""arg1:rsi"",""0x0:r12"",""x53:rbp"",""x54:CF"",""x51:rbx"",""x97:OF"",""x98:r10"",""x101:rdx"",""0x7ffffffffffff:rcx"",""x85:r15"",""x95:r11"",""x90:rax"",""x108:r14"",""x107:r9"",""x100:r8"",""x104:r13""]";
"	mov [rdi + 0x08 * 0 ], r13; out1[0] = x104";
"	mov rbx, [rsp + 0x08 * 0 ]; restoring from stack";
"	mov rbp, [rsp + 0x08 * 1 ]; restoring from stack";
"	mov r12, [rsp + 0x08 * 2 ]; restoring from stack";
"	mov r13, [rsp + 0x08 * 3 ]; restoring from stack";
"	mov r14, [rsp + 0x08 * 4 ]; restoring from stack";
"	mov r15, [rsp + 0x08 * 5 ]; restoring from stack";
"	add rsp, 0x38 ";
"	ret";
"; cyclecount: 209";
"; seed 10 ";
"; time Needed: 423230 ms/ 10000 runs";
"; Time Spent By Invoking Make (measure): 361906 ms";
"; Ratio (time for make measure)/elapsed: 0.8551047893580322";
"; Reverts a mutation because test was slower: 8966";
"; number tried mutation Permutation: 3369";
"; number tried mutation Spill: 3333";
"; number tried mutation Decision: 3298";
"; FailedEvals (cannot swap because of edge to the next node): 2235";
""].
