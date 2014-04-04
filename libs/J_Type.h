typedef unsigned int u32;

struct jOperand{
	u32 address;
};

static void j_type_funct(u32 instr){
    u32 opcode = (instr >> 26) & 0x3F;
    if(opcode == "0x02"){
        emu_j(instr);
    }
    else{
        emu_jal(instr);
    }
}
static void emu_j(int instr){
    struct jOperand jOperand;
    u32 C = 0;
    jOperand.address = instr & 0x3FFFFFF;
    C = jOperand.address >> 4;
    buf = (vcpu.PC + 4);
    buf = (buf >> 28) & 0xF;
    vcpu.PC = buf| C;

}
static void emu_jal(){
    struct jOperand jOperand;
    u32 C = 0;
    vcpu.reg[31] = vcpu.PC;
    jOperand.address = instr & 0x3FFFFFF;
    C = jOperand.address >> 4;
    buf = (vcpu.PC + 4);
    buf = (buf >> 28) & 0xF;
    vcpu.PC = buf| C;
}


