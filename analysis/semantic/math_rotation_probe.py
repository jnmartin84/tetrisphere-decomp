"""Host sanity check of inferred rotation orders; not an N64 numerical gate."""
import ctypes
import json
import math
from pathlib import Path
import random
import subprocess
import sys
import tempfile

source = Path(sys.argv[1]).read_text()
names = ('func_8002FD9C', 'func_8002FF08')
bodies = []
for name in names:
    start = source.index('void ' + name + '(')
    end = source.index('\n}', start) + 2
    bodies.append(source[start:end])

def rotate_reference(vector, angles, order):
    # Independent column-vector matrices; arguments are Y, X, Z in degrees.
    by_axis = dict(zip('YXZ', angles))
    for axis in order:
        angle = ctypes.c_float(by_axis[axis] * 0.017453293).value
        c, s = math.cos(angle), math.sin(angle)
        matrix = {'X': ((1, 0, 0), (0, c, -s), (0, s, c)),
                  'Y': ((c, 0, s), (0, 1, 0), (-s, 0, c)),
                  'Z': ((c, -s, 0), (s, c, 0), (0, 0, 1))}[axis]
        vector = [sum(row[j] * vector[j] for j in range(3)) for row in matrix]
    return vector

with tempfile.TemporaryDirectory() as directory:
    directory = Path(directory)
    cfile = directory / 'rotations.c'
    library = directory / 'rotations.so'
    cfile.write_text('#include <math.h>\ntypedef float f32;\ntypedef double f64;\n'
                     '#define __cosf cosf\n' + '\n'.join(bodies) + '\n')
    subprocess.run(['cc', '-shared', '-fPIC', '-O0', '-ffp-contract=off',
                    str(cfile), '-lm', '-o', str(library)], check=True)
    lib = ctypes.CDLL(str(library))
    funcs = [getattr(lib, name) for name in names]
    for fn in funcs:
        fn.argtypes = [ctypes.c_float] * 3 + [ctypes.POINTER(ctypes.c_float)] * 3
        fn.restype = None
    def call(fn, angles, vector):
        values = [ctypes.c_float(x) for x in vector]
        fn(*angles, *(ctypes.byref(x) for x in values))
        return [x.value for x in values]
    rng = random.Random(8170)
    cases = [([0, 0, 0], [1, 2, 3])]
    for axis in range(3):
        angles = [0, 0, 0]
        angles[axis] = 90
        for basis in range(3):
            vector = [0, 0, 0]
            vector[basis] = 1
            cases.append((angles, vector))
    cases += [([ctypes.c_float(rng.uniform(-180, 180)).value for _ in range(3)],
               [ctypes.c_float(rng.uniform(-120, 120)).value for _ in range(3)])
              for _ in range(100)]
    worst = 0
    for angles, vector in cases:
        scale = max(1, math.sqrt(sum(x*x for x in vector)))
        for fn, order in zip(funcs, ('ZXY', 'YXZ')):
            actual = call(fn, angles, vector)
            expected = rotate_reference(vector, angles, order)
            error = max(abs(a-b) for a,b in zip(actual, expected)) / scale
            worst = max(worst, error)
            assert error < 2e-6, (order, angles, vector, actual, expected)
        recovered = call(funcs[1], [-a for a in angles], call(funcs[0], angles, vector))
        assert max(abs(a-b) for a,b in zip(recovered,vector)) / scale < 2e-6
    print(json.dumps({'status':'PASS', 'cases':len(cases), 'order_checks':2*len(cases),
                      'inverse_checks':len(cases), 'max_normalized_order_error':worst,
                      'scope':'Host extracted baseline C versus independent axis matrices; not target floating-point equivalence.'}, indent=2))
