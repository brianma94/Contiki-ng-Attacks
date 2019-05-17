#!/usr/bin/env python

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
import sys
import backends.backend
import argparse
import collections
import subprocess


class Motelist(object):
    defaults = {
        'omit_header': False,
        'csv_out': False,
        'brief': False,
    }

    version_string = '0.1-beta'

    def __init__(self, omit_header=defaults['omit_header'],
                 csv_out=defaults['csv_out'],
                 brief=defaults['brief']):
        self.__omit_header = omit_header
        self.__csv_out = csv_out
        self.__brief = brief
        self.__motes = []
        self.__backend = backends.backend.Backend.detect(self)

        try:
            self.__backend.run()
        except AttributeError:
            raise

    def create_mote(self):
        mote = Mote()
        self.__motes.append(mote)
        return mote

    def __str__(self):
        if len(self.__motes) == 0:
            return 'No motes detected'

        # Map output column headings to class Mote attribute names. Allows
        # us to easily change column text later, or re-order cols.
        if self.__brief:
            cols = collections.OrderedDict([
                ('Port', 'port'),
            ])
        else:
            cols = collections.OrderedDict([
                ('Port', 'port'),
                ('Serial', 'serial'),
                ('VID', 'vid'),
                ('PID', 'pid'),
                ('Product', 'product'),
                ('Vendor', 'vendor'),
            ])

        s = ''

        if self.__csv_out:
            if not self.__omit_header:
                s += ';'.join(heading for heading in cols.keys()) + '\n'

            for mote in self.__motes:
                s += ';'.join(getattr(mote, attr)
                              for attr in cols.values()) + '\n'
        else:
            # Prepare table column width
            lengths = dict(
                [(heading, len(heading)) for heading in cols.keys()]
            )

            for mote in self.__motes:
                for c, a in cols.items():
                    lengths[c] = max(lengths[c], len(getattr(mote, a)))

            # Create the string format on the fly. Easy way to handle brief out
            string_fmt = '{}  '.join('' for col in cols.keys()) + '{}\n'

            if not self.__omit_header:
                s = string_fmt.format(*[c.ljust(lengths[c]) for c in cols.keys()])
                s += string_fmt.format(*[''.ljust(lengths[c], '-') for c in cols.keys()])

            for mote in self.__motes:
                s+= string_fmt.format(*[getattr(mote, a).ljust(lengths[c]) for c, a in cols.items()])

        # Remove the trailing newline
        return s[:-1]


class Mote(object):
    def __init__(self):
        self.port = "n/a"
        self.vid = "n/a"
        self.pid = "n/a"
        self.product = "n/a"
        self.vendor = "n/a"
        self.serial = "n/a"


def print_version():
    git_describe_cmd = ['git', 'describe', '--tags', '--always']
    try:
        # In 2.7 check_output returns string, in 3+ it returns bytes.
        # This should be portable.
        version = subprocess.check_output(git_describe_cmd).decode('utf-8')
    except (IOError, OSError, subprocess.CalledProcessError):
        version = Motelist.version_string
    return version


if __name__ == '__main__':
    parser = argparse.ArgumentParser(add_help=False,
                                     description='Automatically detect and '
                                                 'print out a list of motes '
                                                 'connected to this computer')
    parser.add_argument('-c', '--csv', action='store_true',
                        default=Motelist.defaults['csv_out'],
                        help = 'Print list in CSV format')
    parser.add_argument('-o', '--omit-header', action='store_true',
                        default=Motelist.defaults['omit_header'],
                        help='Omit header row')
    parser.add_argument('-b', '--brief', action='store_true',
                        default=Motelist.defaults['brief'],
                        help='Only print serial port paths')
    parser.add_argument('-h', '--help', action='help',
                        help='Show this message and exit')
    parser.add_argument('-v', '--version', action='version',
                        version='%(prog)s ' + print_version(),
                        help='Prints software version')

    args = parser.parse_args()

    print(str(Motelist(omit_header=args.omit_header,
                       csv_out=args.csv,
                       brief=args.brief)))
