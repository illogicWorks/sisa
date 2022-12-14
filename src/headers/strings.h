#pragma once

#define _VERSION "1.0"
#define _WELCOME "SISA assembler by Plopez"
#define _USAGE "Usage:\n       sisa [flags] infile\n    or\n       sisa infile [flags]"
#define _FLAGS "Options:\n    -h        print this summary\n    -i        assemble inline instruction (-i \"ADD R0, R0, R3\")\n    -o        specify ouput file path\n    -v        increase verbosity"

#define _NO_INPUT_ERROR "Provide output path"
#define _FILE_READ_ERROR "Unable to open file"
#define _FILE_WRITE_ERROR "Unable to write file"

#define _MISSING_OPERAND_ERROR "Missing operand in opcode"
#define _UNKNOWN_INSTRUCTION_ERROR "Unkown instruction"
#define _INVALID_IMMEDIATE_ERROR "Invalid immediate in opcode"