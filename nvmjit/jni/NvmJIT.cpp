/*
 * NvmJIT.cpp
 *
 *  Created on: Apr 19, 2017
 *      Author: yulong
 */

#include "NvmJIT.h"

int64_t maxTotalMemory = 1024 * 1024 * 1024;

int h256Type = 0;

void doQuery(union evm_variant* result, struct evm_env* env,
        enum evm_query_key key, const union evm_variant* arg) {
    if (!env->callbacks.empty()) {
        env->callbacks.top()->doQuery(result, key, arg);
    }
}

void doUpdate(struct evm_env* env, enum evm_update_key key,
        const union evm_variant* arg1, const union evm_variant* arg2) {
    if (!env->callbacks.empty()) {
        env->callbacks.top()->doUpdate(key, arg1, arg2);
    }
}

int64_t doCall(struct evm_env* env, enum evm_call_kind kind, int64_t gas,
        const struct evm_uint160be* address, const struct evm_uint256be* value,
        uint8_t const* input, size_t input_size, uint8_t* output,
        size_t output_size) {
    if (!env->callbacks.empty()) {
        return env->callbacks.top()->doCall(kind, gas, address, value, input,
                input_size, output, output_size);
    } else {
        return EVM_FAILURE;
    }
}

bool isCompiled(enum evm_mode mode, struct evm_uint256be code_hash) {
    struct evm_factory factory = evmjit_get_factory();
    struct evm_instance *instance = factory.create(&doQuery, &doUpdate,
            &doCall);

    bool result = instance->get_code_status(instance, mode, code_hash)
            == EVM_READY;
    instance->destroy(instance);

    return result;
}

void compileCode(enum evm_mode mode, struct evm_uint256be code_hash,
        uint8_t const* code, size_t code_size) {
    struct evm_factory factory = evmjit_get_factory();
    struct evm_instance *instance = factory.create(&doQuery, &doUpdate,
            &doCall);

    instance->prepare_code(instance, mode, code_hash, code, code_size);
    instance->destroy(instance);
}

struct evm_env *createEnv() {
    struct evm_env *env = new struct evm_env();
    env->interrupted = false;

    return env;
}

void createVM(struct evm_env *env, Callback *cb) {
    struct evm_factory factory = evmjit_get_factory();
    struct evm_instance *instance = factory.create(&doQuery, &doUpdate,
            &doCall);

    env->instances.push(instance);
    env->callbacks.push(cb);

    int64_t maxMemSize = env->maxMemSizes.empty() ? maxTotalMemory : maxTotalMemory - *env->curMemSizes.top();
    int64_t *curMemSize = new int64_t(0);
    env->maxMemSizes.push(maxMemSize);
    env->curMemSizes.push(curMemSize);
}

struct evm_result executeCode(struct evm_env *env, enum evm_mode mode,
        struct evm_uint256be code_hash, uint8_t const* code, size_t code_size,
        int64_t gas, uint8_t const* input, size_t input_size,
        struct evm_uint256be value) {
    struct evm_result result;
    result.code = EVM_FAILURE;

    if (!env->instances.empty()) {
        struct evm_instance *instance = env->instances.top();
        result = instance->execute(instance, env, mode, code_hash, code,
                code_size, gas, input, input_size, value);
    }

    return result;
}

void releaseResult(struct evm_env *env, struct evm_result const* result) {
    if (result != NULL) {
        result->release(result);
    }
}

void releaseVM(struct evm_env *env) {
    if (!env->instances.empty()) {
        struct evm_instance *instance = env->instances.top();
        instance->destroy(instance);
        env->instances.pop();
    }

    if (!env->callbacks.empty()) {
        Callback *callback = env->callbacks.top();
        callback->~Callback();
        env->callbacks.pop();
    }

    if (!env->maxMemSizes.empty()) {
        env->maxMemSizes.pop();
    }

    if (!env->curMemSizes.empty()) {
        delete env->curMemSizes.top();
        env->curMemSizes.pop();
    }
}

void releaseEnv(struct evm_env *env) {
    if (env) {
        delete env;
    }
}

void interrupt(struct evm_env *env) {
    env->interrupted = true;
}
