#include "pythonscript.h"

#include <Python.h>
#include <iostream>

void initializePython()
{
	if (!Py_IsInitialized()) {
		Py_Initialize();
		PyRun_SimpleString("import sys; sys.path.append('data/python')");
		FILE* f = fopen("data/python/server.py", "r");
		if (f) {
			PyRun_SimpleFile(f, "server.py");
			fclose(f);
		} else {
			std::clog << "[Warning] Could not open Python script data/python/server.py" << std::endl;
		}
	}
}

void finalizePython()
{
	if (Py_IsInitialized()) {
		Py_Finalize();
	}
}
