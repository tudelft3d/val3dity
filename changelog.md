
# Changelog

## [Unreleased]
- validation of IndoorGML features 

## [2.1.0] - 2018-02-14
### Changed
- the report is slightly changed: the CityObjects/Primitives subdivision in the report is replaced by Features having Primitives, where Features are the top-level objects, containing one or many Primitives. This is done to allow other data model to be used as input, eg IndoorGML is coming soon!
### Added
- pytest allows to specify the binary to use if not under 'build/'

## [2.0.4] - 2018-01-26
### Changed
- fixed bug where inner rings of gml:Polygon wasn't read properly when that polygon is referenced by an XLink.

## [2.0.3] - 2018-01-23
### Changed
- each surface are now triangulated with a constrained Delaunay triangulation (CDT) instead of a non-Delaunay one. That improves stability, especially when there are nearly collinear vertices in a surfaces: slivers are avoided, which means less errors 204, and less wrong errors caused by numerical stability.

## [2.0.2] - 2018-01-13 
### Changed
- fixes issue with wrong errors 104 often raised. Explanation is there: https://github.com/CGAL/cgal/issues/2733. This releases fixes it with a hack, but I think this is solid (touch wood).

## [2.0.1] - 2017-12-12 
### Changed
- fixed bug with least-square fitting that caused wrong 203 errors

## [2.0.0] - 2017-11-27 
### Added
- completely new reports: in JSON and HTML (browsable version)
- complete unit test suite (with pytest)
- support for all 3D primitives in ISO19107
- support for new formats: CityJSON, OFF

## [2.0 beta 1] - 2017-08-01 
### Added
- CompositeSolid, MultiSolid
- CityObjects in the report
- support for CityJSON
