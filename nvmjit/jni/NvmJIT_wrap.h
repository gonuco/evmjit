/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.8
 *
 * This file is not intended to be easily readable and contains a number of
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG
 * interface file instead.
 * ----------------------------------------------------------------------------- */

#ifndef SWIG_NvmJIT_WRAP_H_
#define SWIG_NvmJIT_WRAP_H_

class SwigDirector_Callback : public Callback, public Swig::Director {

public:
    void swig_connect_director(JNIEnv *jenv, jobject jself, jclass jcls, bool swig_mem_own, bool weak_global);
    SwigDirector_Callback(JNIEnv *jenv);
    virtual ~SwigDirector_Callback();
    virtual void doQuery(evm_variant *result, enum evm_query_key key, evm_variant const *arg);
    virtual void doUpdate(enum evm_update_key key, evm_variant const *arg1, evm_variant const *arg2);
    virtual int64_t doCall(enum evm_call_kind kind, int64_t gas, evm_uint160be const *address, evm_uint256be const *value, uint8_t const *input, size_t input_size, uint8_t *output, size_t output_size);
public:
    bool swig_overrides(int n) {
      return (n < 3 ? swig_override[n] : false);
    }
protected:
    Swig::BoolArray<3> swig_override;
};


#endif
