"""Tesing command-line user input.
"""
import pytest
import subprocess, os
import re

@pytest.fixture(scope="module")
def validate_full():
    def _validate(command):
        try:
            proc = subprocess.run(command,
                                  stdout=subprocess.PIPE,
                                  stderr=subprocess.PIPE,
                                  universal_newlines=True,
                                  timeout=6)
        except subprocess.TimeoutExpired:
            return([" ".join(["Something went really wrong.",
                             "Validate the file separately with val3dity.",
                             "Or set a higher timeout in conftest.py."])])
        out = proc.stdout
        err = proc.stderr
        rcode = proc.returncode
        if rcode < 0:
            # For example Segmentation fault
            return(["Something went really wrong. Validate the file separately with val3dity."])
        else:
            return([out, err])
        
    return(_validate)


@pytest.fixture(scope="module",
                params=[
                    ["--unittests", "--notranslate"],
                    ["--unittests", "--overlap_tol 1.0"],
                    ["--unittests", "--snap_tol 1"],
                    ["--unittests", "--planarity_n_tol 18.5"],
                    ["--unittests", "--planarity_d2p_tol 0.5"]
                    ])
def options_valid(request):
    return(request.param)


@pytest.fixture(scope="module",
                params=[
                    ["--unittests", "-p", "Solid"],
                    ["--unittests", "-p", "MultiSurface"],
                    ["--unittests", "-p", "CompositeSurface"]
                    ])
def options_primitive(request):
    return(request.param)


@pytest.fixture(scope="module",
                params=[
                    ["--unittests", "--overlap_tol 1cm"],
                    ["--unittests", "--snap_tol 1ft"],
                    ["--unittests", "--planarity_n_tol 18degree"],
                    ["--unittests", "--planarity_n_tol 18rad"],
                    ["--unittests", "--planarity_d2p_tol 2.5mm"]
                    ])
def options_invalid(request):
    return(request.param)


@pytest.fixture(scope="module")
def data_ignore_204():
    """Unit cube with a vertical fold (0.0099) in the top face"""
    root = os.getcwd()
    file_path = os.path.abspath(
        os.path.join(root, "data/test_geometry_generic/204_1.poly")
        )
    return([file_path])


@pytest.fixture(scope="module",
                params=["basecube.off",
                        "basecube.obj",
                        "basecube.poly"])
def data_basecube(request):
    """Unit cube"""
    root = os.getcwd()
    file_path = os.path.abspath(
        os.path.join(root, "data/test_valid/", request.param)
        )
    return([file_path])


@pytest.fixture(scope="module")
def verbose_reference():
    """The part of val3dity console output that is only printed when 
    validating composite_solid.json with --verbose option"""
    
    reference = """
======== Validating Primitive ========
CompositeSolid
id: id-1(0)
--
--- Shell validation (#-1) ---
-----2D validation of each surface
-----Triangulation of each surface
-----Planarity of surfaces (with normals deviation)
-----Combinatorial consistency
-----Geometrical consistency
-----Global orientation of normals
--- Shell validation (#-1) ---
-----2D validation of each surface
-----Triangulation of each surface
-----Planarity of surfaces (with normals deviation)
-----Combinatorial consistency
-----Geometrical consistency
-----Global orientation of normals
-----Are two solids duplicated
-----Intersections of solids
-----Forming one solid (union)
========= VALID =========
"""
    return reference


@pytest.fixture(scope="module",
                params=["empty_primitive.json",
                        "empty_primitive.obj",
                        "empty_primitive.off",
                        "empty_primitive.xml"])
def data_no_information(request):
    root = os.getcwd()
    file_path = os.path.abspath(
        os.path.join(root, "data/test_empty", request.param)
        )
    return([file_path])


