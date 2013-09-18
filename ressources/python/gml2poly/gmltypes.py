
# val3dity - Copyright (c) 2011, Hugo Ledoux.  All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of the authors nor the
#       names of its contributors may be used to endorse or promote products
#       derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL HUGO LEDOUX BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS


from geomtools import Point, Vector
import geomtools
import StringIO
import string
from lxml import etree



class ValidationError(Exception):
    def __init__(self, no, err):
        self.no = no
        self.err = err
    def __str__(self):
        return "ValidationError #" + str(self.no) +  ": " + self.err


class Ring:
    def __init__(self, lsPts=None):
        self.cur = 0
        self.l = [] #-- list of Point
        if lsPts is not None:
            for p in lsPts:
                self.l.append(p)
    def append(self, p):
        assert(isinstance(p, Point))
        self.l.append(p)
    def __getitem__(self, index):
        return self.l[index]
    def __len__(self):
        return len(self.l)
    def reverse(self):
        self.l.reverse()
    def set_cur_i(self, index):
        self.cur = index
    def set_cur_p(self, p):
        self.cur = self.index(p)
    def index(self, p):
        assert(isinstance(p, Point))
        try:
            return self.l.index(p)
        except ValueError, err:
            return -1
    def get_cur(self):
        return self[self.cur]
    def get_next(self):
        if self.cur == (len(self) - 1):
            return self[0]
        else:
            return self[self.cur+1]
    def get_prev(self):
        if self.cur == 0:
            return self[len(self) - 1]
        else:
            return self[self.cur-1]
    def move_next(self):
        if self.cur == (len(self) - 1):
            self.cur = 0
        else:
            self.cur += 1
    def move_prev(self):
        if self.cur == 0:
            self.cur = (len(self) - 1)
        else:
            self.cur -= 1
    def get_projection_plane(self):
        normal = geomtools.get_normal_rhr(self[0], self[1], self[2])
        #-- check if the plane if vertical, and assign the projection plane
        m = 0 #-- xy plane
        n = 1
        if geomtools.cmp_doubles(normal.z, 0.0) == 0:
            if  geomtools.cmp_doubles(normal.y, 0.0) == 0:
                m = 1 #-- yz plane
                n = 2
            else:
                m = 0 #-- xz plane
                n = 2
        return m, n
    def get_a_convex_corner(self):
        m, n = self.get_projection_plane()
        candidates = []
        temp = self[0]
        #-- find lowest
        for j in range(len(self)):
            p = self[j]
            if geomtools.cmp_doubles(p[n], temp[n]) == -1:
                temp = p
        candidates.append(temp)
        #-- check if another with same bottom
        for j in range(len(self)):
            p = self[j]
            if p != temp and geomtools.cmp_doubles(p[n], temp[n]) == 0:
                candidates.append(p)
        if len(candidates) > 1:
            temp = candidates[0]
            #-- find lowest
            for p in candidates:
                if geomtools.cmp_doubles(p[m], temp[m]) == 1:
                    temp = p
            return temp
        else:
            return candidates[0]
    def get_orientation(self):
        corner = self.get_a_convex_corner()
        self.set_cur_p(corner)
        v1 = Vector()
        v2 = Vector()
        v1.set_vector(self.get_cur(), self.get_next())
        v2.set_vector(self.get_cur(), self.get_prev())
        n = v1.cross_product(v2)
        return n
    def get_a_point_inside(self):
        m, n = self.get_projection_plane()
        cc = self.get_a_convex_corner()
        self.set_cur_p(cc)
        ccprev = self.get_prev()
        ccnext = self.get_next()
        self.move_next()
        dist = 1e8
        closest = None
        while self.get_next() != ccprev:
            p = self.get_next()
            if geomtools.point_in_triangle_3D(ccprev, cc, ccnext, p, m, n) == True:
                temp = cc.distance_to_proj(p, m, n)
                if temp <= dist:
                    dist = temp
                    closest = p
            self.move_next()
        if closest is None:
            thept = geomtools.get_midpoint_of_segment(ccprev, ccnext)
        else:
            thept = geomtools.get_midpoint_of_segment(cc, closest)
        return thept
    def validate(self):
        self.validate_first_last_coords_are_same()
        self.validate_no_2_consecutive_vertices_same()
        #self.validate_flatness()
    def validate_first_last_coords_are_same(self):
        if self.l[0] != self.l[-1]:
            raise ValidationError(1, "1st and last point of a ring is not the same.")
        self.l.pop()
    def validate_no_2_consecutive_vertices_same(self):
        for i in range(len(self.l) - 1):
            if self.l[i] == self.l[i+1]:
                raise ValidationError(2, "2 vertices of a ring are at the same location. " + str(self.l[i]))
    def validate_flatness(self):
        for i in range(3, len(self.l)):
            if geomtools.orient3D(self.l[0], self.l[1], self.l[2], self.l[i]) != 0:
                raise ValidationError(4, "One ring is not a flat face.")
    def str_poly(self):
        ls = []
        ls.append(str(len(self) - 1))
        for i in range(0, len(self.l) - 1):
            ls.append(str(self.l[i].id))
        ls.append("\n")
        return " ".join(ls)



