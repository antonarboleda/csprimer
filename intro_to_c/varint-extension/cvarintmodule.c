#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject *cvarint_encode(PyObject *self, PyObject *args) {
    unsigned long n;
    int index = 0;
    char part;
    char* bytes = malloc(10);
    
    if (!PyArg_ParseTuple(args, "k", &n)) {
        return NULL;
    }

    while (n != 0) {
        part = n & 0x7f;
        n >>= 7;
        if (n > 0) {
            part |= 0x80;
        }

        bytes[index++] = part;
    }
    return PyBytes_FromStringAndSize(bytes, index);
}

static PyObject *cvarint_decode(PyObject *self, PyObject *args) {
    char* bytes;
    unsigned long v = 0;
    int i = 0;

    if (!PyArg_ParseTuple(args, "y", &bytes)) {
        return NULL;
    };
    
    // get the length of bytes
    while (bytes[i]) {
        i++;
    }
    
    for (int j = i - 1; j >= 0; j--) {
        v <<= 7;
        v |= (bytes[j] & 0x7f);
    }
    return PyLong_FromUnsignedLong(v);
}

static PyMethodDef CVarintMethods[] = {
    {"encode", cvarint_encode, METH_VARARGS, "Encode an integer as varint."},
    {"decode", cvarint_decode, METH_VARARGS,
     "Decode varint bytes to an integer."},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef cvarintmodule = {
    PyModuleDef_HEAD_INIT, "cvarint",
    "A C implementation of protobuf varint encoding", -1, CVarintMethods};

PyMODINIT_FUNC PyInit_cvarint(void) { return PyModule_Create(&cvarintmodule); }
