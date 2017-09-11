# Geometry errors

The intention is to isolate the geometry from the file format. The POLY format is simple, supports inner rings and the parser is reliable. Therefore each geometry [error case](http://val3dity.readthedocs.io/en/v2/errors/#) is tested with the POLY format *only*. Don't replicate these geometry error cases in different file formats, because test maintenance will become very error prone (ie update one file but forget the other...).

## [101 – TOO_FEW_POINTS](http://val3dity.readthedocs.io/en/v2/errors/#too-few-points)

- [ ] polygon with 1 point
- [ ] polygon with 2 points
- [ ] polygon with 3 points

## 102

## 104

## 105

## 201

## 202

## 203

## 204

## 205

## 206

## 207

## 208

## 301

## 302

## 303

## 304

## 305

## 306

## 307

## 309

## 401

## 402

## 403

## 404

## 405

## 501

## 502

## 503

# File formats

Here each file contains the same, valid geometry. Thus the various formatting options and errors are tested.

## 901

# Valid data

Valid files in each format. One should be enough per format.

# Empty files

Try to break val3dity by giving it (partially) empty files in each format.

## 902

# Format specific geometry errors

Error cases that are only relevant for a particular format and cannot be modelled by each format, thus don't belong to *Geometry errors* (eg 601).

## 103

## 601

# User input

Testing command-line user input.

## 903