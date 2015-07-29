#!/usr/bin/env python

import sys, re

stack = []

if len(sys.argv) == 3:
    input = open(sys.argv[1], 'r')
    output = open(sys.argv[2], 'w')
else:
    input = sys.stdin
    output = sys.stdout

for line in input.readlines():
    grp = re.search('.*TVDB_PROPERTY\((.*)\)', line)
    if grp and '#define' not in line:
        property = grp.group(1).split(' ')

        data = {}
        data['type'] = ' '.join(property[:-1])
        data['name'] = property[-1:][0]
        data['getter'] = data['name']
        data['setter'] = "set" + data['name'][0:1].title() + data['name'][1:]
        data['priv'] = data['name'] + '_'
        data['notify'] = data['name'] + 'Changed'
        stack.append(data)
    elif 'TVDB_PROPS' in line:
        for p in stack:
            l = '\tTVDB_PROPERTY(%s, %s, %s, %s);'
            print >>output, l % (p['type'], p['name'], p['getter'], p['setter'])
    elif 'TVDB_Q_PROPS' in line:
        for p in stack:
            l = '\tQ_PROPERTY(%s %s READ %s WRITE %s NOTIFY %s);'
            print >>output, l % (p['type'], p['name'], p['getter'], p['setter'], p['notify'])
    elif 'TVDB_Q_SIGNALS' in line:
        print >>output, '    signals:'
        for p in stack:
            print >>output, '\tvoid %s();' % p['notify']
    elif 'class' in line:
        stack = []
        print >>output, line[:-1]
    else:
        print >>output, line[:-1]
