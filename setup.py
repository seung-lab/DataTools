from Cython.Build import cythonize
# from distutils.core import Extension
from distutils.sysconfig import get_python_inc
from setuptools import setup, Extension

import numpy
import os


include_dirs = [
    './datatools',
    './datatools/backend',
    os.path.dirname(get_python_inc()),
    numpy.get_include(),
]


extensions = [
    Extension(
        'datatools._frontend',
        sources = ['datatools/*.pyx', 'datatools/c_frontend.cpp'],
        include_dirs=include_dirs,
        language='c++',
        extra_link_args=['-std=c++11'],
        extra_compile_args=['-std=c++11', '-w']
    ),
]


setup(
    name='datatools',
    version='0.0.1',
    description='A C++ extension to DataProvider.',
    url='https://github.com/torms3/DataProviderExtension',
    author='Kisuk Lee',
    author_email='kisuklee@mit.edu',
    license='MIT',
    requires=['cython','numpy'],
    packages=['datatools'],
    package_data={
        '': [
            'datatools/*.h',
            'datatools/*.cpp',
            'datatools/*.pyx',
            'datatools/backend/*.hpp',
        ]
    },
    include_package_data=True,
    zip_safe=False,
    ext_modules = cythonize(extensions)
)
