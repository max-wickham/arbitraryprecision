from distutils.core import setup, Extension

bigint_module = Extension('bigint',sources = ['bigint.hpp'])
encryption_module = Extension('encryption',sources = ['encryption.cpp'])

setup(name = 'Encryption',version='1.0',description = 'This is an encryption package',ext_modules = [encryption_module])