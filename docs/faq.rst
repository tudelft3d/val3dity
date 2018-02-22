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

There are 2 options for a report: HTML and JSON report (the HTML report is just a navigable view of the JSON report).

:ref:`report`

Outputs the validation report in a navigable HTML file that can be viewed in a web browser. 
There is a summary page with an overview, and also a page with all the details of each features present in the file. 
Some statistics (eg number of faces, IDs, etc) for each feature and primitive is also given, as a convenience.

.. image:: _static/report1.png
   :width: 49%
.. image:: _static/report2.png
   :width: 49%

   
:ref:`report_json`

Outputs a single JSON file with the information shown in the HTML page.
Use it to produce your own report or extract statistics.

The top level objects are called "features", and there are at this moment 2 kinds of features: CityObjects (for CityGML objects, like Building or Bridge) and GenericObject (when the features are not known, eg for an OBJ file).
Each feature contains a list of 3D primitives.
The errors are reported as children of either a 3D primitive (errors 1xx to 5xx)  or a feature (errors 6xx).
The errors 9xx are reported in the ``"errors_dataset"``.
All the features and primitives contain an entry ``"validity"`` state whether it is valid or not.



I get many errors 203 and 204, but my planes look planar to me. Why is that?
----------------------------------------------------------------------------

This is a very common error, actually :ref:`error_203` is the most common error for `all the files so far uploaded to our web application <http://geovalidation.bk.tudelft.nl/val3dity/stats>`_.

Read carefully the explanations of the errors :ref:`error_203` and :ref:`error_204`.

A surface is first check for error 203, if valid then error 204 is checked. 
By definition, if an error 204 is reported then all the vertices are within 1cm (tolerance you used), thus you wouldn’t be able to visualise them. 
That usually means that you have vertices that are very close (say 0.1mm) and thus it’s easy to get a large deviation (say 80degree; the report contains the deviation).  



I don't see all the errors in my solid
--------------------------------------

It's normal: as shown in the figure below, a solid is validated *hierarchically*, ie first every surface (a polygon embedded in 3D) is validated in 2D (by projecting it to a plane), then every shell is validated, and finally the interactions between the shells are analysed to verify whether the solid is valid. 
If at one stage there are errors, then the validation stops to avoid "cascading errors". So if you get the error :ref:`error_203`, then fix it and re-run the validator again. 
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


The validation report says that there are no solids in my CityGML file, but I can see the buildings with my viewer!
-------------------------------------------------------------------------------------------------------------------

There are many (or more precisely: `too many <http://erouault.blogspot.nl/2014/04/gml-madness.html>`_) ways to model geometries in GML, and that applies for buildings in CityGML. 
See `on this page <https://www.citygml.org/samplefiles/building/>`_ the same simple volumetric objects is modelled with different primitives.

If your dataset contains only Semantic Surfaces, then use the option :ref:`option_geom_is_sem_surfaces`.


Can my GML file contain more than one ``gml:Solid`` or ``gml:MultiSurface``?
----------------------------------------------------------------------------
Yes, all the 3D primitives in the file will be validated, one by one.


The validator says my CityGML file is invalid?
----------------------------------------------
You can verify this by validating it against the CityGML schemas (this [online validator](http://geovalidation.bk.tudelft.nl/schemacitygml/) can be used).


Do you validate the topological relationships between the solids?
-----------------------------------------------------------------
If these solids are part of a ``gml:CompositeSolid`` then yes, otherwise no.
We do verify whether two ``BuildingParts`` forming a ``Building`` overlap though.

We however plan to offer in the future this for all primitives/buildings in a file, so that one can verify whether two different buildings overlap for instance.


The IDs for the shells and surfaces in the report, are they 0-based or 1-based?
-------------------------------------------------------------------------------
0-based.


Where can I get files containing ``gml:Solids`` or ``gml:CompositeSolid``?
--------------------------------------------------------------------------
In the folder ``/data/`` of the `GitHub repository of val3dity <https://github.com/tudelft3d/val3dity>`_ there are many examples of files containing different primitives, and in different formats.
Also, on the `official CityGML website <https://www.citygml.org/samplefiles/>`_ there are a few files with 3D buildings, and all the `known publicly available 3D cities are listed too <https://www.citygml.org/3dcities/>`_.


