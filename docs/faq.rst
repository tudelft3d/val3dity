===
FAQ
===

.. contents:: :local:


Who validates the validator, huh?
---------------------------------

We wrote a comprehensive suite of tests using the *pytest* python framework and a custom setup.
This tests, among many others, the following:

- Empty files and geometries, invalid input file formats. However, val3dity *does not* validate the schema of the input.
- All the error cases listed in :ref:`errors`.
- Various valid geometries and boundary conditions.
- Command-line user input.

You can read more about the `details <https://github.com/tudelft3d/val3dity/blob/master/tests/README.md>`_, or check the `complete list of tested geometries <https://github.com/tudelft3d/val3dity/blob/master/data/test_metadata.yml>`_


How to interpret the report?
----------------------------

With the option ``--report`` a JSON report is output.

The report lists errors at 3 levels:

  1. errors with the input files (errors 9xx)
  2. errors with the features, eg Buildings in CityJSON (errors 6xx and 7xx)
  3. errors with the geometries (errors 1xx -- 5xx)

If you use CityJSON, the sub-primitives cannot have IDs, so a 0-based system is used for reporting. For example, if you have a Solid with 2 Shells, then the first one is "0" and the second is "1", and the same applies for each of the surface of a Shell.

In the report, if one error of a Solid is like this one:

.. code-block:: json

  {
    "code": 102,
    "description": "CONSECUTIVE_POINTS_SAME",
    "id": "0 | 2",
    "info": "",
    "type": "Error"
  }

this means that the Shell with ID=0 (the first one, thus the outer Shell) and the 3rd surface in it (because of ID=2) has the error 102.
The same principle applies to all primitives, the "|" separate the primitive IDs.

You can navigate this report with a JSON browser (eg drag it in Firefox) or by loading it to the `val3dity report browser <http://geovalidation.bk.tudelft.nl/val3dity/browse/>`_:

.. image:: _static/report1.png
   :width: 49%
.. image:: _static/report2.png
   :width: 49%

There you get an overview of the statistics per features and primitives, and each feature has its primitives and errors as children.   



I get many errors 203 and 204, but my planes look planar to me. Why is that?
----------------------------------------------------------------------------

This is a very common error, actually :ref:`e203` is the most common error for `all the files so far uploaded to our web application <http://geovalidation.bk.tudelft.nl/val3dity/stats>`_.

Read carefully the explanations of the errors :ref:`e203` and :ref:`e204`.

A surface is first check for error 203, if valid then error 204 is checked. 
By definition, if an error 204 is reported then all the vertices are within 1cm (tolerance you used), thus you wouldn’t be able to visualise them. 
That usually means that you have vertices that are very close (say 0.1mm) and thus it’s easy to get a large deviation (say 80degree; the report contains the deviation).  



I don't see all the errors in my solid
--------------------------------------

It's normal: as shown in the figure below, a solid is validated *hierarchically*, ie first every surface (a polygon embedded in 3D) is validated in 2D (by projecting it to a plane), then every shell is validated, and finally the interactions between the shells are analysed to verify whether the solid is valid. 
If at one stage there are errors, then the validation stops to avoid "cascading errors". So if you get the error :ref:`e203`, then fix it and re-run the validator again. 
That does mean that you might have to upload your file and get it validated several times---if that becomes too tedious we strongly suggest you to download the `code <https://github.com/tudelft3d/val3dity>`_, compile it and run it locally (it's open-source and free to use).


.. image:: _static/workflow.svg
   :width: 60%


I'm sure my 3D primitive is valid, but the validator says that something is wrong
---------------------------------------------------------------------------------

It's possible that there are bugs in `val3dity <https://github.com/tudelft3d/val3dity>`_. 
Please `report the issue <https://github.com/tudelft3d/val3dity/issues>`_ and provide the following:

  1. the JSON report (use option ``--report_json``)
  2. (a link to) the input file you used
  3. which platform you use, and whether you compiled it yourself or used the web-application



Do you validate the topological relationships between the solids?
-----------------------------------------------------------------
If these solids are part of a ``CompositeSolid`` then yes, otherwise no.
We do verify whether two ``BuildingParts`` forming a ``Building`` overlap though.

We however plan to offer in the future this for all primitives/buildings in a file, so that one can verify whether two different buildings overlap for instance.


The IDs for the shells and surfaces in the report, are they 0-based or 1-based?
-------------------------------------------------------------------------------
0-based.


Where can I get files containing ``Solids`` or ``CompositeSolid``?
--------------------------------------------------------------------------

  - `www.cityjson.org <https://www.cityjson.org/datasets/>`_ has many files
  - in the folder ``/data/`` of the `GitHub repository of val3dity <https://github.com/tudelft3d/val3dity>`_ there are many examples of files containing different primitives, and in different formats.
  - `www.indoorgml.net <http://indoorgml.net/resources/>`_ has a few files
  - `overview of cities with 3D city models <https://3d.bk.tudelft.nl/opendata/opencities/>`_


