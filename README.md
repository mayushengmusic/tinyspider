
# tinyspder

the fastest static web spider, using mordern C++,multithread and boost lib.

this tool is very fast. if you donnot believe, just try it.

hopefully,welcome some peole develop with me.

thanks for [Simple-Web-Server](https://github.com/eidheim/Simple-Web-Server/blob/master/http_examples.cpp)

complie:

```
you must complie it with boost lib.

cd project

mkdir build

cd build

cmake ..

make -j 4
```

usage:

```
./spider startpage file_store_path type threadnum
```

example:

```
./tinyspider www.meitulu.com/item/4446.html ./image/ jpg 4
```

