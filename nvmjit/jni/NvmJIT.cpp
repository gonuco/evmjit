/*
 * NvmJIT.cpp
 *
 *  Created on: Apr 19, 2017
 *      Author: yulong
 */

#include <stack>
#include "NvmJIT.h"

#include "../src/JIT.h"
extern std::stack<dev::evmjit::RuntimeData *> rts;


bool interrupted = false;

struct evm_env *env = NULL; // not used

std::stack<struct evm_instance *> instances;
std::stack<Callback *> callbacks;


void doQuery(union evm_variant* result, struct evm_env* env,
        enum evm_query_key key, const union evm_variant* arg) {
    if (!callbacks.empty()) {
        callbacks.top()->doQuery(result, key, arg);
    }
}

void doUpdate(struct evm_env* env, enum evm_update_key key,
        const union evm_variant* arg1, const union evm_variant* arg2) {
    if (!callbacks.empty()) {
        callbacks.top()->doUpdate(key, arg1, arg2);
    }
}

int64_t doCall(struct evm_env* env, enum evm_call_kind kind, int64_t gas,
        const struct evm_uint160be* address, const struct evm_uint256be* value,
        uint8_t const* input, size_t input_size, uint8_t* output,
        size_t output_size) {
    if (!callbacks.empty()) {
        return callbacks.top()->doCall(kind, gas, address, value, input,
                input_size, output, output_size);
    } else {
        return EVM_FAILURE;
    }
}

void createVM(Callback *cb) {
    struct evm_factory factory = evmjit_get_factory();
    struct evm_instance *instance = factory.create(&doQuery, &doUpdate,
            &doCall);

    instances.push(instance);
    callbacks.push(cb);

    interrupted = false;
}

struct evm_result executeCode(enum evm_mode mode, struct evm_uint256be code_hash,
        uint8_t const* code, size_t code_size, int64_t gas,
        uint8_t const* input, size_t input_size, struct evm_uint256be value) {
    struct evm_result result;
    result.code = EVM_FAILURE;

    if (!instances.empty()) {
        struct evm_instance *instance = instances.top();
        result = instance->execute(instance, env, mode, code_hash, code,
                code_size, gas, input, input_size, value);
    }

    return result;
}

void releaseResult(struct evm_result const* result) {
    if (result != NULL) {
        result->release(result);
    }
}

void releaseVM() {
    if (!instances.empty()) {
        struct evm_instance *instance = instances.top();
        instance->destroy(instance);
        instances.pop();
    }

    if (!callbacks.empty()) {
        Callback *callback = callbacks.top();
        callback->~Callback();
        callbacks.pop();
    }
}

void interrupt() {
    interrupted = true;
}

