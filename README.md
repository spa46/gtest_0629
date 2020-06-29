```
$ wget https://github.com/google/googletest/archive/release-1.10.0.tar.gz
$ tar xvf release-1.10.0.tar.gz
$ rm release-1.10.0.tar.gz
$ mv googletest-release-1.10.0/ googletest
```
```
$ cd ./googletest/googletest/scripts
$ ./fuse_gtest_files.py ~/chansik.yun
$ cd ~/chansik.yun
$ g++ ./gtest/gtest-all.cc -c -I.
$ ar rcv libgtest.a gtest-all.o

```

## 라이브러리
1. 동적
2. 정적: gtest는 정적 라이브러리를 권장합니다.
