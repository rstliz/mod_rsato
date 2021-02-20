# Apache Handler Json Api

## 概要

Apache Handler を C++で実装している例が世の中に少ないので実装しました。
実装のサンプルとして参考程度にお役立てください。

## Install

```
$ cd src
$ sudo gmake install
```

### Set Configuration

```
vi /etc/httpd/conf.d/api.conf

<Location "/api">
    SetHandler rsato
</Location>

vi /etc/httpd/conf.modules.d/99-api.conf

Include conf.modules.d/apreq.conf
LoadModule rsato_module modules/mod_rsato.so
```

## Development

```
cat yum-devel.txt|xargs -I@ sh -c "sudo yum install -y @"
```

## Test

```
$ cd test
$ gmake test
```

## Copyright

Ryo Sato all rights reserved.
