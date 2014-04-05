#ifndef __OPCODE_H
#define __OPCODE_H

/******************************************************************************/
/*I-type                                                                      */
/******************************************************************************/
#define OP_addi	0x08
#define OP_lw	0x23
#define OP_lh	0x21
#define OP_lhu	0x25
#define OP_lb	0x20
#define OP_lbu	0x24
#define OP_sw	0x2B
#define OP_sh	0x29
#define OP_sb	0x28
#define OP_lui	0x0F
#define OP_andi	0x0C
#define OP_ori	0x0D
#define OP_nori	0x0E
#define OP_slti	0x0A
#define OP_beq	0x04
#define OP_bne	0x05

#endif
