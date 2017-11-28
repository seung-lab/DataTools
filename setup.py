from setuptools import setup

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
                'datatools/*.hpp',
                'datatools/*.pyx',
                'datatools/backend/*.hpp',
            ]
        },
        include_package_data=True,
        zip_safe=False
)
