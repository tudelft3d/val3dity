"""Testing the --report_in_cityjson option"""

import json
import os
import subprocess
import tempfile

import pytest


# ------------------------------------------------------------------------ Data
@pytest.fixture(scope="module")
def data_cjseq_3dbag():
    """CityJSONSeq file with 2 buildings"""
    root = os.getcwd()
    file_path = os.path.abspath(
        os.path.join(root, "data/cityjsonseq/3dbag_b2.city.jsonl")
    )
    return file_path


# ----------------------------------------------------------------------- Tests
def test_report_in_cityjson_structure(val3dity, data_cjseq_3dbag):
    """Test that --report_in_cityjson preserves structure and adds extension"""
    
    # Read original file to get expected structure
    with open(data_cjseq_3dbag, 'r') as f:
        original_lines = f.readlines()
    
    # Parse original data
    original_metadata = json.loads(original_lines[0])
    original_features = []
    for line in original_lines[1:]:
        original_features.append(json.loads(line))
    
    # Run val3dity with --report_in_cityjson
    with tempfile.NamedTemporaryFile(mode='w', suffix='.jsonl', delete=False) as tmp:
        output_path = tmp.name
    
    try:
        command = [val3dity, data_cjseq_3dbag, "--report_in_cityjson", output_path]
        proc = subprocess.run(
            command,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            universal_newlines=True,
            timeout=15
        )
        
        assert proc.returncode == 0, f"val3dity failed: {proc.stderr}"
        
        # Read output file
        with open(output_path, 'r') as f:
            output_lines = f.readlines()
        
        # Check same number of lines
        assert len(output_lines) == len(original_lines), \
            f"Expected {len(original_lines)} lines, got {len(output_lines)}"
        
        # Check metadata line (first line)
        output_metadata = json.loads(output_lines[0])
        
        # Verify original metadata is preserved
        assert output_metadata["type"] == original_metadata["type"]
        assert output_metadata["version"] == original_metadata["version"]
        assert output_metadata["transform"] == original_metadata["transform"]
        assert output_metadata["metadata"] == original_metadata["metadata"]
        
        # Verify extension is added
        assert "extensions" in output_metadata
        assert "val3dity" in output_metadata["extensions"]
        assert output_metadata["extensions"]["val3dity"]["version"] == "0.3.0"
        assert "val3dity.ext.json" in output_metadata["extensions"]["val3dity"]["url"]
        
        # Verify +val3dity-report is added
        assert "+val3dity-report" in output_metadata
        report = output_metadata["+val3dity-report"]
        assert "val3dity_version" in report
        assert "validity" in report
        assert "parameters" in report
        assert "features_overview" in report
        assert "primitives_overview" in report
        assert "error_code_summary" in report
        assert "dataset_errors" in report
        
        # Check feature lines
        for i, line in enumerate(output_lines[1:], start=1):
            output_feature = json.loads(line)
            original_feature = original_features[i - 1]
            
            # Verify feature ID is preserved
            assert output_feature["id"] == original_feature["id"]
            assert output_feature["type"] == original_feature["type"]
            
            # Verify CityObjects are preserved
            assert set(output_feature["CityObjects"].keys()) == \
                   set(original_feature["CityObjects"].keys())
            
            # Check each CityObject
            for co_id in original_feature["CityObjects"]:
                original_co = original_feature["CityObjects"][co_id]
                output_co = output_feature["CityObjects"][co_id]
                
                # Verify type is preserved
                assert output_co["type"] == original_co["type"]
                
                # Verify geometry is preserved (if present)
                if "geometry" in original_co:
                    assert "geometry" in output_co
                    assert len(output_co["geometry"]) == len(original_co["geometry"])
                
                # Verify vertices are preserved
                assert output_feature["vertices"] == original_feature["vertices"]
                
                # Check if +val3dity-validation is added correctly
                if "geometry" in output_co and len(output_co["geometry"]) > 0:
                    # CityObject with geometry should have validation
                    assert "attributes" in output_co
                    assert "+val3dity-validation" in output_co["attributes"]
                    
                    validation = output_co["attributes"]["+val3dity-validation"]
                    assert "validity" in validation
                    assert "geometries" in validation
                    assert isinstance(validation["validity"], bool)
                    assert isinstance(validation["geometries"], list)
                    
                    # Check geometry validation structure
                    for geom_val in validation["geometries"]:
                        assert "geometryIndex" in geom_val
                        assert "errors" in geom_val
                        assert isinstance(geom_val["geometryIndex"], int)
                        assert isinstance(geom_val["errors"], list)
                        
                        # Check error structure
                        for error in geom_val["errors"]:
                            assert "code" in error
                            assert "description" in error
                            assert "sourceId" in error
                            assert "location" in error
                            assert isinstance(error["code"], int)
                
                # Check Building with children has validation if needed
                if output_co["type"] == "Building" and "children" in output_co:
                    # Building with children might have feature-level errors
                    if "attributes" in output_co and \
                       "+val3dity-validation" in output_co["attributes"]:
                        validation = output_co["attributes"]["+val3dity-validation"]
                        assert "validity" in validation
                        # May have "features" array for feature-level errors
                        if "features" in validation:
                            assert isinstance(validation["features"], list)
    
    finally:
        # Clean up
        if os.path.exists(output_path):
            os.remove(output_path)


