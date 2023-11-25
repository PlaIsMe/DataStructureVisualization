# import cffi
# import importlib
# import unittest
# import subprocess

# def preprocess(source_path):
#     with open(source_path, 'r') as source_file:
#         source_content = source_file.read()
#     result = subprocess.run(['g++', '-std=c++20', '-Isrc/Include', '-Lsrc/lib', 'sort.cpp', 'utils.cpp', 'main.cpp',
#                               'menu.cpp', 'page.cpp', '-lmingw32', '-lSDL2main' , '-lSDL2', '-lSDL2_image', '-lSDL2_ttf'],
#                            input=source_content,
#                             stdout=subprocess.PIPE,
#                             text=True,
#                             check=True)
#     return result.stdout

# def load(filename):
#     includes = preprocess(filename + '.hpp')

#     ffibuilder = cffi.FFI()
#     ffibuilder.cdef(includes)

#     with open(filename + '.cpp', 'r') as source_file:
#         source = source_file.read()

#     ffibuilder.set_source(filename + '_', source)
#     ffibuilder.compile()

#     module = importlib.import_module(filename + '_')
#     return module.lib

# class AddTest(unittest.TestCase):
#     def test_selection_sort(self):
#         module = load('sort')
#         input_vector = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5]
#         is_sorting = False
#         module.selectionSort(cffi.ffi.NULL, input_vector, is_sorting)
#         self.assertEqual(input_vector, [1, 1, 2, 3, 3, 4, 5, 5, 6, 9])

# if __name__ == '__main__':
#     unittest.main()