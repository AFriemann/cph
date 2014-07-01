#!/bin/env python
# cph_server.py
# 2014-06-30

from sys import exit
from argparse import ArgumentParser,Action # argparse documentation: https://docs.python.org/dev/library/argparse.html

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

from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer
from subprocess import Popen,PIPE
import urlparse

class MyHandler(BaseHTTPRequestHandler):
    def do_HEAD(self):
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()

    def do_GET(self):
        self.do_HEAD()

    def BAD_INPUT(self):
        self.send_response(700)
        self.send_header("Content-type", "text/html")
        self.end_headers()

    def do_POST(self):
        length = int(self.headers['Content-Length'])
        post_data = urlparse.parse_qs(self.rfile.read(length).decode('utf-8'))
        try:
            out, err = Popen(['cph','-w',post_data['word'][0],'-s',post_data['salt'][0]], stdout=PIPE, stderr=PIPE).communicate()
            self.wfile.write(out)
        except KeyError:
            self.BAD_INPUT()

def main(namespace):
    try:
        HOST_NAME = 'CPH'
        PORT = 12123
        server = HTTPServer(('', PORT), MyHandler)

        print("serving at port " + str(PORT))
        server.serve_forever()
    except KeyboardInterrupt:
        print('^C received, shutting down server')
        server.socket.close()

if __name__ == '__main__':
    args = parser.parse_args()

    main(args)

    exit(0)

# vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4
