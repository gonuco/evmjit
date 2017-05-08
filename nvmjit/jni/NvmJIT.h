#include <stddef.h>
#include <cstdint>

#include <iostream>
#include <stack>

#include "evm.h"
#include "evmjit.h"

class Callback {
public:
    virtual ~Callback() {
    }

    virtual void doQuery(union evm_variant* result, enum evm_query_key key,
            const union evm_variant* arg) {
        std::cout << "Callback::doQuery()" << std::endl;
    }

    virtual void doUpdate(enum evm_update_key key,
            const union evm_variant* arg1, const union evm_variant* arg2) {
        std::cout << "Callback::doUpdate()" << std::endl;
    }

    virtual int64_t doCall(enum evm_call_kind kind, int64_t gas,
            const struct evm_uint160be* address,
            const struct evm_uint256be* value, uint8_t const* input,
            size_t input_size, uint8_t* output, size_t output_size) {
        std::cout << "Callback::doCall()" << std::endl;
        return EVM_CALL_FAILURE;
    }
};

bool isCompiled(enum evm_mode mode, struct evm_uint256be code_hash);

void compileCode(enum evm_mode mode, struct evm_uint256be code_hash,
        uint8_t const* code, size_t code_size);

struct evm_env {
    std::stack<struct evm_instance *> instances;
    std::stack<Callback *> callbacks;
    std::stack<int64_t> maxMemSizes;
    std::stack<int64_t *> curMemSizes;
    bool interrupted;
};

evm_env *createEnv();

void createVM(struct evm_env *env, Callback *cb);

struct evm_result executeCode(struct evm_env *env, enum evm_mode mode,
        struct evm_uint256be code_hash, uint8_t const* code, size_t code_size,
        int64_t gas, uint8_t const* input, size_t input_size,
        struct evm_uint256be value);

void releaseResult(struct evm_env *env, struct evm_result const* result);

void releaseVM(struct evm_env *env);

void releaseEnv(struct evm_env *env);

void interrupt(struct evm_env *env);

// using signed integer for JNI convenience
extern int64_t maxTotalMemory;