class Surface:
    def __init__(self, oring=None):
        self.oring = oring #-- outer Ring
        self.irings = [] #-- list of inner Ring(s)
    def get_gml_repr(self, ns):
        topnode = etree.Element('{%s}surfaceMember' % ns['gml'], nsmap=ns)
        polynode = etree.SubElement(topnode, '{%s}Polygon' % ns['gml'], nsmap=ns)
        temp = etree.SubElement(polynode, '{%s}exterior' % ns['gml'], nsmap=ns)
        temp.append(self.oring.get_gml_repr(ns))
        if self.get_number_inner_rings() > 0:
            temp = etree.SubElement(polynode, '{%s}interior' % ns['gml'], nsmap=ns)
            for each in self.irings:
                temp.append(each.get_gml_repr(ns))
        return topnode
    def set_outer_ring(self, ring):
        assert(isinstance(ring, Ring))
        self.oring = ring
    def append_inner_ring(self, ring):
        assert(isinstance(ring, Ring))
        self.irings.append(ring)
    def validate(self):
        #-- first validate each ring separately
        self.oring.validate()
        for i in self.irings:
            i.validate()
        #-- then validate the surface itself, orientation of the rings
        self.validate_orientation_rings()
    def validate_orientation_rings(self):
        re = True
        if len(self.irings) > 0:
            ne = self.oring.get_orientation()
            for i in self.irings:
                ni = i.get_orientation()
                if ne.dot_product(ni) > 0:
                    re = False
                    raise ValidationError(3, "Respective orientations of the rings of a gml:Polygon are not correct")
        return re
    def get_number_inner_rings(self):
        return len(self.irings)
    def str_poly(self):
        ls = []
        ls.append(str(self.get_number_inner_rings() + 1) + " ")
        ls.append(str(self.get_number_inner_rings()))
        ls.append("\n")
        ls.append(self.oring.str_poly())
        if self.get_number_inner_rings() > 0:
            for i in self.irings:
                ls.append(i.str_poly())
                pt = i.get_a_point_inside()
                ls.append("1 " + str(pt.x) + " " + str(pt.y) + " " + str(pt.z))
                ls.append("\n")
        return "".join(ls)
    def str_off(self):
        if (self.get_number_inner_rings() > 0):
            print "ERROR, cannot write inner rings to OFF file."
            return ""
        else:
            return self.oring.str_poly()

#####################################################################

