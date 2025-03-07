import setuptools

with open('README.whl', 'r') as fh:
    long_description = fh.read()

setuptools.setup(
        name = 'Pythonic',
        version = '1.02',
        author = 'Stephan Avenwedde',
        author_email = 's.avenwedde@gmail.com',
        license = 'GPLv3',
        description='Graphical automation tool',
        long_description=long_description,
        long_description_content_type='text/markdown',
        url='https://github.com/hANSIc99/Pythonic',
        packages = ['Pythonic', 'Pythonic.executables'],
        package_dir = { '' : 'src'},
        package_data = { '' :
            ['public_html/static/GenericPipe.png',
             'public_html/static/GenericProcess.png',
             'public_html/static/ProcessPipe.png',
             'public_html/static/Scheduler.png',
             'public_html/static/python.ico',
             'public_html/static/qtlogo.svg',
             'public_html/static/qtloader.js',
             'public_html/static/*.js',
             'public_html/static/*.wasm',
             'public_html/static/*.data',
             'public_html/templates/*.html',
             'public_html/config/Toolbox/Basic/*'
             ]
        },
        entry_points = {
            'console_scripts' : ['Pythonic = Pythonic.script:run']
            },
        python_requires = '>=3.7',
        install_requires = [
            'PySide2==5.14.2.3',
            'eventlet>=0.27.0',
             'debugpy==1.2.1'
             ],
        classifiers = [
            'Programming Language :: Python :: 3.7',
            'Programming Language :: Python :: 3.8',
            'Programming Language :: Python :: 3.9',
            'Programming Language :: Python :: 3.10',
            'Development Status :: 4 - Beta',
            'Intended Audience :: Manufacturing',
            'Intended Audience :: End Users/Desktop',
            'Intended Audience :: Developers',
            'Intended Audience :: Education',
            'License :: OSI Approved :: GNU General Public License v3 (GPLv3)',
            'Operating System :: OS Independent',
            'Environment :: Web Environment',
            'Environment :: Console',
            'Natural Language :: English',
            'Topic :: Software Development'
            ],
        )
