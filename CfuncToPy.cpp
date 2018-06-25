#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "/usr/include/python2.7/Python.h"
#include <math.h>
#include <numpy/arrayobject.h>


using namespace std;


static PyObject* Hello(PyObject* self, PyObject* args);
static PyObject* ShowStr(PyObject* self, PyObject* args);
static PyObject* ShowList(PyObject* self, PyObject* args);
static PyObject* Operation(PyObject* self, PyObject* args);
static PyObject* ShowNumpy(PyObject* self, PyObject* args);

//{"function name in python program", function name in C program, METH_VARARGS (use C function) , "describe" }
static PyMethodDef CMethod[] = {
    {"Hello", Hello, METH_VARARGS, "A hello function."},
    {"ShowStr", ShowStr, METH_VARARGS, "Print string."},
    {"ShowList", ShowList, METH_VARARGS, "Print string."},
    {"Operation", Operation, METH_VARARGS, "GetImage."},
    {"ShowNumpy",ShowNumpy,METH_VARARGS,"new_vec"},
    {NULL, NULL, 0, NULL} //end
};

// init"*.so", * file name must be same as function name, that is rule
PyMODINIT_FUNC initCfuncToPy(void) {
     (void) Py_InitModule("CfuncToPy", CMethod);
     import_array();
};

static PyObject* Operation(PyObject* self, PyObject* args){
		//PyObject* listObj;		
		float f1,f2;
		float add,sub,mul,div;
		if(!PyArg_ParseTuple(args, "ff",&f1,&f2)) 
			return NULL;
		add=f1+f2;
		sub=f1-f2;
		mul=f1*f2;
		div=f1/f2;
		
		return Py_BuildValue("ffff", add,sub,mul,div);
};

static PyObject* ShowList(PyObject* self, PyObject* args){
		PyObject* listObj;		
		
		if(!PyArg_ParseTuple(args, "O" ,&listObj)) //"O" : object
			return NULL;

		long length = PyList_Size(listObj);
		PyObject *lst = PyList_New(length);
		int i;
		for (i = 0; i < length; i++) {
			//get an element out of the list - the element is also a python objects
			PyObject* temp = PyList_GetItem(listObj, i);
			//we know that object represents an integer - so convert it into C 
			//const char* elem = PyString_AsString(temp);
			double elem = PyFloat_AsDouble(temp);
			PyList_SET_ITEM(lst, i, temp);
		}
		return lst;
};

static PyObject* ShowStr(PyObject* self, PyObject* args) {
    const char*  str;
    if (!PyArg_ParseTuple(args, "s", &str))
        return NULL; 
    return Py_BuildValue("s", str);
};


static PyObject* Hello(PyObject* self, PyObject* args) {
    printf("Hello! The C functions are already prepared \n");
    Py_RETURN_NONE;
};


static PyObject *ShowNumpy(PyObject *self, PyObject *args) {
    PyObject *out=NULL;
    PyArrayObject *oarr=NULL;

    if (!PyArg_ParseTuple(args, "O!", &PyArray_Type, &out)) return NULL;

    oarr = (PyArrayObject*)PyArray_FROM_OTF(out, NPY_DOUBLE, NPY_INOUT_ARRAY);
    if (oarr == NULL)  return NULL;
   
  
    for (int i=0; i<oarr->dimensions[0]; ++i) {
        for (int j=0; j<oarr->dimensions[1]; ++j) {
            double *v = (double*)PyArray_GETPTR2(oarr, i, j);
            *v = *v * 2;
        }
    }

    Py_DECREF(oarr);
    Py_INCREF(Py_None);
    return Py_None;

}

