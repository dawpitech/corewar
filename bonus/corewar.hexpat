/* Corewar byte code */

#include <std/mem.pat>
#include <std/io.pat>

#pragma endian big

#define MAGIC_HEADER 0xea83f3
#define PROG_NAME_LENGTH 128
#define COMMENT_LENGTH 2048

#define MAX_ARGS_NUMBER 4
#define IND_SIZE 2
#define DIR_SIZE 4
#define REG_SIZE 1
#define IDX_SIZE 2

// Header

struct Header {
  u8 magic[4];
  char prog_name[PROG_NAME_LENGTH + 1];
  padding[3];
  u32 prog_size;
  char comment[COMMENT_LENGTH + 1];
  padding[3];
};

// Operation structures

enum Code: u8 {
  Live = 0x01,
  Ld = 0x02,
  St = 0x03,
  Add = 0x04,
  Sub = 0x05,
  And = 0x06,
  Or = 0x07,
  Xor = 0x08,
  Zjmp = 0x09,
  Ldi = 0x0a,
  Sti = 0x0b,
  Fork = 0x0c,
  Lld = 0x0d,
  Lldi = 0x0e,
  Lfork = 0x0f,
  Aff = 0x10,
};

enum ParamType: u8 {
  Register = 0b01,
  Direct = 0b10,
  Indirect = 0b11,
  None = 0b00,
};

bitfield CodingByte {
  ParamType p1: 2;
  ParamType p2: 2;
  ParamType p3: 2;
  ParamType p4: 2;
} [[single_color]];

struct Param<auto Size> {
  u8 value[Size] [[inline]];
};

fn size(ParamType param_type) {
  match (param_type) {
    (ParamType::Register): return REG_SIZE;
    (ParamType::Direct): return DIR_SIZE;
    (ParamType::Indirect): return IND_SIZE;
    (ParamType::None): return 0;
  }
};

fn idx_or_reg(ParamType param_type) {
  match (param_type) {
    (ParamType::Register): return REG_SIZE;
    (_): return IDX_SIZE;
  }
};

// Operation types

struct LiveOp {
  u32 player_id;
};

struct LdOp {
  CodingByte cb;
  Param<size(cb.p1)> value;
  Param<REG_SIZE> register;
};

struct StOp {
  CodingByte cb;
  Param<REG_SIZE> register;
  Param<size(cb.p2)> value;
};

struct AddOp {
  CodingByte cb;
  Param<REG_SIZE> first;
  Param<REG_SIZE> second;
  Param<REG_SIZE> sum;
};

struct SubOp {
  CodingByte cb;
  Param<REG_SIZE> first;
  Param<REG_SIZE> second;
  Param<REG_SIZE> diff;
};

struct AndOp {
  CodingByte cb;
  Param<size(cb.p1)> first;
  Param<size(cb.p2)> second;
  Param<REG_SIZE> result;
};

struct OrOp {
  CodingByte cb;
  Param<size(cb.p1)> first;
  Param<size(cb.p2)> second;
  Param<REG_SIZE> result;
};

struct XorOp {
  CodingByte cb;
  Param<size(cb.p1)> first;
  Param<size(cb.p2)> second;
  Param<REG_SIZE> result;
};

struct ZjmpOp {
  Param<IDX_SIZE> index;
};

struct LdiOp {
  CodingByte cb;
  Param<idx_or_reg(cb.p1)> first;
  Param<idx_or_reg(cb.p2)> second;
  Param<REG_SIZE> result;
};

struct StiOp {
  CodingByte cb;
  Param<REG_SIZE> source;
  Param<idx_or_reg(cb.p2)> first;
  Param<idx_or_reg(cb.p3)> second;
};

struct ForkOp {
  Param<IDX_SIZE> index;
};

struct LldOp {
  CodingByte cb;
  Param<size(cb.p1)> value;
  Param<REG_SIZE> register;
};

struct LldiOp {
  CodingByte cb;
  Param<idx_or_reg(cb.p1)> first;
  Param<idx_or_reg(cb.p2)> second;
  Param<REG_SIZE> result;
};

struct LforkOp {
  Param<IDX_SIZE> index;
};

struct AffOp {
  CodingByte cb;
  Param<REG_SIZE> register;
};

struct Op {
  Code code;

  match (code) {
    (Code::Live): LiveOp data [[inline]];
    (Code::Ld): LdOp data [[inline]];
    (Code::St): StOp data [[inline]];
    (Code::Add): AddOp data [[inline]];
    (Code::Sub): SubOp data [[inline]];
    (Code::And): AndOp data [[inline]];
    (Code::Or): OrOp data [[inline]];
    (Code::Xor): XorOp data [[inline]];
    (Code::Zjmp): ZjmpOp data [[inline]];
    (Code::Ldi): LdiOp data [[inline]];
    (Code::Sti): StiOp data [[inline]];
    (Code::Fork): ForkOp data [[inline]];
    (Code::Lld): LldOp data [[inline]];
    (Code::Lldi): LldiOp data [[inline]];
    (Code::Lfork): LforkOp data [[inline]];
    (Code::Aff): AffOp data [[inline]];
  }
} [[single_color, format("format_code")]];

fn format_code(Op op) {
  return std::format("{}", op.code);
};

// Corewar structures (top level)

struct Corewar {
  Header header;
  Op ops[while(!std::mem::eof())] [[inline]];
};

Corewar corewar @ 0x00;
