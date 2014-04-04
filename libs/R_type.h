typedef unsigned int u32;
struct rOperand{
	u32 rs;
	u32 rt;
	u32 rd;
	u32 shamt;
	u32 funct;
};

void r_type_funct(u32 instr){
    rOperand.funct = instr & 0x3F;
    if(rOperand.funct == "0x20"){
        emu_add(instr);
    }
    else if(rOperand.funct == "0x22"){
        emu_sub(instr);
    }
    else if(rOperand.funct == "0x24"){
        emu_and(instr);
    }
    else if(rOperand.funct == "0x25"){
        emu_or(instr);
    }
    else if(rOperand.funct == "0x26"){
        emu_xor(instr);
    }
    else if(rOperand.funct == "0x27"){
        emu_nor(instr);
    }
    else if(rOperand.funct == "0x28"){
        emu_nand(instr);
    }
    else if(rOperand.funct == "0x2A"){
        emu_slt(instr);
    }
    else if(rOperand.funct == "0x00"){
        emu_sll(instr);
    }
    else if(rOperand.funct == "0x02"){
        emu_srl(instr);
    }
    else if(rOperand.funct == "0x03"){
        emu_sra(instr);
    }
    else if(rOperand.funct == "0x08"){
        emu_jr(instr);
    }
    /*是否做funct的例外處理*/
}



/******************************************************************************/
/*R-type                                                                        */
/******************************************************************************/
static void emu_add(u32 instr)
{
    struct rOperand rOperand;
    rOperand.rs = ((instr >> 21) & 0x1F);
    rOperand.rt = ((instr >> 16) & 0x1F);
    rOperand.rd = ((instr >> 11) & 0x1F);
    u32 value_to_be_stored;
    u32 rs = get_regs(rOperand.rs);
    u32 rt = get_regs(rOperand.rt);
    value_to_be_stored = rs + rt;
    set_regs(rOperand.rd,value_to_be_stored);
}

static void emu_sub(u32 instr)
{
    struct rOperand rOperand;
    rOperand.rs = ((instr >> 21) & 0x1F);
    rOperand.rt = ((instr >> 16) & 0x1F);
    rOperand.rd = ((instr >> 11) & 0x1F);
    u32 value_to_be_stored;
    u32 rs = get_regs(rOperand.rs);
    u32 rt = get_regs(rOperand.rt);
    value_to_be_stored = rs + rt;
    set_regs(rOperand.rd,value_to_be_stored);
}
static void emu_and(u32 instr)
{
    struct rOperand rOperand;
    rOperand.rs = ((instr >> 21) & 0x1F);
    rOperand.rt = ((instr >> 16) & 0x1F);
    rOperand.rd = ((instr >> 11) & 0x1F);
    u32 value_to_be_stored;
    u32 rs = get_regs(rOperand.rs);
    u32 rt = get_regs(rOperand.rt);
    value_to_be_stored = rs + rt;
    set_regs(rOperand.rd,value_to_be_stored);

}

static void emu_or(u32 instr)
{
    struct rOperand rOperand;
    rOperand.rs = ((instr >> 21) & 0x1F);
    rOperand.rt = ((instr >> 16) & 0x1F);
    rOperand.rd = ((instr >> 11) & 0x1F);
    u32 value_to_be_stored;
    u32 rs = get_regs(rOperand.rs);
    u32 rt = get_regs(rOperand.rt);
    value_to_be_stored = rs + rt;
    set_regs(rOperand.rd,value_to_be_stored);
}

static void emu_xor(u32 instr)
{
    struct rOperand rOperand;
    rOperand.rs = ((instr >> 21) & 0x1F);
    rOperand.rt = ((instr >> 16) & 0x1F);
    rOperand.rd = ((instr >> 11) & 0x1F);
    u32 value_to_be_stored;
    u32 rs = get_regs(rOperand.rs);
    u32 rt = get_regs(rOperand.rt);
    value_to_be_stored = rs + rt;
    set_regs(rOperand.rd,value_to_be_stored);
}

static void emu_nor(u32 instr)
{
    struct rOperand rOperand;
    rOperand.rs = ((instr >> 21) & 0x1F);
    rOperand.rt = ((instr >> 16) & 0x1F);
    rOperand.rd = ((instr >> 11) & 0x1F);
    u32 value_to_be_stored;
    u32 rs = get_regs(rOperand.rs);
    u32 rt = get_regs(rOperand.rt);
    value_to_be_stored = (~(rs | rt));
    set_regs(rOperand.rd,value_to_be_stored);
}

static void emu_nand(u32 instr)
{
    struct rOperand rOperand;
    rOperand.rs = ((instr >> 21) & 0x1F);
    rOperand.rt = ((instr >> 16) & 0x1F);
    rOperand.rd = ((instr >> 11) & 0x1F);
    u32 value_to_be_stored;
    u32 rs = get_regs(rOperand.rs);
    u32 rt = get_regs(rOperand.rt);
    value_to_be_stored = (~(rs & rt));
    set_regs(rOperand.rd,value_to_be_stored);
}
static void emu_slt(u32 instr)
{
    struct rOperand rOperand;
    rOperand.rs = ((instr >> 21) & 0x1F);
    rOperand.rt = ((instr >> 16) & 0x1F);
    rOperand.rd = ((instr >> 11) & 0x1F);
    u32 value_to_be_stored;
    u32 rs = get_regs(rOperand.rs);
    u32 rt = get_regs(rOperand.rt);
    if(rs < rt)
    {
        value_to_be_stored = 1;
    }
    else
    {
        value_to_be_stored = 0;
    }
    set_regs(rOperand.rd,value_to_be_stored);
}
static void emu_sll(u32 instr)
{
    struct rOperand rOperand;
    rOperand.shamt = ((instr >> 6) & 0x1F);
    rOperand.rt = ((instr >> 16) & 0x1F);
    rOperand.rd = ((instr >> 11) & 0x1F);
    u32 value_to_be_stored;
    u32 rt = get_regs(rOperand.rt);
    value_to_be_stored = rt << rOperand.shamt
    set_regs(rOperand.rd,value_to_be_stored);

}
static void emu_srl(u32 instr)
{
    struct rOperand rOperand;
    rOperand.shamt = ((instr >> 6) & 0x1F);
    rOperand.rt = ((instr >> 16) & 0x1F);
    rOperand.rd = ((instr >> 11) & 0x1F);
    u32 value_to_be_stored;
    u32 rt = get_regs(rOperand.rt);
    value_to_be_stored = rt >> rOperand.shamt
    set_regs(rOperand.rd,value_to_be_stored);
}

static void emu_sra(u32 instr)
{
    struct rOperand rOperand;
    int temp;
    rOperand.shamt = ((instr >> 6) & 0x1F);
    rOperand.rt = ((instr >> 16) & 0x1F);
    rOperand.rd = ((instr >> 11) & 0x1F);

    int temp = get_regs(rOperand.rt);

    int value_to_be_stored = temp >> rOperand.shamt
    set_regs(rOperand.rd,value_to_be_stored);
}

static void emu_jr(u32 instr)
{
    struct rOperand rOperand;
    rOperand.rs = ((instr >> 21) & 0x1F);
    vcpu.PC = vcpu.reg[rOperand.rs];
}




