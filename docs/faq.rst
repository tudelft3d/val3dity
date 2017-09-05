===
FAQ
===

.. contents:: :local:

How should I interpret the report?
----------------------------------

All reports are XML files with the following headers, it contains the information used for the validation.
The errors in the input file are listed with ``<Error>`` tags in the XML report, depending on the type of errors it will be a child of:
  - ``<val3dity>``: for errors with the input file (errors 9xx);
  - ``<Solid>`` (or other 3D primitives): for errors in a specific 3D primitives (errors 1xx --> 5xx);
  - ``<Building>``: for errors related to ``Buildings`` and ``BuildingParts`` (errors 6xx);

By default, the report lists all the primitives and/or city objects in the file, whether it contains an error or not. 
To list only the ones with errors, use the option ``--onlyinvalid``.

.. code-block:: xml

  <val3dity>
    <inputFile>delft.gml</inputFile>
    <snap_tol>0.001</snap_tol>
    <overlap_tol>-1</overlap_tol>
    <planarity_d2p_tol>0.01</planarity_d2p_tol>
    <planarity_n_tol>1</planarity_n_tol>
    <totalprimitives>0</totalprimitives>
    <validprimitives>0</validprimitives>
    <invalidprimitives>0</invalidprimitives>
    <totalcityobjects>0</totalcityobjects>
    <validcityobjects>0</validcityobjects>
    <invalidcityobjects>0</invalidcityobjects>
    <time>Tue Aug 22 14:38:17 2017 CEST</time>
    ...
  </val3dity>

CityGML and CityJSON
********************

The City Objects (``Building``, ``GenericCityObject``, ``LandUse``, etc) are listed and their primitives listed. 
In the following, the ``Building`` with ``gml:id = myhouse`` has one ``Solid`` containing one error, and a city object of type ``GenericCityObject`` has one ``CompositeSolid`` containing one error.

.. code-block:: xml

  <val3dity>
    ...
    <Building>
      <id>myhouse</id>
      <Solid>
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
      </Solid>
    </Building>
    ...
    <GenericCityObject>
      <id>something</id>
      <CompositeSolid>
        <id>elvisisalive</id>
        <numbersolids>3</numbersolids>
        <Error>
          <code>501</code>
          <type>INTERSECTION_SOLIDS</type>
          <id>1;2</id>
          <info></info>
        </Error>
      </CompositeSolid>  
    </GenericCityObject>  
  </val3dity>


GML, OBJ, OFF, and POLY
***********************

.. code-block:: xml

  <val3dity>
    ...
    <Solid>
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
    </Solid>
    ...
    <Solid>
      <id>68</id>
      <numbershells>1</numbershells>
      <numberfaces>9</numberfaces>
      <numbervertices>21</numbervertices>
    </Solid>
  </val3dity>


If your file is a GML file and the primitives have ``gml:id`` (for ``gml:Solid`` and ``gml:Shell`` and ``gml:Polygon``) then these are used to report the errors, if not then the number means the order of the primitives in the file (the first one being 0). 

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

If these solids are part of a ``gml:CompositeSolid`` then yes, otherwise no.
We do verify whether two ``BuildingParts`` forming a ``Building`` overlap though.

We however plan to offer in the future this for all primitives/buildings in a file, so that one can verify whether two different buildings overlap for instance.


The IDs for the shells and surfaces in the report, are they 0-based or 1-based?
-------------------------------------------------------------------------------

0-based.


Where can I get files containing ``gml:Solids``?
------------------------------------------------

We maintain a `repository of unit tests <https://github.com/tudelft3d/CityGML-QIE-3Dvalidation>`_ (file containing one solid that has *one* error) for testing our code. 
Also, on the `official CityGML website <https://www.citygml.org/samplefiles/>`_ there are a few files with 3D buildings, and all the `known publicly available 3D cities are listed too <https://www.citygml.org/3dcities/>`_.


