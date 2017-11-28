<?xml version="1.0" encoding="UTF-8"?>
<CityModel xmlns="http://www.opengis.net/citygml/1.0"
  xmlns:app="http://www.opengis.net/citygml/appearance/1.0"
  xmlns:bldg="http://www.opengis.net/citygml/building/1.0"
  xmlns:gen="http://www.opengis.net/citygml/generics/1.0"
  xmlns:dem="http://www.opengis.net/citygml/relief/1.0"
  xmlns:gml="http://www.opengis.net/gml"
  xmlns:xAL="urn:oasis:names:tc:ciq:xsdschema:xAL:2.0"
  xmlns:xlink="http://www.w3.org/1999/xlink"
  xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
  xsi:schemaLocation="http://www.opengis.net/citygml/appearance/1.0 http://www.citygml.org/citygml/appearance/1.0/appearance.xsd http://www.opengis.net/citygml/building/1.0 http://www.citygml.org/citygml/building/1.0/building.xsd http://www.opengis.net/citygml/generics/1.0 http://www.citygml.org/citygml/generics/1.0/generics.xsd http://www.opengis.net/citygml/relief/1.0 http://www.citygml.org/citygml/relief/1.0/relief.xsd ">
  <gml:description>Exported by tridicon CityGML Exporter. GTA Geoinformatik GmbH. (URL:www.tridicon.com)</gml:description>
  <gml:name>3D Stadtmodell</gml:name>
  <gml:boundedBy>
    <gml:Envelope srsName="urn:ogc:def:crs:EPSG::28992">
      <gml:lowerCorner>79269.72 456685.421 1.673</gml:lowerCorner>
      <gml:upperCorner>80479.564 457807.545 31.235</gml:upperCorner>
    </gml:Envelope>
  </gml:boundedBy>
