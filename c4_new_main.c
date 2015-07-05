int main(int argc, char **argv)
/*
 * Two special built-in arguments, argc and argv, are used to receive command line arguments.
 *  Argument counter (argc)
 * The argc parameter holds the number of arguments on the command line and is an integer. 
 * It is always at least 1 because the name of the program qualifies as the first argument.
 * Arguent variable (argv)
 * The argv parameter is a pointer to an array of character pointers. 
 * Each element in this array points to a command line argument. 
 * All command line arguments are strings— any numbers will have to be converted by the program into the proper binary format, manually.
 * 
 * Here, the argv is a pointer to a pointer (2D array initialiation). This means that the expected input is an array of strings and the number of strings is specified by argc.
 */
{
	//****** Variable Declarations:
	
  int fd, bt, ty, poolsz, *idmain; 
  /* The integers are described as follows:
   * 1. fd = Stores the output from the open() function. If successful, will store a non-negative value. If not, it will store the error code of the error type.
   * 2. bt = 
   * 3. ty =
   * 4. poolsz = Poolsize of the buffer.
   * 5. *idmain = Integer pointer for keeping track of main. 
   * */ 
  int *pc, *sp, *bp, a, cycle; // vm (Virtual Machine) registers.
  int i, *t; // temps

/* Since the minimum value of 'argc' is 1 as the program name counts as an argument, one needs to decrement the argc by 1 to check the following conditions:
 * Case 1: There are three strings in the argv array
 * 		a. The 
 * argv is incremented by 1 since the default or zeroth value would be the program name.
 */




// ******* Input Assimilation:

  --argc; ++argv;
  /* **argv points to the 1st element(character) of the 1st string of the 2D array declared. Thus, **argc=(*argc)[0].
   * Two flags are set.
   * 1. Src-> Source flag (Print source and assembly flag). The source flag is turned on if the '-s' attribute is given as an argument.
   * 2. Debug-> Debug flag. The debug flag is turned on if the '-d' attribute is given as an argument.
   */
  if (argc > 0 && (*argv)[0] == '-' && (*argv)[1] == 's') { src = 1; --argc; ++argv; }
  /* If string.h were used, we could have avoided the above method and used an alternative:
   * if ( (argc > 0) && (strcmp(argv,"-s")==0) ){ src = 1; --argc; ++argv; }
   * */
  if (argc > 0 && **argv == '-' && (*argv)[1] == 'd') { debug = 1; --argc; ++argv; }
  // Default case: The default case gives an output where it prompts the user to input the command in a certain manner.
  if (argc < 1) { printf("usage: c4 [-s] [-d] file ...\n"); return -1; }
	// fd flag stores the output of the open() function. If an error occurs, it can be mapped to the exact error type using the error code. 
  if ((fd = open(*argv, 0)) < 0) { printf("could not open(%s)\n", *argv); return -1; }
/* If open() returns '-1' as a return value, i.e. less than zero, this indicates that the file has failed to open!
 * Function: int open (const char *filename, int flags[, mode_t mode])
 * 1. Argument 1: (const char* filename.) i.e. The 'const' specifies that the function cannot change the 
 * 2. Argument 2: The flags argument controls how the file is to be opened. 
 * This is a bit mask; you create the value by the bitwise OR of the appropriate parameters (using the `|' operator in C).
 * Bit mask:-
 * 1. Mask : Masking is the process or operation to set bit on to off or off to on in a byte,nibble or word.
 * 2. 
 * Errors are negative values and each error has a specified code/error number.
 * */
 


 // ****** Actual inernal program starts after input assimilation:
 
  poolsz = 256*1024; // Arbitrary size for pool memory allocation.
  /* The variables:
   * 1. sym,le,e are global int pointers, now allocated memory of size=poolsz. Integer arrays namely.
   * 	a. sym = SYMBOL Table
   * 	b. le = ?
   * 	c. e = ?
   * 2. data -> data/bss pointer (char*).
   * 3. sp = Virtual machine register (stack pointer)
   * 
   * The memory is allocated to the above pointers alongwith the error cases and outputs in the below code block.
   * */
  if (!(sym = malloc(poolsz))) { printf("could not malloc(%d) symbol area\n", poolsz); return -1; }
  if (!(le = e = malloc(poolsz))) { printf("could not malloc(%d) text area\n", poolsz); return -1; }
  if (!(data = malloc(poolsz))) { printf("could not malloc(%d) data area\n", poolsz); return -1; }
  if (!(sp = malloc(poolsz))) { printf("could not malloc(%d) stack area\n", poolsz); return -1; }
  
// Memory initialization.
  memset(sym,  0, poolsz);
  memset(e,    0, poolsz);
  memset(data, 0, poolsz);
  
// ?
// (char*) p is pointed to the constant string specified below.
  p = "char else enum if int return sizeof while "
		"open read close printf malloc memset memcmp exit void main";
/* i is set to the enumeration 'Char' declared earlier.*/
  i = Char; while (i <= While) { next(); id[Tk] = i++; } // add keywords to symbol table
  i = OPEN; while (i <= EXIT) { next(); id[Class] = Sys; id[Type] = INT; id[Val] = i++; } // add library to symbol table
  next(); id[Tk] = Char; // handle void type
  next(); idmain = id; // keep track of main

  if (!(lp = p = malloc(poolsz))) { printf("could not malloc(%d) source area\n", poolsz); return -1; }
  /* Function-> read()
   * Arguments:
   * 1.  
  */
  if ((i = read(fd, p, poolsz-1)) <= 0) { printf("read() returned %d\n", i); return -1; }
  p[i] = 0;
  close(fd);
  
  
  
  
  
  
  
  
  

  // parse declarations
  line = 1;
  next();
  while (tk) {
    bt = INT; // basetype
    if (tk == Int) next();
    else if (tk == Char) { next(); bt = CHAR; }
    else if (tk == Enum) {
      next();
      if (tk != '{') next();
      if (tk == '{') {
        next();
        i = 0;
        while (tk != '}') {
          if (tk != Id) { printf("%d: bad enum identifier %d\n", line, tk); return -1; }
          next();
          if (tk == Assign) {
            next();
            if (tk != Num) { printf("%d: bad enum initializer\n", line); return -1; }
            i = ival;
            next();
          }
          id[Class] = Num; id[Type] = INT; id[Val] = i++;
          if (tk == ',') next();
        }
        next();
      }
    }
    while (tk != ';' && tk != '}') {
      ty = bt;
      while (tk == Mul) { next(); ty = ty + PTR; }
      if (tk != Id) { printf("%d: bad global declaration\n", line); return -1; }
      if (id[Class]) { printf("%d: duplicate global definition\n", line); return -1; }
      next();
      id[Type] = ty;
      if (tk == '(') { // function
        id[Class] = Fun;
        id[Val] = (int)(e + 1);
        next(); i = 0;
        while (tk != ')') {
          ty = INT;
          if (tk == Int) next();
          else if (tk == Char) { next(); ty = CHAR; }
          while (tk == Mul) { next(); ty = ty + PTR; }
          if (tk != Id) { printf("%d: bad parameter declaration\n", line); return -1; }
          if (id[Class] == Loc) { printf("%d: duplicate parameter definition\n", line); return -1; }
          id[HClass] = id[Class]; id[Class] = Loc;
          id[HType]  = id[Type];  id[Type] = ty;
          id[HVal]   = id[Val];   id[Val] = i++;
          next();
          if (tk == ',') next();
        }
        next();
        if (tk != '{') { printf("%d: bad function definition\n", line); return -1; }
        loc = ++i;
        next();
        while (tk == Int || tk == Char) {
          bt = (tk == Int) ? INT : CHAR;
          next();
          while (tk != ';') {
            ty = bt;
            while (tk == Mul) { next(); ty = ty + PTR; }
            if (tk != Id) { printf("%d: bad local declaration\n", line); return -1; }
            if (id[Class] == Loc) { printf("%d: duplicate local definition\n", line); return -1; }
            id[HClass] = id[Class]; id[Class] = Loc;
            id[HType]  = id[Type];  id[Type] = ty;
            id[HVal]   = id[Val];   id[Val] = ++i;
            next();
            if (tk == ',') next();
          }
          next();
        }
        *++e = ENT; *++e = i - loc;
        while (tk != '}') stmt();
        *++e = LEV;
        id = sym; // unwind symbol table locals
        while (id[Tk]) {
          if (id[Class] == Loc) {
            id[Class] = id[HClass];
            id[Type] = id[HType];
            id[Val] = id[HVal];
          }
          id = id + Idsz;
        }
      }
      else {
        id[Class] = Glo;
        id[Val] = (int)data;
        data = data + sizeof(int);
      }
      if (tk == ',') next();
    }
    next();
  }

  if (!(pc = (int *)idmain[Val])) { printf("main() not defined\n"); return -1; }
  if (src) return 0;

  // setup stack
  sp = (int *)((int)sp + poolsz);
  *--sp = EXIT; // call exit if main returns
  *--sp = PSH; t = sp;
  *--sp = argc;
  *--sp = (int)argv;
  *--sp = (int)t;

  // run...
  cycle = 0;
  while (1) {
    i = *pc++; ++cycle;
    if (debug) {
      printf("%d> %.4s", cycle,
        &"LEA ,IMM ,JMP ,JSR ,BZ  ,BNZ ,ENT ,ADJ ,LEV ,LI  ,LC  ,SI  ,SC  ,PSH ,"
         "OR  ,XOR ,AND ,EQ  ,NE  ,LT  ,GT  ,LE  ,GE  ,SHL ,SHR ,ADD ,SUB ,MUL ,DIV ,MOD ,"
         "OPEN,READ,CLOS,PRTF,MALC,MSET,MCMP,EXIT,"[i * 5]);
      if (i <= ADJ) printf(" %d\n", *pc); else printf("\n");
    }
    if      (i == LEA) a = (int)(bp + *pc++);                             // load local address
    else if (i == IMM) a = *pc++;                                         // load global address or immediate
    else if (i == JMP) pc = (int *)*pc;                                   // jump
    else if (i == JSR) { *--sp = (int)(pc + 1); pc = (int *)*pc; }        // jump to subroutine
    else if (i == BZ)  pc = a ? pc + 1 : (int *)*pc;                      // branch if zero
    else if (i == BNZ) pc = a ? (int *)*pc : pc + 1;                      // branch if not zero
    else if (i == ENT) { *--sp = (int)bp; bp = sp; sp = sp - *pc++; }     // enter subroutine
    else if (i == ADJ) sp = sp + *pc++;                                   // stack adjust
    else if (i == LEV) { sp = bp; bp = (int *)*sp++; pc = (int *)*sp++; } // leave subroutine
    else if (i == LI)  a = *(int *)a;                                     // load int
    else if (i == LC)  a = *(char *)a;                                    // load char
    else if (i == SI)  *(int *)*sp++ = a;                                 // store int
    else if (i == SC)  a = *(char *)*sp++ = a;                            // store char
    else if (i == PSH) *--sp = a;                                         // push

    else if (i == OR)  a = *sp++ |  a;
    else if (i == XOR) a = *sp++ ^  a;
    else if (i == AND) a = *sp++ &  a;
    else if (i == EQ)  a = *sp++ == a;
    else if (i == NE)  a = *sp++ != a;
    else if (i == LT)  a = *sp++ <  a;
    else if (i == GT)  a = *sp++ >  a;
    else if (i == LE)  a = *sp++ <= a;
    else if (i == GE)  a = *sp++ >= a;
    else if (i == SHL) a = *sp++ << a;
    else if (i == SHR) a = *sp++ >> a;
    else if (i == ADD) a = *sp++ +  a;
    else if (i == SUB) a = *sp++ -  a;
    else if (i == MUL) a = *sp++ *  a;
    else if (i == DIV) a = *sp++ /  a;
    else if (i == MOD) a = *sp++ %  a;

    else if (i == OPEN) a = open((char *)sp[1], *sp);
    else if (i == READ) a = read(sp[2], (char *)sp[1], *sp);
    else if (i == CLOS) a = close(*sp);
    else if (i == PRTF) { t = sp + pc[1]; a = printf((char *)t[-1], t[-2], t[-3], t[-4], t[-5], t[-6]); }
    else if (i == MALC) a = (int)malloc(*sp);
    else if (i == MSET) a = (int)memset((char *)sp[2], sp[1], *sp);
    else if (i == MCMP) a = memcmp((char *)sp[2], (char *)sp[1], *sp);
    else if (i == EXIT) { printf("exit(%d) cycle = %d\n", *sp, cycle); return *sp; }
    else { printf("Unknown Instruction = %d! cycle = %d\n", i, cycle); return -1; }
  }
}
