import unittest
import os
import sys
import glob
import subprocess
from lxml import etree

VAL3DITYEXE = '../val3dity'
SOLIDFOLDER = '../data/poly/'


class Test_RingErrors(unittest.TestCase):
    def test_101(self):
        self.assertIn('101', validate('toofewpts'))
    def test_102(self):
        self.assertIn('102', validate('duplicates'))
    def test_104(self):
        self.assertIn('104', validate('cube18'))
        self.assertIn('104', validate('cube23'))
    def test_105(self):
        self.assertIn('105', validate('cube17'))


class Test_PolygonErrors(unittest.TestCase):
    def test_201(self):
        self.assertIn('201', validate('cube31'))
    def test_202(self):
        self.assertIn('202', validate('cube30'))
    def test_205(self):
        self.assertIn('205', validate('cube32'))
    def test_206(self):
        self.assertIn('206', validate('cube2'))
    def test_207(self):
        self.assertIn('207', validate('cube33'))
    def test_208(self):
        self.assertIn('208', validate('cube19'))


class Test_ShellErrors(unittest.TestCase):
    def test_301(self):
        self.assertIn('301', validate('toofewpolys'))
        self.assertIn('301', validate('cube20'))
    def test_302(self):
        self.assertIn('302', validate('cube10'))
        self.assertIn('302', validate('cube3'))
    def test_303(self):
        self.assertIn('303', validate('cube12'))
        self.assertIn('303', validate('cube15'))
        self.assertIn('303', validate('cube29'))
    def test_304(self):
        self.assertIn('304', validate('cube8'))
        self.assertIn('304', validate('cube11'))
    def test_305(self):
        self.assertIn('305', validate('cube16'))
        self.assertIn('305', validate('cube21'))
    def test_306(self):
        self.assertIn('306', validate('house2'))
        self.assertIn('306', validate('house3'))
        self.assertIn('306', validate('cube4'))
        self.assertIn('306', validate('torus2'))
    def test_307(self):
        self.assertIn('307', validate('cube9'))
    def test_308(self):
        self.assertIn('308', validate('cube14'))
        self.assertIn('308', validate('cube14r'))

class Test_ValidSolids(unittest.TestCase):
    def test_no_rings(self):
        self.assertIs(len(validate('cube')), 0)
        self.assertIs(len(validate('cube14r2')), 0)
        self.assertIs(len(validate('cube22')), 0)
        self.assertIs(len(validate('cube25')), 0)
        self.assertIs(len(validate('cube26')), 0)
        self.assertIs(len(validate('cube27')), 0)
        self.assertIs(len(validate('m41')), 0)
        self.assertIs(len(validate('concave')), 0)
        self.assertIs(len(validate('house')), 0)
        # self.assertIs(len(validate('bunny_repaired')), 0)
    def test_rings(self):
        self.assertIs(len(validate('cube5')), 0)
        self.assertIs(len(validate('cube6')), 0)
        self.assertIs(len(validate('cube13')), 0)
        self.assertIs(len(validate('torus')), 0)


class Test_TolerancePlanarity_d2p(unittest.TestCase):
    def test_1dm(self):
        self.assertNotIn('203', validate('p1e-1', 1e-1))
        self.assertNotIn('203', validate('p1e-2', 1e-1))
        self.assertNotIn('203', validate('p1e-3', 1e-1))
        self.assertNotIn('203', validate('p1e-4', 1e-1))
    def test_1cm(self):
        self.assertIn('203', validate('p1e-1', 1e-2))
        self.assertNotIn('203', validate('p1e-2', 1e-2))
        self.assertNotIn('203', validate('p1e-3', 1e-2))
        self.assertNotIn('203', validate('p1e-4', 1e-2))
    def test_1mm(self):
        self.assertIn('203', validate('p1e-1', 1e-3))
        self.assertIn('203', validate('p1e-2', 1e-3))
        self.assertNotIn('203', validate('p1e-3', 1e-3))
        self.assertNotIn('203', validate('p1e-4', 1e-3))


class Test_TolerancePlanarity_normals(unittest.TestCase):
    def test(self):
        self.assertIn('204', validate('pfold1', 1e-3))
        self.assertIn('204', validate('pfold2', 1e-3))
        # self.assertIn('204', validate('pfold2', 1e-1))


def validate(file, planartol=0.01):
    str1 = VAL3DITYEXE + " -xml -planarity_d2p " + str(planartol) + " " + SOLIDFOLDER + file +'.poly'
    # print str1
    op = subprocess.Popen(str1.split(' '), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    R = op.poll()
    if R:
        res = op.communicate()
        raise ValueError(res[1])
    re =  op.communicate()[0]
    output = []
    if (re != ''):
        parser = etree.XMLParser(remove_blank_text=True)
        root = etree.XML("<report>" + re + "</report>", parser)
        codes = []
        # msg = []
        for each in root.findall(".//errorCode"):
            if output.count(each.text) == 0:
                output.append(each.text)
    return output

if __name__ == '__main__':
    unittest.main()