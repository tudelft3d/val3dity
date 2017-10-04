<?xml version="1.0" encoding="utf-8"?>
<!-- hand-coded with <3 by the 3D Geoinformation group at the TU Delft -->
<!-- https://3d.bk.tudelft.nl -->

	<cityObjectMember>
		<bldg:Building>
			<bldg:lod2Solid>
				<!-- notice that here the volume of the building is subdivided into 2 solids, and a new surface representing the ceiling of the first flooris added (gml:id="internal-ceiling") -->
				<gml:CompositeSolid>
					<gml:solidMember>
						<gml:Solid>
							<gml:exterior>
								<gml:CompositeSurface>
									<gml:surfaceMember xlink:href="#b_ground"/>
									<gml:surfaceMember xlink:href="#b_wall_1"/>
									<gml:surfaceMember xlink:href="#b_wall_2"/>
									<gml:surfaceMember xlink:href="#b_wall_3"/>
									<gml:surfaceMember xlink:href="#b_wall_4"/>
									<gml:surfaceMember xlink:href="#internal-ceiling"/>
								</gml:CompositeSurface>
							</gml:exterior>
						</gml:Solid>
					</gml:solidMember>
					<gml:solidMember>
						<gml:Solid>
							<gml:exterior>
								<gml:CompositeSurface>
									<!-- here the internal-ceiling surface is reused, but its orientation is flipped -->
									<gml:surfaceMember>
										<gml:OrientableSurface orientation="-">
											<gml:baseSurface xlink:href="#internal-ceiling"/>
										</gml:OrientableSurface>
									</gml:surfaceMember>
									<gml:surfaceMember xlink:href="#b_roof_1"/>
									<gml:surfaceMember xlink:href="#b_roof_2"/>
									<gml:surfaceMember xlink:href="#b_roof_3"/>
									<gml:surfaceMember xlink:href="#b_roof_4"/>
								</gml:CompositeSurface>
							</gml:exterior>
						</gml:Solid>
					</gml:solidMember>					
				</gml:CompositeSolid>		
			</bldg:lod2Solid>
			<!-- the extra surface used to subdivide the volume of the building into a CompositeSolid -->
			<bldg:lod2MultiSurface>
				<gml:MultiSurface>
					<gml:surfaceMember>
						<gml:Polygon gml:id="internal-ceiling">
							<gml:exterior>
								<gml:LinearRing>
									<gml:pos>0.00 0.00 100.00</gml:pos>
									<gml:pos>100.00 0.00 100.00</gml:pos>
									<gml:pos>100.00 100.00 100.00</gml:pos>
									<gml:pos>0.00 100.00 100.00</gml:pos>
									<gml:pos>0.00 0.00 100.00</gml:pos>
								</gml:LinearRing>
							</gml:exterior>
						</gml:Polygon>
					</gml:surfaceMember>
				</gml:MultiSurface>
			</bldg:lod2MultiSurface>
			<!-- all the boundary surfaces -->
			<bldg:boundedBy>
				<bldg:GroundSurface gml:id="b_ground_sem">
					<bldg:lod2MultiSurface>
						<gml:MultiSurface>
							<gml:surfaceMember>
								<gml:Polygon gml:id="b_ground">
									<gml:exterior>
										<gml:LinearRing>
											<gml:pos>0.00 0.00 0.00</gml:pos>
											<gml:pos>0.00 100.00 0.00</gml:pos>
											<gml:pos>100.00 100.00 0.00</gml:pos>
											<gml:pos>100.00 0.00 0.00</gml:pos>
											<gml:pos>0.00 0.00 0.00</gml:pos>
										</gml:LinearRing>
									</gml:exterior>
								</gml:Polygon>
							</gml:surfaceMember>
						</gml:MultiSurface>
					</bldg:lod2MultiSurface>
				</bldg:GroundSurface>
			</bldg:boundedBy>
			<bldg:boundedBy>
				<bldg:WallSurface gml:id="b_wall_1_sem">
					<bldg:lod2MultiSurface>
						<gml:MultiSurface>						
							<gml:surfaceMember>
								<gml:Polygon gml:id="b_wall_1">
									<gml:exterior>
										<gml:LinearRing>
											<gml:pos>0.00 0.00 0.00</gml:pos>
											<gml:pos>100.00 0.00 0.00</gml:pos>
											<gml:pos>100.00 0.00 100.00</gml:pos>
											<gml:pos>0.00 0.00 100.00</gml:pos>
											<gml:pos>0.00 0.00 0.00</gml:pos>
										</gml:LinearRing>
									</gml:exterior>
								</gml:Polygon>
							</gml:surfaceMember>
						</gml:MultiSurface>
					</bldg:lod2MultiSurface>
				</bldg:WallSurface>
			</bldg:boundedBy>
			<bldg:boundedBy>
				<bldg:WallSurface gml:id="b_wall_2_sem">
					<bldg:lod2MultiSurface>
						<gml:MultiSurface>						
							<gml:surfaceMember>
								<gml:Polygon gml:id="b_wall_2">
									<gml:exterior>
										<gml:LinearRing>
											<gml:pos>100.00 0.00 0.00</gml:pos>
											<gml:pos>100.00 100.00 0.00</gml:pos>
											<gml:pos>100.00 100.00 100.00</gml:pos>
											<gml:pos>100.00 0.00 100.00</gml:pos>
											<gml:pos>100.00 0.00 0.00</gml:pos>
										</gml:LinearRing>
									</gml:exterior>
								</gml:Polygon>
							</gml:surfaceMember>
						</gml:MultiSurface>
					</bldg:lod2MultiSurface>
				</bldg:WallSurface>
			</bldg:boundedBy>
			<bldg:boundedBy>
				<bldg:WallSurface gml:id="b_wall_3_sem">
					<bldg:lod2MultiSurface>
						<gml:MultiSurface>						
							<gml:surfaceMember>
								<gml:Polygon gml:id="b_wall_3">
									<gml:exterior>
										<gml:LinearRing>
											<gml:pos>100.00 100.00 0.00</gml:pos>
											<gml:pos>0.00 100.00 0.00</gml:pos>
											<gml:pos>0.00 100.00 100.00</gml:pos>
											<gml:pos>100.00 100.00 100.00</gml:pos>
											<gml:pos>100.00 100.00 0.00</gml:pos>
										</gml:LinearRing>
									</gml:exterior>
								</gml:Polygon>
							</gml:surfaceMember>
						</gml:MultiSurface>
					</bldg:lod2MultiSurface>
				</bldg:WallSurface>
			</bldg:boundedBy>
			<bldg:boundedBy>
				<bldg:WallSurface gml:id="b_wall_4_sem">
					<bldg:lod2MultiSurface>
						<gml:MultiSurface>						
							<gml:surfaceMember>
								<gml:Polygon gml:id="b_wall_4">
									<gml:exterior>
										<gml:LinearRing>
											<gml:pos>0.00 100.00 0.00</gml:pos>
											<gml:pos>0.00 0.00 0.00</gml:pos>
											<gml:pos>0.00 0.00 100.00</gml:pos>
											<gml:pos>0.00 100.00 100.00</gml:pos>
											<gml:pos>0.00 100.00 0.00</gml:pos>
										</gml:LinearRing>
									</gml:exterior>
								</gml:Polygon>
							</gml:surfaceMember>
						</gml:MultiSurface>
					</bldg:lod2MultiSurface>
				</bldg:WallSurface>
			</bldg:boundedBy>
			<bldg:boundedBy>
				<bldg:RoofSurface gml:id="b_roof_1_sem">
					<bldg:lod2MultiSurface>
						<gml:MultiSurface>						
							<gml:surfaceMember>
								<gml:Polygon gml:id="b_roof_1">
									<gml:exterior>
										<gml:LinearRing>
											<gml:pos>0.00 0.00 100.00</gml:pos>
											<gml:pos>100.00 0.00 100.00</gml:pos>
											<gml:pos>50.00 0.00 150.00</gml:pos>
											<gml:pos>0.00 0.00 100.00</gml:pos>
										</gml:LinearRing>
									</gml:exterior>
								</gml:Polygon>
							</gml:surfaceMember>
						</gml:MultiSurface>
					</bldg:lod2MultiSurface>
				</bldg:RoofSurface>
			</bldg:boundedBy>
			<bldg:boundedBy>
				<bldg:RoofSurface gml:id="b_roof_2_sem">
					<bldg:lod2MultiSurface>
						<gml:MultiSurface>						
							<gml:surfaceMember>
								<gml:Polygon gml:id="b_roof_2">
									<gml:exterior>
										<gml:LinearRing>
											<gml:pos>100.00 100.00 100.00</gml:pos>
											<gml:pos>0.00 100.00 100.00</gml:pos>
											<gml:pos>50.00 100.00 150.00</gml:pos>
											<gml:pos>100.00 100.00 100.00</gml:pos>
										</gml:LinearRing>
									</gml:exterior>
								</gml:Polygon>
							</gml:surfaceMember>
						</gml:MultiSurface>
					</bldg:lod2MultiSurface>
				</bldg:RoofSurface>
			</bldg:boundedBy>
			<bldg:boundedBy>
				<bldg:RoofSurface gml:id="b_roof_3_sem">
					<bldg:lod2MultiSurface>
						<gml:MultiSurface>						
							<gml:surfaceMember>
								<gml:Polygon gml:id="b_roof_3">
									<gml:exterior>
										<gml:LinearRing>
											<gml:pos>100.00 0.00 100.00</gml:pos>
											<gml:pos>100.00 100.00 100.00</gml:pos>
											<gml:pos>50.00 100.00 150.00</gml:pos>
											<gml:pos>50.00 0.00 150.00</gml:pos>
											<gml:pos>100.00 0.00 100.00</gml:pos>
										</gml:LinearRing>
									</gml:exterior>
								</gml:Polygon>
							</gml:surfaceMember>
						</gml:MultiSurface>
					</bldg:lod2MultiSurface>
				</bldg:RoofSurface>
			</bldg:boundedBy>
			<bldg:boundedBy>
				<bldg:RoofSurface gml:id="b_roof_4_sem">
					<bldg:lod2MultiSurface>
						<gml:MultiSurface>						
							<gml:surfaceMember>
								<gml:Polygon gml:id="b_roof_4">
									<gml:exterior>
										<gml:LinearRing>
											<gml:pos>0.00 0.00 100.00</gml:pos>
											<gml:pos>50.00 0.00 150.00</gml:pos>
											<gml:pos>50.00 100.00 150.00</gml:pos>
											<gml:pos>0.00 100.00 100.00</gml:pos>
											<gml:pos>0.00 0.00 100.00</gml:pos>
										</gml:LinearRing>
									</gml:exterior>
								</gml:Polygon>
							</gml:surfaceMember>
						</gml:MultiSurface>
					</bldg:lod2MultiSurface>
				</bldg:RoofSurface>
			</bldg:boundedBy>
		</bldg:Building>
	</cityObjectMember>
</CityModel>
