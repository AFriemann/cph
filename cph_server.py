#!/bin/env python
# cph_server.py
# 2014-06-30

from sys import exit
from argparse import ArgumentParser,Action # argparse documentation: https://docs.python.org/dev/library/argparse.html
import SimpleHTTPServer
import SocketServer

# class executableClass(Action):
#     def __call__(self, parser, namespace, values, option_string=None):
#         return None

parser = ArgumentParser(
    prog=__file__,
    description='',
    usage='%(prog)s [options] search_term')

# parser.add_argument(
#     '--do-nothing',
#     nargs=0,
#     action=executableClass,
#     help='')
#
# parser.add_argument(
#     '-c', '--categories',
#     nargs='+',
#     metavar='',
#     choices=['ABC','DEF'],
#     help='')
#
# parser.add_argument(
#     '-p','--pages',
#     default=0,
#     type=int,
#     help='')
#
# parser.add_argument(
#     '--count',
#     action='store_true',
#     help='')
#
# parser.add_argument(
#     'useless_things',
#     nargs='+',
#     help='')

if __name__ == '__main__':
    args = parser.parse_args()

    PORT = 12123

    Handler = SimpleHTTPServer.SimpleHTTPRequestHandler

    httpd = SocketServer.TCPServer(("", PORT), Handler)

    print("serving at port" + str(PORT))
    httpd.serve_forever()

    exit(0)

# vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4
