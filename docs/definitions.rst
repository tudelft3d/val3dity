===========
Definitions
===========

The international standard `ISO19107 <http://www.iso.org/iso/catalogue_detail.htm?csnumber=26012>`_ provides definitions for the 3D primitives as used in GIS applications and the "geo-world".
Because the aim is to represent *all* the possible real-world features, the 3D primitives are more complex than that in other fields (where often-times a volumetric object is restricted to be a 2-manifold, and where inner rings in surfaces are disallowed), or that of 3D objects in several commercial 3D GIS packages (where the 3D primitives are simply not defined and where inner boundaries in surfaces and solids are disallowed).


ISO19107 primitives
-------------------

The 3D primitives as defined in ISO19107 are a generalisation to 3D of the 2D ones and are as follows:

.. image:: _static/isoprimitives.svg
   :width: 70%

A 0D primitive is a ``GM_Point``, a 1D a ``GM_Curve``, a 2D a ``GM_Surface``, and a 3D a ``GM_Solid``.
A *d*-dimensional primitive is built with a set of (*d*-1)-dimensional primitives, eg a ``GM_Solid`` is formed by several ``GM_Surfaces``, which are formed of several ``GM_Curves``, which are themselves formed of ``GM_Point``.

.. note::
  While the ISO19107 primitives do not need to be linear or planar (eg curves defined by mathematical functions are allowed), val3dity uses the following restrictions (which are the same as the `international standard CityGML <https://www.citygml.org>`_ and most (all perhaps?) 3D GIS):
    
    1. ``GM_Curves`` can only be *linear*; 
    2. ``GM_Surfaces`` can only be *planar*.


Aggregates & composites
-----------------------

Primitives can be combined into either *aggregates* or *composites*.

An aggregate is an arbitrary collection of primitives of the same dimensionality that is simply used to bundle together geometries.
GML (and CityGML) has classes for each dimensionality (``Multi*``).
An aggregate does not prescribe any topological relationships between the primitives, it is simply a list of primitives (ie they can overlap or be disconnected).

A composite of dimension *d* is a collection of *d*-dimensional primitives that form a *d*-manifold, which is a topological space that is locally like a *d*-dimensional Euclidean space (:math:\mathbb{R}^d`). 
The most relevant example in a GIS context is a ``CompositeSurface``: it is a 2-manifold, or, in other words, a surface embedded in :math:\mathbb{R}^d`.
An obvious example is the surface of the Earth, for which near to every point the surrounding area is topologically equivalent to a plane. 


Overview of 3D primitives handled
---------------------------------

.. image:: _static/geomprimitives.svg
   :width: 70%




``MultiSurface``
----------------


``CompositeSurface`` 
--------------------

This implies that the surfaces part of a composite are not allowed to overlap and/or to be disjoint.
Furthermore, if we store a ``CompositeSurface`` in a data structure, each edge is guaranteed to have a maximum of two incident surfaces, and around each vertex the incident faces form one umbrella.


``Solid``
---------

``MultiSolid``
--------------

``CompositeSolid``
------------------
   








