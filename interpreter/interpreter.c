// This is where you put your VM code.
// I am trying to follow the coding style of the original.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "minivm.h"

#define NUM_REGS   (256)
#define NUM_FUNCS  (256)

// Global variable that indicates if the process is running.
static bool is_running = true;
uint32_t* ptr = NULL;

void usageExit() {
    // TODO: show usage
    printf("Set argument with just one bytecode!\n");
    exit(1);
}

void halt(struct VMContext* ctx, const uint32_t i){
    exit(1);
}

void load(struct VMContext* ctx, const uint32_t i){
    uint32_t value = EXTRACT_B3(*(ptr+(ctx->r[EXTRACT_B2(i)].value/4)));
    ctx->r[EXTRACT_B1(i)].value = value;	
}

void store(struct VMContext* ctx, const uint32_t i){
    *(ptr+(ctx->r[EXTRA_B1(i)].value/4)) = B0(ctx->r[EXTRA_B2(i)].value); 	
}

void move(struct VMContext* ctx, const uint32_t i){}
void puti(struct VMContext* ctx, const uint32_t i){}
void add(struct VMContext* ctx, const uint32_t i){}
void sub(struct VMContext* ctx, const uint32_t i){}
void gt(struct VMContext* ctx, const uint32_t i){}
void ge(struct VMContext* ctx, const uint32_t i){}
void eq(struct VMContext* ctx, const uint32_t i){}
void ite(struct VMContext* ctx, const uint32_t i){}
void jump(struct VMContext* ctx, const uint32_t i){}
void puts(struct VMContext* ctx, const uint32_t i){}

void initFuncs(FunPtr *f, uint32_t cnt) {
    uint32_t i;
    for (i = 0; i < cnt; i++) {
        f[i] = NULL;
    }

    f[0x00] = halt;
    f[0x10] = load;
    f[0x20] = store;
    f[0x30] = move;
    f[0x40] = puti;
    f[0x50] = add;
    f[0x60] = sub;
    f[0x70] = gt;
    f[0x80] = ge;
    f[0x90] = eq;
    f[0xa0] = ite;
    f[0xb0] = jump;
    f[0xc0] = puts;
    f[0xd0] = gets;

    // TODO: initialize function pointers
    // f[0x00] = halt;
    // f[0x10] = load;
}

void initRegs(Reg *r, uint32_t cnt)
{
    uint32_t i;
    for (i = 0; i < cnt; i++) {
        r[i].type = 0;
        r[i].value = 0;
    }
}

int main(int argc, char** argv) {
    VMContext vm;
    Reg r[NUM_REGS];
    FunPtr f[NUM_FUNCS];
    FILE* bytecode;
    uint32_t* pc;
    uint32_t len = 0;
    ptr = (uint32_t*)malloc(8192);
	
    // There should be at least one argument.
    if (argc < 2) usageExit();

    // Initialize registers.
    initRegs(r, NUM_REGS);
    // Initialize interpretation functions.
    initFuncs(f, NUM_FUNCS);
    // Initialize VM context.
    initVMContext(&vm, NUM_REGS, NUM_FUNCS, r, f);

    // Load bytecode file
    bytecode = fopen(argv[1], "rb");
    if (bytecode == NULL) {
        perror("fopen");
        return 1;
    }
    
    fseek(bytecode,0,SEEK_END);
    len = ftell(bytecode);  //find size of file.
    fseek(bytecode,0,SEEK_SET);

    fread(pc,4,len/4,bytecode);//Connect file pointer and integer pointer(Initialize pc)

    while (is_running) {
        // TODO: Read 4-byte bytecode, and set the pc accordingly
	// If we reach end of file, we must escape loop.
      stepVMContext(&vm, &pc);
      
         if(pc==NULL) // if instrcution fetch is finish, terminate program.
      is_running = false;
    }

    fclose(bytecode);

    // Zero indicates normal termination.
    return 0;
}
