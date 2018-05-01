import os
import sys
import re


def process_tabstop_with_placeholder(s):
    matches = re.finditer(
            r"TABSTOP\((?P<id>[0-9]+),(?P<placeholder>[\w\s\&\"'<>/*+-=]*)", s)
    prev_end = 0
    news = ''
    for m in matches:
        prefix = s[prev_end:m.start()]
        prev_end = m.end() + 1
        body = '${%s:%s}' % (
                m.group('id'), m.group('placeholder'))
        news += prefix + body
    news += s[prev_end:]
    return news


def process_tabstop(s):
    matches = re.finditer(
            r"(TABSTOP|MIRROR)\((?P<id>[0-9]+)\)", s)
    prev_end = 0
    news = ''
    for m in matches:
        prefix = s[prev_end:m.start()]
        prev_end = m.end() + 1
        body = '$%s' % (m.group('id'),)
        news += prefix + body
    news += s[prev_end:]
    return news

def process_snippet(s):
    match = re.match(
            r"(SNIPPET|MACROSNIPPET|INLINESNIPPET)\(\"(?P<trigger>.+)\",(\s+)?\"(?P<file>.+)\",(\s+)?\"(?P<title>.+)\",(\s+)?\"(?P<desc>.+)\"\)", s)
    if match is None:
        return None
    return match.group('trigger'), match.group('file'), match.group('title'), match.group('desc')

def process_cpp_file(filepath, outdir):
    print('processing {}'.format(filepath), end=' ')
    if not os.path.exists(filepath):
        print('File not found!')
        return None

    lines = open(filepath).read().split('\n')
    if not os.path.exists(os.path.join(outdir, 'cpp')):
        os.mkdir(os.path.join(outdir, 'cpp'))

    outfile = None
    for line in lines:
        line = process_tabstop_with_placeholder(line)
        line = process_tabstop(line)

        if ('TESTSNIPPET' in line) or ('ENDSNIPPET' in line) or ('ENDINLINESNIPPET' in line) or ('ENDMACROSNIPPET' in line):
            if outfile is not None:
                outfile.write('endsnippet\n')
                outfile.close()
                outfile = None

        if outfile is not None:
            outfile.write(line + '\n')
        else:
            snipinfo = process_snippet(line)
            if snipinfo is None:
                continue
            trigger, fname, title, desc = snipinfo
            outfile = open(os.path.join(outdir, 'cpp', fname), "a+")
            outfile.write('snippet {trigger} "{title}{desc}"\n'.format(
                trigger=trigger, title=title.ljust(25), desc=desc))
    print('Done!')

if __name__ == '__main__':
    assert len(sys.argv) == 3
    cpp_dir = sys.argv[1]
    snippets_dir = sys.argv[2]
    for snippet in os.listdir(os.path.join(snippets_dir, 'cpp')):
        if not snippet == 'common.snippets':
            os.remove(os.path.join(snippets_dir, 'cpp', snippet))

    for cpp_file in os.listdir(cpp_dir):
        if not (cpp_file.split('.')[-1] == 'cpp' or cpp_file.split('.')[-1] == 'hpp'):
            continue
        cpp_path = os.path.join(cpp_dir, cpp_file)
        process_cpp_file(cpp_path, snippets_dir)

