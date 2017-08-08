===
FAQ
===

.. contents:: :local:

How should I interpret the report?
----------------------------------

.. code-block:: xml

  <val3dity>
    <inputFile>delft.gml</inputFile>
    <primitives>gml:Solid</primitives>
    <snap_tolerance>0.001</snap_tolerance>
    <planarity_d2p>0.01</planarity_d2p>
    <planarity_n>1</planarity_n>
    <totalprimitives>111</totalprimitives>
    <validprimitives>86</validprimitives>
    <invalidprimitives>25</invalidprimitives>
    <time>Fri Mar 11 09:31:01 2016 CET</time>
    <Primitive>
      <id>0</id>
      <numbershells>1</numbershells>
      <numberfaces>7</numberfaces>
      <numbervertices>10</numbervertices>
    </Primitive>
    <Primitive>
      <id>1</id>
      <numbershells>1</numbershells>
      <numberfaces>127</numberfaces>
      <numbervertices>192</numbervertices>
      <Error>
        <code>102</code>
        <type>CONSECUTIVE_POINTS_SAME</type>
        <shell>0</shell>
        <face>774f3cebd44a</face>
        <info></info>
      </Error>
    </Primitive>
    ...
    <Primitive>
      <id>5</id>
      <numbershells>1</numbershells>
      <numberfaces>15</numberfaces>
      <numbervertices>35</numbervertices>
      <Error>
        <code>203</code>
        <type>NON_PLANAR_POLYGON_DISTANCE_PLANE</type>
        <shell>0</shell>
        <face>c6e90d82</face>
        <info>distance to fitted plane: 0.0129827 (tolerance=0.01)</info>
      </Error>
    </Primitive>
    ...
    <Primitive>
      <id>68</id>
      <numbershells>1</numbershells>
      <numberfaces>9</numberfaces>
      <numbervertices>21</numbervertices>
      <Error>
        <code>302</code>
        <type>SHELL_NOT_CLOSED</type>
        <shell>0</shell>
        <face></face>
        <info>Location hole: 8.59499 11.5695 13.7672</info>
      </Error>
      <Error>
        <code>302</code>
        <type>SHELL_NOT_CLOSED</type>
        <shell>0</shell>
        <face></face>
        <info>Location hole: 10.405 8.5995 0</info>
      </Error>
    </Primitive>
    ...
  </val3dity>

The report lists all the 3D primitives with some statistics about them, and gives if invalid one or more errors for each. 

If your your file is a GML file and the primitives have ``gml:id`` (for ``gml:Solid`` and ``gml:Shell`` and ``gml:Polygon``) then these are used to report the errors, if not then the number means the order of the primitives in the file (the first one being 0). 
Some examples, referring to the example above. 
The first (ID #0) solid in the file is valid, and some of its properties are shown.
The solid with ID #1 is invalid with error 102.
The solid with ID #5 is invalid because its face ID #c6e90d82 is non-planar; if the tolerance was modified to 0.20m then it would be.
The solid with ID #68 is invalid its exterior shell (ID #0) has holes (2 of them).


I get many errors 203 and 204, but my planes look planar to me. Why is that?
----------------------------------------------------------------------------

This is a very common error, actually 203 is the most common error for `all the files so far uploaded to our web application <http://geovalidation.bk.tudelft.nl/val3dity/stats>`_.

Read carefully the explanations of the errors 203 and 204.

A surface is first check for error 203, if valid then error 204 is checked. By definition, if an error 204 is reported then all the vertices are within 1cm (tolerance you used), thus you wouldn’t be able to visualise them. 
That usually means that you have vertices that are very close (say 0.1mm) and thus it’s easy to get a large deviation (say 80degree; the report contains the deviation).  


I don't see all the errors in my solid
--------------------------------------

It's normal: as shown in the figure below, a solid is validated *hierarchically*, ie first every surface (a polygon embedded in 3D) is validated in 2D (by projecting it to a plane), then every shell is validated, and finally the interactions between the shells are analysed to verify whether the solid is valid. 
If at one stage there are errors, then the validation stops to avoid "cascading errors". So if you get the error `203 NON_PLANAR_POLYGON_DISTANCE_PLANE`, then fix it and re-run the validator again. 
That does mean that you might have to upload your file and get it validated several times---if that becomes too tedious we strongly suggest you to download the `code <https://github.com/tudelft3d/val3dity>`_, compile it and run it locally (it's open-source and free to use).


.. image:: _static/workflow.svg
   :width: 100%


I'm sure my solid is valid, but the validator says that something is wrong
--------------------------------------------------------------------------

It's possible that there are bugs in `val3dity <https://github.com/tudelft3d/val3dity>`_. 
Please `report the issue <https://github.com/tudelft3d/val3dity/issues>`_.


The validation report says that there are no solids in my file, but I can see the buildings with my viewer!
-----------------------------------------------------------------------------------------------------------

There are many (or more precisely: `too many <http://erouault.blogspot.nl/2014/04/gml-madness.html>`_) ways to model a volume/polyhedron in GML (eg a building in CityGML), but usually practitioners do it with either ``gml:Solid`` or ``gml:MultiSurface``. 
See `on this page <https://www.citygml.org/samplefiles/building/>`_ the same simple volumetric objects modelled with different primitives.

If your dataset contains volumes but these are stored as ``gml:MultiSurfaces`` (eg `the open dataset of Rotterdam <http://www.rotterdamopendata.nl/dataset/rotterdam-3d-bestanden>`_), then you could use our [CityGML Solidifier](https://github.com/tudelft3d/citygml-solidifier).


Can my GML file contain more than one ``gml:Solid`` or ``gml:MultiSurface``?
----------------------------------------------------------------------------

Yes, all the 3D primitives in the file will be validated, one by one.


Do you validate the topological relationships between the solids?
-----------------------------------------------------------------

If these solids are part of a ``gml:CompositeSolid`` yes, otherwise no.
We do verify whether 2 BuildingParts forming a Building overlap though.

We however plan to offer in the future this for all primitives/buildings in a file, so that one can verify whether 2 different buildings overlap for instance.


The IDs for the shells and surfaces in the report, are they 0-based or 1-based?
-------------------------------------------------------------------------------

0-based.


Where can I get files containing ``gml:Solids``?
------------------------------------------------

We maintain a `repository of unit tests <https://github.com/tudelft3d/CityGML-QIE-3Dvalidation>`_ (file containing one solid that has *one* error) for testing our code. 
Also, on the `official CityGML website <https://www.citygml.org/samplefiles/>`_ there are a few files with 3D buildings, and all the `known publicly available 3D cities are listed too <https://www.citygml.org/3dcities/>`_.


