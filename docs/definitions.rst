===========
Definitions
===========

The international standard `ISO19107 <http://www.iso.org/iso/catalogue_detail.htm?csnumber=26012>`_ provides definitions for the 3D primitives as used in GIS applications and the "geo-world".
Because the aim is to represent *all* the possible real-world features, the 3D primitives are more complex than that in other fields (where often-times a volumetric object is restricted to be a 2-manifold, and where inner rings in surfaces are disallowed), or that of 3D objects in several commercial 3D GIS packages (where the 3D primitives are simply not defined and where inner boundaries in surfaces and solids are disallowed).

The 3D primitives as defined in ISO19107 are a generalisation to 3D of the 2D ones and are as follows:

.. image:: _static/isoprimitives.svg
   :width: 70%


.. image:: _static/geomprimitives.svg
   :width: 70%



definition of a solid is broader than that of a 2-manifold, and it permit us to represent all the real-world features.
It is basically a generalisation to 3D of a polygon, which can have interior boundaries/rings:

``MultiSurface``
----------------

``CompositeSurface`` 
--------------------

``Solid``
---------

``MultiSolid``
--------------

``CompositeSolid``
------------------
   








