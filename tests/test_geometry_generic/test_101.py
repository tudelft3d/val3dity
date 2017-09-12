import pytest
from subprocess import call

VAL3DITYEXE = "/home/bdukai/Development/val3dity/build/val3dity"

def test_101():
    file = "/home/bdukai/Development/val3dity/tests/test_geometry_generic/cube28.poly"
    command = " ".join((VAL3DITYEXE, file, '-p Solid'))
    call(command, shell=True)
