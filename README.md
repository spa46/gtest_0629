## 설치 방법
```
$ wget https://github.com/google/googletest/archive/release-1.10.0.tar.gz
$ tar xvf release-1.10.0.tar.gz
$ rm release-1.10.0.tar.gz
$ mv googletest-release-1.10.0/ googletest
```
### Google Test
```
$ cd ./googletest/googletest/scripts
$ ./fuse_gtest_files.py ~/chansik.yun
$ cd ~/chansik.yun
$ g++ ./gtest/gtest-all.cc -c -I.
$ g++ ./googletest/googletest/src/gtest_main.cc -c -I.
$ ar rcv libgtest.a gtest-all.o gtest_main.o

$ g++ 1_시작.cpp -I. -lgtest -L. -pthread
```
### Google Mock
 Google Test가 포함되어 있기 때문에, Google Mock을 설치하시면, 같이 사용 가능합니다.
```
$ cd ./googletest/googlemock/scripts
$ ./fuse_gmock_files.py ~/chansik.yun
$ cd ~/chansik.yun
$ g++ gmock-gtest-all.cc -c -I.
$ g++ ./googletest/googlemock/src/gmock_main.cc -c -I.
$ ar rcv libgtest.a gmock-gtest-all.o gmock_main.o
```




## 라이브러리
1. 동적
2. 정적: gtest는 정적 라이브러리를 권장합니다.
