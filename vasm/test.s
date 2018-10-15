_start:
  add x1, x2, x3
  sub x1, x1, x2
  addi x3, x6, -0x33
  addi x5, x7, 10000

_stuff:
  .illegal "my string"
  .illegal "my \"escaped\" string"
  .illegal "string"thing, right,after
  .illegal "f my lexer up

meme:
  a,a,a,a