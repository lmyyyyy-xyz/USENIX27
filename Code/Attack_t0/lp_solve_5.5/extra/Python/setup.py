# usage:
#python setup.py build
#python setup.py install
#python setup.py bdist
#python setup.py bdist_wininst
#python setup.py bdist --format=msi

from distutils.core import setup, Extension
from os import getenv
from sys import platform
import sys
import os

py2 = sys.version_info[0] == 2
py3 = sys.version_info[0] == 3

print('Python2: ' + str(py2))
print('Python3: ' + str(py3))

p = sys.prefix

NUMPYPATH = '.'
try:
  import numpy

  if os.path.isdir(p + '/include/numpy'):
    NUMPY = 'NUMPY'
  elif os.path.isdir(p + '/Lib/site-packages/numpy/core/include/numpy'):
    NUMPY = 'NUMPY'
    NUMPYPATH = p + '/Lib/site-packages/numpy/core/include'
  elif py2 and os.path.isdir('/Library/Python/2.7/site-packages/numpy/core/include/numpy'):
#   osx
    NUMPY = 'NUMPY'
    NUMPYPATH='/Library/Python/2.7/site-packages/numpy/core/include'
  elif py2 and os.path.isdir('/Library/Developer/CommandLineTools/SDKs/MacOSX11.3.sdk/System/Library/Frameworks/Python.framework/Versions/2.7/Extras/lib/python/numpy'):
#   osx
    NUMPY = 'NUMPY'
    NUMPYPATH='/Library/Developer/CommandLineTools/SDKs/MacOSX11.3.sdk/System/Library/Frameworks/Python.framework/Versions/2.7/Extras/lib/python/numpy/core/include'
  elif py3 and os.path.isdir('/Library/Python/3.8/site-packages/numpy/core/include/numpy'):
#   osx
    NUMPY = 'NUMPY'
    NUMPYPATH='/Library/Python/3.8/site-packages/numpy/core/include'
  elif py3 and os.path.isdir('/usr/local/lib/python3.10/dist-packages/numpy/core/include/numpy'):
#   ubuntu
    NUMPY = 'NUMPY'
    NUMPYPATH='/usr/local/lib/python3.10/dist-packages/numpy/core/include'
  else:
    NUMPY = 'NONUMPY'

except:
  NUMPY = 'NONUMPY'

#NUMPY = 'NONUMPY'
#NUMPYPATH = '.'

if py2:
  NPY_NO_DEPRECATED_API='NPY_NO_DEPRECATED_API'
else:
  NPY_NO_DEPRECATED_API='NPY_NO_DEPRECATED_API_IGNORE'

NPY_NO_DEPRECATED_API='NPY_NO_DEPRECATED_API_IGNORE'

print('numpy: ' + NUMPY)
windir = getenv('windir')

if windir == None:
  WIN32 = 'NOWIN32'
  if platform == 'darwin':
    prefix='osx'
  else:
    prefix='ux'
else:
  WIN32 = 'WIN32'
  prefix='win'

LPSOLVE55 = '../../lpsolve55/bin/' + prefix

is_64bits = sys.maxsize > 2**32

print('is_64bits:' + str(is_64bits))

if is_64bits:
  LPSOLVE55 = LPSOLVE55 + '64'
else:
  LPSOLVE55 = LPSOLVE55 + '32'

setup (name = "lpsolve55",
       version = "5.5.2.13",
       description = "Linear Program Solver, Interface to lpsolve",
       author = "Peter Notebaert",
       author_email = "lpsolve@peno.be",
       url = "http://www.peno.be/",
       py_modules=['lp_solve', 'lp_maker'],
       ext_modules = [Extension("lpsolve55",
				["lpsolve.c", "hash.c", "pythonmod.c"],
                                define_macros=[('PYTHON', '1'), (WIN32, '1'), ('NODEBUG', '1'), ('DINLINE', 'static'), (NUMPY, '1'), (NPY_NO_DEPRECATED_API, 'NPY_1_7_API_VERSION'), ('_CRT_SECURE_NO_WARNINGS', '1')],
                                include_dirs=['../..', NUMPYPATH],
                                library_dirs=[LPSOLVE55],
				libraries = ['lpsolve55'])
		      ]
)
