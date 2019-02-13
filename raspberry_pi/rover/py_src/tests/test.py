# -*- coding: utf-8 -*-
from unittest import TestCase
import rover_module


class TestGPS(TestCase):
    def test_GPRMC(self):
        self.assertEqual(rover_module.gps_reader('$GPRMC,081836,A,3751.65,S,14507.36,E,000.0,360.0,130998,011.3,E*62'), [37.86083333333333, 145.12266666666667]) 