function index_error_table(){
    var body = document.body,
        tbl  = document.createElement('table');
    tbl.setAttribute('id', "errors");

    var tr = tbl.insertRow(0);
    var headers = ['Error', '# of primitives'];
    for (var i = 0; i < 2; i++){
        var h = document.createElement('th');
        h.appendChild(document.createTextNode(headers[i]));
        tr.appendChild(h);
    }

    var nr_errors = report.overview_errors.length;
    var l_errors = report.overview_errors;
    var nr_prims = report.overview_errors_no_primitives;

    for(var i = 0; i < nr_errors; i++){
        var tr = tbl.insertRow();
        var td0 = tr.insertCell(0);
        var td1 = tr.insertCell(1);
        var err = errors[l_errors[i]];
        var a = document.createElement('a');
        var linkText = document.createTextNode(err.name);
        a.appendChild(linkText);
        a.title = err.name;
        a.href = err.link.href;
        a.target = '_blank';
        td0.appendChild(a);
        td1.appendChild(document.createTextNode(nr_prims[i]));

        // set colour
        if (l_errors[i] < 200) {
            tr.setAttribute('class', 'linear-ring-level');
        } else if (100 < l_errors[i] && l_errors[i] < 300) {
            tr.setAttribute('class', 'polygon-level');
        } else if(200 < l_errors[i] && l_errors[i] < 400) {
            tr.setAttribute('class', 'shell-level');
        } else if (300 < l_errors[i] && l_errors[i] < 500) {
            tr.setAttribute('class', 'solid-level');
        } else if (400 < l_errors[i] && l_errors[i] < 600) {
            tr.setAttribute('class', 'solid-interactions-level');
        } else if (500 < l_errors[i] && l_errors[i] < 700) {
            tr.setAttribute('class', 'citygml-building');
        } else if (800 < l_errors[i] && l_errors[i] < 1000) {
            tr.setAttribute('class', 'others');
        }
    }
    body.appendChild(tbl);
}
index_error_table();
