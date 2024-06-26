#ifndef Py_SLICEOBJECT_H
#define Py_SLICEOBJECT_H
#include "third_party/python/Include/object.h"
COSMOPOLITAN_C_START_

/* The unique ellipsis object "..." */

extern PyObject _Py_EllipsisObject; /* Don't use this directly */

#define Py_Ellipsis (&_Py_EllipsisObject)

/* Slice object interface */

/*

A slice object containing start, stop, and step data members (the
names are from range).  After much talk with Guido, it was decided to
let these be any arbitrary python type.  Py_None stands for omitted values.
*/
#ifndef Py_LIMITED_API
typedef struct {
    PyObject_HEAD
    PyObject *start, *stop, *step;	/* not NULL */
} PySliceObject;
#endif

extern PyTypeObject PySlice_Type;
extern PyTypeObject PyEllipsis_Type;

#define PySlice_Check(op) (Py_TYPE(op) == &PySlice_Type)

PyObject * PySlice_New(PyObject* start, PyObject* stop,
                                  PyObject* step);
#ifndef Py_LIMITED_API
PyObject * _PySlice_FromIndices(Py_ssize_t start, Py_ssize_t stop);
int _PySlice_GetLongIndices(PySliceObject *self, PyObject *length,
                                 PyObject **start_ptr, PyObject **stop_ptr,
                                 PyObject **step_ptr);
#endif
int PySlice_GetIndices(PyObject *r, Py_ssize_t length,
                                  Py_ssize_t *start, Py_ssize_t *stop, Py_ssize_t *step);
int PySlice_GetIndicesEx(PyObject *r, Py_ssize_t length,
                                     Py_ssize_t *start, Py_ssize_t *stop,
                                     Py_ssize_t *step, Py_ssize_t *slicelength);

#if !defined(Py_LIMITED_API) || (Py_LIMITED_API+0 >= 0x03050400 && Py_LIMITED_API+0 < 0x03060000) || Py_LIMITED_API+0 >= 0x03060100
#ifdef Py_LIMITED_API
#define PySlice_GetIndicesEx(slice, length, start, stop, step, slicelen) (  \
    PySlice_Unpack((slice), (start), (stop), (step)) < 0 ?                  \
    ((*(slicelen) = 0), -1) :                                               \
    ((*(slicelen) = PySlice_AdjustIndices((length), (start), (stop), *(step))), \
     0))
#endif
int PySlice_Unpack(PyObject *slice,
                               Py_ssize_t *start, Py_ssize_t *stop, Py_ssize_t *step);
Py_ssize_t PySlice_AdjustIndices(Py_ssize_t length,
                                             Py_ssize_t *start, Py_ssize_t *stop,
                                             Py_ssize_t step);
#endif

COSMOPOLITAN_C_END_
#endif /* !Py_SLICEOBJECT_H */
