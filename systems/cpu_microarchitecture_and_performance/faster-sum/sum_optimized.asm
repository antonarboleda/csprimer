; Thirty-two 128-bit registers V0-V31.
; Thirty-two 64-bit registers D0-D31.
; Thirty-two 32-bit registers S0-S31.
; Thirty-two 16-bit registers H0-H31.
; Thirty-two 8-bit registers B0-B31.
; A combination of registers from these views.
       0: 3f 04 00 71   cmp     w1, #1
       4: eb 01 00 54   b.lt    0x40 <ltmp0+0x40>
       8: ef 3b bc 6d   stp     d15, d14, [sp, #-64]! ; save register values on stack
       c: ed 33 01 6d   stp     d13, d12, [sp, #16]
      10: eb 2b 02 6d   stp     d11, d10, [sp, #32]
      14: e9 23 03 6d   stp     d9, d8, [sp, #48]
      18: e8 03 01 2a   mov     w8, w1
      1c: 09 05 00 d1   sub     x9, x8, #1
      20: 3f f1 00 f1   cmp     x9, #60
      24: 22 01 00 54   b.hs    0x48 <ltmp0+0x48>
      28: 09 00 80 d2   mov     x9, #0
      2c: 0f 00 80 52   mov     w15, #0
      30: 0e 00 80 52   mov     w14, #0
      34: 0d 00 80 52   mov     w13, #0
      38: 0c 00 80 52   mov     w12, #0
      3c: 49 00 00 14   b       0x160 <ltmp0+0x160>
      40: 00 00 80 52   mov     w0, #0
      44: c0 03 5f d6   ret
      48: 00 e4 00 6f   movi.2d v0, #0000000000000000 ; v
      4c: 29 fd 42 d3   lsr     x9, x9, #2
      50: 01 e4 00 6f   movi.2d v1, #0000000000000000
      54: 2a 05 00 91   add     x10, x9, #1
      58: 02 e4 00 6f   movi.2d v2, #0000000000000000
      5c: 4b e9 7c 92   and     x11, x10, #0x7ffffffffffffff0
      60: 03 e4 00 6f   movi.2d v3, #0000000000000000
      64: 69 f5 7e d3   lsl     x9, x11, #2
      68: 04 e4 00 6f   movi.2d v4, #0000000000000000
      6c: 0c 00 02 91   add     x12, x0, #128
      70: 05 e4 00 6f   movi.2d v5, #0000000000000000
      74: ed 03 0b aa   mov     x13, x11
      78: 06 e4 00 6f   movi.2d v6, #0000000000000000
      7c: 07 e4 00 6f   movi.2d v7, #0000000000000000
      80: 10 e4 00 6f   movi.2d v16, #0000000000000000
      84: 11 e4 00 6f   movi.2d v17, #0000000000000000
      88: 12 e4 00 6f   movi.2d v18, #0000000000000000
      8c: 13 e4 00 6f   movi.2d v19, #0000000000000000
      90: 14 e4 00 6f   movi.2d v20, #0000000000000000
      94: 15 e4 00 6f   movi.2d v21, #0000000000000000
      98: 16 e4 00 6f   movi.2d v22, #0000000000000000
      9c: 17 e4 00 6f   movi.2d v23, #0000000000000000
      a0: 8e 01 02 d1   sub     x14, x12, #128
      a4: 8f 01 01 d1   sub     x15, x12, #64
      a8: d8 09 40 4c   ld4.4s  { v24, v25, v26, v27 }, [x14]
      ac: fc 09 40 4c   ld4.4s  { v28, v29, v30, v31 }, [x15]
      b0: ee 03 0c aa   mov     x14, x12
      b4: c8 09 df 4c   ld4.4s  { v8, v9, v10, v11 }, [x14], #64
      b8: cc 09 40 4c   ld4.4s  { v12, v13, v14, v15 }, [x14]
      ; in ARM assembly, .4s indicates that the operation is performed 
      ; on 4 single precision floating point elements. Adds contents of vector 
      ; register v24 to the contents of vector register v20 and the result 
      ; is stored in vector register v20
      bc: 14 87 b4 4e   add.4s  v20, v24, v20 
      c0: 95 87 b5 4e   add.4s  v21, v28, v21
      c4: 16 85 b6 4e   add.4s  v22, v8, v22
      c8: 97 85 b7 4e   add.4s  v23, v12, v23
      cc: 30 87 b0 4e   add.4s  v16, v25, v16
      d0: b1 87 b1 4e   add.4s  v17, v29, v17
      d4: 32 85 b2 4e   add.4s  v18, v9, v18
      d8: b3 85 b3 4e   add.4s  v19, v13, v19
      dc: 44 87 a4 4e   add.4s  v4, v26, v4
      e0: c5 87 a5 4e   add.4s  v5, v30, v5
      e4: 46 85 a6 4e   add.4s  v6, v10, v6
      e8: c7 85 a7 4e   add.4s  v7, v14, v7
      ec: 60 87 a0 4e   add.4s  v0, v27, v0
      f0: e1 87 a1 4e   add.4s  v1, v31, v1
      f4: 62 85 a2 4e   add.4s  v2, v11, v2
      f8: e3 85 a3 4e   add.4s  v3, v15, v3
      fc: 8c 01 04 91   add     x12, x12, #256
     100: ad 41 00 f1   subs    x13, x13, #16
     104: e1 fc ff 54   b.ne    0xa0 <ltmp0+0xa0>
     108: b4 86 b4 4e   add.4s  v20, v21, v20
     10c: d4 86 b4 4e   add.4s  v20, v22, v20
     110: f4 86 b4 4e   add.4s  v20, v23, v20
     114: 94 ba b1 4e   addv.4s s20, v20
     118: 8c 02 26 1e   fmov    w12, s20
     11c: 30 86 b0 4e   add.4s  v16, v17, v16
     120: 50 86 b0 4e   add.4s  v16, v18, v16
     124: 70 86 b0 4e   add.4s  v16, v19, v16
     128: 10 ba b1 4e   addv.4s s16, v16
     12c: 0d 02 26 1e   fmov    w13, s16
     130: a4 84 a4 4e   add.4s  v4, v5, v4
     134: c4 84 a4 4e   add.4s  v4, v6, v4
     138: e4 84 a4 4e   add.4s  v4, v7, v4
     13c: 84 b8 b1 4e   addv.4s s4, v4
     140: 8e 00 26 1e   fmov    w14, s4
     144: 20 84 a0 4e   add.4s  v0, v1, v0
     148: 40 84 a0 4e   add.4s  v0, v2, v0
     14c: 60 84 a0 4e   add.4s  v0, v3, v0
     150: 00 b8 b1 4e   addv.4s s0, v0
     154: 0f 00 26 1e   fmov    w15, s0
     158: 5f 01 0b eb   cmp     x10, x11
     15c: 80 01 00 54   b.eq    0x18c <ltmp0+0x18c>
     160: 0a 08 09 8b   add     x10, x0, x9, lsl #2
     164: 4a 21 00 91   add     x10, x10, #8
     168: 4b 41 7f 29   ldp     w11, w16, [x10, #-8]
     16c: 6c 01 0c 0b   add     w12, w11, w12
     170: 0d 02 0d 0b   add     w13, w16, w13
     174: 4b 41 c2 28   ldp     w11, w16, [x10], #16
     178: 6e 01 0e 0b   add     w14, w11, w14
     17c: 0f 02 0f 0b   add     w15, w16, w15
     180: 29 11 00 91   add     x9, x9, #4
     184: 3f 01 08 eb   cmp     x9, x8
     188: 03 ff ff 54   b.lo    0x168 <ltmp0+0x168>
     18c: a8 01 0c 0b   add     w8, w13, w12
     190: 08 01 0e 0b   add     w8, w8, w14
     194: 00 01 0f 0b   add     w0, w8, w15
     198: e9 23 43 6d   ldp     d9, d8, [sp, #48]
     19c: eb 2b 42 6d   ldp     d11, d10, [sp, #32]
     1a0: ed 33 41 6d   ldp     d13, d12, [sp, #16]
     1a4: ef 3b c4 6c   ldp     d15, d14, [sp], #64
     1a8: c0 03 5f d6   ret