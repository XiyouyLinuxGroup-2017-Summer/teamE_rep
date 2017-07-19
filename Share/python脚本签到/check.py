#!/usr/bin/env python
# coding=utf-8
import urllib2
import urllib
import re


num=raw_input("请输入学号：")
url='http://118.89.234.46:8080/check/signin.do'
head={'Accept' :'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8',
      'Accept-Encoding' : 'gzip, deflate',
      'Accept-Language' : 'zh-CN,zh;q=0.8',
      'Cache-Control' : 'max-age=0',
      'Connection' : 'keep-alive',
      'Cookie' :'JSESSIONID=0FBB71ED41805E2F641D941708C02DBC',
      'Host' :'118.89.234.46:8080',
      'Upgrade-Insecure-Requests' : '1',
      'User-Agent' : 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/59.0.3071.115 Safari/537.36'}
data={ 'studentid' : num }
data=urllib.urlencode(data)
request=urllib2.Request(url,data,head);
try:
    req=urllib2.urlopen(request,timeout=5)
except :
    print "打开网页失败"
html=req.read()
pattern1=re.compile(r"你今天已经签到了哦，记得每天7点之后再来签到!")
match1=re.search(pattern1,html)
pattern2=re.compile(num)
match2=re.search(pattern2,html)
if (match1 or match2):
    if match1:
        print match1.group()
    if match2:
        print "签到成功！"
else:
    print "登陆失败"
#print html

