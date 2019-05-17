# Copyright (c) 2018, University of Bristol <www.bristol.ac.uk>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
# COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
# STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
# OF THE POSSIBILITY OF SUCH DAMAGE.
#
# Authors:
#   George Oikonomou <g.oikonomou@bristol.ac.uk>
import glob
import subprocess
import xml.dom.minidom as dom
import backends.backend


class OSXBackend(backends.backend.Backend):
    os = 'darwin'
    tmp_file = '/tmp/get-ports-osx.xml'

    port_patterns = [
        '/dev/tty.SLAB*',
        '/dev/tty.usbmodem*',
    ]

    search_attrs = {
        'idVendor': 'vid',
        'USB Vendor Name': 'vendor',
        'idProduct': 'pid',
        'USB Product Name': 'product',
        'USB Serial Number': 'serial'
    }

    @staticmethod
    def __get_dom_node_text(node):
        """Returns the text inside a DOM node, if one exists. None otherwise"""
        try:
            if node.firstChild.nodeType == dom.Node.TEXT_NODE:
                return node.firstChild.data
        except AttributeError:
            return None

    def __dom_node_to_mote(self, port, dom_node):
        mote = self.motelist.create_mote()
        mote.port = port
        parent = dom_node.parentNode.parentNode.parentNode.parentNode.parentNode

        # For a given DOM node, search all its children using depth=1. Collect
        # relevant info and populate the respective Mote object.
        child = parent.firstChild
        while child is not None:
            if child.nodeType == dom.Node.ELEMENT_NODE:
                if child.tagName == 'key':
                    child_text = self.__get_dom_node_text(child)
                    if child_text in self.search_attrs.keys():
                        val = self.__get_dom_node_text(
                            child.nextSibling.nextSibling)
                        try:
                            setattr(mote, self.search_attrs[child_text],
                                    '0x%04X' % (int(val),))

                        except ValueError:
                            setattr(mote, self.search_attrs[child_text], val)

            child = child.nextSibling

    @classmethod
    def __read_iokit(cls):
        ioreg_cmd = '/usr/sbin/ioreg -p IOService -k IODialinDevice -l -r -t -a'
        try:
            outfile = open(cls.tmp_file, 'w')
            subprocess.call(ioreg_cmd, shell=True, stdout=outfile)
            document = dom.parse(cls.tmp_file)
            return document
        except IOError:
            raise

    def run(self):
        ports = []

        for p in self.port_patterns:
            ports.extend(sorted(glob.glob(p)))

        if len(ports) == 0:
            return None

        # Invoke ioreg. This will give us an XML file of connected devices of a
        # specific class. We will then extract information from that XML file.
        doc = self.__read_iokit()

        # Retrieve all XML <string>. One of them will contain the device port
        string_elemenets = doc.getElementsByTagName('string')

        # Inspect all those <string> elements to see if they have a data value
        # that also exists in the list of identified ports. For those elements,
        # traverse the DOM upwards and store their grand-grand-grand-parent...
        # This will be the <dict> element that appears when a device gets
        # connected.
        for se in string_elemenets:
            port = self.__get_dom_node_text(se)
            if port in ports:
                self.__dom_node_to_mote(port, se)
                ports.remove(port)

            # Stop searching if we have found a match for all identified ports
            if len(ports) == 0:
                break
