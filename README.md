# PHP扩展 f_redis_get

redis: get test 

## 依赖
[hiredis](https://github.com/redis/hiredis)

## 初始化

下载PHP7源码ext
```shell
cd ext
```

编辑文件 f_redis_get.def 内容如src/f_redis_get.def
```shell
vim f_redis_get.def
./ext_skel --extname=f_redis_get --proto=f_redis_get.def
```

## 编译配置
```shell
cd f_redis_get  
vim config.m4
```
去掉 PHP_ARG_WITH 和 [  --with-f_redis_get 前面的dnl 在文件底部添加下面两行，内容如src/config.m4
```m4
PHP_ADD_LIBRARY_WITH_PATH(hiredis, /usr/local/lib/, F_REDIS_GET_SHARED_LIBADD)  
PHP_SUBST(F_REDIS_GET_SHARED_LIBADD)  
```

## 功能实现  
实现函数 PHP_FUNCTION(f_redis_get) 代码如 src/f_redis_get.c  
```
vim f_redis_get.c
```

## 编译、安装

```shell
PHP7/bin/phpize  
./configure --with-php-config=PHP7/bin/php-config  
./make && make install  
```
## 配置文件 
php.ini 添加 extension=f_redis_get.so
```php
print_r(f_redis_get('127.0.0.1', 6379, '0', 'test'));
```

