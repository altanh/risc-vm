_start:
  sub x1,x2,x3
  add x3, x4, x5
  xor x3, x4, x4
_end:
  addi x1, x3, 333
  xori x3, x9, 0xFF
  slti x0, x0, -0x1