@pytest.fixture(scope="module")
def info_reference():
    """The part of val3dity console output that is printed when
    val3dity --information composite_solid.gml is called"""
    
    reference = """
++++++++++++++++++++ GENERAL +++++++++++++++++++++
CityGML version: v2.0
+++++++++++++++++++ PRIMITIVES +++++++++++++++++++
gml:Solid                                        2
gml:MultiSolid                                   0
gml:CompositeSolid                               1
gml:MultiSurface                                 0
gml:CompositeSurface                             2
gml:Polygon                                     12

++++++++++++++++++++ BUILDINGS +++++++++++++++++++
Building                                         0
    without BuildingPart                         0
    having BuildingPart                          0
    with gml:id                                  0
BuildingPart                                     0
    with gml:id                                  0
LOD1
    Building stored in gml:Solid                 0
    Building stored in gml:MultiSurface          0
    Building with semantics for surfaces         0
LOD2
    Building stored in gml:Solid                 0
    Building stored in gml:MultiSurface          0
    Building with semantics for surfaces         0
LOD3
    Building stored in gml:Solid                 0
    Building stored in gml:MultiSurface          0
    Building with semantics for surfaces         0
++++++++++++++++++++++++++++++++++++++++++++++++++
"""
    return reference


#----------------------------------------------------------------------- Tests
# TODO: add tests on the report content

# data_composite_solid is in conftest.py
def test_options_valid(validate, data_composite_solid, options_valid):
    error = validate(data_composite_solid, options=options_valid)
    assert(error == [])

def test_default_options_primitive(val3dity, validate_full, data_basecube):
    """See issue  #72"""
    p_option = 'Solid' # default -p is Solid
    pat_re = re.compile(r"(?<=Primitive\(s\) validated: ).+", re.MULTILINE)
    options = ["--unittests"]
    command = [val3dity] + options + data_basecube
    out, err = validate_full(command)
    p_validated = pat_re.search(out).group()
    assert p_validated == p_option

def test_options_primitive(val3dity, validate_full, data_basecube,
                           options_primitive):
    """See issue  #72"""
    p_option = options_primitive[2]
    pat_re = re.compile(r"(?<=Primitive\(s\) validated: ).+", re.MULTILINE)
    command = [val3dity] + options_primitive + data_basecube
    out, err = validate_full(command)
    p_validated = pat_re.search(out).group()
    assert p_validated == p_option
    

def test_options_invalid(validate, data_composite_solid, options_invalid):
    error = validate(data_composite_solid, options=options_invalid)
    assert(error == [903])

def test_ignore_204(validate, data_ignore_204):
    error = validate(data_ignore_204, options=["--unittests",
                                               "-p Solid",
                                               "--ignore204"])
    assert(error == [])

@pytest.mark.skip(reason="not implemented yet, see #80")
def test_verbose(val3dity, validate_full, data_composite_solid, verbose_reference):
    options = ["--verbose"]
    command = [val3dity] + options + data_composite_solid
    out, err = validate_full(command)
    assert verbose_reference in out

@pytest.mark.skip(reason="not implemented yet, see #81")
def test_no_information(val3idity, validate_full, data_no_information):
    info_reference = "Statistics/information only for CityGML files"
    options = ["-i"]
    command = [val3dity] + options + data_no_information
    out, err = validate_full(command)
    assert info_reference in out

def test_information(val3dity, validate_full, info_reference):
    root = os.getcwd()
    data = os.path.abspath(
        os.path.join(root, "data/test_valid/composite_solid.gml")
        )
    options = ["-i"]
    command = [val3dity] + options + [data]
    out, err = validate_full(command)
    assert info_reference in out

def test_ignore_rest(val3dity, validate_full, data_composite_solid):
    options = ["--unittests"]
    command = [val3dity] + options + data_composite_solid + ["--", "-i"]
    out, err = validate_full(command)
    if (out.find('@VALID') != -1):
        error = []
    else:
        error = out
    assert error == []

def test_version(val3dity, validate_full):
    command = [val3dity] + ["--version"]
    out, err = validate_full(command)
    assert "version:" in out
    