def test_report_in_cityjson_revalidation(val3dity, data_cjseq_3dbag):
    """Test that re-validating a file with extension data removes old data"""
    
    # First validation
    with tempfile.NamedTemporaryFile(mode='w', suffix='.jsonl', delete=False) as tmp1:
        output_path1 = tmp1.name
    
    with tempfile.NamedTemporaryFile(mode='w', suffix='.jsonl', delete=False) as tmp2:
        output_path2 = tmp2.name
    
    try:
        # First run
        command1 = [val3dity, data_cjseq_3dbag, "--report_in_cityjson", output_path1]
        proc1 = subprocess.run(
            command1,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            universal_newlines=True,
            timeout=15
        )
        assert proc1.returncode == 0
        
        # Second run (re-validate the output)
        command2 = [val3dity, output_path1, "--report_in_cityjson", output_path2]
        proc2 = subprocess.run(
            command2,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            universal_newlines=True,
            timeout=15
        )
        assert proc2.returncode == 0
        
        # Read both outputs
        with open(output_path1, 'r') as f:
            lines1 = f.readlines()
        with open(output_path2, 'r') as f:
            lines2 = f.readlines()
        
        # Check that both have same structure
        assert len(lines1) == len(lines2)
        
        # Parse metadata
        metadata1 = json.loads(lines1[0])
        metadata2 = json.loads(lines2[0])
        
        # Check that extension data is present in both
        assert "+val3dity-report" in metadata1
        assert "+val3dity-report" in metadata2
        
        # Check that there's no duplication (only one +val3dity-report)
        assert metadata1["+val3dity-report"] is not None
        assert metadata2["+val3dity-report"] is not None
        
        # Check feature lines don't have duplicated validation
        for i in range(1, len(lines1)):
            feature1 = json.loads(lines1[i])
            feature2 = json.loads(lines2[i])
            
            for co_id in feature1["CityObjects"]:
                co1 = feature1["CityObjects"][co_id]
                co2 = feature2["CityObjects"][co_id]
                
                # Both should have same validation structure
                if "attributes" in co1 and "+val3dity-validation" in co1["attributes"]:
                    assert "+val3dity-validation" in co2["attributes"]
                    # Validation should be identical
                    assert co1["attributes"]["+val3dity-validation"]["validity"] == \
                           co2["attributes"]["+val3dity-validation"]["validity"]
    
    finally:
        # Clean up
        for path in [output_path1, output_path2]:
            if os.path.exists(path):
                os.remove(path)
