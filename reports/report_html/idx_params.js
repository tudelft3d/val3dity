// Populate index.html with the validation results from the json report
document.getElementById("in_file").innerHTML = report.input_file;
document.getElementById("version").innerHTML = report.val3dity_version;
document.getElementById("time").innerHTML = report.time;

document.getElementById("planarity_d2p_tol").innerHTML = report.planarity_d2p_tol;
document.getElementById("planarity_n_tol").innerHTML = report.planarity_n_tol;
document.getElementById("snap_tol").innerHTML = report.snap_tol;
document.getElementById("overlap_tol").innerHTML = report.overlap_tol;

if (report.CityObjects == null) {
    document.getElementById("CO_total").innerHTML = 0;
    var CO_valid_pc = 0;
    document.getElementById("CO_valid").innerHTML = 0 + ' (' + CO_valid_pc + '%)';
    var CO_invalid_pc = 0;
    document.getElementById("CO_invalid").innerHTML = 0 + ' (' + CO_invalid_pc + '%)';
} else {
    document.getElementById("CO_total").innerHTML = report.total_cityobjects;
    var CO_valid_pc = Math.round(report.valid_cityobjects / report.total_cityobjects * 100);
    document.getElementById("CO_valid").innerHTML = report.valid_cityobjects + ' (' + CO_valid_pc + '%)';
    var CO_invalid_pc = Math.round(report.invalid_cityobjects / report.total_cityobjects * 100);
    document.getElementById("CO_invalid").innerHTML = report.invalid_cityobjects + ' (' + CO_invalid_pc + '%)';
}

document.getElementById("p_total").innerHTML = report.total_primitives;
var p_valid_pc = Math.round(report.valid_primitives / report.total_primitives * 100);
document.getElementById("p_valid").innerHTML = report.valid_primitives + ' (' + p_valid_pc + '%)';
var p_invalid_pc = Math.round(report.invalid_primitives / report.total_primitives * 100);
document.getElementById("p_invalid").innerHTML = report.invalid_primitives + ' (' + p_invalid_pc + '%)';