<cityObjectMember>
    <bldg:Building gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1">
      <gml:name>{5CC86A11-4364-4898-A75D-7156689DF1A1}</gml:name>
      <bldg:consistsOfBuildingPart>
    <bldg:BuildingPart gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_1">
      <gml:name>{5CC86A11-4364-4898-A75D-7156689DF1A1}</gml:name>
      <gen:doubleAttribute name="RelativeEavesHeight"><gen:value>12.641</gen:value></gen:doubleAttribute>
      <gen:doubleAttribute name="AbsoluteEavesHeight"><gen:value>18.558</gen:value></gen:doubleAttribute>
      <gen:doubleAttribute name="RelativeRidgeHeight"><gen:value>12.641</gen:value></gen:doubleAttribute>
      <gen:doubleAttribute name="AbsoluteRidgeHeight"><gen:value>18.558</gen:value></gen:doubleAttribute>
      <app:appearance>
        <app:Appearance>
          <app:surfaceDataMember>
            <app:X3DMaterial>
              <app:ambientIntensity>0.2</app:ambientIntensity>
              <app:diffuseColor>0.922 0.922 0.922</app:diffuseColor>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_1_1</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_1_2</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_1_3</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_1_4</app:target>
            </app:X3DMaterial>
          </app:surfaceDataMember>
          <app:surfaceDataMember>
            <app:X3DMaterial>
              <app:ambientIntensity>0.2</app:ambientIntensity>
              <app:diffuseColor>0.502 0 0</app:diffuseColor>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_1_5</app:target>
            </app:X3DMaterial>
          </app:surfaceDataMember>
          <app:surfaceDataMember>
            <app:X3DMaterial>
              <app:ambientIntensity>0.2</app:ambientIntensity>
              <app:diffuseColor>0.502 0.502 0.502</app:diffuseColor>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_1_GroundSurface</app:target>
            </app:X3DMaterial>
          </app:surfaceDataMember>
        </app:Appearance>
      </app:appearance>
      <bldg:roofType>1000</bldg:roofType>
      <bldg:lod2Solid>
        <gml:Solid>
          <gml:exterior>
            <gml:CompositeSurface>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_1_1"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_1_2"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_1_3"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_1_4"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_1_5"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_1_GroundSurface"/>
            </gml:CompositeSurface>
          </gml:exterior>
        </gml:Solid>
      </bldg:lod2Solid>
      <bldg:lod2TerrainIntersection>
        <gml:MultiCurve>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79446.767 457357.4 6.085</gml:pos>
              <gml:pos>79447.565 457354.694 6.043</gml:pos>
              <gml:pos>79448.064 457353 6.066</gml:pos>
              <gml:pos>79448.3 457352.198 5.917</gml:pos>
            </gml:LineString>
          </gml:curveMember>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79446.767 457357.4 6.085</gml:pos>
              <gml:pos>79450.258 457358.4 6.07</gml:pos>
              <gml:pos>79452.495 457359.042 6.11</gml:pos>
            </gml:LineString>
          </gml:curveMember>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79452.495 457359.042 6.11</gml:pos>
              <gml:pos>79454.019 457353.893 6.179</gml:pos>
            </gml:LineString>
          </gml:curveMember>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79448.3 457352.198 5.917</gml:pos>
              <gml:pos>79452.484 457353.438 6.151</gml:pos>
              <gml:pos>79454.019 457353.893 6.179</gml:pos>
            </gml:LineString>
          </gml:curveMember>
        </gml:MultiCurve>
      </bldg:lod2TerrainIntersection>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_1_1">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79448.3 457352.198 18.558</gml:pos>
                      <gml:pos>79446.767 457357.4 18.558</gml:pos>
                      <gml:pos>79446.767 457357.4 5.917</gml:pos>
                      <gml:pos>79448.3 457352.198 5.917</gml:pos>
                      <gml:pos>79448.3 457352.198 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_1_2">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79446.767 457357.4 18.558</gml:pos>
                      <gml:pos>79452.495 457359.042 18.558</gml:pos>
                      <gml:pos>79452.495 457359.042 5.917</gml:pos>
                      <gml:pos>79446.767 457357.4 5.917</gml:pos>
                      <gml:pos>79446.767 457357.4 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_1_3">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79452.495 457359.042 18.558</gml:pos>
                      <gml:pos>79454.019 457353.893 18.558</gml:pos>
                      <gml:pos>79454.019 457353.893 5.917</gml:pos>
                      <gml:pos>79452.495 457359.042 5.917</gml:pos>
                      <gml:pos>79452.495 457359.042 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_1_4">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79454.019 457353.893 18.558</gml:pos>
                      <gml:pos>79448.3 457352.198 18.558</gml:pos>
                      <gml:pos>79448.3 457352.198 5.917</gml:pos>
                      <gml:pos>79454.019 457353.893 5.917</gml:pos>
                      <gml:pos>79454.019 457353.893 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:RoofSurface>
          <gen:doubleAttribute name="Slope"><gen:value>90</gen:value></gen:doubleAttribute>
          <gen:doubleAttribute name="Direction"><gen:value>25.81</gen:value></gen:doubleAttribute>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_1_5">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79454.019 457353.893 18.558</gml:pos>
                      <gml:pos>79452.495 457359.042 18.558</gml:pos>
                      <gml:pos>79446.767 457357.4 18.558</gml:pos>
                      <gml:pos>79448.3 457352.198 18.558</gml:pos>
                      <gml:pos>79454.019 457353.893 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:RoofSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:GroundSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_1_GroundSurface">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79448.3 457352.198 5.917</gml:pos>
                      <gml:pos>79446.767 457357.4 5.917</gml:pos>
                      <gml:pos>79452.495 457359.042 5.917</gml:pos>
                      <gml:pos>79454.019 457353.893 5.917</gml:pos>
                      <gml:pos>79448.3 457352.198 5.917</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:GroundSurface>
      </bldg:boundedBy>
    </bldg:BuildingPart>
      </bldg:consistsOfBuildingPart>
      <bldg:consistsOfBuildingPart>
    <bldg:BuildingPart gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2">
      <gml:name>{5CC86A11-4364-4898-A75D-7156689DF1A1}</gml:name>
      <gen:doubleAttribute name="RelativeEavesHeight"><gen:value>9.787</gen:value></gen:doubleAttribute>
      <gen:doubleAttribute name="AbsoluteEavesHeight"><gen:value>15.698</gen:value></gen:doubleAttribute>
      <gen:doubleAttribute name="RelativeRidgeHeight"><gen:value>12.647</gen:value></gen:doubleAttribute>
      <gen:doubleAttribute name="AbsoluteRidgeHeight"><gen:value>18.558</gen:value></gen:doubleAttribute>
      <app:appearance>
        <app:Appearance>
          <app:surfaceDataMember>
            <app:X3DMaterial>
              <app:ambientIntensity>0.2</app:ambientIntensity>
              <app:diffuseColor>0.922 0.922 0.922</app:diffuseColor>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_1</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_2</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_3</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_4</app:target>
            </app:X3DMaterial>
          </app:surfaceDataMember>
          <app:surfaceDataMember>
            <app:X3DMaterial>
              <app:ambientIntensity>0.2</app:ambientIntensity>
              <app:diffuseColor>0.502 0 0</app:diffuseColor>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_5</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_6</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_7</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_8</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_9</app:target>
            </app:X3DMaterial>
          </app:surfaceDataMember>
          <app:surfaceDataMember>
            <app:X3DMaterial>
              <app:ambientIntensity>0.2</app:ambientIntensity>
              <app:diffuseColor>0.502 0.502 0.502</app:diffuseColor>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_GroundSurface</app:target>
            </app:X3DMaterial>
          </app:surfaceDataMember>
        </app:Appearance>
      </app:appearance>
      <bldg:roofType>1040</bldg:roofType>
      <bldg:lod2Solid>
        <gml:Solid>
          <gml:exterior>
            <gml:CompositeSurface>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_1"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_2"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_3"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_4"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_5"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_6"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_7"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_8"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_9"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_GroundSurface"/>
            </gml:CompositeSurface>
          </gml:exterior>
        </gml:Solid>
      </bldg:lod2Solid>
      <bldg:lod2TerrainIntersection>
        <gml:MultiCurve>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79437.27 457363.971 6.154</gml:pos>
              <gml:pos>79444.429 457365.862 6.214</gml:pos>
              <gml:pos>79444.476 457365.874 6.215</gml:pos>
              <gml:pos>79444.576 457365.9 6.215</gml:pos>
              <gml:pos>79450.038 457367.343 6.189</gml:pos>
            </gml:LineString>
          </gml:curveMember>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79450.038 457367.343 6.189</gml:pos>
              <gml:pos>79450.63 457365.343 6.158</gml:pos>
              <gml:pos>79451.982 457360.774 6.086</gml:pos>
              <gml:pos>79453.719 457354.907 6.165</gml:pos>
            </gml:LineString>
          </gml:curveMember>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79440.574 457351.268 5.911</gml:pos>
              <gml:pos>79446.18 457352.82 6.03</gml:pos>
              <gml:pos>79446.199 457352.825 6.03</gml:pos>
              <gml:pos>79446.209 457352.828 6.03</gml:pos>
              <gml:pos>79453.719 457354.907 6.165</gml:pos>
            </gml:LineString>
          </gml:curveMember>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79437.27 457363.971 6.154</gml:pos>
              <gml:pos>79438.547 457359.06 5.993</gml:pos>
              <gml:pos>79439.842 457354.083 5.934</gml:pos>
              <gml:pos>79440.574 457351.268 5.911</gml:pos>
            </gml:LineString>
          </gml:curveMember>
        </gml:MultiCurve>
      </bldg:lod2TerrainIntersection>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_1">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79437.27 457363.971 15.698</gml:pos>
                      <gml:pos>79450.038 457367.343 15.698</gml:pos>
                      <gml:pos>79450.038 457367.343 5.911</gml:pos>
                      <gml:pos>79437.27 457363.971 5.911</gml:pos>
                      <gml:pos>79437.27 457363.971 15.698</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_2">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79450.038 457367.343 15.698</gml:pos>
                      <gml:pos>79453.719 457354.907 15.698</gml:pos>
                      <gml:pos>79453.719 457354.907 5.911</gml:pos>
                      <gml:pos>79450.038 457367.343 5.911</gml:pos>
                      <gml:pos>79450.038 457367.343 15.698</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_3">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79453.719 457354.907 15.698</gml:pos>
                      <gml:pos>79440.574 457351.268 15.698</gml:pos>
                      <gml:pos>79440.574 457351.268 5.911</gml:pos>
                      <gml:pos>79453.719 457354.907 5.911</gml:pos>
                      <gml:pos>79453.719 457354.907 15.698</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_4">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79440.574 457351.268 15.698</gml:pos>
                      <gml:pos>79437.27 457363.971 15.698</gml:pos>
                      <gml:pos>79437.27 457363.971 5.911</gml:pos>
                      <gml:pos>79440.574 457351.268 5.911</gml:pos>
                      <gml:pos>79440.574 457351.268 15.698</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:RoofSurface>
          <gen:doubleAttribute name="Slope"><gen:value>32.919</gen:value></gen:doubleAttribute>
          <gen:doubleAttribute name="Direction"><gen:value>344.504</gen:value></gen:doubleAttribute>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_5">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79450.038 457367.343 15.698</gml:pos>
                      <gml:pos>79437.27 457363.971 15.698</gml:pos>
                      <gml:pos>79439.337 457362.454 18.558</gml:pos>
                      <gml:pos>79448.222 457365.086 18.558</gml:pos>
                      <gml:pos>79450.038 457367.343 15.698</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:RoofSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:RoofSurface>
          <gen:doubleAttribute name="Slope"><gen:value>39.782</gen:value></gen:doubleAttribute>
          <gen:doubleAttribute name="Direction"><gen:value>73.509</gen:value></gen:doubleAttribute>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_6">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79453.719 457354.907 15.698</gml:pos>
                      <gml:pos>79450.038 457367.343 15.698</gml:pos>
                      <gml:pos>79448.222 457365.086 18.558</gml:pos>
                      <gml:pos>79450.833 457356.266 18.558</gml:pos>
                      <gml:pos>79453.719 457354.907 15.698</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:RoofSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:RoofSurface>
          <gen:doubleAttribute name="Slope"><gen:value>34.974</gen:value></gen:doubleAttribute>
          <gen:doubleAttribute name="Direction"><gen:value>164.122</gen:value></gen:doubleAttribute>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_7">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79440.574 457351.268 15.698</gml:pos>
                      <gml:pos>79453.719 457354.907 15.698</gml:pos>
                      <gml:pos>79450.833 457356.266 18.558</gml:pos>
                      <gml:pos>79441.652 457353.555 18.558</gml:pos>
                      <gml:pos>79440.574 457351.268 15.698</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:RoofSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:RoofSurface>
          <gen:doubleAttribute name="Slope"><gen:value>29.508</gen:value></gen:doubleAttribute>
          <gen:doubleAttribute name="Direction"><gen:value>255.421</gen:value></gen:doubleAttribute>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_8">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79437.27 457363.971 15.698</gml:pos>
                      <gml:pos>79440.574 457351.268 15.698</gml:pos>
                      <gml:pos>79441.652 457353.555 18.558</gml:pos>
                      <gml:pos>79439.337 457362.454 18.558</gml:pos>
                      <gml:pos>79437.27 457363.971 15.698</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:RoofSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:RoofSurface>
          <gen:doubleAttribute name="Slope"><gen:value>90</gen:value></gen:doubleAttribute>
          <gen:doubleAttribute name="Direction"><gen:value>0</gen:value></gen:doubleAttribute>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_9">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79450.833 457356.266 18.558</gml:pos>
                      <gml:pos>79448.222 457365.086 18.558</gml:pos>
                      <gml:pos>79439.337 457362.454 18.558</gml:pos>
                      <gml:pos>79441.652 457353.555 18.558</gml:pos>
                      <gml:pos>79450.833 457356.266 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:RoofSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:GroundSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_2_GroundSurface">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79437.27 457363.971 5.911</gml:pos>
                      <gml:pos>79450.038 457367.343 5.911</gml:pos>
                      <gml:pos>79453.719 457354.907 5.911</gml:pos>
                      <gml:pos>79440.574 457351.268 5.911</gml:pos>
                      <gml:pos>79437.27 457363.971 5.911</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:GroundSurface>
      </bldg:boundedBy>
    </bldg:BuildingPart>
      </bldg:consistsOfBuildingPart>
      <bldg:consistsOfBuildingPart>
    <bldg:BuildingPart gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_3">
      <gml:name>{5CC86A11-4364-4898-A75D-7156689DF1A1}</gml:name>
      <gen:doubleAttribute name="RelativeEavesHeight"><gen:value>8.601</gen:value></gen:doubleAttribute>
      <gen:doubleAttribute name="AbsoluteEavesHeight"><gen:value>14.69</gen:value></gen:doubleAttribute>
      <gen:doubleAttribute name="RelativeRidgeHeight"><gen:value>8.601</gen:value></gen:doubleAttribute>
      <gen:doubleAttribute name="AbsoluteRidgeHeight"><gen:value>14.69</gen:value></gen:doubleAttribute>
      <app:appearance>
        <app:Appearance>
          <app:surfaceDataMember>
            <app:X3DMaterial>
              <app:ambientIntensity>0.2</app:ambientIntensity>
              <app:diffuseColor>0.922 0.922 0.922</app:diffuseColor>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_3_1</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_3_2</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_3_3</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_3_4</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_3_5</app:target>
            </app:X3DMaterial>
          </app:surfaceDataMember>
          <app:surfaceDataMember>
            <app:X3DMaterial>
              <app:ambientIntensity>0.2</app:ambientIntensity>
              <app:diffuseColor>0.502 0 0</app:diffuseColor>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_3_6</app:target>
            </app:X3DMaterial>
          </app:surfaceDataMember>
          <app:surfaceDataMember>
            <app:X3DMaterial>
              <app:ambientIntensity>0.2</app:ambientIntensity>
              <app:diffuseColor>0.502 0.502 0.502</app:diffuseColor>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_3_GroundSurface</app:target>
            </app:X3DMaterial>
          </app:surfaceDataMember>
        </app:Appearance>
      </app:appearance>
      <bldg:roofType>1000</bldg:roofType>
      <bldg:lod2Solid>
        <gml:Solid>
          <gml:exterior>
            <gml:CompositeSurface>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_3_1"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_3_2"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_3_3"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_3_4"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_3_5"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_3_6"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_3_GroundSurface"/>
            </gml:CompositeSurface>
          </gml:exterior>
        </gml:Solid>
      </bldg:lod2Solid>
      <bldg:lod2TerrainIntersection>
        <gml:MultiCurve>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79450.038 457367.343 6.189</gml:pos>
              <gml:pos>79451.126 457367.63 6.184</gml:pos>
            </gml:LineString>
          </gml:curveMember>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79451.126 457367.63 6.184</gml:pos>
              <gml:pos>79452.94 457366.475 6.153</gml:pos>
            </gml:LineString>
          </gml:curveMember>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79452.94 457366.475 6.153</gml:pos>
              <gml:pos>79453.323 457365.094 6.132</gml:pos>
              <gml:pos>79453.82 457363.303 6.104</gml:pos>
              <gml:pos>79453.919 457362.946 6.109</gml:pos>
            </gml:LineString>
          </gml:curveMember>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79452.055 457360.528 6.09</gml:pos>
              <gml:pos>79453.919 457362.946 6.109</gml:pos>
            </gml:LineString>
          </gml:curveMember>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79450.038 457367.343 6.189</gml:pos>
              <gml:pos>79450.63 457365.343 6.158</gml:pos>
              <gml:pos>79451.982 457360.774 6.086</gml:pos>
              <gml:pos>79452.055 457360.528 6.09</gml:pos>
            </gml:LineString>
          </gml:curveMember>
        </gml:MultiCurve>
      </bldg:lod2TerrainIntersection>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_3_1">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79450.038 457367.343 14.69</gml:pos>
                      <gml:pos>79451.126 457367.63 14.69</gml:pos>
                      <gml:pos>79451.126 457367.63 6.09</gml:pos>
                      <gml:pos>79450.038 457367.343 6.09</gml:pos>
                      <gml:pos>79450.038 457367.343 14.69</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_3_2">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79451.126 457367.63 14.69</gml:pos>
                      <gml:pos>79452.94 457366.475 14.69</gml:pos>
                      <gml:pos>79452.94 457366.475 6.09</gml:pos>
                      <gml:pos>79451.126 457367.63 6.09</gml:pos>
                      <gml:pos>79451.126 457367.63 14.69</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_3_3">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79452.94 457366.475 14.69</gml:pos>
                      <gml:pos>79453.919 457362.946 14.69</gml:pos>
                      <gml:pos>79453.919 457362.946 6.09</gml:pos>
                      <gml:pos>79452.94 457366.475 6.09</gml:pos>
                      <gml:pos>79452.94 457366.475 14.69</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_3_4">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79453.919 457362.946 14.69</gml:pos>
                      <gml:pos>79452.055 457360.528 14.69</gml:pos>
                      <gml:pos>79452.055 457360.528 6.09</gml:pos>
                      <gml:pos>79453.919 457362.946 6.09</gml:pos>
                      <gml:pos>79453.919 457362.946 14.69</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_3_5">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79452.055 457360.528 14.69</gml:pos>
                      <gml:pos>79450.038 457367.343 14.69</gml:pos>
                      <gml:pos>79450.038 457367.343 6.09</gml:pos>
                      <gml:pos>79452.055 457360.528 6.09</gml:pos>
                      <gml:pos>79452.055 457360.528 14.69</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:RoofSurface>
          <gen:doubleAttribute name="Slope"><gen:value>90</gen:value></gen:doubleAttribute>
          <gen:doubleAttribute name="Direction"><gen:value>0</gen:value></gen:doubleAttribute>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_3_6">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79452.055 457360.528 14.69</gml:pos>
                      <gml:pos>79453.919 457362.946 14.69</gml:pos>
                      <gml:pos>79452.94 457366.475 14.69</gml:pos>
                      <gml:pos>79451.126 457367.63 14.69</gml:pos>
                      <gml:pos>79450.038 457367.343 14.69</gml:pos>
                      <gml:pos>79452.055 457360.528 14.69</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:RoofSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:GroundSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_3_GroundSurface">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79450.038 457367.343 6.09</gml:pos>
                      <gml:pos>79451.126 457367.63 6.09</gml:pos>
                      <gml:pos>79452.94 457366.475 6.09</gml:pos>
                      <gml:pos>79453.919 457362.946 6.09</gml:pos>
                      <gml:pos>79452.055 457360.528 6.09</gml:pos>
                      <gml:pos>79450.038 457367.343 6.09</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:GroundSurface>
      </bldg:boundedBy>
    </bldg:BuildingPart>
      </bldg:consistsOfBuildingPart>
      <bldg:consistsOfBuildingPart>
    <bldg:BuildingPart gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_4">
      <gml:name>{5CC86A11-4364-4898-A75D-7156689DF1A1}</gml:name>
      <gen:doubleAttribute name="RelativeEavesHeight"><gen:value>8.881</gen:value></gen:doubleAttribute>
      <gen:doubleAttribute name="AbsoluteEavesHeight"><gen:value>14.998</gen:value></gen:doubleAttribute>
      <gen:doubleAttribute name="RelativeRidgeHeight"><gen:value>8.881</gen:value></gen:doubleAttribute>
      <gen:doubleAttribute name="AbsoluteRidgeHeight"><gen:value>14.998</gen:value></gen:doubleAttribute>
      <app:appearance>
        <app:Appearance>
          <app:surfaceDataMember>
            <app:X3DMaterial>
              <app:ambientIntensity>0.2</app:ambientIntensity>
              <app:diffuseColor>0.922 0.922 0.922</app:diffuseColor>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_4_1</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_4_2</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_4_3</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_4_4</app:target>
            </app:X3DMaterial>
          </app:surfaceDataMember>
          <app:surfaceDataMember>
            <app:X3DMaterial>
              <app:ambientIntensity>0.2</app:ambientIntensity>
              <app:diffuseColor>0.502 0 0</app:diffuseColor>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_4_5</app:target>
            </app:X3DMaterial>
          </app:surfaceDataMember>
          <app:surfaceDataMember>
            <app:X3DMaterial>
              <app:ambientIntensity>0.2</app:ambientIntensity>
              <app:diffuseColor>0.502 0.502 0.502</app:diffuseColor>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_4_GroundSurface</app:target>
            </app:X3DMaterial>
          </app:surfaceDataMember>
        </app:Appearance>
      </app:appearance>
      <bldg:roofType>1000</bldg:roofType>
      <bldg:lod2Solid>
        <gml:Solid>
          <gml:exterior>
            <gml:CompositeSurface>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_4_1"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_4_2"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_4_3"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_4_4"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_4_5"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_4_GroundSurface"/>
            </gml:CompositeSurface>
          </gml:exterior>
        </gml:Solid>
      </bldg:lod2Solid>
      <bldg:lod2TerrainIntersection>
        <gml:MultiCurve>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79452.653 457358.508 6.117</gml:pos>
              <gml:pos>79454.766 457359.146 6.154</gml:pos>
              <gml:pos>79455.025 457359.224 6.154</gml:pos>
            </gml:LineString>
          </gml:curveMember>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79455.025 457359.224 6.154</gml:pos>
              <gml:pos>79456.361 457354.587 6.188</gml:pos>
            </gml:LineString>
          </gml:curveMember>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79454.019 457353.893 6.179</gml:pos>
              <gml:pos>79454.553 457354.051 6.188</gml:pos>
              <gml:pos>79456.361 457354.587 6.188</gml:pos>
            </gml:LineString>
          </gml:curveMember>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79452.653 457358.508 6.117</gml:pos>
              <gml:pos>79454.019 457353.893 6.179</gml:pos>
            </gml:LineString>
          </gml:curveMember>
        </gml:MultiCurve>
      </bldg:lod2TerrainIntersection>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_4_1">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79452.653 457358.508 14.998</gml:pos>
                      <gml:pos>79455.025 457359.224 14.998</gml:pos>
                      <gml:pos>79455.025 457359.224 6.117</gml:pos>
                      <gml:pos>79452.653 457358.508 6.117</gml:pos>
                      <gml:pos>79452.653 457358.508 14.998</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_4_2">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79455.025 457359.224 14.998</gml:pos>
                      <gml:pos>79456.361 457354.587 14.998</gml:pos>
                      <gml:pos>79456.361 457354.587 6.117</gml:pos>
                      <gml:pos>79455.025 457359.224 6.117</gml:pos>
                      <gml:pos>79455.025 457359.224 14.998</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_4_3">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79456.361 457354.587 14.998</gml:pos>
                      <gml:pos>79454.019 457353.893 14.998</gml:pos>
                      <gml:pos>79454.019 457353.893 6.117</gml:pos>
                      <gml:pos>79456.361 457354.587 6.117</gml:pos>
                      <gml:pos>79456.361 457354.587 14.998</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_4_4">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79454.019 457353.893 14.998</gml:pos>
                      <gml:pos>79452.653 457358.508 14.998</gml:pos>
                      <gml:pos>79452.653 457358.508 6.117</gml:pos>
                      <gml:pos>79454.019 457353.893 6.117</gml:pos>
                      <gml:pos>79454.019 457353.893 14.998</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:RoofSurface>
          <gen:doubleAttribute name="Slope"><gen:value>90</gen:value></gen:doubleAttribute>
          <gen:doubleAttribute name="Direction"><gen:value>0</gen:value></gen:doubleAttribute>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_4_5">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79454.019 457353.893 14.998</gml:pos>
                      <gml:pos>79456.361 457354.587 14.998</gml:pos>
                      <gml:pos>79455.025 457359.224 14.998</gml:pos>
                      <gml:pos>79452.653 457358.508 14.998</gml:pos>
                      <gml:pos>79454.019 457353.893 14.998</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:RoofSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:GroundSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_4_GroundSurface">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79452.653 457358.508 6.117</gml:pos>
                      <gml:pos>79455.025 457359.224 6.117</gml:pos>
                      <gml:pos>79456.361 457354.587 6.117</gml:pos>
                      <gml:pos>79454.019 457353.893 6.117</gml:pos>
                      <gml:pos>79452.653 457358.508 6.117</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:GroundSurface>
      </bldg:boundedBy>
    </bldg:BuildingPart>
      </bldg:consistsOfBuildingPart>
      <bldg:consistsOfBuildingPart>
    <bldg:BuildingPart gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_5">
      <gml:name>{5CC86A11-4364-4898-A75D-7156689DF1A1}</gml:name>
      <gen:doubleAttribute name="RelativeEavesHeight"><gen:value>12.67</gen:value></gen:doubleAttribute>
      <gen:doubleAttribute name="AbsoluteEavesHeight"><gen:value>18.558</gen:value></gen:doubleAttribute>
      <gen:doubleAttribute name="RelativeRidgeHeight"><gen:value>12.67</gen:value></gen:doubleAttribute>
      <gen:doubleAttribute name="AbsoluteRidgeHeight"><gen:value>18.558</gen:value></gen:doubleAttribute>
      <app:appearance>
        <app:Appearance>
          <app:surfaceDataMember>
            <app:X3DMaterial>
              <app:ambientIntensity>0.2</app:ambientIntensity>
              <app:diffuseColor>0.922 0.922 0.922</app:diffuseColor>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_5_1</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_5_2</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_5_3</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_5_4</app:target>
            </app:X3DMaterial>
          </app:surfaceDataMember>
          <app:surfaceDataMember>
            <app:X3DMaterial>
              <app:ambientIntensity>0.2</app:ambientIntensity>
              <app:diffuseColor>0.502 0 0</app:diffuseColor>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_5_5</app:target>
            </app:X3DMaterial>
          </app:surfaceDataMember>
          <app:surfaceDataMember>
            <app:X3DMaterial>
              <app:ambientIntensity>0.2</app:ambientIntensity>
              <app:diffuseColor>0.502 0.502 0.502</app:diffuseColor>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_5_GroundSurface</app:target>
            </app:X3DMaterial>
          </app:surfaceDataMember>
        </app:Appearance>
      </app:appearance>
      <bldg:roofType>1000</bldg:roofType>
      <bldg:lod2Solid>
        <gml:Solid>
          <gml:exterior>
            <gml:CompositeSurface>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_5_1"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_5_2"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_5_3"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_5_4"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_5_5"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_5_GroundSurface"/>
            </gml:CompositeSurface>
          </gml:exterior>
        </gml:Solid>
      </bldg:lod2Solid>
      <bldg:lod2TerrainIntersection>
        <gml:MultiCurve>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79437.248 457354.059 5.888</gml:pos>
              <gml:pos>79438.373 457354.376 5.912</gml:pos>
              <gml:pos>79441.229 457355.18 5.978</gml:pos>
            </gml:LineString>
          </gml:curveMember>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79436.326 457357.612 5.946</gml:pos>
              <gml:pos>79436.55 457356.75 5.918</gml:pos>
              <gml:pos>79437.1 457354.63 5.893</gml:pos>
              <gml:pos>79437.248 457354.059 5.888</gml:pos>
            </gml:LineString>
          </gml:curveMember>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79436.326 457357.612 5.946</gml:pos>
              <gml:pos>79437.608 457357.975 5.958</gml:pos>
              <gml:pos>79440.304 457358.737 6.02</gml:pos>
            </gml:LineString>
          </gml:curveMember>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79440.304 457358.737 6.02</gml:pos>
              <gml:pos>79441.229 457355.18 5.978</gml:pos>
            </gml:LineString>
          </gml:curveMember>
        </gml:MultiCurve>
      </bldg:lod2TerrainIntersection>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_5_1">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79441.229 457355.18 18.558</gml:pos>
                      <gml:pos>79437.248 457354.059 18.558</gml:pos>
                      <gml:pos>79437.248 457354.059 5.888</gml:pos>
                      <gml:pos>79441.229 457355.18 5.888</gml:pos>
                      <gml:pos>79441.229 457355.18 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_5_2">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79437.248 457354.059 18.558</gml:pos>
                      <gml:pos>79436.326 457357.612 18.558</gml:pos>
                      <gml:pos>79436.326 457357.612 5.888</gml:pos>
                      <gml:pos>79437.248 457354.059 5.888</gml:pos>
                      <gml:pos>79437.248 457354.059 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_5_3">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79436.326 457357.612 18.558</gml:pos>
                      <gml:pos>79440.304 457358.737 18.558</gml:pos>
                      <gml:pos>79440.304 457358.737 5.888</gml:pos>
                      <gml:pos>79436.326 457357.612 5.888</gml:pos>
                      <gml:pos>79436.326 457357.612 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_5_4">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79440.304 457358.737 18.558</gml:pos>
                      <gml:pos>79441.229 457355.18 18.558</gml:pos>
                      <gml:pos>79441.229 457355.18 5.888</gml:pos>
                      <gml:pos>79440.304 457358.737 5.888</gml:pos>
                      <gml:pos>79440.304 457358.737 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:RoofSurface>
          <gen:doubleAttribute name="Slope"><gen:value>90</gen:value></gen:doubleAttribute>
          <gen:doubleAttribute name="Direction"><gen:value>75.441</gen:value></gen:doubleAttribute>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_5_5">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79440.304 457358.737 18.558</gml:pos>
                      <gml:pos>79436.326 457357.612 18.558</gml:pos>
                      <gml:pos>79437.248 457354.059 18.558</gml:pos>
                      <gml:pos>79441.229 457355.18 18.558</gml:pos>
                      <gml:pos>79440.304 457358.737 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:RoofSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:GroundSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_5_GroundSurface">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79441.229 457355.18 5.888</gml:pos>
                      <gml:pos>79437.248 457354.059 5.888</gml:pos>
                      <gml:pos>79436.326 457357.612 5.888</gml:pos>
                      <gml:pos>79440.304 457358.737 5.888</gml:pos>
                      <gml:pos>79441.229 457355.18 5.888</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:GroundSurface>
      </bldg:boundedBy>
    </bldg:BuildingPart>
      </bldg:consistsOfBuildingPart>
      <bldg:consistsOfBuildingPart>
    <bldg:BuildingPart gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6">
      <gml:name>{5CC86A11-4364-4898-A75D-7156689DF1A1}</gml:name>
      <gen:doubleAttribute name="RelativeEavesHeight"><gen:value>12.614</gen:value></gen:doubleAttribute>
      <gen:doubleAttribute name="AbsoluteEavesHeight"><gen:value>18.558</gen:value></gen:doubleAttribute>
      <gen:doubleAttribute name="RelativeRidgeHeight"><gen:value>17.482</gen:value></gen:doubleAttribute>
      <gen:doubleAttribute name="AbsoluteRidgeHeight"><gen:value>23.427</gen:value></gen:doubleAttribute>
      <app:appearance>
        <app:Appearance>
          <app:surfaceDataMember>
            <app:X3DMaterial>
              <app:ambientIntensity>0.2</app:ambientIntensity>
              <app:diffuseColor>0.922 0.922 0.922</app:diffuseColor>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_1</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_2</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_3</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_4</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_5</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_6</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_7</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_8</app:target>
            </app:X3DMaterial>
          </app:surfaceDataMember>
          <app:surfaceDataMember>
            <app:X3DMaterial>
              <app:ambientIntensity>0.2</app:ambientIntensity>
              <app:diffuseColor>0.502 0 0</app:diffuseColor>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_9</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_10</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_11</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_12</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_13</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_14</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_15</app:target>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_16</app:target>
            </app:X3DMaterial>
          </app:surfaceDataMember>
          <app:surfaceDataMember>
            <app:X3DMaterial>
              <app:ambientIntensity>0.2</app:ambientIntensity>
              <app:diffuseColor>0.502 0.502 0.502</app:diffuseColor>
              <app:target>#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_GroundSurface</app:target>
            </app:X3DMaterial>
          </app:surfaceDataMember>
        </app:Appearance>
      </app:appearance>
      <bldg:roofType>1070</bldg:roofType>
      <bldg:lod2Solid>
        <gml:Solid>
          <gml:exterior>
            <gml:CompositeSurface>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_1"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_2"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_3"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_4"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_5"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_6"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_7"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_8"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_9"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_10"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_11"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_12"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_13"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_14"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_15"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_16"/>
              <gml:surfaceMember xlink:href="#GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_GroundSurface"/>
            </gml:CompositeSurface>
          </gml:exterior>
        </gml:Solid>
      </bldg:lod2Solid>
      <bldg:lod2TerrainIntersection>
        <gml:MultiCurve>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79433.647 457361.437 6.004</gml:pos>
              <gml:pos>79434.397 457358.569 5.947</gml:pos>
            </gml:LineString>
          </gml:curveMember>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79433.647 457361.437 6.004</gml:pos>
              <gml:pos>79434.635 457363.178 6.116</gml:pos>
            </gml:LineString>
          </gml:curveMember>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79434.635 457363.178 6.116</gml:pos>
              <gml:pos>79434.871 457363.249 6.131</gml:pos>
              <gml:pos>79437.27 457363.971 6.154</gml:pos>
            </gml:LineString>
          </gml:curveMember>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79437.27 457363.971 6.154</gml:pos>
              <gml:pos>79439.278 457362.779 6.115</gml:pos>
            </gml:LineString>
          </gml:curveMember>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79439.278 457362.779 6.115</gml:pos>
              <gml:pos>79439.836 457360.551 6.042</gml:pos>
              <gml:pos>79439.939 457360.14 6.037</gml:pos>
            </gml:LineString>
          </gml:curveMember>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79439.158 457358.413 5.993</gml:pos>
              <gml:pos>79439.939 457360.14 6.037</gml:pos>
            </gml:LineString>
          </gml:curveMember>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79436.143 457357.555 5.944</gml:pos>
              <gml:pos>79437.605 457357.971 5.958</gml:pos>
              <gml:pos>79439.158 457358.413 5.993</gml:pos>
            </gml:LineString>
          </gml:curveMember>
          <gml:curveMember>
            <gml:LineString>
              <gml:pos>79434.397 457358.569 5.947</gml:pos>
              <gml:pos>79434.99 457358.225 5.966</gml:pos>
              <gml:pos>79436.143 457357.555 5.944</gml:pos>
            </gml:LineString>
          </gml:curveMember>
        </gml:MultiCurve>
      </bldg:lod2TerrainIntersection>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_1">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79434.397 457358.569 18.558</gml:pos>
                      <gml:pos>79433.647 457361.437 18.558</gml:pos>
                      <gml:pos>79433.647 457361.437 5.944</gml:pos>
                      <gml:pos>79434.397 457358.569 5.944</gml:pos>
                      <gml:pos>79434.397 457358.569 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_2">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79433.647 457361.437 18.558</gml:pos>
                      <gml:pos>79434.635 457363.178 18.558</gml:pos>
                      <gml:pos>79434.635 457363.178 5.944</gml:pos>
                      <gml:pos>79433.647 457361.437 5.944</gml:pos>
                      <gml:pos>79433.647 457361.437 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_3">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79434.635 457363.178 18.558</gml:pos>
                      <gml:pos>79437.27 457363.971 18.558</gml:pos>
                      <gml:pos>79437.27 457363.971 5.944</gml:pos>
                      <gml:pos>79434.635 457363.178 5.944</gml:pos>
                      <gml:pos>79434.635 457363.178 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_4">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79437.27 457363.971 18.558</gml:pos>
                      <gml:pos>79439.278 457362.779 18.558</gml:pos>
                      <gml:pos>79439.278 457362.779 5.944</gml:pos>
                      <gml:pos>79437.27 457363.971 5.944</gml:pos>
                      <gml:pos>79437.27 457363.971 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_5">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79439.278 457362.779 18.558</gml:pos>
                      <gml:pos>79439.939 457360.14 18.558</gml:pos>
                      <gml:pos>79439.939 457360.14 5.944</gml:pos>
                      <gml:pos>79439.278 457362.779 5.944</gml:pos>
                      <gml:pos>79439.278 457362.779 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_6">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79439.939 457360.14 18.558</gml:pos>
                      <gml:pos>79439.158 457358.413 18.558</gml:pos>
                      <gml:pos>79439.158 457358.413 5.944</gml:pos>
                      <gml:pos>79439.939 457360.14 5.944</gml:pos>
                      <gml:pos>79439.939 457360.14 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_7">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79439.158 457358.413 18.558</gml:pos>
                      <gml:pos>79436.143 457357.555 18.558</gml:pos>
                      <gml:pos>79436.143 457357.555 5.944</gml:pos>
                      <gml:pos>79439.158 457358.413 5.944</gml:pos>
                      <gml:pos>79439.158 457358.413 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:WallSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_8">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79436.143 457357.555 18.558</gml:pos>
                      <gml:pos>79434.397 457358.569 18.558</gml:pos>
                      <gml:pos>79434.397 457358.569 5.944</gml:pos>
                      <gml:pos>79436.143 457357.555 5.944</gml:pos>
                      <gml:pos>79436.143 457357.555 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:WallSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:RoofSurface>
          <gen:doubleAttribute name="Slope"><gen:value>30.247</gen:value></gen:doubleAttribute>
          <gen:doubleAttribute name="Direction"><gen:value>255.345</gen:value></gen:doubleAttribute>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_9">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79433.647 457361.437 18.558</gml:pos>
                      <gml:pos>79434.397 457358.569 18.558</gml:pos>
                      <gml:pos>79436.743 457360.82 23.427</gml:pos>
                      <gml:pos>79433.647 457361.437 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:RoofSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:RoofSurface>
          <gen:doubleAttribute name="Slope"><gen:value>31.616</gen:value></gen:doubleAttribute>
          <gen:doubleAttribute name="Direction"><gen:value>299.574</gen:value></gen:doubleAttribute>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_10">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79434.635 457363.178 18.558</gml:pos>
                      <gml:pos>79433.647 457361.437 18.558</gml:pos>
                      <gml:pos>79436.743 457360.82 23.427</gml:pos>
                      <gml:pos>79434.635 457363.178 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:RoofSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:RoofSurface>
          <gen:doubleAttribute name="Slope"><gen:value>30.48</gen:value></gen:doubleAttribute>
          <gen:doubleAttribute name="Direction"><gen:value>343.251</gen:value></gen:doubleAttribute>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_11">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79437.27 457363.971 18.558</gml:pos>
                      <gml:pos>79434.635 457363.178 18.558</gml:pos>
                      <gml:pos>79436.743 457360.82 23.427</gml:pos>
                      <gml:pos>79437.27 457363.971 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:RoofSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:RoofSurface>
          <gen:doubleAttribute name="Slope"><gen:value>31.456</gen:value></gen:doubleAttribute>
          <gen:doubleAttribute name="Direction"><gen:value>30.706</gen:value></gen:doubleAttribute>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_12">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79439.278 457362.779 18.558</gml:pos>
                      <gml:pos>79437.27 457363.971 18.558</gml:pos>
                      <gml:pos>79436.743 457360.82 23.427</gml:pos>
                      <gml:pos>79439.278 457362.779 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:RoofSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:RoofSurface>
          <gen:doubleAttribute name="Slope"><gen:value>31.082</gen:value></gen:doubleAttribute>
          <gen:doubleAttribute name="Direction"><gen:value>75.929</gen:value></gen:doubleAttribute>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_13">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79439.939 457360.14 18.558</gml:pos>
                      <gml:pos>79439.278 457362.779 18.558</gml:pos>
                      <gml:pos>79436.743 457360.82 23.427</gml:pos>
                      <gml:pos>79439.939 457360.14 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:RoofSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:RoofSurface>
          <gen:doubleAttribute name="Slope"><gen:value>33.252</gen:value></gen:doubleAttribute>
          <gen:doubleAttribute name="Direction"><gen:value>114.353</gen:value></gen:doubleAttribute>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_14">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79439.158 457358.413 18.558</gml:pos>
                      <gml:pos>79439.939 457360.14 18.558</gml:pos>
                      <gml:pos>79436.743 457360.82 23.427</gml:pos>
                      <gml:pos>79439.158 457358.413 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:RoofSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:RoofSurface>
          <gen:doubleAttribute name="Slope"><gen:value>31.434</gen:value></gen:doubleAttribute>
          <gen:doubleAttribute name="Direction"><gen:value>164.12</gen:value></gen:doubleAttribute>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_15">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79436.143 457357.555 18.558</gml:pos>
                      <gml:pos>79439.158 457358.413 18.558</gml:pos>
                      <gml:pos>79436.743 457360.82 23.427</gml:pos>
                      <gml:pos>79436.143 457357.555 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:RoofSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:RoofSurface>
          <gen:doubleAttribute name="Slope"><gen:value>32.688</gen:value></gen:doubleAttribute>
          <gen:doubleAttribute name="Direction"><gen:value>210.133</gen:value></gen:doubleAttribute>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_16">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79434.397 457358.569 18.558</gml:pos>
                      <gml:pos>79436.143 457357.555 18.558</gml:pos>
                      <gml:pos>79436.743 457360.82 23.427</gml:pos>
                      <gml:pos>79434.397 457358.569 18.558</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:RoofSurface>
      </bldg:boundedBy>
      <bldg:boundedBy>
        <bldg:GroundSurface>
          <bldg:lod2MultiSurface>
            <gml:MultiSurface>
              <gml:surfaceMember>
                <gml:Polygon gml:id="GUID_5CC86A11-4364-4898-A75D-7156689DF1A1_6_GroundSurface">
                  <gml:exterior>
                    <gml:LinearRing>
                      <gml:pos>79434.397 457358.569 5.944</gml:pos>
                      <gml:pos>79433.647 457361.437 5.944</gml:pos>
                      <gml:pos>79434.635 457363.178 5.944</gml:pos>
                      <gml:pos>79437.27 457363.971 5.944</gml:pos>
                      <gml:pos>79439.278 457362.779 5.944</gml:pos>
                      <gml:pos>79439.939 457360.14 5.944</gml:pos>
                      <gml:pos>79439.158 457358.413 5.944</gml:pos>
                      <gml:pos>79436.143 457357.555 5.944</gml:pos>
                      <gml:pos>79434.397 457358.569 5.944</gml:pos>
                    </gml:LinearRing>
                  </gml:exterior>
                </gml:Polygon>
              </gml:surfaceMember>
            </gml:MultiSurface>
          </bldg:lod2MultiSurface>
        </bldg:GroundSurface>
      </bldg:boundedBy>
    </bldg:BuildingPart>
      </bldg:consistsOfBuildingPart>
    </bldg:Building>
  </cityObjectMember>
</CityModel>  