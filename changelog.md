
# Changelog

## [Unreleased]
- validation of topological relationships between features, eg ensuring that buildings in a city do not overlap
- phasing out CityGML support

## [2.2.0] - 2020-05-13
### Added
- support for IndoorGML datasets, not just the geometries but specific validation tests for the primal-dual consistency were added
- support for GeometryTemplates in CityJSON (https://www.cityjson.org/specs/#geometry-templates)

### Changed
- completely revamped the JSON error report, it's better and clearer
- no more HTML output for the report (output of report is now with option `--report`, be careful), but you can just drag your JSON report to the HTML page (in folder `/report_browser/index.html`) or at http://geovalidation.bk.tudelft.nl/val3dity/browser/
- improved the error codes a bit: new errors for IndoorGML (7xx) + for handy faulty inputs (error 904)
- code must now be compiled against CGAL5, easier to install and compile for everyone
- CityGML support is deprecated. This is the last version that will support CityGML, I will remove it completely from v2.3+. Most errors/issues reported have to do with a faulty parser of CityGML, and not with val3dity itself. I cannot justify spending 100s of hours fixing the parser, I tried hard but this not possible anymore. If someone wants to do it then great I am willing to help them, but I will not invest time on this anymore. Just upgrade your files to CityJSON (https://www.cityjson.org/help/users/conversion/), I'll always maintain a full CityJSON parser!


## [2.1.1] - 2019-04-30
### Changed
- several small bug fixes: wrong handling of some GML namespaces is one of them
- tol_snap can't be disabled anymore: just too error-prone and means nothing. Give a super small value instead, like 1e-12


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
