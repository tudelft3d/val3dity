function tableCreate(){
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
        td0.appendChild(a);
        td1.appendChild(document.createTextNode(nr_prims[i]));
        tr.style.background = err.colour;
    }
    body.appendChild(tbl);
}
tableCreate();
