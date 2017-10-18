function idx_validation_summary(){
    var body = document.body,
        tbl  = document.createElement('table');
    tbl.setAttribute('id', "summary");

    var tr = tbl.insertRow(0);
    var headers = [" ", "Total", "Valid", "Invalid"];
    for (var i = 0; i < 4; i++){
        var h = document.createElement('th');
        h.appendChild(document.createTextNode(headers[i]));
        tr.appendChild(h);
    }

    if (report.CityObjects != null) {
        var tr = tbl.insertRow();

        // cell CityObjects
        var td0 = tr.insertCell(0);
        var a = document.createElement('a');
        var linkText = document.createTextNode('CityObjects');
        a.appendChild(linkText);
        a.title = "CityObjects";
        a.href = "CityObjects.html";
        td0.appendChild(a);
        // cell Total
        var td_t = tr.insertCell(1);
        td_t.appendChild(document.createTextNode(report.total_cityobjects));
        // cell Valid
        var td_v = tr.insertCell(2);
        var CO_valid_pc = Math.round(report.valid_cityobjects / report.total_cityobjects * 100);
        var v = report.valid_cityobjects + ' (' + CO_valid_pc + '%)';
        td_v.appendChild(document.createTextNode(v));
        // cell Invalid
        var td_i = tr.insertCell(3);
        var CO_invalid_pc = Math.round(report.invalid_cityobjects / report.total_cityobjects * 100);
        var i = report.invalid_cityobjects + ' (' + CO_invalid_pc + '%)';
        td_i.appendChild(document.createTextNode(i));
    }

    if (report.Primitives != null) {
        var tr = tbl.insertRow();

        // cell Primitives
        var td0 = tr.insertCell(0);
        var a = document.createElement('a');
        var linkText = document.createTextNode('Primitives');
        a.appendChild(linkText);
        a.title = "Primitives";
        a.href = "Primitives.html";
        td0.appendChild(a);
        // cell Total
        var td_t = tr.insertCell(1);
        td_t.appendChild(document.createTextNode(report.total_primitives));
        // cell Valid
        var td_v = tr.insertCell(2);
        var p_valid_pc = Math.round(report.valid_primitives / report.total_primitives * 100);
        var v = report.valid_primitives + ' (' + p_valid_pc + '%)';
        td_v.appendChild(document.createTextNode(v));
        // cell Invalid
        var td_i = tr.insertCell(3);
        var p_invalid_pc = Math.round(report.invalid_primitives / report.total_primitives * 100);
        var i = report.invalid_primitives + ' (' + p_invalid_pc + '%)';
        td_i.appendChild(document.createTextNode(i));
    }

    body.appendChild(tbl);
}
idx_validation_summary();