class Shell:
    def __init__(self, gmlnode, gmlns):
        self.gmlns = gmlns
        self.lsNodes = self.fetch_all_unique_points_in_gml(gmlnode)
        self.s = []
        self.parse_gml_shell(gmlnode)
    def append(self, s1):
        assert(isinstance(s1, Surface))
        self.s.append(s1)
    def __getitem__(self, index):
        return self.s[index]
    def __len__(self):
        return len(self.s)

    def fetch_all_unique_points_in_gml(self, gmlnode):
        lsNodes = []
        for s in gmlnode.findall(".//{%s}surfaceMember" % self.gmlns):
            for p in s.find(".//{%s}Polygon" % self.gmlns):
                posList = gmlnode.find(".//{%s}posList" % self.gmlns)
                if posList != None:
                    coords = posList.text.split()
                    assert(len(coords) % 3 == 0)
                    for i in range(0, len(coords), 3):
                        temp = Point(coords[i], coords[i+1], coords[i+2])
                        if lsNodes.count(temp) == 0:
                            lsNodes.append(temp)
                            temp.id = len(lsNodes) - 1
                else: #-- a series of gml:pos
                    posList = gmlnode.findall(".//{%s}pos" % self.gmlns)
                    for i in posList:
                        coords = i.text.split()
                        temp = Point(coords[0], coords[1], coords[2])
                        if lsNodes.count(temp) == 0:
                            lsNodes.append(temp)
                        temp.id = len(lsNodes) - 1
        return lsNodes

    def parse_gml_shell(self, shellnode):
        for i in shellnode.findall(".//{%s}surfaceMember" % self.gmlns):
            self.s.append(self.parse_gml_surfaceMember(i))
    def parse_gml_surfaceMember(self, surfacenode):
        surf = Surface()
        polynode = surfacenode.find(".//{%s}Polygon" % self.gmlns)
        if polynode is not None:
            self.parse_gml_polygon(polynode, surf)
        else: #-- maybe a xlink was used... I don't support that yet
            print "ERROR: xlink to another surface, for surface", surface.tag
        return surf
    def parse_gml_polygon(self, poly, surf):
        extnode = poly.find(".//{%s}exterior" % self.gmlns)
        surf.set_outer_ring(self.parse_gml_polygon_ring(extnode))
        intnodes = poly.findall(".//{%s}interior" % self.gmlns)
        if len(intnodes) != 0:
            irings = []
            for i in range(len(intnodes)):
                surf.append_inner_ring(self.parse_gml_polygon_ring(intnodes[i]))
    def parse_gml_polygon_ring(self, ringnode):
        #-- 2 choices: (1) series of gml:pos; (2) one gml:posList
        posList = ringnode.find(".//{%s}posList" % self.gmlns)
        ring = Ring()
        if posList != None:
            coords = posList.text.split()
            assert(len(coords) % 3 == 0)
            for i in range(0, len(coords), 3):
                temp = Point(coords[i], coords[i+1], coords[i+2])
                j = self.lsNodes.index(temp)
                ring.append(self.lsNodes[j])
        else: #-- a series of gml:pos
            posList = ringnode.findall(".//{%s}pos" % self.gmlns)
            for i in posList:
                coords = i.text.split()
                temp = Point(coords[0], coords[1], coords[2])
                j = self.lsNodes.index(temp)
                ring.append(self.lsNodes[j])
        return ring
        
    def validate(self):
        for i in self.s:
            i.validate()
    def number_of_points(self):
        return len(self.lsNodes)
    def number_of_surfaces(self):
        return len(self.s)
    def str_poly(self):
        sOut = StringIO.StringIO()
        #sOut.write('# Created by val3d_part1.py\n# Hugo Ledoux, h.ledoux@tudelft.nl\n')
        #sOut.write('# Part 1 - node list\n')
        #sOut.write('# node count, 3 dim, no attribute, no boundary marker\n')
        sOut.write(str(self.number_of_points()) + ' 3 0 0\n')
        for i in self.lsNodes:
            sOut.write(i.str_poly() + "\n")
        #sOut.write('\n# Part 2 - facet list\n')
        #sOut.write('# facet count, no boundary marker\n')
        sOut.write(str(self.number_of_surfaces()) + " 0\n")
        for s in self.s:
            sOut.write(s.str_poly())
        #sOut.write('\n# Part 3 - hole list\n0\n')
        sOut.write('0\n0\n')
        #sOut.write('\n# Part 4 - region list\n')
        #sOut.write('0            # no region\n')
        return sOut
    def str_off(self):
        sOut = StringIO.StringIO()
        #sOut.write('# Created by val3d_part1.py\n# Hugo Ledoux, h.ledoux@tudelft.nl\n')
        #sOut.write('# Part 1 - node list\n')
        #sOut.write('# node count, 3 dim, no attribute, no boundary marker\n')
        sOut.write('OFF\n')
        sOut.write(str(self.number_of_points()) + ' ' + str(self.number_of_surfaces()) + ' 0\n')
        for i in self.lsNodes:
            sOut.write(i.str_off() + "\n")
        #sOut.write('\n# Part 2 - facet list\n')
        #sOut.write('# facet count, no boundary marker\n')
        for s in self.s:
            sOut.write(s.str_off())
        return sOut


