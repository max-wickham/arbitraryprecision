from distutils.core import setup, Extension
encryption_module = Extension('encryption',sources = ['encryption.cpp','bigint.cpp'], include_dirs=["../include"])
setup(name = 'Encryption', version='1.0',description = 'This is an encryption package',ext_modules = [encryption_module])
