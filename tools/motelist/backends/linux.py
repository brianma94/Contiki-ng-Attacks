# Copyright (c) 2013, Janis Judvaitis
# Copyright (c) 2018, University of Bristol <www.bristol.ac.uk>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#  * Redistributions of source code must retain the above copyright notice,
#    this list of  conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# Authors:
#   Janis Judvaitis
#   Atis Elsts <atis.elsts@bristol.ac.uk>
#   George Oikonomou <g.oikonomou@bristol.ac.uk>
import os
import glob
import backends.backend


class LinuxDevice(object):
    attr_file_map = {
        'vid': 'idVendor',
        'pid': 'idProduct',
        'product': 'product',
        'vendor': 'manufacturer',
        'serial': 'serial'
    }

    def __init__(self, port, motelist):
        self.__port = port
        self.__base = os.path.basename(port)
        self.__motelist = motelist
        self.__sys_path = self.find_sys_path(self.__base)

    def create(self):
        mote = self.__motelist.create_mote()
        mote.port = self.__port

        for attr, file in self.attr_file_map.items():
            value = self.__read_line(os.path.join(self.__sys_path, file))
            try:
                setattr(mote, attr, '0x%04X' % (int(value, 16),))
            except ValueError:
                setattr(mote, attr, value)

    @classmethod
    def __read_line(cls, filename):
        line = "Unknown"
        try:
            with open(filename) as f:
                line = f.readline().strip()
        finally:
            return line


class USBSerialDevice(LinuxDevice):
    @staticmethod
    def find_sys_path(base):
        sys_dev_path = '/sys/class/tty/{}/device/driver/{}'.format(base, base)
        return os.path.dirname(os.path.dirname(os.path.realpath(sys_dev_path)))


class CDCACMDevice(LinuxDevice):
    @staticmethod
    def find_sys_path(base):
        sys_dev_path = '/sys/class/tty/{}/device'.format(base)
        return os.path.dirname(os.path.realpath(sys_dev_path))


class LinuxBackend(backends.backend.Backend):
    os = 'linux'

    port_patterns = {
        '/dev/ttyUSB': USBSerialDevice,
        '/dev/ttyACM': CDCACMDevice,
    }

    def run(self):
        ports = []

        for p in self.port_patterns:
            ports.extend(sorted(glob.glob(p + '*')))

        for port in ports:
            for pattern, device_class in self.port_patterns.items():
                if port.startswith(pattern):
                    device_class(port, self.motelist).create()
