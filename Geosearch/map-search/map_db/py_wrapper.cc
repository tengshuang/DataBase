#include <Python.h>

#include "db/kit.h"
#include "db/poi.h"



using namespace map_search::db;

PyObject* wrap_ReadJson(PyObject* self, PyObject* args) {
  char* filename;
  if (!PyArg_ParseTuple(args, "s", &filename))
    return NULL;
  ReadJson(filename);

  Py_INCREF(Py_None);
  return Py_None;
}

PyObject* wrap_Search(PyObject* self, PyObject* args) {
  double lat;
  double lng;
  char* input;
  unsigned num;
  if (!PyArg_ParseTuple(args, "ddsi", &lat, &lng, &input, &num))
    return NULL;

  const std::vector<POI>& pois = map_search::db::Search(lat, lng, input, num);
  PyObject* py_pois = PyList_New(pois.size());
  for (unsigned index = 0; index < pois.size(); ++index) {
    const POI& poi = pois.at(index);
    PyObject* py_poi = PyList_New(4);
    PyList_SetItem(py_poi, 0, PyString_FromString(poi.name_.data()));
    PyList_SetItem(py_poi, 1, PyFloat_FromDouble(poi.lat_));
    PyList_SetItem(py_poi, 2, PyFloat_FromDouble(poi.lng_));
    PyList_SetItem(py_poi, 3, PyString_FromString(poi.addr_.data()));

    PyList_SetItem(py_pois, index, py_poi);
  }
  return py_pois;
}

static PyMethodDef methods[] = {
  {"read_json", wrap_ReadJson, METH_VARARGS, "read POIs from file in json"},
  {"search", wrap_Search, METH_VARARGS, "knn search"},
  {NULL, NULL}
};

PyMODINIT_FUNC initdb() {
  Py_InitModule("db", methods);
}