class Solid:
    def __init__(self, lsNodes=None):
        self.oshell = None #- outer Shell
        self.ishells = [] #-- of inner Shell(s)
        self.lsNodes = lsNodes #-- of Point
        self.gmlns = None
    def gml_to_solid(self, gmlnode, gmlns):
        self.gmlns = gmlns
        self.lsNodes = self.fetch_all_unique_points_in_gml(gmlnode)
        self.parse_gml_solid(gmlnode)
    def solid_to_tetgen(self):
        sOut = StringIO.StringIO()
        sOut.write('# Created by gml2tetgen\n# Hugo Ledoux, h.ledoux@tudelft.nl\n')

        sOut.write('# Part 1 - node list\n')
        sOut.write('# node count, 3 dim, no attribute, no boundary marker\n')
        sOut.write(str(self.number_of_points()) + ' 3 0 0\n')
        for i in self.lsNodes:
            sOut.write(i.str_tetgen() + "\n")

        sOut.write('\n# Part 2 - facet list\n')
        sOut.write('# facet count, no boundary marker\n')
        sOut.write(str(self.number_of_surfaces()) + " 0\n")

        for surf in self.oshell:
            sOut.write(surf.str_tetgen())

        for ishell in self.ishells:
            for surf in ishell:
                sOut.write(surf.str_tetgen())

        sOut.write('\n# Part 3 - hole list\n')
        sOut.write(str(len(self.ishells)) + "\n")
        for ishell in self.ishells:
            sOut.write("1 " + repr(ishell.get_a_point_inside()))

        sOut.write('\n# Part 4 - region list\n')
        sOut.write('0            # no region\n')
        return sOut
    def get_gml_repr(self, ns):
        topnode = etree.Element('{%s}Solid' % ns['gml'], nsmap=ns)
        temp = etree.SubElement(topnode, '{%s}exterior' % ns['gml'], nsmap=ns)
        temp.append(self.oshell.get_gml_repr(ns))
        if len(self.ishells) > 0:
            temp = etree.SubElement(topnode, '{%s}interior' % ns['gml'], nsmap=ns)
            for each in self.ishells:
                temp.append(each.get_gml_repr(ns))
        return topnode
    def set_outer_shell(self, shell):
        assert(isinstance(shell, Shell))
        self.oshell = shell
    def append_inner_shell(self, shell):
        assert(isinstance(shell, Shell))
        self.ishells.append(shell)
    def validate(self):
        self.oshell.validate()
        for i in self.ishells:
            i.validate()
    def number_of_points(self):
        return len(self.lsNodes)
    def number_of_surfaces(self):
        total = 0
        total += len(self.oshell)
        for i in self.ishells:
            total += len(i)
        return total
    def fetch_all_unique_points_in_gml(self, solidnode):
        lsNodes = []
        for s in solidnode.findall(".//{%s}surfaceMember" % self.gmlns):
            for p in s.find(".//{%s}Polygon" % self.gmlns):
                posList = solidnode.find(".//{%s}posList" % self.gmlns)
                if posList != None:
                    coords = posList.text.split()
                    assert(len(coords) % 3 == 0)
                    for i in range(0, len(coords), 3):
                        temp = Point(coords[i], coords[i+1], coords[i+2])
                        if lsNodes.count(temp) == 0:
                            lsNodes.append(temp)
                            temp.id = len(lsNodes) - 1
                else: #-- a series of gml:pos
                    posList = solidnode.findall(".//{%s}pos" % self.gmlns)
                    for i in posList:
                        coords = i.text.split()
                        temp = Point(coords[0], coords[1], coords[2])
                        if lsNodes.count(temp) == 0:
                            lsNodes.append(temp)
                        temp.id = len(lsNodes) - 1
        return lsNodes
    def parse_gml_solid(self, solidnode):
        #-- process exterior shell
        oshell = Shell()
        self.parse_gml_shell(solidnode.find(".//{%s}exterior" % self.gmlns), oshell)
        self.set_outer_shell(oshell)
        #-- process interior shell
        for i in solidnode.findall("{%s}interior" % self.gmlns):
            s = Shell()
            self.parse_gml_shell(i, s)
            self.append_inner_shell(s)
        print "no of inner shells:", len(self.ishells)
    def parse_gml_shell(self, shellnode, shell):
        for i in shellnode.findall(".//{%s}surfaceMember" % self.gmlns):
            shell.append(self.parse_gml_surfaceMember(i))
    def parse_gml_surfaceMember(self, surfacenode):
        surf = Surface()
        polynode = surfacenode.find(".//{%s}Polygon" % self.gmlns)
        if polynode is not None:
            self.parse_gml_polygon(polynode, surf)
        else: #-- maybe a xlink was used... I don't support that yet
            print "ERROR: xlink to another surface, for surface", surface.tag
        return surf
    def parse_gml_polygon(self, poly, surf):
        extnode = poly.find(".//{%s}exterior" % self.gmlns)
        surf.set_outer_ring(self.parse_gml_polygon_ring(extnode))
        intnodes = poly.findall(".//{%s}interior" % self.gmlns)
        if len(intnodes) != 0:
            irings = []
            for i in range(len(intnodes)):
                surf.append_inner_ring(self.parse_gml_polygon_ring(intnodes[i]))
    def parse_gml_polygon_ring(self, ringnode):
        #-- 2 choices: (1) series of gml:pos; (2) one gml:posList
        posList = ringnode.find(".//{%s}posList" % self.gmlns)
        ring = Ring()
        if posList != None:
            coords = posList.text.split()
            assert(len(coords) % 3 == 0)
            for i in range(0, len(coords), 3):
                temp = Point(coords[i], coords[i+1], coords[i+2])
                j = self.lsNodes.index(temp)
                ring.append(self.lsNodes[j])
        else: #-- a series of gml:pos
            posList = ringnode.findall(".//{%s}pos" % self.gmlns)
            for i in posList:
                coords = i.text.split()
                temp = Point(coords[0], coords[1], coords[2])
                j = self.lsNodes.index(temp)
                ring.append(self.lsNodes[j])
        return ring


def max_in_list_wrt_dim(ls, dim):
    re = []
    temp = ls[0]
    for i in ls:
        if geomtools.cmp_doubles(i[dim], temp[dim]) == 1:
                temp = i
    re.append(temp)
    #-- check if another with same value
    for i in ls:
        if i != temp and geomtools.cmp_doubles(i[dim], temp[dim]) == 0:
            re.append(i)
    return re




