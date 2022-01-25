#!/usr/bin/python
# -*- coding: UTF-8 -*-
import sys


def get_src_code(src_code, file_path, src_thrift):
  flag = False
  public_cnt = 0
  other_cnt = 0
  for line in open(file_path, "r"):
    if not line.find('class %sClient' % src_thrift):
      flag = True
    if flag:
      if line.find('public:') != -1:
        public_cnt += 1
      if public_cnt is 2 and line.find('}') != -1:
        other_cnt += 1
      if public_cnt is 2 and line.find('protected:') != -1:
        public_cnt = 0
      if public_cnt is 2 and other_cnt is 2 and line.find('}') == -1:
        src_code.append(line)
    if not line.find('};'):
      flag = False


def get_declarations_implementations(src_code, src_thrift):
  for src in src_code:
    if not (src.find('send_') != -1 or src.find('recv_') != -1):
      if src.find('  void ') != -1:
        src = src[len('  void '):]
        fun_name = src[:src.find('(')]
        str_args = src[src.find('('):]
        str_args_splited = str_args.split(' ')
        arg_list = '('
        for arg in str_args_splited:
          if arg.find(',') != -1 and arg.find('map') == -1:
            arg_list += arg + ' '
          elif arg.find(';') != -1:
            arg_list += arg[:arg.find(';')]
        declarations.append('int tcmcp_%s' % src)
        implementations.append('int %s::tcmcp_%s' % (class_name, src[0:src.find(';')]))
        implementations.append('{')
        implementations.append('    USE_tcmcp_NOT_POD(%sClient, %s, %s);' % (src_thrift, fun_name, arg_list))
        implementations.append('}')
      else:
        pass
  return declarations, implementations


if len(sys.argv) != 2:
  print 'len(sys.argv) != 2...'
  exit()

file_path = sys.argv[1]
file_name = file_path.split('/')[file_path.count('/')]
src_thrift = file_name[0:file_name.find('.h')]
class_name = 'tcmcp_%sClient' % src_thrift

src_code = []
get_src_code(src_code, file_path, src_thrift)

declarations = []
implementations = []
declarations, implementations = get_declarations_implementations(src_code, src_thrift)

print '#ifndef _TCMCP_%s_H_' % src_thrift
print '#define _TCMCP_%s_H_' % src_thrift
print ''
print '#include "ThriftClientMultiConnectPlug.h"'
print '#include "%s.h"' % src_thrift
print '// diy include <other.h> if you need.'
print ''
print ''
print 'class %s:public CThriftClinetMultiConnectPlug<%sClient>' % (class_name, src_thrift)
print '{'
print ''
print 'public:'
print '    /*'
print '    * constructor'
print '    */'
print '    %s(const string zkHost, const string zkPath, const int connectNumber, const int timeout=1000*10, const double checkTimes=1.0):' % class_name
print '                    CThriftClinetMultiConnectPlug<%sClient>(zkHost, zkPath, connectNumber, timeout, checkTimes){}' % src_thrift
print ''
print 'private:'
print '    /*'
print '    * virtual function.'
print '    * create your thrift and insert into pool.'
print '    */'
print '    void createConnect(map<STR_ip_port_suffix, connectNode<%sClient>>& pool, const string& ip, const int port);' % src_thrift
print ''
print 'public:'
print '    /*'
print '    * tcmcp function list.'
print '    */'
for declaration in declarations:
  print '    ' + declaration
print ''
print '};'
print '#endif //_TCMCP_%s_H_' % src_thrift
print ''
print ''
print '------------------------------------------------------------------------------------------------------------------------------'
print '               tcmcp_%s.h           ' % src_thrift
print '               tcmcp_%s.cpp         ' % src_thrift
print '------------------------------------------------------------------------------------------------------------------------------'
print ''
print ''
print ''
print '#include "tcmcp_%s.h"' % src_thrift
print ''
print ''
print 'void %s::createConnect(map<STR_ip_port_suffix, connectNode<%sClient>>& pool, const string& ip, const int port)' % (
    class_name, src_thrift)
print '{'
print '    CREATE_CONNECT_TFramedTransport_TBinaryProtocol(%sClient);' % src_thrift
print '}'
print '/*'
print '****************************************************'
print '*****---tcmcp function list implementations.---*****'
print '****************************************************'
print '*/'
for implementation in implementations:
  print implementation
print ''
