%module(directors="1") NvmJIT
%{
#include "NvmJIT.h"
%}


%feature("director") Callback;
%include "NvmJIT.h"


// for unbound c array
%include "carrays.i"
%array_class(unsigned char, ByteArray);


// for java enums
%include "enums.swg"


// for uint_8, int64_t
%include "stdint.i"


enum evm_result_code {
    EVM_SUCCESS = 0,
    EVM_FAILURE = 1,
    EVM_OUT_OF_GAS = 2,
    EVM_BAD_INSTRUCTION = 3,
    EVM_BAD_JUMP_DESTINATION = 4,
    EVM_STACK_OVERFLOW = 5,
    EVM_STACK_UNDERFLOW = 6,
    EVM_REVERT = 7,
    EVM_INTERNAL_ERROR = -1,
};

enum evm_query_key {
    EVM_SLOAD = 0,
    EVM_ADDRESS = 1,
    EVM_CALLER = 2,
    EVM_ORIGIN = 3,
    EVM_GAS_PRICE = 4,
    EVM_COINBASE = 5,
    EVM_DIFFICULTY = 6,
    EVM_GAS_LIMIT = 7,
    EVM_NUMBER = 8,
    EVM_TIMESTAMP = 9,
    EVM_CODE_BY_ADDRESS = 10,
    EVM_CODE_SIZE = 11,
    EVM_BALANCE = 12,
    EVM_BLOCKHASH = 13,
    EVM_ACCOUNT_EXISTS = 14,
    EVM_CALL_DEPTH = 15,
};

enum evm_update_key {
    EVM_SSTORE = 0,
    EVM_LOG = 1,
    EVM_SELFDESTRUCT = 2,
};

enum evm_call_kind {
    EVM_CALL = 0,
    EVM_DELEGATECALL = 1,
    EVM_CALLCODE = 2,
    EVM_CREATE = 3
};

enum evm_mode {
    EVM_FRONTIER = 0,
    EVM_HOMESTEAD = 1,
    EVM_ANTI_DOS = 2,
    EVM_CLEARING = 3,
    EVM_METROPOLIS = 4,
};

enum evm_code_status {
    EVM_UNKNOWN,
    EVM_READY,
    EVM_CACHED,
};

struct evm_uint160be {
    uint8_t bytes[20];
};

struct evm_uint256be {
    uint8_t bytes[32];
};

union evm_variant {
    int64_t int64;
    struct evm_uint256be uint256be;
    struct {
        uint8_t address_padding[12];
        struct evm_uint160be address;
    };
    struct {
        uint8_t const* data;
        size_t data_size;
    };
};

struct evm_result {
    enum evm_result_code code;
    int64_t gas_left;
    uint8_t const* output_data;
    size_t output_size;
    evm_release_result_fn release;
    void* context;
};