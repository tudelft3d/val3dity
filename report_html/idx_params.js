// Populate index.html with the validation results from the json report
document.getElementById("in_file").innerHTML = report.input_file.split("/").pop();
document.getElementById("version").innerHTML = report.val3dity_version;
document.getElementById("time").innerHTML = report.time;

document.getElementById("planarity_d2p_tol").innerHTML = report.planarity_d2p_tol;
document.getElementById("planarity_n_tol").innerHTML = report.planarity_n_tol;
document.getElementById("snap_tol").innerHTML = report.snap_tol;
document.getElementById("overlap_tol").innerHTML = report.overlap_tol;
