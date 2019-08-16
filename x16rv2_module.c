#include <Python.h>

#include "x16rv2.h"

static PyObject *x16rv2_getpowhash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
#if PY_MAJOR_VERSION >= 3
    PyBytesObject *input;
#else
    PyStringObject *input;
#endif
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);

#if PY_MAJOR_VERSION >= 3
    x16rv2_hash((char *)PyBytes_AsString((PyObject*) input), output);
#else
    x16rv2_hash((char *)PyString_AsString((PyObject*) input), output);
#endif
    Py_DECREF(input);
#if PY_MAJOR_VERSION >= 3
    value = Py_BuildValue("y#", output, 32);
#else
    value = Py_BuildValue("s#", output, 32);
#endif
    PyMem_Free(output);
    return value;
}

static PyMethodDef X16Rv2Methods[] = {
    { "getPoWHash", x16rv2_getpowhash, METH_VARARGS, "Returns the proof of work hash using X16Rv2 hash" },
    { NULL, NULL, 0, NULL }
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef X16Rv2Module = {
    PyModuleDef_HEAD_INIT,
    "x16rv2_hash",
    "...",
    -1,
    X16Rv2Methods
};

PyMODINIT_FUNC PyInit_x16rv2_hash(void) {
    return PyModule_Create(&X16Rv2Module);
}

#else

PyMODINIT_FUNC initx16rv2_hash(void) {
    (void) Py_InitModule("x16rv2_hash", X16Rv2Methods);
}
#endif
