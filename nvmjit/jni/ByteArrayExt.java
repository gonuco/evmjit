package com.nuco.nvmjit;

public class ByteArrayExt {

    private final static native void copyToJNI(long cptr, byte[] bytes);

    private final static native byte[] copyFromJNI(long cptr, int size);

    /**
     * Convert a ByteArray into a java byte array.
     * 
     * @param arr
     *            a ByteArray reference
     * @param size
     *            the size of the ByteArray. Size is not checked, so make sure
     *            it's correct.
     * @return
     */
    public static byte[] toBytes(ByteArray arr, int size) {
        return copyFromJNI(ByteArray.getCPtr(arr), size);
    }

    /**
     * Convert a java byte array into a ByteArray
     * 
     * @param bytes
     *            a java byte array
     * @return
     */
    public static ByteArray fromBytes(byte[] bytes) {
        ByteArray arr = new ByteArray(bytes.length);

        copyToJNI(ByteArray.getCPtr(arr), bytes);
        return arr;
    }

}
